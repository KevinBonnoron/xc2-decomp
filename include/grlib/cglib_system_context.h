#pragma once
#include <stddef.h>

#include "grlib/cglib_buff_mem_pool_tbl.h"
#include "grlib/cglib_buff_min_uniform.h"
#include "grlib/cglib_buff_occlusion.h"
#include "grlib/cglib_buff_sampler_tbl.h"
#include "grlib/cglib_buff_texture.h"
#include "grlib/cglib_color_ctl.h"
#include "grlib/cglib_dec_shader.h"
#include "grlib/cglib_depth_target.h"
#include "grlib/cglib_gpu_time_stamp.h"
#include "grlib/cglib_mem_pool.h"
#include "grlib/cglib_mem_pool_adder.h"
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
struct CGLibMemType;

namespace context {

class CGLibSystemContext : public mm::mtl::PtrSingleton<CGLibSystemContext> {
public:
  static int s_nvReportCounterSize;

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
  void setPixelResidentArea(bool isEnable, u32 size);

  u8 _0008[0x0538 - 0x0008];
  CGLibTexDescriptor unknown538; // Inferred role: tex descriptor; original member name unknown.
  u8 _05a0[0x0608 - 0x05a0];
  CGLibBuffSamplerTbl unknown608; // Inferred role: buff sampler tbl; original member name unknown.
  CGLibBuffOcclusion unknowne38;  // Inferred role: buff occlusion; original member name unknown.
  CGLibBuffTexture unknowne60;    // Inferred role: buff texture; original member name unknown.
  CGLibBuffMemPoolTbl unknowne90; // Inferred role: buff mem pool tbl; original member name unknown.
  u8 _0eb8[0x0ef8 - 0x0eb8];
  CGLibMemPoolAdder unknownef8;      // Inferred role: mem pool adder; original member name unknown.
  CGLibBuffMinUniform unknownf08[5]; // Inferred role: min uniform buffers by size class; original member name unknown.
  CGLibPipeline unknown1070;         // Inferred role: pipeline; original member name unknown.
  CGLibRenderTarget unknown1110[2];  // Inferred role: main render targets; original member name unknown.
  CGLibDepthTarget unknown18a0;      // Inferred role: main depth target; original member name unknown.
  u8 _19c8[0x20d4 - 0x19c8];
  s32 unknown20d4; // Inferred role: main render target index; original member name unknown.
  u8 _20d8[0x2320 - 0x20d8];
  CGLibDecShader unknown2320;   // Inferred role: dec shader; original member name unknown.
  CGLibVtxFetch unknown2388[3]; // Inferred role: vtx fetches; original member name unknown.
  u8 _23b8[0x2458 - 0x23b8];
  CGLibMemPool unknown2458;      // Inferred role: counter mem pool; original member name unknown.
  CGLibMemPool unknown2478;      // Inferred role: pixel mem pool; original member name unknown.
  CGLibMemPool unknown2498;      // Inferred role: vertex mem pool; original member name unknown.
  CGLibMemPool unknown24b8;      // Inferred role: uniform mem pool; original member name unknown.
  CGLibGpuTimeStamp unknown24d8; // Inferred role: gpu time stamp; original member name unknown.
  u8 _2540[0x2548 - 0x2540];
  u64 unknown2548; // Inferred role: glb uniform gpu address; original member name unknown.
  u8 *unknown2550; // Inferred role: glb uniform buffer; original member name unknown.
  u8 _2558[0x2568 - 0x2558];
  u64 unknown2568; // Inferred role: glb uniform offset; original member name unknown.
  u32 unknown2570; // Inferred role: glb uniform size; original member name unknown.
  u32 unknown2574; // Inferred role: glb uniform rest; original member name unknown.
  u8 _2578[0x2580 - 0x2578];
  void *unknown2580;    // Inferred role: pixel resident area; original member name unknown.
  void *unknown2588[2]; // Inferred role: stacked pixel resident areas; original member name unknown.
  u32 unknown2598;      // Inferred role: pixel resident area size; original member name unknown.
  u8 _259c[0x25a0 - 0x259c];
  u64 unknown25a0;                      // Inferred role: pixel res area gpu address; original member name unknown.
  u32 unknown25a8;                      // Inferred role: pixel res area offset; original member name unknown.
  s32 unknown25ac;                      // Inferred role: register num; original member name unknown.
  const NVNtextureView *unknown25b0[8]; // Inferred role: register views; original member name unknown.
  const NVNtexture *unknown25f0[8];     // Inferred role: register textures; original member name unknown.
  LibMainStateViewPort unknown2630;     // Inferred role: def view port; original member name unknown.
  const NVNtexture *unknown2648;        // Inferred role: register depth; original member name unknown.
};

static_assert(offsetof(CGLibSystemContext, unknown538) == 0x0538, "");
static_assert(offsetof(CGLibSystemContext, unknown608) == 0x0608, "");
static_assert(offsetof(CGLibSystemContext, unknowne38) == 0x0e38, "");
static_assert(offsetof(CGLibSystemContext, unknowne60) == 0x0e60, "");
static_assert(offsetof(CGLibSystemContext, unknowne90) == 0x0e90, "");
static_assert(offsetof(CGLibSystemContext, unknownef8) == 0x0ef8, "");
static_assert(offsetof(CGLibSystemContext, unknownf08) == 0x0f08, "");
static_assert(offsetof(CGLibSystemContext, unknown1070) == 0x1070, "");
static_assert(offsetof(CGLibSystemContext, unknown1110) == 0x1110, "");
static_assert(offsetof(CGLibSystemContext, unknown18a0) == 0x18a0, "");
static_assert(offsetof(CGLibSystemContext, unknown20d4) == 0x20d4, "");
static_assert(offsetof(CGLibSystemContext, unknown2320) == 0x2320, "");
static_assert(offsetof(CGLibSystemContext, unknown2388) == 0x2388, "");
static_assert(offsetof(CGLibSystemContext, unknown2458) == 0x2458, "");
static_assert(offsetof(CGLibSystemContext, unknown24d8) == 0x24d8, "");
static_assert(offsetof(CGLibSystemContext, unknown2548) == 0x2548, "");
static_assert(offsetof(CGLibSystemContext, unknown2568) == 0x2568, "");
static_assert(offsetof(CGLibSystemContext, unknown2580) == 0x2580, "");
static_assert(offsetof(CGLibSystemContext, unknown2598) == 0x2598, "");
static_assert(offsetof(CGLibSystemContext, unknown25a0) == 0x25a0, "");
static_assert(offsetof(CGLibSystemContext, unknown25ac) == 0x25ac, "");
static_assert(offsetof(CGLibSystemContext, unknown25b0) == 0x25b0, "");
static_assert(offsetof(CGLibSystemContext, unknown25f0) == 0x25f0, "");
static_assert(offsetof(CGLibSystemContext, unknown2630) == 0x2630, "");
static_assert(offsetof(CGLibSystemContext, unknown2648) == 0x2648, "");

} // namespace context
} // namespace grlib
