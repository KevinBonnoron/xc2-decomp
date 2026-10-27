#pragma once
#include <stddef.h>

#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_one_uniform_block.h"
#include "grlib/cglib_render_target.h"
#include "layer/layer_obj.h"
#include "layer/layer_obj_manager.h"
#include "types.h"

namespace layer {

class LayerObjTopMemObj : public LayerObj {
public:
  ~LayerObjTopMemObj() override;
  void releaseWorkBuffer();
  void resourceInit() override;
  void *getBuffer();
  void updateBufer();
  void setRender(bool render);
  bool isRender() const;
  void setupRender();
  void lastRender();
  void finalRender();

  u8 _250[0x270 - 0x250];
  u32 unknown270; // Inferred role: flags; original member name unknown.
  u8 _274[0x278 - 0x274];
  grlib::CGLibRenderTarget unknown278;       // Inferred role: render target; original member name unknown.
  grlib::CGLibDblUniformBlock unknown640;    // Inferred role: uniform block; original member name unknown.
  grlib::CGLibOneUniformBlock unknown678;    // Inferred role: uniform block; original member name unknown.
  grlib::CGLibOneUniformBlock unknown6a0[2]; // Inferred role: uniform blocks; original member name unknown.
  grlib::CGLibOneUniformBlock unknown6f0[2]; // Inferred role: uniform blocks; original member name unknown.
  u32 unknown740;                            // Inferred role: width; original member name unknown.
  u32 unknown744;                            // Inferred role: height; original member name unknown.
  u32 unknown748;                            // Inferred role: first buffer size; original member name unknown.
  u32 unknown74c;                            // Inferred role: second buffer size; original member name unknown.
  LayerMemType unknown750;                   // Inferred role: memory type; original member name unknown.
};

static_assert(offsetof(LayerObjTopMemObj, unknown270) == 0x270, "");
static_assert(offsetof(LayerObjTopMemObj, unknown278) == 0x278, "");
static_assert(offsetof(LayerObjTopMemObj, unknown640) == 0x640, "");
static_assert(offsetof(LayerObjTopMemObj, unknown678) == 0x678, "");
static_assert(offsetof(LayerObjTopMemObj, unknown6a0) == 0x6a0, "");
static_assert(offsetof(LayerObjTopMemObj, unknown6f0) == 0x6f0, "");
static_assert(offsetof(LayerObjTopMemObj, unknown740) == 0x740, "");
static_assert(offsetof(LayerObjTopMemObj, unknown748) == 0x748, "");
static_assert(offsetof(LayerObjTopMemObj, unknown750) == 0x750, "");

} // namespace layer
