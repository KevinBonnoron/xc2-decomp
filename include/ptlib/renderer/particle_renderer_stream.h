#pragma once
#include <stddef.h>

#include "grlib/cglib_vtx_vertex.h"
#include "types.h"

namespace grlib {
class CGLibSampler;
class CGLibVtxFetch;
} // namespace grlib

namespace ptlib {

struct DrDrawWorkInfoEF;

enum FxVertexType {
  FX_VERTEX_TYPE_UNKNOWN_0 = 0,
  FX_VERTEX_TYPE_UNKNOWN_1 = 1,
};

namespace renderer {

class RenderSet;

enum STREAM_SIZE_TYPE {
  STREAM_SIZE_TYPE_UNKNOWN_20 = 0x14,
  STREAM_SIZE_TYPE_UNKNOWN_24 = 0x18,
  STREAM_SIZE_TYPE_UNKNOWN_28 = 0x1c,
  STREAM_SIZE_TYPE_UNKNOWN_32 = 0x20,
  STREAM_SIZE_TYPE_UNKNOWN_36 = 0x24,
  STREAM_SIZE_TYPE_UNKNOWN_40 = 0x28,
};

// Layout evidence: init 0x710093f210, initFetchVertex 0x710093f394, lockStream 0x710093f49c.
class StreamObj {
public:
  void init(STREAM_SIZE_TYPE sizeType, u32 count, FxVertexType vertexType);
  void initSub();
  void initVertex();
  void initFetchVertex();
  void release();
  void releaseSub();
  void *lockStream(const DrDrawWorkInfoEF *info);
  void unlockStream(const DrDrawWorkInfoEF *info, u32 count);
  void renderStreamNum(RenderSet &renderSet, const DrDrawWorkInfoEF *info);
  grlib::CGLibSampler *getSampler(u32 clamp);
  grlib::CGLibSampler *getSampler(u32 clampS, u32 clampT);
  grlib::CGLibSampler *getSampler(u32 clampS, u32 clampT, u32 clampR);

  grlib::CGLibVtxFetch *unknown00;  // Inferred role: vertex fetch; original member name unknown.
  grlib::CGLibVtxFetch *unknown08;  // Inferred role: instance vertex fetch; original member name unknown.
  grlib::CGLibVtxVertex *unknown10; // Inferred role: vertex buffer in use; original member name unknown.
  grlib::CGLibVtxVertex unknown18;  // Inferred role: owned vertex buffer; original member name unknown.
  u32 unknown40;                    // Inferred role: index buffer number; original member name unknown.
  STREAM_SIZE_TYPE unknown44;       // Inferred role: size type; original member name unknown.
  u32 unknown48;                    // Inferred role: instance buffer offset; original member name unknown.
  FxVertexType unknown4c;           // Inferred role: vertex type; original member name unknown.
  bool unknown50;                   // Inferred role: valid; original member name unknown.
};

static_assert(offsetof(StreamObj, unknown08) == 0x08, "");
static_assert(offsetof(StreamObj, unknown10) == 0x10, "");
static_assert(offsetof(StreamObj, unknown18) == 0x18, "");
static_assert(offsetof(StreamObj, unknown40) == 0x40, "");
static_assert(offsetof(StreamObj, unknown44) == 0x44, "");
static_assert(offsetof(StreamObj, unknown48) == 0x48, "");
static_assert(offsetof(StreamObj, unknown4c) == 0x4c, "");
static_assert(offsetof(StreamObj, unknown50) == 0x50, "");

} // namespace renderer
} // namespace ptlib
