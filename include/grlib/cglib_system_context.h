#pragma once
#include <stddef.h>

#include "grlib/cglib_buff_mem_pool_tbl.h"
#include "grlib/cglib_buff_sampler_tbl.h"
#include "grlib/cglib_buff_texture.h"
#include "grlib/cglib_color_ctl.h"
#include "grlib/cglib_dec_shader.h"
#include "grlib/cglib_depth_target.h"
#include "grlib/cglib_pipeline.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_state.h"
#include "grlib/cglib_tex_descriptor.h"
#include "grlib/cglib_vtx_fetch.h"
#include "mm_mtl/singleton.h"
#include "types.h"

struct NVNmemoryPool;
struct NVNtexture;
struct NVNtextureView;

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace ml {
class CriticalSection;
} // namespace ml

namespace grlib {

class CGLibColorBuffer;
class CGLibDepthBuffer;
class CGLibMemPool;
struct CGLibMemType;

namespace context {

class CGLibSystemContext : public mm::mtl::PtrSingleton<CGLibSystemContext> {
public:
  static ml::CriticalSection &getCriticalSection();
  void createMemPool(CGLibMemPool &memPool, mtl::ALLOC_HANDLE handle, u32 flags);
  bool isRelease();
  void beginRegisterRenderTarget();
  void setRegisterRenderTarget(CGLibColorBuffer &colorBuffer, GrlMrtType mrt);
  void setRegisterDepthTarget(CGLibDepthBuffer &depthBuffer);
  void endRegisterRenderTarget();
  void setMainFrameBuffer();
  void getUniformoGpuAddress(u64 &address, const CGLibMemType &memType);
  void getVertexGpuAddress(u64 &address, const CGLibMemType &memType);
  void getGlbUniformParam(u8 *&buffer, u64 &address);
  void nextGlbUniformOfs(u32 size);
  u64 getPixelResAreaGpuAddress(u32 offset);
  u32 getPixelResAreaOffset(u32 offset);
  void releaseDelayMempool(NVNmemoryPool *pool, void *buffer);
  void releaseDelayTexture(NVNtexture *texture, void *buffer, int textureId, int samplerId);
  void releaseDelayVertex(CGLibMemType &memType);

  u8 _0008[0x0538 - 0x0008];
  CGLibTexDescriptor m_texDescriptor;
  u8 _05a0[0x0608 - 0x05a0];
  CGLibBuffSamplerTbl m_buffSamplerTbl;
  u8 _0e38[0x0e60 - 0x0e38];
  CGLibBuffTexture m_buffTexture;
  CGLibBuffMemPoolTbl m_buffMemPoolTbl;
  u8 _0eb8[0x1070 - 0x0eb8];
  CGLibPipeline m_pipeline;
  CGLibRenderTarget m_mainRenderTargets[2];
  CGLibDepthTarget m_mainDepthTarget;
  u8 _19c8[0x20d4 - 0x19c8];
  s32 m_mainRenderTargetIndex;
  u8 _20d8[0x2320 - 0x20d8];
  CGLibDecShader m_decShader;
  CGLibVtxFetch m_vtxFetches[3];
  u8 _23b8[0x2548 - 0x23b8];
  u64 m_glbUniformGpuAddress;
  u8 *m_glbUniformBuffer;
  u8 _2558[0x2568 - 0x2558];
  u64 m_glbUniformOffset;
  u32 m_glbUniformSize;
  u32 m_glbUniformRest;
  u8 _2578[0x25a0 - 0x2578];
  u64 m_pixelResAreaGpuAddress;
  u32 m_pixelResAreaOffset;
  s32 m_registerNum;
  const NVNtextureView *m_registerViews[8];
  const NVNtexture *m_registerTextures[8];
  LibMainStateViewPort m_defViewPort;
  const NVNtexture *m_registerDepth;
};

static_assert(offsetof(CGLibSystemContext, m_texDescriptor) == 0x0538, "");
static_assert(offsetof(CGLibSystemContext, m_buffSamplerTbl) == 0x0608, "");
static_assert(offsetof(CGLibSystemContext, m_buffTexture) == 0x0e60, "");
static_assert(offsetof(CGLibSystemContext, m_buffMemPoolTbl) == 0x0e90, "");
static_assert(offsetof(CGLibSystemContext, m_pipeline) == 0x1070, "");
static_assert(offsetof(CGLibSystemContext, m_mainRenderTargets) == 0x1110, "");
static_assert(offsetof(CGLibSystemContext, m_mainDepthTarget) == 0x18a0, "");
static_assert(offsetof(CGLibSystemContext, m_mainRenderTargetIndex) == 0x20d4, "");
static_assert(offsetof(CGLibSystemContext, m_decShader) == 0x2320, "");
static_assert(offsetof(CGLibSystemContext, m_vtxFetches) == 0x2388, "");
static_assert(offsetof(CGLibSystemContext, m_glbUniformGpuAddress) == 0x2548, "");
static_assert(offsetof(CGLibSystemContext, m_glbUniformOffset) == 0x2568, "");
static_assert(offsetof(CGLibSystemContext, m_pixelResAreaGpuAddress) == 0x25a0, "");
static_assert(offsetof(CGLibSystemContext, m_registerNum) == 0x25ac, "");
static_assert(offsetof(CGLibSystemContext, m_registerViews) == 0x25b0, "");
static_assert(offsetof(CGLibSystemContext, m_registerTextures) == 0x25f0, "");
static_assert(offsetof(CGLibSystemContext, m_defViewPort) == 0x2630, "");
static_assert(offsetof(CGLibSystemContext, m_registerDepth) == 0x2648, "");

} // namespace context
} // namespace grlib
