#pragma once
#include <stddef.h>

#include "grlib/cglib_sampler.h"
#include "grlib/cglib_vtx_fetch.h"
#include "grlib/cglib_vtx_index.h"
#include "grlib/cglib_vtx_instans.h"
#include "grlib/cglib_vtx_vertex.h"
#include "types.h"

namespace ptlib {

class StaticAllocObj;

namespace renderer {

// Layout evidence: constructor 0x710093e200 (member offsets), initVtxIndex 0x710093ed18 (u16 tables at 0x648, 0x690, 0x6d8, each indexed [6][6]).
class EffStateManager {
public:
  EffStateManager();
  ~EffStateManager();
  static EffStateManager *get();
  void initSampler();
  void init(StaticAllocObj *allocator);
  void initVtxFetch();
  void initVtxIndex();
  void begin();

  grlib::CGLibSampler unknown00[27];  // Inferred role: samplers indexed by clamp s + t * 3 + r * 9; original member name unknown.
  grlib::CGLibSampler unknown360;     // Inferred role: depth compare sampler; original member name unknown.
  grlib::CGLibSampler unknown380;     // Inferred role: border sampler; original member name unknown.
  grlib::CGLibSampler unknown3a0;     // Inferred role: sampler; original member name unknown.
  grlib::CGLibSampler unknown3c0;     // Inferred role: sampler; original member name unknown.
  grlib::CGLibSampler unknown3e0;     // Inferred role: sampler; original member name unknown.
  grlib::CGLibVtxFetch unknown400[7]; // Inferred role: vertex fetch objects; original member name unknown.
  grlib::CGLibVtxFetch unknown470[7]; // Inferred role: instance vertex fetch objects; original member name unknown.
  grlib::CGLibVtxFetch unknown4e0;    // Inferred role: vertex fetch object; original member name unknown.
  grlib::CGLibVtxFetch unknown4f0;    // Inferred role: vertex fetch object; original member name unknown.
  grlib::CGLibVtxVertex unknown500;   // Inferred role: vertex buffer; original member name unknown.
  grlib::CGLibVtxVertex unknown528;   // Inferred role: vertex buffer; original member name unknown.
  grlib::CGLibVtxIndex unknown550;    // Inferred role: index buffer; original member name unknown.
  grlib::CGLibVtxIndex unknown578[4]; // Inferred role: index buffers indexed by stream index type; original member name unknown.
  grlib::CGLibVtxInstans unknown618;  // Inferred role: instance buffer; original member name unknown.
  u16 unknown648[6][6];               // Inferred role: offset table; original member name unknown.
  u16 unknown690[6][6];               // Inferred role: offset table; original member name unknown.
  u16 unknown6d8[6][6];               // Inferred role: offset table; original member name unknown.
};

static_assert(offsetof(EffStateManager, unknown360) == 0x360, "");
static_assert(offsetof(EffStateManager, unknown3e0) == 0x3e0, "");
static_assert(offsetof(EffStateManager, unknown400) == 0x400, "");
static_assert(offsetof(EffStateManager, unknown470) == 0x470, "");
static_assert(offsetof(EffStateManager, unknown4f0) == 0x4f0, "");
static_assert(offsetof(EffStateManager, unknown500) == 0x500, "");
static_assert(offsetof(EffStateManager, unknown550) == 0x550, "");
static_assert(offsetof(EffStateManager, unknown578) == 0x578, "");
static_assert(offsetof(EffStateManager, unknown618) == 0x618, "");
static_assert(offsetof(EffStateManager, unknown648) == 0x648, "");
static_assert(offsetof(EffStateManager, unknown690) == 0x690, "");
static_assert(offsetof(EffStateManager, unknown6d8) == 0x6d8, "");
static_assert(sizeof(EffStateManager) == 0x720, "");

} // namespace renderer
} // namespace ptlib
