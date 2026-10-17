#pragma once
#include <stddef.h>

#include "grlib/cglib_buff_fix_alloc.h"
#include "grlib/cglib_dec_shader.h"
#include "grlib/cglib_depth_target.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_state.h"
#include "grlib/cglib_vtx_fetch.h"
#include "mm_mtl/singleton.h"
#include "nvn/nvn.h"
#include "types.h"

struct NVNcommandBuffer;
struct NVNmemoryPool;
struct NVNtexture;

namespace grlib {
namespace context {

class CGLibSystemContext : public mm::mtl::PtrSingleton<CGLibSystemContext> {
public:
  void releaseDelayMempool(NVNmemoryPool *pool, void *buffer);
  void releaseDelayTexture(NVNtexture *texture, void *buffer, int textureId, int samplerId);

  u8 _0008[0x0538 - 0x0008];
  CGLibBuffFixAlloc m_descriptorAlloc;
  u8 _0568[0x0e60 - 0x0568];
  CGLibBuffFixAlloc m_textureAlloc;
  CGLibBuffFixAlloc m_memoryPoolAlloc;
  u8 _0ec0[0x1070 - 0x0ec0];
  NVNcommandBuffer *m_cmdBuf;
  u8 _1078[0x1084 - 0x1078];
  NVNchannelMaskState m_colorBufferOn;
  NVNchannelMaskState m_colorBufferOff;
  u8 _108c[0x10a0 - 0x108c];
  NVNpolygonState m_cullingOff;
  NVNpolygonState m_cullingFront;
  NVNpolygonState m_cullingBack;
  NVNpolygonState m_cullingDispOff;
  NVNpolygonState m_pointMode;
  NVNpolygonState m_lineMode;
  NVNpolygonState m_triangle;
  u8 _10bc[0x1110 - 0x10bc];
  CGLibRenderTarget m_mainRenderTargets[2];
  CGLibDepthTarget m_mainDepthTarget;
  u8 _19c8[0x20d4 - 0x19c8];
  s32 m_mainRenderTargetIndex;
  u8 _20d8[0x2320 - 0x20d8];
  CGLibDecShader m_decShader;
  CGLibVtxFetch m_vtxFetches[3];
  u8 _23b8[0x25ac - 0x23b8];
  s32 m_registerNum;
  const NVNtextureView *m_registerViews[8];
  const NVNtexture *m_registerTextures[8];
  LibMainStateViewPort m_defViewPort;
  const NVNtexture *m_registerDepth;
};

static_assert(offsetof(CGLibSystemContext, m_descriptorAlloc) == 0x0538, "");
static_assert(offsetof(CGLibSystemContext, m_textureAlloc) == 0x0e60, "");
static_assert(offsetof(CGLibSystemContext, m_memoryPoolAlloc) == 0x0e90, "");
static_assert(offsetof(CGLibSystemContext, m_cmdBuf) == 0x1070, "");
static_assert(offsetof(CGLibSystemContext, m_colorBufferOn) == 0x1084, "");
static_assert(offsetof(CGLibSystemContext, m_cullingOff) == 0x10a0, "");
static_assert(offsetof(CGLibSystemContext, m_mainRenderTargets) == 0x1110, "");
static_assert(offsetof(CGLibSystemContext, m_mainDepthTarget) == 0x18a0, "");
static_assert(offsetof(CGLibSystemContext, m_mainRenderTargetIndex) == 0x20d4, "");
static_assert(offsetof(CGLibSystemContext, m_decShader) == 0x2320, "");
static_assert(offsetof(CGLibSystemContext, m_vtxFetches) == 0x2388, "");
static_assert(offsetof(CGLibSystemContext, m_registerNum) == 0x25ac, "");
static_assert(offsetof(CGLibSystemContext, m_registerViews) == 0x25b0, "");
static_assert(offsetof(CGLibSystemContext, m_registerTextures) == 0x25f0, "");
static_assert(offsetof(CGLibSystemContext, m_defViewPort) == 0x2630, "");
static_assert(offsetof(CGLibSystemContext, m_registerDepth) == 0x2648, "");

} // namespace context
} // namespace grlib
