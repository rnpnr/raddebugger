// Copyright (c) 2024 Epic Games Tools
// Licensed under the MIT license (https://opensource.org/license/mit/)

//- rjf: top-level layer initialization

r_hook void
r_init(CmdLine *cmdln)
{
}

//- rjf: window setup/teardown

r_hook R_Handle
r_window_equip(OS_Handle window)
{
  R_Handle handle = {0};
  handle.u64[0] = 1;
  return handle;
}

r_hook void
r_window_unequip(OS_Handle window, R_Handle window_equip)
{
}

//- rjf: textures

r_hook R_Handle
r_tex2d_alloc(R_ResourceKind kind, Vec2S32 size, R_Tex2DFormat format, void *data)
{
  R_Handle handle = {0};
  handle.u64[0] = 1;
  return handle;
}

r_hook void
r_tex2d_release(R_Handle texture)
{
}

r_hook R_ResourceKind
r_kind_from_tex2d(R_Handle texture)
{
  return R_ResourceKind_Static;
}

r_hook Vec2S32
r_size_from_tex2d(R_Handle texture)
{
  return v2s32(1, 1);
}

r_hook R_Tex2DFormat
r_format_from_tex2d(R_Handle texture)
{
  return R_Tex2DFormat_RGBA8;
}

r_hook void
r_fill_tex2d_region(R_Handle texture, Rng2S32 subrect, void *data)
{
}

//- rjf: buffers

r_hook R_Handle
r_buffer_alloc(R_ResourceKind kind, U64 size, void *data)
{
  R_Handle handle = {0};
  handle.u64[0] = 1;
  return handle;
}

r_hook void
r_buffer_release(R_Handle buffer)
{
}

//- rjf: frame markers

r_hook void
r_begin_frame(void)
{
}

r_hook void
r_end_frame(void)
{
}

r_hook void
r_window_begin_frame(OS_Handle window, R_Handle window_equip)
{
}

r_hook void
r_window_end_frame(OS_Handle window, R_Handle window_equip)
{
}

//- rjf: render pass submission

r_hook void
r_window_submit(OS_Handle window, R_Handle window_equip, R_PassList *passes)
{
}
