#pragma once
#include <stddef.h>

#include "nvn/nvn.h"

struct NVNcommandBuffer;

namespace grlib {

class CGLibShader_plf;

class CGLibPipeline {
public:
  static const int COLOR_TARGET_NUM = 8;
  static const int VERTEX_STREAM_NUM = 8;

  void setDefaults();
  void relase();
  void begin();
  void updateVertex();
  CGLibPipeline();
  ~CGLibPipeline();

  NVNcommandBuffer *unknown00;                       // Inferred role: cmd buf; original member name unknown.
  NVNblendState unknown08;                           // Inferred role: blend state; original member name unknown.
  NVNchannelMaskState unknown10;                     // Inferred role: channel mask default; original member name unknown.
  NVNchannelMaskState unknown14;                     // Inferred role: color buffer on; original member name unknown.
  NVNchannelMaskState unknown18;                     // Inferred role: color buffer off; original member name unknown.
  NVNcolorState unknown1c;                           // Inferred role: color state default; original member name unknown.
  NVNcolorState unknown20;                           // Inferred role: blend off; original member name unknown.
  NVNcolorState unknown24;                           // Inferred role: blend on; original member name unknown.
  NVNdepthStencilState unknown28;                    // Inferred role: depth stencil state; original member name unknown.
  NVNpolygonState unknown30;                         // Inferred role: culling off; original member name unknown.
  NVNpolygonState unknown34;                         // Inferred role: culling front; original member name unknown.
  NVNpolygonState unknown38;                         // Inferred role: culling back; original member name unknown.
  NVNpolygonState unknown3c;                         // Inferred role: culling disp off; original member name unknown.
  NVNpolygonState unknown40;                         // Inferred role: point mode; original member name unknown.
  NVNpolygonState unknown44;                         // Inferred role: line mode; original member name unknown.
  NVNpolygonState unknown48;                         // Inferred role: triangle; original member name unknown.
  NVNvertexStreamState unknown50[VERTEX_STREAM_NUM]; // Inferred role: vertex streams; original member name unknown.
  int unknown90;                                     // Inferred role: vertex stream max; original member name unknown.
  bool unknown94;                                    // Inferred role: vertex stream dirty; original member name unknown.
  CGLibShader_plf *_98;
};

static_assert(offsetof(CGLibPipeline, unknown08) == 0x08, "");
static_assert(offsetof(CGLibPipeline, unknown14) == 0x14, "");
static_assert(offsetof(CGLibPipeline, unknown1c) == 0x1c, "");
static_assert(offsetof(CGLibPipeline, unknown28) == 0x28, "");
static_assert(offsetof(CGLibPipeline, unknown30) == 0x30, "");
static_assert(offsetof(CGLibPipeline, unknown50) == 0x50, "");
static_assert(offsetof(CGLibPipeline, unknown90) == 0x90, "");
static_assert(offsetof(CGLibPipeline, _98) == 0x98, "");

} // namespace grlib
