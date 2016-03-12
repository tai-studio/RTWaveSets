#include "ScObject.h"

/** Pointer to the SC interface table*/
World *ScObject::scWorld=NULL;

/** Pointer to the SC world */
InterfaceTable *ScObject::scInterface=NULL;

/**
 * @brief Allocate memory for an object using SC RTalloc.
 * @param size size of requested memory in bytes
 * @return
 */

void *ScObject::operator new(size_t size)
{
    if(scInterface==NULL) throw "ScObject allocation error: interfacetable not set";
    if(scWorld==NULL) throw "ScObject allocation error: scWorld not set";

    void* space = scInterface->fRTAlloc(scWorld,size);

    if(space==NULL) throw "ScObject allocation error";

    return space;
}

/**
 * @brief Placement new operator, that uses existing memory.
 * @param size size of requested memory in bytes
 * @param ptr pointer to existing memory
 * @return
 */

void *ScObject::operator new(std::size_t size, void *ptr)
{
    return ptr;
}

/**
 * @brief ScObject::operator delete
 * @param ptr
 */

void ScObject::operator delete(void * ptr)
{
    scInterface->fRTFree(scWorld,ptr);
    //printf("successfull deleted ScObject\n");
}

/*void ScObject::debugPrint(const char *format, ...)
{
    va_list argptr;
    va_start(argptr, format);
    vfprintf(stderr, format, argptr);
    va_end(argptr);
}*/
