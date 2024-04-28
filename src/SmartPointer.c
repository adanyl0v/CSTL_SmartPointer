#include "../include/SmartPointer.h"

#include <stdlib.h>
#include <CSTL_Exception/Exception.h>

#ifndef CSTL_SmartPtrThrowExceptionIfNull
#define CSTL_SmartPtrThrowExceptionIfNull(RV, ARG, C)       \
    if (ARG == NULL) {                                      \
        CSTL_ThrowException(C, "arg. '%s' is null", #ARG); \
        return RV;                                          \
    }
#endif /* CSTL_SmartPtrThrowExceptionIfNull */

#ifndef CSTL_SmartPtrThrowExceptionIfNullNoReturn
#define CSTL_SmartPtrThrowExceptionIfNullNoReturn(ARG, C) \
    CSTL_SmartPtrThrowExceptionIfNull( , ARG, C)
#endif /* CSTL_SmartPtrThrowExceptionIfNullNoReturn */

#ifndef CSTL_SmartPtrThrowWarningIfNull
#define CSTL_SmartPtrThrowWarningIfNull(RV, ARG, C)         \
    if (ARG == NULL) {                                      \
        CSTL_ThrowWarning(C, "arg. '%s' is null", #ARG);   \
        return RV;                                          \
    }
#endif /* CSTL_SmartPtrThrowWarningIfNull */

#ifndef CSTL_SmartPtrThrowWarningIfNullNoReturn
#define CSTL_SmartPtrThrowWarningIfNullNoReturn(ARG, C) \
    CSTL_SmartPtrThrowExceptionIfNull( , ARG, C)
#endif /* CSTL_SmartPtrThrowWarningIfNullNoReturn */

struct CSTL_SmartPtr {
    size_t refCount;
    void *d; // Pointer to an actual data
};

CSTL_SmartPtr *CSTL_AllocateSmartPtr(void *d) {
    CSTL_SmartPtr *new_sp = (CSTL_SmartPtr *)malloc(sizeof(CSTL_SmartPtr));
    if (new_sp == NULL) {
        CSTL_ThrowException(CSTL_FAILED_ALLOC, "failed to allocate memory for a new smart pointer");
        return NULL;
    }

    new_sp->refCount = 1;
    new_sp->d = d;
    return new_sp;
}

void *_CSTL_SmartPtrMalloc(size_t size) {
    void *p = malloc(size);
    if (p == NULL) {
        CSTL_ThrowException(CSTL_FAILED_ALLOC, "failed to allocate memory");
        return NULL;
    }

    return p;
}

void CSTL_ForceDestroySmartPtr(CSTL_SmartPtr *sp) {
    CSTL_SmartPtrThrowWarningIfNullNoReturn(sp, CSTL_INVALID_ARGS);

    if (sp->d != NULL)
        free(sp->d);

    free(sp);
}

void *CSTL_GetSmartPtrData(const CSTL_SmartPtr *sp) {
    CSTL_SmartPtrThrowWarningIfNull(NULL, sp, CSTL_INVALID_ARGS);
    return sp->d;
}

size_t CSTL_GetSmartPtrRefCount(const CSTL_SmartPtr *sp) {
    CSTL_SmartPtrThrowWarningIfNull(0, sp, CSTL_INVALID_ARGS);
    return sp->refCount;
}

void CSTL_SetSmartPtrData(CSTL_SmartPtr *sp, void *d) {
    CSTL_SmartPtrThrowWarningIfNullNoReturn(sp, CSTL_INVALID_ARGS);
    sp->d = d;
}

void CSTL_AddSmartPtrRef(CSTL_SmartPtr *sp) {
    CSTL_SmartPtrThrowWarningIfNullNoReturn(sp, CSTL_INVALID_ARGS);
    sp->refCount++;
}

void CSTL_DestroySmartPtr(CSTL_SmartPtr *sp) {
    CSTL_SmartPtrThrowWarningIfNullNoReturn(sp, CSTL_INVALID_ARGS);
    sp->refCount--;
    if (sp->refCount <= 1) 
        CSTL_ForceDestroySmartPtr(sp);
}
