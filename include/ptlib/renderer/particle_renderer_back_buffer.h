#pragma once
#include <stddef.h>

#include "grlib/cglib_render_target.h"
#include "grlib/cglib_texture_buffer.h"
#include "types.h"

namespace ptlib {

class StaticAllocObj;

namespace renderer {

// Layout evidence: createAll 0x7100939b30, bufferClear 0x7100939e6c.
class BackBuffer {
public:
  ~BackBuffer() { unknown001(); }

  // Inferred role: destroys the render targets; original name unknown.
  void unknown001() {
    if (unknown00 != nullptr) {
      if (unknown18 != nullptr) {
        unknown18->~CGLibRenderTarget();
      }
      if (unknown00 != nullptr) {
        unknown00->~CGLibRenderTarget();
      }
      if (unknown10 != nullptr) {
        unknown10->~CGLibRenderTarget();
      }
      if (unknown20 != nullptr) {
        unknown20->~CGLibRenderTarget();
      }
      unknown002();
    }
  }

  // Inferred role: forgets the render targets; original name unknown.
  void unknown002() {
    unknown00 = nullptr;
    unknown10 = nullptr;
    unknown18 = nullptr;
    unknown20 = nullptr;
    unknown28 = true;
  }

  void createAll(StaticAllocObj *allocator, f32 width, f32 height, f32 width2, f32 height2, u32 offset);
  void setTextureAll(f32 width, f32 height, f32 width2, f32 height2, u32 offset);
  u32 getImgSize(u32 &offset, u32 width, u32 height, GrlSurfaceFormat format);
  void bufferClear();

  grlib::CGLibRenderTarget *unknown00; // Inferred role: reduced color target; original member name unknown.
  u8 _08[0x10 - 0x08];
  grlib::CGLibRenderTarget *unknown10; // Inferred role: black target; original member name unknown.
  grlib::CGLibRenderTarget *unknown18; // Inferred role: reduced depth target; original member name unknown.
  grlib::CGLibRenderTarget *unknown20; // Inferred role: white target; original member name unknown.
  bool unknown28;                      // Inferred role: needs clear; original member name unknown.
};

static_assert(offsetof(BackBuffer, unknown10) == 0x10, "");
static_assert(offsetof(BackBuffer, unknown18) == 0x18, "");
static_assert(offsetof(BackBuffer, unknown20) == 0x20, "");
static_assert(offsetof(BackBuffer, unknown28) == 0x28, "");

} // namespace renderer
} // namespace ptlib
