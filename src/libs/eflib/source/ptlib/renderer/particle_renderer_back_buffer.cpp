#include "ptlib/renderer/particle_renderer_back_buffer.h"

#include <new>

#include "grlib/cglib_render_target.h"
#include "grlib/cglib_texture.h"
#include "mm_math/mm_col4.h"
#include "ptlib/particle_stack_allocater.h"

namespace ptlib {
namespace renderer {

void BackBuffer::createAll(StaticAllocObj *allocator, f32 width, f32 height, f32 width2, f32 height2, u32 offset) {
  unknown18 = static_cast<grlib::CGLibRenderTarget *>(allocator->sysAlloc(sizeof(grlib::CGLibRenderTarget), 0x10, nullptr, 0));
  unknown00 = static_cast<grlib::CGLibRenderTarget *>(allocator->sysAlloc(sizeof(grlib::CGLibRenderTarget), 0x10, nullptr, 0));
  unknown10 = static_cast<grlib::CGLibRenderTarget *>(allocator->sysAlloc(sizeof(grlib::CGLibRenderTarget), 0x10, nullptr, 0));
  unknown20 = static_cast<grlib::CGLibRenderTarget *>(allocator->sysAlloc(sizeof(grlib::CGLibRenderTarget), 0x10, nullptr, 0));
  new (unknown18) grlib::CGLibRenderTarget();
  new (unknown00) grlib::CGLibRenderTarget();
  new (unknown10) grlib::CGLibRenderTarget();
  new (unknown20) grlib::CGLibRenderTarget();
  unknown10->setTextureInfo(8.0f, 8.0f, GRL_SURFACE_FORMAT_R8, false, 0);
  unknown20->setTextureInfo(8.0f, 8.0f, GRL_SURFACE_FORMAT_RGBA8SN, false, 0);
  setTextureAll(width, height, width2, height2, offset);
}

void BackBuffer::setTextureAll(f32 width, f32 height, f32 width2, f32 height2, u32 offset) {
  f32 halfWidth = width * 0.5f;
  f32 halfHeight = height * 0.5f;
  u32 start = getImgSize(offset, halfWidth, halfHeight, GRL_SURFACE_FORMAT_R11G11B10F);
  unknown18->setTextureInfo(halfWidth, halfHeight, GRL_SURFACE_FORMAT_R11G11B10F, true, start);
  start = getImgSize(offset, halfWidth, halfHeight, GRL_SURFACE_FORMAT_R16F);
  unknown00->setTextureInfo(halfWidth, halfHeight, GRL_SURFACE_FORMAT_R16F, true, start);
}

u32 BackBuffer::getImgSize(u32 &offset, u32 width, u32 height, GrlSurfaceFormat format) {
  u32 size;
  u32 alignment;
  grlib::CGLibTexture::getDefPixelSize(size, alignment, width, height, 0, format);
  u32 start = (alignment - offset % alignment) % alignment + offset;
  offset = size + start;
  return start;
}

void BackBuffer::bufferClear() {
  if (unknown28) {
    unknown10->clearTexture(mm::Col4::black, static_cast<GrlClaerMask>(0xf));
    unknown20->clearTexture(mm::Col4::white, static_cast<GrlClaerMask>(0xf));
    unknown28 = false;
  }
}

} // namespace renderer
} // namespace ptlib
