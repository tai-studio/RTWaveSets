cmake_minimum_required (VERSION 2.8)
project (sc3-plugins)

#if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/libs/nova-simd/simd_memory.hpp)
#        message(FATAL_ERROR "nova-simd submodule is missing: please run `git submodule init && #git submodule update' from the toplevel of your git working tree")
#endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules
                      ${CMAKE_MODULE_PATH})

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

add_custom_target(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")

find_package(SuperCollider3)
if (NOT SC_FOUND)
	message(SEND_ERROR "cannot find SuperCollider3 headers. Set the variable SC_PATH.")
else()
	message(STATUS "Using SC source located at ${SC_PATH}")
endif()

include("${SC_PATH}/SCVersion.txt")
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}${PROJECT_VERSION_PATCH}")
message(STATUS "Building plugins for SuperCollider version: ${PROJECT_VERSION}")

#option(SUPERNOVA "Build plugins for supernova")
option(AY "Build with AY ugens" ON)
option(QUARKS "Install plugins as quarks")
option(OSX_PACKAGE "Package dmg for Apple")
option(IN_PLACE_BUILD "Build and install in cmake build folder" ON)
option(NOVA_SIMD "Build VBAP with nova-simd support." ON)
option(CPP11 "Build with c++11." ON)
option(NATIVE "Optimize for this specific machine." OFF)

option(NOVA_DISK_IO "Build with Nova's DiskIO UGens. Requires boost source tree, break warranty & eats your children." OFF)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	set(CMAKE_COMPILER_IS_CLANG 1)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG)
    add_definitions(-fvisibility=hidden)

	if(NATIVE)
		add_definitions(-march=native)
	endif()

	if(CPP11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
		if(CMAKE_COMPILER_IS_CLANG)
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
		endif()
	endif()
endif()


if (NOVA_SIMD)
  add_definitions(-DNOVA_SIMD)
  include_directories(libs/nova-simd)
endif()

# osx `make install' defaults into cmake_build/SC3-plugins directory
if (APPLE AND IN_PLACE_BUILD)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}")
endif()

# when packaging OSX dmg, install in 'cmake_build/build_osx' so we can include
# directly the created SC3plugins subfolder in the root of the dmg (instead of
# all plugins directories in the dmg root)
if (APPLE AND OSX_PACKAGE)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/build_osx")
endif()

#add_subdirectory(RTWaveSetsUGens)

if (QUARKS OR OSX_PACKAGE) # add quarks DIRECTORY in osx dmg
  add_subdirectory(quarks)
endif()

if (OSX_PACKAGE)
  add_subdirectory(osx_package)
endif()

if(WIN32)
    configure_file( README_WINDOWS.txt.in README_WINDOWS.txt)
    install( FILES "${CMAKE_CURRENT_BINARY_DIR}/README_WINDOWS.txt" DESTINATION . RENAME README.txt )
endif()

#############################################
# CPack support

set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})

if(WIN32)
    set(CPACK_GENERATOR ZIP)
    set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY 0)
    set(CPACK_MONOLITHIC_INSTALL 1)
endif()

include(CPack)


#---------
# includes
#---------

if (SUPERNOVA)
    include_directories(${SC_PATH}/external_libraries/nova-tt)
    # actually just boost.atomic
    include_directories(${SC_PATH}/external_libraries/boost)
    include_directories(${SC_PATH}/external_libraries/boost_lockfree)
    include_directories(${SC_PATH}/external_libraries/boost-lockfree)
endif()

include_directories(${CMAKE_SOURCE_DIR}/include/)
include_directories(scfft_old/)

include_directories(${SC_PATH}/common)
include_directories(${SC_PATH}/plugin_interface)

include_directories(${SC_PATH}/include/plugin_interface)
include_directories(${SC_PATH}/include/common)
include_directories(${SC_PATH}/server/plugins) # for FFT_UGens.h

# old-style directory layout
include_directories(${SC_PATH}/common/Headers/plugin_interface)
include_directories(${SC_PATH}/common/Headers/common)
include_directories(${SC_PATH}/common/Source/plugins) # for FFT_UGens.h

include_directories(${SC_PATH}/external_libraries/libsndfile/)


#-------
# macros
#-------

