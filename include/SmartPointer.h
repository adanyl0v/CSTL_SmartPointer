#pragma once
#ifndef CSTL_SMART_POINTER
#define CSTL_SMART_POINTER

#include "BeginCode.h"

typedef struct CSTL_SmartPtr CSTL_SmartPtr;

#ifdef __cplusplus
extern "C" {
#endif

#pragma region CSTL_SmartPointer
    DECLSPEC CSTL_SmartPtr * CSTLCALL CSTL_AllocateSmartPtr(void *d);
    DECLSPEC void * CSTLCALL _CSTL_SmartPtrMalloc(size_t size);

#ifndef CSTL_CreateSmartPtr
    #define CSTL_CreateSmartPtr(T, N, V)                                \
        CSTL_SmartPtr *N = NULL;                                        \
        do {                                                            \
            T *__cstl_ad_data = (T *)_CSTL_SmartPtrMalloc(sizeof(T));   \
            *__cstl_ad_data = (T)V;                                     \
            N = CSTL_AllocateSmartPtr(__cstl_ad_data);                  \
        } while (0)
#endif /* CSTL_CreateSmartPtr */

    DECLSPEC void CSTLCALL CSTL_DestroySmartPtr(CSTL_SmartPtr *sp);
    DECLSPEC void CSTLCALL CSTL_ForceDestroySmartPtr(CSTL_SmartPtr *sp);

    DECLSPEC void * CSTLCALL CSTL_GetSmartPtrData(const CSTL_SmartPtr *sp);
    DECLSPEC size_t CSTLCALL CSTL_GetSmartPtrRefCount(const CSTL_SmartPtr *sp);
    DECLSPEC void CSTLCALL CSTL_SetSmartPtrData(CSTL_SmartPtr *sp, void *d);

    DECLSPEC void CSTLCALL CSTL_AddSmartPtrRef(CSTL_SmartPtr *sp);
#pragma endregion

#ifdef __cplusplus
}
#endif

#endif /* CSTL_SMART_POINTER */
