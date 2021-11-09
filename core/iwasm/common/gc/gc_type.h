/*
 * Copyright (C) 2019 Intel Corporation. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 */

#ifndef _GC_TYPE_H_
#define _GC_TYPE_H_

#include "../interpreter/wasm.h"

#ifdef __cplusplus
extern "C" {
#endif

void
wasm_dump_value_type(uint8 type, const WASMRefType *ref_type);

void
wasm_dump_func_type(const WASMFuncType *type);

void
wasm_dump_struct_type(const WASMStructType *type);

void
wasm_dump_array_type(const WASMArrayType *type);

/* Operations of function type */

/* Whether two function types are equal */
bool
wasm_func_type_equal(const WASMFuncType *type1, const WASMFuncType *type2);

/* Whether func type1 is subtype of func type2 */
bool
wasm_func_type_is_subtype_of(const WASMFuncType *type1,
                             const WASMFuncType *type2, const WASMType **types,
                             uint32 type_count);

/* Operations of struct type */

/* Whether two struct types are equal */
bool
wasm_struct_type_equal(const WASMStructType *type1,
                       const WASMStructType *type2);

/* Whether struct type1 is subtype of struct type2 */
bool
wasm_struct_type_is_subtype_of(const WASMStructType *type1,
                               const WASMStructType *type2,
                               const WASMType **types, uint32 type_count);

/* Operations of array type */

/* Whether two array types are equal */
bool
wasm_array_type_equal(const WASMArrayType *type1, const WASMArrayType *type2);

/* Whether array type1 is subtype of array type2 */
bool
wasm_array_type_is_subtype_of(const WASMArrayType *type1,
                              const WASMArrayType *type2,
                              const WASMType **types, uint32 type_count);

/* Operations of wasm type */

/* Whether a wasm type is a function type */
inline static bool
wasm_type_is_func_type(const WASMType *type)
{
    return type->type_flag == WASM_TYPE_FUNC ? true : false;
}

/* Whether a wasm type is a struct type */
inline static bool
wasm_type_is_struct_type(const WASMType *type)
{
    return type->type_flag == WASM_TYPE_STRUCT ? true : false;
}

/* Whether a wasm type is an array type */
inline static bool
wasm_type_is_array_type(const WASMType *type)
{
    return type->type_flag == WASM_TYPE_ARRAY ? true : false;
}

/* Whether two wasm types are equal */
bool
wasm_type_equal(const WASMType *type1, const WASMType *type2);

/* Whether wasm type1 is subtype of wasm type2 */
bool
wasm_type_is_subtype_of(const WASMType *type1, const WASMType *type2,
                        const WASMType **types, uint32 type_count);

/* Operations of reference type */

/* Whether a value type is a reference type */
inline static bool
wasm_is_type_reftype(uint8 type)
{
    return (type >= (uint8)REF_TYPE_DATAREF && type <= (uint8)REF_TYPE_FUNCREF)
               ? true
               : false;
}

/* Whether a value type is multi-byte type, or, requires ref type map
   to retrieve extra info */
inline static bool
wasm_is_type_multi_byte_type(uint8 type)
{
    return (type == (uint8)REF_TYPE_HT_NULLABLE
            || type == (uint8)REF_TYPE_HT_NON_NULLABLE
            || type == (uint8)REF_TYPE_RTTN || type == (uint8)REF_TYPE_RTT)
               ? true
               : false;
}

/* Whether a reference type is a funcref type */
inline static bool
wasm_is_reftype_funcref(uint8 type)
{
    return type == (uint8)REF_TYPE_FUNCREF ? true : false;
}

/* Whether a reference type is an externref type */
inline static bool
wasm_is_reftype_externref(uint8 type)
{
    return type == (uint8)REF_TYPE_EXTERNREF ? true : false;
}

/* Whether a reference type is an anyref type */
inline static bool
wasm_is_reftype_anyref(uint8 type)
{
    return type == (uint8)REF_TYPE_ANYREF ? true : false;
}

/* Whether a reference type is an eqref type */
inline static bool
wasm_is_reftype_eqref(uint8 type)
{
    return type == (uint8)REF_TYPE_EQREF ? true : false;
}

/* Whether a reference type is a (ref null ht) type */
inline static bool
wasm_is_reftype_htref_nullable(uint8 type)
{
    return type == (uint8)REF_TYPE_HT_NULLABLE ? true : false;
}

/* Whether a reference type is a (ref ht) type */
inline static bool
wasm_is_reftype_htref_non_nullable(uint8 type)
{
    return type == (uint8)REF_TYPE_HT_NON_NULLABLE ? true : false;
}

/* Whether a reference type is an i31ref type */
inline static bool
wasm_is_reftype_i31ref(uint8 type)
{
    return type == (uint8)REF_TYPE_I31REF ? true : false;
}

/* Whether a reference type is an (rtt n $t) type */
inline static bool
wasm_is_reftype_rttnref(uint8 type)
{
    return type == (uint8)REF_TYPE_RTTN ? true : false;
}

/* Whether a reference type is an (rtt $t) type */
inline static bool
wasm_is_reftype_rttref(uint8 type)
{
    return type == (uint8)REF_TYPE_RTT ? true : false;
}

/* Whether a reference type is a dataref type */
inline static bool
wasm_is_reftype_dataref(uint8 type)
{
    return type == (uint8)REF_TYPE_DATAREF ? true : false;
}

/* Return the size of a reference type */
uint32
wasm_reftype_size(uint8 type);

/* Operations of ref heap type */

/* Whether a ref heap type is (type i), i : typeidx, >= 0 */
inline static bool
wasm_is_refheaptype_typeidx(const RefHeapType_Common *ref_heap_type)
{
    return ref_heap_type->heap_type >= 0 ? true : false;
}

/* Whether a ref heap type is (rtt n i), n: u32, i: typeidx, >= 0 */
inline static bool
wasm_is_refheaptype_rttn(const RefHeapType_Common *ref_heap_type)
{
    return ref_heap_type->heap_type == HEAP_TYPE_RTTN ? true : false;
}

/* Whether a ref heap type is (rtt i), i: typeidx, >= 0 */
inline static bool
wasm_is_refheaptype_rtt(const RefHeapType_Common *ref_heap_type)
{
    return ref_heap_type->heap_type == (int32)HEAP_TYPE_RTT ? true : false;
}

/* Whether a ref heap type is a common type: func/extern/any/eq/i31/data,
   not (type i) or (rtt n i) or (rtt i) */
inline static bool
wasm_is_refheaptype_common(const RefHeapType_Common *ref_heap_type)
{
    return ((ref_heap_type->heap_type >= (int32)HEAP_TYPE_EQ
             && ref_heap_type->heap_type <= (int32)HEAP_TYPE_FUNC)
            || ref_heap_type->heap_type == (int32)HEAP_TYPE_I31
            || ref_heap_type->heap_type == (int32)HEAP_TYPE_DATA)
               ? true
               : false;
}

/* Whether a ref heap type is a func type */
inline static bool
wasm_is_refheaptype_func(const RefHeapType_Common *ref_heap_type)
{
    return ref_heap_type->heap_type == (int32)HEAP_TYPE_FUNC ? true : false;
}

/* Whether a ref heap type is an extern type */
inline static bool
wasm_is_refheaptype_extern(const RefHeapType_Common *ref_heap_type)
{
    return ref_heap_type->heap_type == (int32)HEAP_TYPE_EXTERN ? true : false;
}

/* Whether a ref heap type is an any type */
inline static bool
wasm_is_refheaptype_any(const RefHeapType_Common *ref_heap_type)
{
    return ref_heap_type->heap_type == (int32)HEAP_TYPE_ANY ? true : false;
}

/* Whether a ref heap type is an eq type */
inline static bool
wasm_is_refheaptype_eq(const RefHeapType_Common *ref_heap_type)
{
    return ref_heap_type->heap_type == (int32)HEAP_TYPE_EQ ? true : false;
}

/* Whether a ref heap type is an i31 type */
inline static bool
wasm_is_refheaptype_i31(const RefHeapType_Common *ref_heap_type)
{
    return ref_heap_type->heap_type == (int32)HEAP_TYPE_I31 ? true : false;
}

/* Whether a ref heap type is a data type */
inline static bool
wasm_is_refheaptype_data(const RefHeapType_Common *ref_heap_type)
{
    return ref_heap_type->heap_type == (int32)HEAP_TYPE_DATA ? true : false;
}

/* Whether two ref heap types are equal */
bool
wasm_refheaptype_equal(const RefHeapType_Common *ref_heap_type1,
                       const RefHeapType_Common *ref_heap_type2);

/* Operations of ref rttn type */

/* Whether two ref rttn types are equal */
bool
wasm_refrttntype_equal(const RefRttNType *ref_rttn_type1,
                       const RefRttNType *ref_rttn_type2);

/* Operations of ref rtt type */

/* Whether two ref rtt types are equal */
bool
wasm_refrtttype_equal(const RefRttType *ref_rtt_type1,
                      const RefRttType *ref_rtt_type2);

/* Whether two ref types are equal */
bool
wasm_reftype_equal(uint8 type1, const WASMRefType *reftype1, uint8 type2,
                   const WASMRefType *reftype2);

/* Whether ref type1 is subtype of ref type2 */
bool
wasm_reftype_is_subtype_of(uint8 type1, const WASMRefType *reftype1,
                           uint8 type2, const WASMRefType *reftype2,
                           const WASMType **types, uint32 type_count);

/* Returns a new reference type which is a duplication of ref_type,
   the caller should use wasm_runtime_free() to free the new ref type */
WASMRefType *
wasm_reftype_dup(const WASMRefType *ref_type);

/* Create a new hash set of reference type */
HashMap *
wasm_reftype_set_create(uint32 size);

/* Insert a reference type into the hash set */
WASMRefType *
wasm_reftype_set_insert(HashMap *ref_type_set, const WASMRefType *ref_type);

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif /* end of _GC_TYPE_H_ */