macro(GET_GCC_VERSION VAR)
    if (CMAKE_COMPILER_IS_GNUCC)
        execute_process(
            COMMAND ${CMAKE_CXX_COMPILER} --version OUTPUT_VARIABLE OUTPUT)
        string(REGEX REPLACE
            ".* ([0-9]\\.[0-9]\\.[0-9]) .*" "\\1" ${VAR} ${OUTPUT})
    endif()
endmacro(GET_GCC_VERSION)


macro(FIND_AND_BUILD_PLUGINS DIR)
    file(GLOB PLUGIN_SRC RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${DIR}/*.cpp")
    foreach(plugin ${PLUGIN_SRC})
        get_filename_component(basename ${plugin} NAME_WE)
        BUILD_PLUGIN(${basename} ${plugin} "" "${DIR}")
    endforeach(plugin)
endmacro()


# Hacky: OSX plugins should install in PLUGIN_DIR
macro(BUILD_PLUGIN PLUGIN_NAME PLUGIN_SOURCES PLUGIN_LIBS PLUGIN_DIR)
    add_library(${PLUGIN_NAME} MODULE ${PLUGIN_SOURCES})
    list(APPEND plugins ${PLUGIN_NAME})
    target_link_libraries(${PLUGIN_NAME} ${PLUGIN_LIBS})

    if(APPLE)
        install(TARGETS ${PLUGIN_NAME}
                DESTINATION ${INSTALL_DESTINATION}/${PLUGIN_DIR})
    endif()

    if(SUPERNOVA)
        add_library(${PLUGIN_NAME}_supernova MODULE ${PLUGIN_SOURCES})
        target_link_libraries(${PLUGIN_NAME}_supernova ${PLUGIN_LIBS})

        list(APPEND supernova_plugins ${PLUGIN_NAME}_supernova)
        set_property(TARGET ${PLUGIN_NAME}_supernova
                     PROPERTY COMPILE_DEFINITIONS SUPERNOVA)
        if(APPLE)
            install(TARGETS ${PLUGIN_NAME}_supernova
                    DESTINATION ${INSTALL_DESTINATION}/${PLUGIN_DIR})
        endif()
    endif()

endmacro()


#-----------------------
# plugins without extras
#-----------------------

set(PLUGIN_DIRS

)

# plugins with extra lib
set(PLUGIN_DIRS_EXTRA
    RTWaveSetsUGens
)

#if (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang" AND ${CMAKE_CXX_COMPILER_VERSION} MATCHES "^6.0.")
#  set(BHOBFILT_CPP "${CMAKE_CURRENT_SOURCE_DIR}/BhobUGens/BhobFilt.cpp")
#  message(STATUS "Skipping vectorization on BhobFilt.cpp because of Clang bug. (${BHOBFILT_CPP})")
#  SET_SOURCE_FILES_PROPERTIES(${BHOBFILT_CPP} PROPERTIES COMPILE_FLAGS "-fno-slp-vectorize")
#endif()

set(plugins "")
set(supernova_plugins "")

set(CMAKE_SHARED_MODULE_PREFIX "")
set(PLUGIN_EXTENSION ".so")

if (APPLE OR WIN32)
    set(CMAKE_SHARED_MODULE_SUFFIX ".scx")
    set(PLUGIN_EXTENSION ".scx")
endif()


GET_GCC_VERSION(gcc_version)


if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(INSTALL_DESTINATION "lib/SuperCollider/plugins")
    if (QUARKS)
        set(INSTALL_DESTINATION_LADSPALIST
                "share/SuperCollider/SC3plugins/LadspaUGen")
        set(INSTALL_DESTINATION_DISTRO
                "share/SuperCollider/SC3plugins")
    else()
        set(INSTALL_DESTINATION_LADSPALIST
                "share/SuperCollider/Extensions/SC3plugins/LadspaUGen")
        set(INSTALL_DESTINATION_DISTRO
                "share/SuperCollider/Extensions/SC3plugins")
    endif(QUARKS)
else()
    set(INSTALL_DESTINATION "SC3plugins")
    set(INSTALL_DESTINATION_LADSPALIST "SC3plugins/LadspaUGen")
    set(INSTALL_DESTINATION_DISTRO "SC3plugins")
endif()


foreach(DIR ${PLUGIN_DIRS})
    FIND_AND_BUILD_PLUGINS(${DIR})
endforeach(DIR)

# build source files placed in 'local' by the user (i.e. by default this does nothing)
file(GLOB local_sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "local/*.cpp")
message(STATUS "local_sources: ${local_sources}")
foreach(plugin ${local_sources})
    string(REPLACE .cpp "" plugin_name ${plugin} )
    string(REPLACE "local/" "" plugin_name ${plugin_name} )
    BUILD_PLUGIN(${plugin_name} ${plugin} "" "local")
endforeach(plugin)
# local can have help files and classes too
install(DIRECTORY local DESTINATION "${INSTALL_DESTINATION_DISTRO}"
    FILES_MATCHING PATTERN "*.sc" PATTERN "*.scd" PATTERN "*.html" PATTERN "*.schelp" PATTERN "*.rtf")

#---------------------
# plugins with extras:
#---------------------
## RTWaveSetsUGens
file(GLOB RTWaveSetSources RTWaveSetsUGens/*cpp)
BUILD_PLUGIN(RTWaveSetsUGens "${RTWaveSetSources}" "" "RTWaveSetsUGens")

## AuditoryModeling
#file(GLOB AuditoryModelingSources AuditoryModeling/*cpp)

#BUILD_PLUGIN(AuditoryModeling "${AuditoryModelingSources}" "" "AuditoryModeling")


##BetablockerUGens
#BUILD_PLUGIN(BetablockerUGens "BetablockerUGens/BetablockerUGens.cpp;BetablockerUGens/betablocker/machine.cpp;BetablockerUGens/betablocker/thread.cpp"
#             "" "BetablockerUGens")

## DEINDUGens
#BUILD_PLUGIN(DiodeRingMod
#"DEINDUGens/DiodeRingMod.cpp"
#             "" "DiodeRingMod")
#BUILD_PLUGIN(NoiseRing
#"DEINDUGens/NoiseRing.cpp"
#             "" "NoiseRing")
#BUILD_PLUGIN(complexRes
#"DEINDUGens/complexRes.cpp"
#             "" "complexRes")
#include_directories(DEINDUGens/include)
#BUILD_PLUGIN(JPverb
#"DEINDUGens/JPverbRaw.cpp"
#             "" "JPverb")
#      set_property(TARGET JPverb APPEND PROPERTY COMPILE_DEFINITIONS SC_FAUST_PREFIX="\"\"")
#      set_property(TARGET JPverb APPEND PROPERTY COMPILE_DEFINITIONS mydsp=JPVERB)
#      set_property(TARGET JPverb APPEND PROPERTY COMPILE_DEFINITIONS NDEBUG)
#BUILD_PLUGIN(Greyhole
#"DEINDUGens/GreyholeRaw.cpp"
#             "" "Greyhole")
#      set_property(TARGET Greyhole APPEND PROPERTY COMPILE_DEFINITIONS SC_FAUST_PREFIX="\"\"")
#      set_property(TARGET Greyhole APPEND PROPERTY COMPILE_DEFINITIONS mydsp=GREYHOLE)
#      set_property(TARGET Greyhole APPEND PROPERTY COMPILE_DEFINITIONS NDEBUG)

## MembraneUGens
#BUILD_PLUGIN(MembraneUGens "MembraneUGens/Membrane_shape.c;MembraneUGens/Membrane.cpp"
#             "" "MembraneUGens")

## LadspaUGen
#if(NOT WIN32)
#    BUILD_PLUGIN(LadspaUGen "LadspaUGen/LadspaUGen.cpp;LadspaUGen/search.c" "" "LadspaUGen")
#    add_executable(ladspalist LadspaUGen/ladspalist.c LadspaUGen/search.c)
#    target_link_libraries(ladspalist dl)
#endif()

## OteyPianoUGens
#BUILD_PLUGIN(OteyPianoUGens "OteyPianoUGens/OteyPiano.cpp;OteyPianoUGens/dwgs.cpp;OteyPianoUGens/filter.cpp;OteyPianoUGens/hammer.cpp;OteyPianoUGens/DWG.cpp;OteyPianoUGens/reverb.cpp"
#             "" "OteyPianoUGens")
             
## PitchDetectionUGens
#file(GLOB PitchDetectionSources PitchDetection/*cpp)
#if(APPLE)
#    set (PitchDetectionLibs "-framework Accelerate")
#else()
#    set (PitchDetectionLibs ${FFTW3F_LIBRARY})
#endif()

#BUILD_PLUGIN(PitchDetection "${PitchDetectionSources}"
#             "${PitchDetectionLibs}" "PitchDetection")



#if (NOT APPLE)
#    find_package(FFTW3f)

#    if (!FFTW3F_FOUND)
#        message(SEND_ERROR "Cannot find libfftw3f")
#    endif()

#    include_directories(${FFTW3F_INCLUDE_DIR})

#    set_property(TARGET PitchDetection
#        APPEND PROPERTY COMPILE_DEFINITIONS SC_FFT_FFTW)
#    if (SUPERNOVA)
#        set_property(TARGET PitchDetection_supernova
#            APPEND PROPERTY COMPILE_DEFINITIONS SC_FFT_FFTW)
#    endif()
#else()
#    set_property(TARGET PitchDetection
#    APPEND PROPERTY COMPILE_DEFINITIONS SC_FFT_VDSP)
#    if (SUPERNOVA)
#        set_property(TARGET PitchDetection_supernova
#        APPEND PROPERTY COMPILE_DEFINITIONS SC_FFT_VDSP)
#    endif()
#endif()

## StkUGens
#file(GLOB STKSources "StkUGens/stk-4.4.2/src/*.cpp")
#file(GLOB UnneededSTKSources "StkUGens/stk-4.4.2/src/Rt*.cpp"
#                             "StkUGens/stk-4.4.2/src/Inet*.cpp"
#                             "StkUGens/stk-4.4.2/src/Socket.cpp"
#                             "StkUGens/stk-4.4.2/src/Tcp*.cpp"
#                             "StkUGens/stk-4.4.2/src/UdpSocket.cpp"
#                             "StkUGens/stk-4.4.2/src/Thread.cpp"
#                             "StkUGens/stk-4.4.2/src/Mutex.cpp"
#)
#list(REMOVE_ITEM STKSources ${UnneededSTKSources})
#include_directories(StkUGens/stk-4.4.2)
#include_directories(StkUGens/stk-4.4.2/include)
#include_directories(StkUGens/stk-4.4.2/src/include)
#BUILD_PLUGIN(StkUGens "StkUGens/StkAll.cpp;${STKSources}" "" "StkUGens")

## NCAnalysisUGens
#file(GLOB NCAnalysisSources NCAnalysisUGens/*cpp)
#if(APPLE)
#    set (NCAnalysisLibs "-framework Accelerate")
#else()
#    set (NCAnalysisLibs ${FFTW3F_LIBRARY})
#endif()

#BUILD_PLUGIN(NCAnalysisUGens "${NCAnalysisSources}"
#             ${NCAnalysisLibs} "NCAnalysisUGens")

## AYUGens
#if (AY)
#    list(APPEND PLUGIN_DIRS_EXTRA AYUGens)
#    include_directories(AYUGens/AY_libayemu/include)
#    BUILD_PLUGIN(AY_UGen "AYUGens/AY_UGen.cpp;AYUGens/AY_libayemu/src/ay8912.c"
#                 "" "AYUGens")
#endif()

## TJUGens
#if (APPLE AND gcc_version MATCHES "4\\.0.*")
#    list(REMOVE_ITEM PLUGIN_DIRS_EXTRA TJUGens)
#    message(WARNING "TJUGens won't be built with gcc-4.0 on Apple")
#else()
#    file(GLOB TJUGensSources TJUGens/*.cpp)
#    BUILD_PLUGIN(TJUGens "${TJUGensSources}" "" "TJUGens")
#endif()

#if (NOVA_DISK_IO)
#  add_subdirectory(NovaDiskIO)
#endif()


#--------
# INSTALL
#--------

# OSX plugins install is done in BUILD_PLUGIN macro
if (NOT APPLE)
    install(TARGETS ${plugins} ${supernova_plugins}
            DESTINATION ${INSTALL_DESTINATION})
endif()

#if(NOT WIN32)
#  install(TARGETS ladspalist
#    DESTINATION ${INSTALL_DESTINATION_LADSPALIST})
#endif()

# install help and sc specific files that are found in 'PLUGIN_NAME/sc' folder
foreach (DIR ${PLUGIN_DIRS};${PLUGIN_DIRS_EXTRA})
    install(DIRECTORY "${DIR}/sc/" DESTINATION "${INSTALL_DESTINATION_DISTRO}/${DIR}"
            PATTERN "*")
endforeach(DIR)

