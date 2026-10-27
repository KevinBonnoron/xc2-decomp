#include "grlib/cglib_texture_buffer.h"

#include "grlib/cglib_buff_texture.h"
#include "grlib/cglib_color_buffer.h"
#include "grlib/cglib_color_ctl.h"
#include "grlib/cglib_depth_buffer.h"
#include "grlib/cglib_depth_ctl.h"
#include "grlib/cglib_manager.h"
#include "grlib/cglib_render_array.h"
#include "grlib/cglib_render_cube_map.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_render_target_1d.h"
#include "grlib/cglib_render_target_base.h"
#include "grlib/cglib_render_target_mip_map.h"
#include "grlib/cglib_render_volume.h"
#include "grlib/cglib_state.h"
#include "grlib/cglib_system_context.h"
#include "grlib/cglib_tex_descriptor.h"
#include "grlib/cglib_texture.h"
#include "mtl/mem_manager.h"
#include "nvn/nvn.h"

namespace mm {
struct Col4;
} // namespace mm

namespace grlib {

void CGLibColorBuffer::release() { unknown0c &= ~FLAG_INITIALIZED; }

void CGLibTextureBuffer::delayRelease() {
  if ((unknown10 & (FLAG_INITIALIZED | FLAG_OWN_BUFFER)) == 0) {
    return;
  }
  void *buffer = (unknown10 & FLAG_OWN_BUFFER) ? m_buffer : nullptr;
  NVNtexture *texture = (unknown10 & FLAG_INITIALIZED) ? unknown18 : nullptr;
  m_buffer = nullptr;
  unknown30 = 0;
  unknown10 &= ~(FLAG_INITIALIZED | FLAG_OWN_BUFFER);
  context::CGLibSystemContext::get()->releaseDelayTexture(texture, buffer, unknown34, unknown38);
  unknown34 = -1;
  unknown38 = -1;
  unknown40.delayRelease();
}

void CGLibRenderTargetBase::setColorInvalidate() {}

u32 CGLibRenderTargetBase::getImageSize() const { return unknown70->CGLibTextureBuffer::getImageSize(); }

CGLibRenderArray::CGLibRenderArray() : unknown70(this), unknown78(nullptr), unknown80(false), unknown84(0), unknown88(0), unknown8c(0), unknown90(0) {}

CGLibRenderArray::~CGLibRenderArray() { releaseWork(); }

void CGLibRenderArray::releaseWork() {
  u32 count = unknown8c + unknown90 * unknown8c;
  for (u32 i = 0; i < count; i++) {
    unknown78[i].release();
  }
  if (unknown78 != nullptr) {
    mtl::MemManager::deallocate(unknown78, 0, false);
    unknown78 = nullptr;
  }
  delayRelease();
  unknown80 = false;
  unknown8c = 0;
  unknown90 = 0;
  unknown84 = 0;
  unknown88 = 0;
}

void CGLibRenderArray::release() { releaseWork(); }

CGLibRenderTarget1D::CGLibRenderTarget1D() : unknown70(this), unknownb8(0), unknownbc(false) {}

CGLibRenderTarget1D::~CGLibRenderTarget1D() { releaseWork(); }

void CGLibRenderTarget1D::releaseWork() {
  unknown78.release();
  delayRelease();
  unknownbc = false;
}

CGLibRenderTargetMipMap::CGLibRenderTargetMipMap() : unknown70(this) {
  unknown47c = 0;
  unknown480 = 0;
  unknown484 = 0;
  unknown478 = false;
}

CGLibRenderTargetMipMap::~CGLibRenderTargetMipMap() { releaseWork(); }

void CGLibRenderTargetMipMap::releaseWork() {
  unknown484 = 0;
  for (u32 i = 0; i < 16; i++) {
    unknown78[i].release();
  }
  delayRelease();
  unknown478 = false;
}

CGLibRenderCubeMapMipMap::CGLibRenderCubeMapMipMap() : unknown70(this) {
  unknown1880 = 0;
  unknown1884 = 0;
  unknown187c = 0;
  unknown1878 = false;
}

CGLibRenderCubeMapMipMap::~CGLibRenderCubeMapMipMap() { releaseWork(); }

void CGLibRenderCubeMapMipMap::releaseWork() {
  for (u32 i = 0; i < GRL_CUBE_MAP_FACE_NUM; i++) {
    for (u32 j = 0; j < 16; j++) {
      unknown78[i][j].release();
    }
  }
  unknown187c = 0;
  delayRelease();
  unknown1878 = false;
}

CGLibRenderTarget::~CGLibRenderTarget() {
  releaseWork();
  for (int i = 0; i < 6; i++) {
    unknown128[i].delayRelease();
  }
  unknownc4 = 0;
}

void CGLibRenderTarget::releaseWork() {
  unknown78.release();
  delayRelease();
  unknownb8 = false;
}

CGLibRenderCubeMap::CGLibRenderCubeMap() : unknown70(this) {
  unknown1fc = 0.0f;
  unknown200 = 0.0f;
  unknown1f8 = false;
}

CGLibRenderCubeMap::~CGLibRenderCubeMap() { releaseWork(); }

void CGLibRenderCubeMap::releaseWork() {
  for (u32 i = 0; i < GRL_CUBE_MAP_FACE_NUM; i++) {
    unknown78[i].release();
  }
  delayRelease();
  unknown1f8 = false;
}

CGLibRenderVolume::CGLibRenderVolume() : unknown70(this), unknown78(nullptr) {
  unknown84 = 0;
  unknown88 = 0;
  unknown8c = 0;
  unknown80 = false;
}

CGLibRenderVolume::~CGLibRenderVolume() { releaseWork(); }

void CGLibRenderVolume::releaseWork() {
  for (u32 i = 0; i < unknown8c; i++) {
    unknown78[i].release();
  }
  if (unknown78 != nullptr) {
    mtl::MemManager::deallocate(unknown78, 0, false);
    unknown78 = nullptr;
  }
  delayRelease();
  unknown80 = false;
  unknown84 = 0;
  unknown88 = 0;
  unknown8c = 0;
}

void CGLibRenderTarget1D::release() { releaseWork(); }

void CGLibRenderTarget1D::releaseTexture() {
  releaseWork();
  unknownb8 = 0;
}

void CGLibRenderTarget1D::clearTexture(const mm::Col4 &color, GrlClaerMask mask) { CGLibDepthCtl::clearColorBuffer(unknown78, color, mask); }

void CGLibRenderTarget1D::clearIntTexture(const int *color, GrlClaerMask mask) { CGLibDepthCtl::clearIntColorBuffer(unknown78, color, mask); }

void CGLibRenderTarget1D::setRenderTarget() {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknownb8, 1.0f, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(unknown78, GRL_MRT_TYPE_0);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderTarget1D::setRenderTarget(CGLibDepthBuffer &depthBuffer) {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknownb8, 1.0f, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(unknown78, GRL_MRT_TYPE_0);
  CGLibState::setRegisterDepthTarget(depthBuffer);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderTargetMipMap::release() { releaseWork(); }

void CGLibRenderTargetMipMap::releaseTexture() {
  releaseWork();
  unknown47c = 0;
  unknown480 = 0;
}

void CGLibRenderTargetMipMap::clearTexture(u32 mipmap, const mm::Col4 &color, GrlClaerMask mask) { CGLibDepthCtl::clearColorBuffer(unknown78[mipmap], color, mask); }

void CGLibRenderTargetMipMap::clearIntTexture(u32 mipmap, const int *color, GrlClaerMask mask) { CGLibDepthCtl::clearIntColorBuffer(unknown78[mipmap], color, mask); }

void CGLibRenderTargetMipMap::setRenderTarget(u32 mipmap) {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknown78[mipmap].getWidth(), unknown78[mipmap].getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(unknown78[mipmap], GRL_MRT_TYPE_0);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderTargetMipMap::setRenderTarget(u32 mipmap, CGLibDepthBuffer &depthBuffer) {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknown78[mipmap].getWidth(), unknown78[mipmap].getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(unknown78[mipmap], GRL_MRT_TYPE_0);
  CGLibState::setRegisterDepthTarget(depthBuffer);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderCubeMapMipMap::release() { releaseWork(); }

void CGLibRenderCubeMapMipMap::releaseTexture() {
  releaseWork();
  unknown1880 = 0;
  unknown1884 = 0;
}

void CGLibRenderCubeMapMipMap::clearTexture(GrlCubeMapFace face, u32 mipmap, const mm::Col4 &color, GrlClaerMask mask) { CGLibDepthCtl::clearColorBuffer(unknown78[face][mipmap], color, mask); }

void CGLibRenderCubeMapMipMap::clearIntTexture(GrlCubeMapFace face, u32 mipmap, const int *color, GrlClaerMask mask) { CGLibDepthCtl::clearIntColorBuffer(unknown78[face][mipmap], color, mask); }

CGLibColorBuffer *CGLibRenderCubeMapMipMap::getColorBuffer(GrlCubeMapFace face, u32 mipmap) { return &unknown78[face][mipmap]; }

const CGLibColorBuffer *CGLibRenderCubeMapMipMap::getColorBuffer(GrlCubeMapFace face, u32 mipmap) const { return &unknown78[face][mipmap]; }

void CGLibRenderCubeMapMipMap::setRegisterRenderTarget(GrlCubeMapFace face, u32 mipmap, GrlMrtType mrt) { CGLibState::setRegisterRenderTarget(unknown78[face][mipmap], mrt); }

void CGLibRenderCubeMapMipMap::setRenderTarget(GrlCubeMapFace face, u32 mipmap) {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknown78[face][mipmap].getWidth(), unknown78[face][mipmap].getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(unknown78[face][mipmap], GRL_MRT_TYPE_0);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderCubeMapMipMap::setRenderTarget(GrlCubeMapFace face, u32 mipmap, CGLibDepthBuffer &depthBuffer) {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknown78[face][mipmap].getWidth(), unknown78[face][mipmap].getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(unknown78[face][mipmap], GRL_MRT_TYPE_0);
  CGLibState::setRegisterDepthTarget(depthBuffer);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderTarget::release() { releaseWork(); }

void CGLibRenderTarget::releaseTexture() {
  releaseWork();
  unknownbc = 0;
  unknownc0 = 0;
}

void CGLibRenderTarget::clearTexture(const mm::Col4 &color, GrlClaerMask mask) { CGLibDepthCtl::clearColorBuffer(unknown78, color, mask); }

void CGLibRenderTarget::clearIntTexture(const int *color, GrlClaerMask mask) { CGLibDepthCtl::clearIntColorBuffer(unknown78, color, mask); }

void CGLibRenderTarget::setRenderTarget() {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknownbc, unknownc0, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(unknown78, GRL_MRT_TYPE_0);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderTarget::setRenderTarget(CGLibColorBuffer &colorBuffer) {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknownbc, unknownc0, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(unknown78, GRL_MRT_TYPE_0);
  CGLibState::setRegisterRenderTarget(colorBuffer, GRL_MRT_TYPE_1);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderTarget::setRenderTarget(CGLibRenderTarget &target1) {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknownbc, unknownc0, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(unknown78, GRL_MRT_TYPE_0);
  CGLibState::setRegisterRenderTarget(target1, GRL_MRT_TYPE_1);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderTarget::setRenderTarget(CGLibRenderTarget &target1, CGLibRenderTarget &target2) {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknownbc, unknownc0, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(unknown78, GRL_MRT_TYPE_0);
  CGLibState::setRegisterRenderTarget(target1, GRL_MRT_TYPE_1);
  CGLibState::setRegisterRenderTarget(target2, GRL_MRT_TYPE_2);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderTarget::setRenderTarget(CGLibRenderTarget &target1, CGLibRenderTarget &target2, CGLibRenderTarget &target3) {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknownbc, unknownc0, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(unknown78, GRL_MRT_TYPE_0);
  CGLibState::setRegisterRenderTarget(target1, GRL_MRT_TYPE_1);
  CGLibState::setRegisterRenderTarget(target2, GRL_MRT_TYPE_2);
  CGLibState::setRegisterRenderTarget(target3, GRL_MRT_TYPE_UNKNOWN_3);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderTarget::setRenderTarget(CGLibDepthBuffer &depthBuffer) {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknownbc, unknownc0, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(unknown78, GRL_MRT_TYPE_0);
  CGLibState::setRegisterDepthTarget(depthBuffer);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderTarget::setRenderTarget(CGLibDepthBuffer &depthBuffer, CGLibRenderTarget &target1) {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknownbc, unknownc0, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(unknown78, GRL_MRT_TYPE_0);
  CGLibState::setRegisterRenderTarget(target1, GRL_MRT_TYPE_1);
  CGLibState::setRegisterDepthTarget(depthBuffer);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderTarget::setRenderTarget(CGLibDepthBuffer &depthBuffer, CGLibRenderTarget &target1, CGLibRenderTarget &target2) {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknownbc, unknownc0, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(unknown78, GRL_MRT_TYPE_0);
  CGLibState::setRegisterRenderTarget(target1, GRL_MRT_TYPE_1);
  CGLibState::setRegisterRenderTarget(target2, GRL_MRT_TYPE_2);
  CGLibState::setRegisterDepthTarget(depthBuffer);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderTarget::setRenderTarget(CGLibRenderTarget &target1, CGLibRenderTarget &target2, CGLibRenderTarget &target3, CGLibRenderTarget &target4) {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknownbc, unknownc0, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(unknown78, GRL_MRT_TYPE_0);
  CGLibState::setRegisterRenderTarget(target1, GRL_MRT_TYPE_1);
  CGLibState::setRegisterRenderTarget(target2, GRL_MRT_TYPE_2);
  CGLibState::setRegisterRenderTarget(target3, GRL_MRT_TYPE_UNKNOWN_3);
  CGLibState::setRegisterRenderTarget(target4, GRL_MRT_TYPE_UNKNOWN_4);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderCubeMap::release() { releaseWork(); }

void CGLibRenderCubeMap::releaseTexture() {
  releaseWork();
  unknown1fc = 0;
  unknown200 = 0;
}

void CGLibRenderCubeMap::clearTexture(GrlCubeMapFace face, const mm::Col4 &color, GrlClaerMask mask) { CGLibDepthCtl::clearColorBuffer(unknown78[face], color, mask); }

void CGLibRenderCubeMap::clearIntTexture(GrlCubeMapFace face, const int *color, GrlClaerMask mask) { CGLibDepthCtl::clearIntColorBuffer(unknown78[face], color, mask); }

void CGLibRenderCubeMap::setRegisterRenderTarget(GrlCubeMapFace face, GrlMrtType mrt) { CGLibState::setRegisterRenderTarget(unknown78[face], mrt); }

void CGLibRenderCubeMap::setRenderTarget(GrlCubeMapFace face) {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknown1fc, unknown200, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(unknown78[face], GRL_MRT_TYPE_0);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderCubeMap::setRenderTarget(GrlCubeMapFace face, CGLibDepthBuffer &depthBuffer) {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknown1fc, unknown200, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(unknown78[face], GRL_MRT_TYPE_0);
  CGLibState::setRegisterDepthTarget(depthBuffer);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderVolume::release() { releaseWork(); }

void CGLibRenderVolume::releaseTexture() { releaseWork(); }

void CGLibRenderVolume::clearTexture(u32 slice, const mm::Col4 &color, GrlClaerMask mask) { CGLibDepthCtl::clearColorBuffer(unknown78[slice], color, mask); }

void CGLibRenderVolume::clearIntTexture(u32 slice, const int *color, GrlClaerMask mask) { CGLibDepthCtl::clearIntColorBuffer(unknown78[slice], color, mask); }

void CGLibRenderVolume::setRenderTarget(u32 slice) {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknown84, unknown88, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(unknown78[slice], GRL_MRT_TYPE_0);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderVolume::setRenderTarget(u32 slice, CGLibDepthBuffer &depthBuffer) {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknown84, unknown88, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(unknown78[slice], GRL_MRT_TYPE_0);
  CGLibState::setRegisterDepthTarget(depthBuffer);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderVolume::setRenderTarget(u32 slice, CGLibRenderVolume &target) {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknown84, unknown88, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(unknown78[slice], GRL_MRT_TYPE_0);
  CGLibState::setRegisterRenderTarget(target.unknown78[slice], GRL_MRT_TYPE_1);
  CGLibState::endRegisterRenderTarget();
}

u16 CGLibColorBuffer::getWidth() const { return m_width; }

u16 CGLibColorBuffer::getHeight() const { return m_height; }

void CGLibRenderArray::releaseTexture() {
  releaseWork();
  unknown84 = 0;
  unknown88 = 0;
}

void CGLibRenderArray::clearTexture(u32 slice, const mm::Col4 &color, GrlClaerMask mask) { CGLibDepthCtl::clearColorBuffer(unknown78[slice], color, mask); }

CGLibColorBuffer *CGLibRenderArray::getColorBuffer(u32 slice) { return &unknown78[slice]; }

void CGLibRenderArray::clearMipmapTexture(u32 slice, u32 mipmap, const mm::Col4 &color, GrlClaerMask mask) { CGLibDepthCtl::clearColorBuffer(unknown78[slice + unknown8c * mipmap], color, mask); }

CGLibColorBuffer *CGLibRenderArray::getMipmapColorBuffer(u32 slice, u32 mipmap) { return &unknown78[slice + unknown8c * mipmap]; }

void CGLibRenderArray::clearIntTexture(u32 slice, const int *color, GrlClaerMask mask) { CGLibDepthCtl::clearIntColorBuffer(unknown78[slice], color, mask); }

void CGLibRenderArray::clearIntMipmapTexture(u32 slice, u32 mipmap, const int *color, GrlClaerMask mask) { CGLibDepthCtl::clearIntColorBuffer(unknown78[slice + unknown8c * mipmap], color, mask); }

void CGLibRenderArray::setRenderTarget(u32 slice) {
  CGLibColorBuffer &colorBuffer = unknown78[slice];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknown84, unknown88, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(colorBuffer, GRL_MRT_TYPE_0);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderArray::setRenderTarget(u32 slice, CGLibColorBuffer &colorBuffer) {
  CGLibColorBuffer &target = unknown78[slice];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknown84, unknown88, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(target, GRL_MRT_TYPE_0);
  CGLibState::setRegisterRenderTarget(colorBuffer, GRL_MRT_TYPE_1);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderArray::setRenderTarget(u32 slice, CGLibDepthBuffer &depthBuffer) {
  CGLibColorBuffer &target = unknown78[slice];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknown84, unknown88, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(target, GRL_MRT_TYPE_0);
  CGLibState::setRegisterDepthTarget(depthBuffer);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderArray::setMipmapRenderTarget(u32 slice, u32 mipmap) {
  CGLibColorBuffer &target = unknown78[slice + unknown8c * mipmap];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, target.getWidth(), target.getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(target, GRL_MRT_TYPE_0);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderArray::setMipmapRenderTarget(u32 slice, u32 mipmap, CGLibColorBuffer &colorBuffer) {
  CGLibColorBuffer &target = unknown78[slice + unknown8c * mipmap];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, target.getWidth(), target.getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(target, GRL_MRT_TYPE_0);
  CGLibState::setRegisterRenderTarget(colorBuffer, GRL_MRT_TYPE_1);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderArray::setMipmapRenderTarget(u32 slice, u32 mipmap, CGLibDepthBuffer &depthBuffer) {
  CGLibColorBuffer &target = unknown78[slice + unknown8c * mipmap];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, target.getWidth(), target.getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(target, GRL_MRT_TYPE_0);
  CGLibState::setRegisterDepthTarget(depthBuffer);
  CGLibState::endRegisterRenderTarget();
}

const CGLibColorBuffer *CGLibRenderArray::getColorBuffer(u32 slice) const { return &unknown78[slice]; }

const CGLibColorBuffer *CGLibRenderArray::getMipmapColorBuffer(u32 slice, u32 mipmap) const { return &unknown78[slice + unknown8c * mipmap]; }

CGLibRenderArrayCubeMap::CGLibRenderArrayCubeMap() : unknown70(this), unknown78(nullptr), unknown80(false), unknown84(0), unknown88(0), unknown8c(0), unknown90(0) {}

CGLibRenderArrayCubeMap::~CGLibRenderArrayCubeMap() { releaseWork(); }

void CGLibRenderArrayCubeMap::releaseWork() {
  u32 count = getFaceBufferNum() * GRL_CUBE_MAP_FACE_NUM;
  for (u32 i = 0; i < count; i++) {
    unknown78[i].release();
  }
  if (unknown78 != nullptr) {
    mtl::MemManager::deallocate(unknown78, 0, false);
    unknown78 = nullptr;
  }
  delayRelease();
  unknown80 = false;
  unknown8c = 0;
  unknown90 = 0;
  unknown84 = 0;
  unknown88 = 0;
}

void CGLibRenderArrayCubeMap::release() { releaseWork(); }

void CGLibRenderArrayCubeMap::releaseTexture() {
  releaseWork();
  unknown84 = 0;
  unknown88 = 0;
}

void CGLibRenderArrayCubeMap::clearTexture(GrlCubeMapFace face, u32 slice, const mm::Col4 &color, GrlClaerMask mask) {
  CGLibDepthCtl::clearColorBuffer(unknown78[getFaceBufferNum() * face + slice], color, mask);
}

CGLibColorBuffer *CGLibRenderArrayCubeMap::getColorBuffer(GrlCubeMapFace face, u32 slice) { return &unknown78[getFaceBufferNum() * face + slice]; }

void CGLibRenderArrayCubeMap::clearMipmapTexture(GrlCubeMapFace face, u32 slice, u32 mipmap, const mm::Col4 &color, GrlClaerMask mask) {
  CGLibDepthCtl::clearColorBuffer(unknown78[getFaceBufferNum() * face + slice + unknown8c * mipmap], color, mask);
}

CGLibColorBuffer *CGLibRenderArrayCubeMap::getMipmapColorBuffer(GrlCubeMapFace face, u32 slice, u32 mipmap) { return &unknown78[getFaceBufferNum() * face + slice + unknown8c * mipmap]; }

void CGLibRenderArrayCubeMap::clearIntTexture(GrlCubeMapFace face, u32 slice, const int *color, GrlClaerMask mask) {
  CGLibDepthCtl::clearIntColorBuffer(unknown78[getFaceBufferNum() * face + slice], color, mask);
}

void CGLibRenderArrayCubeMap::clearIntMipmapTexture(GrlCubeMapFace face, u32 slice, u32 mipmap, const int *color, GrlClaerMask mask) {
  CGLibDepthCtl::clearIntColorBuffer(unknown78[getFaceBufferNum() * face + slice + unknown8c * mipmap], color, mask);
}

void CGLibRenderArrayCubeMap::setRenderTarget(GrlCubeMapFace face, u32 slice) {
  CGLibColorBuffer &target = unknown78[getFaceBufferNum() * face + slice];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, target.getWidth(), target.getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(target, GRL_MRT_TYPE_0);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderArrayCubeMap::setRenderTarget(GrlCubeMapFace face, u32 slice, CGLibColorBuffer &colorBuffer) {
  CGLibColorBuffer &target = unknown78[getFaceBufferNum() * face + slice];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, target.getWidth(), target.getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(target, GRL_MRT_TYPE_0);
  CGLibState::setRegisterRenderTarget(colorBuffer, GRL_MRT_TYPE_1);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderArrayCubeMap::setRenderTarget(GrlCubeMapFace face, u32 slice, CGLibDepthBuffer &depthBuffer) {
  CGLibColorBuffer &target = unknown78[getFaceBufferNum() * face + slice];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, target.getWidth(), target.getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(target, GRL_MRT_TYPE_0);
  CGLibState::setRegisterDepthTarget(depthBuffer);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderArrayCubeMap::setMipmapRenderTarget(GrlCubeMapFace face, u32 slice, u32 mipmap) {
  CGLibColorBuffer &target = unknown78[getFaceBufferNum() * face + slice + unknown8c * mipmap];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, target.getWidth(), target.getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(target, GRL_MRT_TYPE_0);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderArrayCubeMap::setMipmapRenderTarget(GrlCubeMapFace face, u32 slice, u32 mipmap, CGLibColorBuffer &colorBuffer) {
  CGLibColorBuffer &target = unknown78[getFaceBufferNum() * face + slice + unknown8c * mipmap];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, target.getWidth(), target.getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(target, GRL_MRT_TYPE_0);
  CGLibState::setRegisterRenderTarget(colorBuffer, GRL_MRT_TYPE_1);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderArrayCubeMap::setMipmapRenderTarget(GrlCubeMapFace face, u32 slice, u32 mipmap, CGLibDepthBuffer &depthBuffer) {
  CGLibColorBuffer &target = unknown78[getFaceBufferNum() * face + slice + unknown8c * mipmap];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, target.getWidth(), target.getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(target, GRL_MRT_TYPE_0);
  CGLibState::setRegisterDepthTarget(depthBuffer);
  CGLibState::endRegisterRenderTarget();
}

const CGLibColorBuffer *CGLibRenderArrayCubeMap::getColorBuffer(GrlCubeMapFace face, u32 slice) const { return &unknown78[getFaceBufferNum() * face + slice]; }

const CGLibColorBuffer *CGLibRenderArrayCubeMap::getMipmapColorBuffer(GrlCubeMapFace face, u32 slice, u32 mipmap) const { return &unknown78[getFaceBufferNum() * face + slice + unknown8c * mipmap]; }

void CGLibDepthBuffer::delayRelease() {
  if ((unknown08 & (FLAG_INITIALIZED | FLAG_OWN_BUFFER)) == 0) {
    return;
  }
  void *buffer = (unknown08 & FLAG_OWN_BUFFER) ? m_buffer : nullptr;
  m_buffer = nullptr;
  unknown28 = 0;
  NVNtexture *texture = (unknown08 & FLAG_INITIALIZED) ? unknown10 : nullptr;
  unknown08 &= ~(FLAG_INITIALIZED | FLAG_OWN_BUFFER);
  context::CGLibSystemContext::get()->releaseDelayTexture(texture, buffer, -1, -1);
}

CGLibTextureBuffer::CGLibTextureBuffer() {
  unknown10 = 0;
  m_buffer = nullptr;
  unknown30 = 0;
  unknown34 = -1;
  unknown38 = -1;
  unknown18 = nullptr;
  unknown20 = 0;
}

CGLibTextureBuffer::~CGLibTextureBuffer() { release(); }

void CGLibTextureBuffer::release() {
  if (unknown10 & FLAG_OWN_BUFFER) {
    if (m_buffer != nullptr) {
      mtl::MemManager::deallocate(m_buffer, 0, false);
      m_buffer = nullptr;
    }
  } else {
    m_buffer = nullptr;
  }
  unknown30 = 0;
  unknown20 = 0;
  if (unknown10 & FLAG_INITIALIZED) {
    nvnTextureFinalize(unknown18);
    context::CGLibSystemContext::get()->unknowne60.freeBuffer(unknown18);
  }
  unknown40.release();
  if (unknown34 != -1) {
    context::CGLibSystemContext::get()->unknown538.freeID(unknown34);
    unknown34 = -1;
  }
  if (unknown38 != -1) {
    context::CGLibSystemContext::get()->unknown538.freeID(unknown38);
    unknown38 = -1;
  }
  unknown10 &= ~(FLAG_INITIALIZED | FLAG_OWN_BUFFER);
}

u16 CGLibTextureBuffer::getSlice() const { return m_slice; }

bool CGLibTextureBuffer::isTexture1D() const { return unknown0e == 1; }

bool CGLibTextureBuffer::isTexture2D() const { return unknown0e == 0; }

bool CGLibTextureBuffer::isTexture3D() const { return unknown0e == 5; }

void CGLibTextureBuffer::setTexturePass(CGLibTextureBuffer &texture) {}

void CGLibTextureBuffer::invalidate() {}

bool CGLibTextureBuffer::isInitialized() const { return unknown10 & FLAG_INITIALIZED; }

f32 CGLibTextureBuffer::get1PixelTextureInfo() {
  f32 info;
  CGLibTexture::get1PixelTextureInfo(&info, *this);
  return info;
}

void CGLibTextureBuffer::writeDDS(const char *path, bool isMipmap) {}

CGLibColorBuffer::CGLibColorBuffer() { unknown0c = 0; }

CGLibColorBuffer::~CGLibColorBuffer() { release(); }

u16 CGLibColorBuffer::getSlice() const { return m_slice; }

GrlSurfaceFormat CGLibColorBuffer::getFormat() const { return m_format; }

u16 CGLibColorBuffer::getMipmap() const { return m_mipmap; }

u32 CGLibColorBuffer::getImageSize() const {
  int width = m_width;
  int height = m_height;
  GrlSurfaceFormat format = m_format;
  NVNtextureBuilder builder;
  nvnTextureBuilderSetDefaults(&builder);
  nvnTextureBuilderSetDevice(&builder, &CGLibManager::get()->unknown00);
  nvnTextureBuilderSetTarget(&builder, NVN_TEXTURE_TARGET_2D);
  nvnTextureBuilderSetFormat(&builder, static_cast<NVNformat>(format));
  nvnTextureBuilderSetSize2D(&builder, width, height);
  nvnTextureBuilderSetDepth(&builder, 1);
  nvnTextureBuilderSetLevels(&builder, 1);
  nvnTextureBuilderSetFlags(&builder, NVN_TEXTURE_FLAGS_IMAGE | NVN_TEXTURE_FLAGS_COMPRESSIBLE);
  u32 size = nvnTextureBuilderGetStorageSize(&builder);
  nvnTextureBuilderGetStorageAlignment(&builder);
  return size;
}

u32 CGLibColorBuffer::get1PixelImageSize() const {
  switch (m_format) {
  case GRL_SURFACE_FORMAT_R8:
  case GRL_SURFACE_FORMAT_R8SN:
  case GRL_SURFACE_FORMAT_R8UI:
  case GRL_SURFACE_FORMAT_R8I:
  case GRL_SURFACE_FORMAT_RGBA_DXT1:
  case GRL_SURFACE_FORMAT_RGBA_DXT1_SRGB:
  case GRL_SURFACE_FORMAT_RGTC1_UNORM:
  case GRL_SURFACE_FORMAT_RGTC1_SNORM:
    return 1;
  case GRL_SURFACE_FORMAT_R16F:
  case GRL_SURFACE_FORMAT_R16:
  case GRL_SURFACE_FORMAT_R16SN:
  case GRL_SURFACE_FORMAT_R16UI:
  case GRL_SURFACE_FORMAT_R16I:
  case GRL_SURFACE_FORMAT_RG8:
  case GRL_SURFACE_FORMAT_RG8SN:
  case GRL_SURFACE_FORMAT_RG8UI:
  case GRL_SURFACE_FORMAT_RG8I:
  case GRL_SURFACE_FORMAT_RGBA4:
  case GRL_SURFACE_FORMAT_RGB5A1:
  case GRL_SURFACE_FORMAT_RGB565:
  case GRL_SURFACE_FORMAT_RGBA_DXT3:
  case GRL_SURFACE_FORMAT_RGBA_DXT5:
  case GRL_SURFACE_FORMAT_RGBA_DXT3_SRGB:
  case GRL_SURFACE_FORMAT_RGBA_DXT5_SRGB:
  case GRL_SURFACE_FORMAT_RGTC2_UNORM:
  case GRL_SURFACE_FORMAT_RGTC2_SNORM:
    return 2;
  case GRL_SURFACE_FORMAT_R32F:
  case GRL_SURFACE_FORMAT_R32UI:
  case GRL_SURFACE_FORMAT_R32I:
  case GRL_SURFACE_FORMAT_RG16F:
  case GRL_SURFACE_FORMAT_RG16:
  case GRL_SURFACE_FORMAT_RG16SN:
  case GRL_SURFACE_FORMAT_RG16UI:
  case GRL_SURFACE_FORMAT_RG16I:
  case GRL_SURFACE_FORMAT_RGBA8:
  case GRL_SURFACE_FORMAT_RGBA8SN:
  case GRL_SURFACE_FORMAT_RGBA8UI:
  case GRL_SURFACE_FORMAT_RGBA8I:
  case GRL_SURFACE_FORMAT_DEPTH24_STENCIL8:
  case GRL_SURFACE_FORMAT_DEPTH32F_STENCIL8:
  case GRL_SURFACE_FORMAT_RGBA8_SRGB:
  case GRL_SURFACE_FORMAT_RGB10A2:
  case GRL_SURFACE_FORMAT_RGB10A2UI:
  case GRL_SURFACE_FORMAT_R11G11B10F:
  case GRL_SURFACE_FORMAT_BPTC_UNORM:
  case GRL_SURFACE_FORMAT_BPTC_SIGNED_FLOAT:
  case GRL_SURFACE_FORMAT_BPTC_UNSIGNED_FLOAT:
    return 4;
  case GRL_SURFACE_FORMAT_RG32F:
  case GRL_SURFACE_FORMAT_RG32UI:
  case GRL_SURFACE_FORMAT_RG32I:
  case GRL_SURFACE_FORMAT_RGBA16F:
  case GRL_SURFACE_FORMAT_RGBA16:
  case GRL_SURFACE_FORMAT_RGBA16SN:
  case GRL_SURFACE_FORMAT_RGBA16UI:
  case GRL_SURFACE_FORMAT_RGBA16I:
    return 8;
  case GRL_SURFACE_FORMAT_RGBA32F:
  case GRL_SURFACE_FORMAT_RGBA32UI:
  case GRL_SURFACE_FORMAT_RGBA32I:
    return 16;
  default:
    return 0;
  }
}

bool CGLibColorBuffer::isInitialized() const { return unknown0c & FLAG_INITIALIZED; }

CGLibDepthBuffer::CGLibDepthBuffer() {
  unknown08 = 0;
  unknown28 = 0;
  unknown18 = 0;
  m_buffer = nullptr;
}

CGLibDepthBuffer::~CGLibDepthBuffer() { release(); }

void CGLibDepthBuffer::release() {
  if (unknown08 & FLAG_OWN_BUFFER) {
    if (m_buffer != nullptr) {
      mtl::MemManager::deallocate(m_buffer, 0, false);
      m_buffer = nullptr;
    }
  } else {
    m_buffer = nullptr;
  }
  unknown18 = 0;
  unknown28 = 0;
  if (unknown08 & FLAG_INITIALIZED) {
    nvnTextureFinalize(unknown10);
    context::CGLibSystemContext::get()->unknowne60.freeBuffer(unknown10);
  }
  unknown08 &= ~(FLAG_INITIALIZED | FLAG_OWN_BUFFER);
}

u16 CGLibDepthBuffer::getWidth() const { return m_width; }

u16 CGLibDepthBuffer::getHeight() const { return m_height; }

GrlSurfaceFormat CGLibDepthBuffer::getFormat() const { return m_format; }

u32 CGLibDepthBuffer::getImageSize() const {
  int width = m_width;
  int height = m_height;
  GrlSurfaceFormat format = m_format;
  NVNtextureBuilder builder;
  nvnTextureBuilderSetDefaults(&builder);
  nvnTextureBuilderSetDevice(&builder, &CGLibManager::get()->unknown00);
  nvnTextureBuilderSetTarget(&builder, NVN_TEXTURE_TARGET_2D);
  nvnTextureBuilderSetFormat(&builder, static_cast<NVNformat>(format));
  nvnTextureBuilderSetSize2D(&builder, width, height);
  nvnTextureBuilderSetFlags(&builder, NVN_TEXTURE_FLAGS_COMPRESSIBLE);
  u32 size = nvnTextureBuilderGetStorageSize(&builder);
  nvnTextureBuilderGetStorageAlignment(&builder);
  return size;
}

u32 CGLibDepthBuffer::get1PixelImageSize() const {
  switch (m_format) {
  case GRL_SURFACE_FORMAT_DEPTH16:
    return 2;
  case GRL_SURFACE_FORMAT_DEPTH32F:
  case GRL_SURFACE_FORMAT_DEPTH24_STENCIL8:
    return 4;
  case GRL_SURFACE_FORMAT_DEPTH32F_STENCIL8:
    return 5;
  default:
    return 0;
  }
}

void CGLibDepthBuffer::invalidate() {}

bool CGLibDepthBuffer::isInitialized() const { return unknown08 & FLAG_INITIALIZED; }

} // namespace grlib
