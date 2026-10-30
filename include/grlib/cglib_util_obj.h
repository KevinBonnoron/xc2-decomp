#pragma once
#include <stddef.h>

#include "grlib/cglib_dec_shader.h"
#include "grlib/cglib_sampler.h"
#include "grlib/cglib_vtx_fetch.h"
#include "grlib/cglib_vtx_index.h"
#include "grlib/cglib_vtx_vertex.h"

namespace grlib {

// Layout evidence: the constructor (0x71007abee4) and release (0x71007ac0cc) construct or release members at
// 0x0, 0x68, 0x78, 0x88, 0x98, 0xb8, 0xd8 and 0x100; the sizes follow from the member types.
class CGLibUtilObj {
public:
  CGLibUtilObj();
  ~CGLibUtilObj();
  void setup();
  void release();

  CGLibDecShader unknown00;   // Inferred role: copy shader; original member name unknown.
  CGLibVtxFetch unknown68[3]; // Inferred role: vertex fetches; original member name unknown.
  CGLibSampler unknown98[2];  // Inferred role: util samplers; original member name unknown.
  CGLibVtxVertex unknownd8;   // Inferred role: copy vertex buffer; original member name unknown.
  CGLibVtxIndex unknown100;   // Inferred role: copy index buffer; original member name unknown.
};

static_assert(offsetof(CGLibUtilObj, unknown68) == 0x68, "");
static_assert(offsetof(CGLibUtilObj, unknown98) == 0x98, "");
static_assert(offsetof(CGLibUtilObj, unknownd8) == 0xd8, "");
static_assert(offsetof(CGLibUtilObj, unknown100) == 0x100, "");
static_assert(sizeof(CGLibUtilObj) == 0x128, "");

} // namespace grlib
