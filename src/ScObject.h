#ifndef ScObject_H
#define ScObject_H

#include "SC_PlugIn.h"

/**
 * @brief Abstract base class that overwrites the new and delete operators to use the realtime memory of SuperCollider.
 * To use the SC memory allocation the SC interface table and world have to be set.
 */

class ScObject
{
protected:
    static World *scWorld;
    static InterfaceTable *scInterface;
    static bool debug;
    ScObject(){}

public:
    void* operator new(size_t size);
    void* operator new(std::size_t size, void* ptr);
    void operator delete(void*);

    static void setScInterface(InterfaceTable *ft){ scInterface = ft; }
    static void setScWorld(World *world){ scWorld = world; }
};

#endif // WSOBJECT_H
