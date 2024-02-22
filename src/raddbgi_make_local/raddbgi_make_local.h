// Copyright (c) 2024 Epic Games Tools
// Licensed under the MIT license (https://opensource.org/license/mit/)

#ifndef RADDBGI_MAKE_LOCAL_H
#define RADDBGI_MAKE_LOCAL_H

////////////////////////////////
//~ rjf: Overrides

// rjf: memory ops
#define RDIM_MEMSET_OVERRIDE
#define RDIM_MEMCPY_OVERRIDE
#define rdim_memset MemorySet
#define rdim_memcpy MemoryCopy

// rjf: string overrides
#define RDI_STRING8_OVERRIDE
#define RDIM_String8 String8
#define RDIM_String8_BaseMember str
#define RDIM_String8_SizeMember size
#define RDI_STRING8LIST_OVERRIDE
#define RDIM_String8Node String8Node
#define RDIM_String8Node_NextPtrMember next
#define RDIM_String8Node_StringMember string
#define RDIM_String8List String8List
#define RDIM_String8List_FirstMember first
#define RDIM_String8List_LastMember last
#define RDIM_String8List_NodeCountMember node_count
#define RDIM_String8List_TotalSizeMember total_size

// rjf: arena overrides
#define RDIM_ARENA_OVERRIDE
#define RDIM_Arena Arena
#define rdim_arena_alloc     arena_alloc
#define rdim_arena_release   arena_release
#define rdim_arena_pos       arena_pos
#define rdim_arena_push      arena_push
#define rdim_arena_pop_to    arena_pop_to

// rjf: scratch arena overrides
#define RDIM_SCRATCH_OVERRIDE
#define RDIM_Temp Temp
#define rdim_temp_arena(t)   ((t).arena)
#define rdim_scratch_begin   scratch_begin
#define rdim_scratch_end     scratch_end

// rjf: guarded hash access overrides
#define RDIM_GUARD_OVERRIDE
#define RDIM_Guard RDIML_StripeTable
#define rdim_guard_scope_begin_r rdiml_stripe_table_scope_begin_r
#define rdim_guard_scope_end_r rdiml_stripe_table_scope_end_r
#define rdim_guard_scope_begin_w rdiml_stripe_table_scope_begin_w
#define rdim_guard_scope_end_w rdiml_stripe_table_scope_end_w
#define rdim_arena_from_guard_hash rdiml_stripe_table_arena

// rjf: profiling markup overrides
#define RDIM_ProfBegin(...) ProfBeginDynamic(__VA_ARGS__)
#define RDIM_ProfEnd(...) ProfEnd()

////////////////////////////////
//~ rjf: Wrapped Data Structures, for Asynchronous Access

//- rjf: stripe table, for striping hash tables with synchronization

typedef struct RDIML_Stripe RDIML_Stripe;
struct RDIML_Stripe
{
  Arena *arena;
  OS_Handle rw_mutex;
};

typedef struct RDIML_StripeTable RDIML_StripeTable;
struct RDIML_StripeTable
{
  U64 count;
  RDIML_Stripe *v;
};

////////////////////////////////
//~ rjf: Library Include

#include "lib_raddbgi_make/raddbgi_make.h"

////////////////////////////////
//~ rjf: Wrapped Data Structure Functions

//- rjf: stripe table creation/destruction

internal RDIML_StripeTable *rdiml_stripe_table_alloc(Arena *arena, U64 stripe_count);
internal void rdiml_stripe_table_release(RDIML_StripeTable *stripes);

//- rjf: stripe table access

internal void rdiml_stripe_table_scope_begin_r(RDIML_StripeTable *stripes, U64 hash);
internal void rdiml_stripe_table_scope_end_r(RDIML_StripeTable *stripes, U64 hash);
internal void rdiml_stripe_table_scope_begin_w(RDIML_StripeTable *stripes, U64 hash);
internal void rdiml_stripe_table_scope_end_w(RDIML_StripeTable *stripes, U64 hash);
internal Arena *rdiml_stripe_table_arena(RDIML_StripeTable *stripes, U64 hash);

#endif // RADDBGI_MAKE_LOCAL_H
