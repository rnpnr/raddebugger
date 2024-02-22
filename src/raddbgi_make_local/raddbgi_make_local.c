// Copyright (c) 2024 Epic Games Tools
// Licensed under the MIT license (https://opensource.org/license/mit/)

////////////////////////////////
//~ rjf: Library Include

#include "lib_raddbgi_make/raddbgi_make.c"

////////////////////////////////
//~ rjf: Wrapped Data Structure Functions

//- rjf: stripe table creation/destruction

internal RDIML_StripeTable *
rdiml_stripe_table_alloc(Arena *arena, U64 stripe_count)
{
  RDIML_StripeTable *stripes = push_array(arena, RDIML_StripeTable, 1);
  stripes->count = stripe_count;
  stripes->v = push_array(arena, RDIML_Stripe, stripes->count);
  for(U64 idx = 0; idx < stripe_count; idx += 1)
  {
    stripes->v[idx].arena = arena_alloc();
    stripes->v[idx].rw_mutex = os_rw_mutex_alloc();
  }
  return stripes;
}

internal void
rdiml_stripe_table_release(RDIML_StripeTable *stripes)
{
  for(U64 idx = 0; idx < stripes->count; idx += 1)
  {
    arena_release(stripes->v[idx].arena);
    os_rw_mutex_release(stripes->v[idx].rw_mutex);
  }
}

//- rjf: stripe table access

internal void
rdiml_stripe_table_scope_begin_r(RDIML_StripeTable *stripes, U64 hash)
{
  U64 stripe_idx = hash%stripes->count;
  RDIML_Stripe *stripe = &stripes->v[stripe_idx];
  os_rw_mutex_take_r(stripe->rw_mutex);
}

internal void
rdiml_stripe_table_scope_end_r(RDIML_StripeTable *stripes, U64 hash)
{
  U64 stripe_idx = hash%stripes->count;
  RDIML_Stripe *stripe = &stripes->v[stripe_idx];
  os_rw_mutex_drop_r(stripe->rw_mutex);
}

internal void
rdiml_stripe_table_scope_begin_w(RDIML_StripeTable *stripes, U64 hash)
{
  U64 stripe_idx = hash%stripes->count;
  RDIML_Stripe *stripe = &stripes->v[stripe_idx];
  os_rw_mutex_take_w(stripe->rw_mutex);
}

internal void
rdiml_stripe_table_scope_end_w(RDIML_StripeTable *stripes, U64 hash)
{
  U64 stripe_idx = hash%stripes->count;
  RDIML_Stripe *stripe = &stripes->v[stripe_idx];
  os_rw_mutex_drop_w(stripe->rw_mutex);
}

internal Arena *
rdiml_stripe_table_arena(RDIML_StripeTable *stripes, U64 hash)
{
  U64 stripe_idx = hash%stripes->count;
  RDIML_Stripe *stripe = &stripes->v[stripe_idx];
  return stripe->arena;
}
