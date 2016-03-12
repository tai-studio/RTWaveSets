#include "WsObject.h"

/** Pointer to the SC interface table*/
World *WsObject::scWorld=NULL;

/** Pointer to the SC world */
InterfaceTable *WsObject::scInterface=NULL;

/**
 * @brief Allocate memory for an object using SC RTalloc.
 * @param size size of requested memory in bytes
 * @return
 */

void *WsObject::operator new(size_t size)
{
    if(scInterface==NULL) throw "WsObject allocation error: interfacetable not set";
    if(scWorld==NULL) throw "WsObject allocation error: scWorld not set";

    void* space = scInterface->fRTAlloc(scWorld,size);

    if(space==NULL) throw "WsObject allocation error";

    return space;
}

/**
 * @brief Placement new operator, that uses existing memory.
 * @param size size of requested memory in bytes
 * @param ptr pointer to existing memory
 * @return
 */

void *WsObject::operator new(std::size_t size, void *ptr)
{
    return ptr;
}

/**
 * @brief WsObject::operator delete
 * @param ptr
 */

void WsObject::operator delete(void * ptr)
{
    scInterface->fRTFree(scWorld,ptr);
    //printf("successfull deleted WsObject\n");
}

/*void WsObject::debugPrint(const char *format, ...)
{
    va_list argptr;
    va_start(argptr, format);
    vfprintf(stderr, format, argptr);
    va_end(argptr);
}*/
