#pragma once
#include <stddef.h>

#include "grlib/cglib_vtx_vertex.h"
#include "ptlib/renderer/particle_renderer_stream.h"
#include "types.h"

namespace grlib {
class CGLibSampler;
} // namespace grlib

namespace ptlib {

struct DrDrawWorkInfoEF;

namespace renderer {

// Layout evidence: constructor 0x710093fc24, init 0x710093fd30, lockStream 0x710094002c.
class StreamObjKizuna {
public:
  ~StreamObjKizuna();
  void release();
  void releaseSub();
  void *lockStream(const DrDrawWorkInfoEF *info);
  void unlockStream(const DrDrawWorkInfoEF *info);
  grlib::CGLibSampler *getSampler(u32 clamp);
  grlib::CGLibSampler *getSampler(u32 clampS, u32 clampT);

  grlib::CGLibVtxVertex unknown00; // Inferred role: vertex buffer; original member name unknown.
  STREAM_SIZE_TYPE unknown28;      // Inferred role: size type; original member name unknown.
  u32 unknown2c;                   // Inferred role: count; original member name unknown.
  u16 unknown30;                   // Inferred role: flags; original member name unknown.
  bool unknown32;                  // Inferred role: valid; original member name unknown.
  void *unknown38;                 // Inferred role: locked buffer; original member name unknown.
};

static_assert(offsetof(StreamObjKizuna, unknown28) == 0x28, "");
static_assert(offsetof(StreamObjKizuna, unknown2c) == 0x2c, "");
static_assert(offsetof(StreamObjKizuna, unknown30) == 0x30, "");
static_assert(offsetof(StreamObjKizuna, unknown32) == 0x32, "");
static_assert(offsetof(StreamObjKizuna, unknown38) == 0x38, "");

} // namespace renderer
} // namespace ptlib
