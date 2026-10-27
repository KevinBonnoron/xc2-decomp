#pragma once
#include <stddef.h>

#include "layer/layer_obj_work.h"
#include "types.h"

namespace grlib {
class CGLibDblUniformBlock;
} // namespace grlib

namespace layer {

// Inferred layout of a draw entry; original member names unknown.
struct LyrDrawData {
  u8 _00[0x04];
  u16 unknown04; // Inferred role: vertex index; original member name unknown.
  u16 unknown06; // Inferred role: draw index; original member name unknown.
  u32 unknown08; // Inferred role: index of the first texture entry; original member name unknown.
  u8 unknown0c;  // Inferred role: texture count; original member name unknown.
  u8 unknown0d;  // Inferred role: draw call index; original member name unknown.
  u8 _0e[0x10 - 0x0e];
};

static_assert(offsetof(LyrDrawData, unknown0d) == 0x0d, "");
static_assert(sizeof(LyrDrawData) == 0x10, "");

// Inferred layout of a mesh entry; original member names unknown.
struct LyrMeshData {
  u8 _00[0x18];
  u16 unknown18; // Inferred role: first draw entry; original member name unknown.
  u16 unknown1a; // Inferred role: draw entry count; original member name unknown.
};

static_assert(offsetof(LyrMeshData, unknown1a) == 0x1a, "");

class LayerObjDraw : public LayerObjWork {
public:
  void renderMesh(grlib::CGLibDblUniformBlock *uniform, const LyrMeshData *mesh);
  void draw_call_onm_def(grlib::CGLibDblUniformBlock *uniform, const LyrDrawData *draw);
  void draw_call_onm_tex(grlib::CGLibDblUniformBlock *uniform, const LyrDrawData *draw);
  void draw_call_res_def(grlib::CGLibDblUniformBlock *uniform, const LyrDrawData *draw);
  void draw_call_icon(grlib::CGLibDblUniformBlock *uniform, const LyrDrawData *draw);
  void draw_call_number(grlib::CGLibDblUniformBlock *uniform, const LyrDrawData *draw);
  void draw_call_hdr(grlib::CGLibDblUniformBlock *uniform, const LyrDrawData *draw);
  void draw_call_res_tex(grlib::CGLibDblUniformBlock *uniform, const LyrDrawData *draw);

  static void (LayerObjDraw::*s_pCallDraw[])(grlib::CGLibDblUniformBlock *uniform, const LyrDrawData *draw);
};

} // namespace layer
