#pragma once
#include <stddef.h>

#include "grlib/cglib_dbl_uniform_block.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_mat44.h"
#include "types.h"

namespace grlib {
class CGLibDepthBuffer;
class CGLibRenderTarget;
} // namespace grlib

namespace ml {
class IDrDrawWorkInfo;
} // namespace ml

namespace cloud {

enum CldTileType {};

class CloudCalcParams {
public:
  // One tiled-cache state per (buffer, tile type); beginTile/endTile select [unknown498][type].
  // Inferred role: tiled cache state; original type name unknown.
  struct unknown001 {
    u32 unknown00; // Inferred role: tile width; original member name unknown.
    u32 unknown04; // Inferred role: tile height; original member name unknown.
    u8 unknown08;  // Inferred role: tiled cache enabled; original member name unknown.
    u8 _09[0x0c - 0x09];
  };

  static_assert(offsetof(unknown001, unknown08) == 0x08, "");
  static_assert(sizeof(unknown001) == 0x0c, "");

  CloudCalcParams();
  ~CloudCalcParams();
  void apply(const ml::IDrDrawWorkInfo *workInfo);
  void parmUpdate();
  void end();
  void setMainRenderTarget();
  const f32 *getFogTbl() const;
  f32 getShadowOfs(u32 index) const;
  void *getShadowTex(u32 index);
  const mm::Mat44 &getShadowMatrix(u32 index) const;
  void setMainRenderTargetAndDepth(bool isDepth, bool isSecondDepth);
  void setPlnReductionTarget(bool isDepth);
  void setMdlReductionTarget();
  void setSkyReductionTarget();
  void setMdlZBuffReductionTarget(bool isSky);
  void beginTile(CldTileType type);
  void endTile(CldTileType type);

  ml::IDrDrawWorkInfo *unknown00; // Inferred role: draw work info; original member name unknown.
  mm::Mat44 unknown10;            // Inferred role: projection copy; original member name unknown.
  mm::Mat44 unknown50;            // Inferred role: view projection; original member name unknown.
  mm::Mat44 unknown90;            // Inferred role: copy of unknown50; original member name unknown.
  mm::Mat44 unknownd0;            // Inferred role: sky vertex uniform matrix; original member name unknown.
  mm::Mat44 unknown110;           // Inferred role: global fog uniform matrix; original member name unknown.
  f32 unknown150;                 // Inferred role: original member name unknown.
  f32 unknown154;                 // Inferred role: original member name unknown.
  f32 unknown158;                 // Inferred role: original member name unknown.
  u8 _15c[0x170 - 0x15c];
  f32 unknown170; // Inferred role: cloud density; original member name unknown.
  u8 _174[0x180 - 0x174];
  f32 unknown180; // Inferred role: original member name unknown.
  u8 _184[0x188 - 0x184];
  f32 unknown188; // Inferred role: original member name unknown.
  u8 _18c[0x190 - 0x18c];
  f32 unknown190;  // Inferred role: original member name unknown.
  f32 unknown194;  // Inferred role: height; original member name unknown.
  f32 unknown198;  // Inferred role: original member name unknown.
  u32 unknown19c;  // Inferred role: cld num; original member name unknown.
  bool unknown1a0; // Inferred role: original member name unknown.
  u8 _1a1[0x1b8 - 0x1a1];
  mm::Col3 unknown1b8[2]; // Inferred role: plane cols; original member name unknown.
  f32 unknown1d0;         // Inferred role: cloud color blended by updateCloudParams; original member name unknown.
  f32 unknown1d4;         // Inferred role: cloud color blended by updateCloudParams; original member name unknown.
  f32 unknown1d8;         // Inferred role: cloud color copied by updateCloudParams (version 0x1001); original member name unknown.
  f32 unknown1dc;         // Inferred role: cloud color blended by updateCloudParams; original member name unknown.
  f32 unknown1e0[20];     // Inferred role: cloud colors blended by updateCloudParams; original member name unknown.
  f32 unknown230[8];      // Inferred role: cloud colors copied by updateCloudParams (version 0x1001); original member name unknown.
  u8 _250[0x254 - 0x250];
  f32 unknown254[6];  // Inferred role: cloud colors blended by updateCloudParams; original member name unknown.
  f32 unknown26c;     // Inferred role: cloud color blended by updateCloudParams; original member name unknown.
  f32 unknown270;     // Inferred role: cloud color blended by updateCloudParams; original member name unknown.
  f32 unknown274;     // Inferred role: cloud color copied by updateCloudParams; original member name unknown.
  f32 unknown278;     // Inferred role: cloud color blended by updateCloudParams; original member name unknown.
  f32 unknown27c[20]; // Inferred role: cloud colors blended by updateCloudParams; original member name unknown.
  u8 _2cc[0x2f0 - 0x2cc];
  f32 unknown2f0[3]; // Inferred role: cloud colors blended by updateCloudParams; original member name unknown.
  f32 unknown2fc;    // Inferred role: sky color; original member name unknown.
  f32 unknown300;    // Inferred role: sky color; original member name unknown.
  f32 unknown304;    // Inferred role: sky color; original member name unknown.
  f32 unknown308;    // Inferred role: sky color; original member name unknown.
  f32 unknown30c;    // Inferred role: sky color; original member name unknown.
  f32 unknown310;    // Inferred role: sky color; original member name unknown.
  f32 unknown314;    // Inferred role: sky color copied by updateCloudParams (version 0x1001); original member name unknown.
  f32 unknown318;    // Inferred role: sky height; original member name unknown.
  f32 unknown31c;    // Inferred role: sky height range; original member name unknown.
  f32 unknown320;    // Inferred role: sky color blended by updateCloudParams; original member name unknown.
  f32 unknown324;    // Inferred role: sky color blended by updateCloudParams; original member name unknown.
  f32 unknown328;    // Inferred role: sky color blended by updateCloudParams; original member name unknown.
  f32 unknown32c;    // Inferred role: detail uniform color; original member name unknown.
  f32 unknown330;    // Inferred role: detail uniform color; original member name unknown.
  f32 unknown334;    // Inferred role: detail uniform color; original member name unknown.
  f32 unknown338;    // Inferred role: sky parameter blended by updateCloudParams; original member name unknown.
  f32 unknown33c;    // Inferred role: sky parameter blended by updateCloudParams; original member name unknown.
  f32 unknown340;    // Inferred role: sky scale; original member name unknown.
  f32 unknown344;    // Inferred role: sky scale; original member name unknown.
  f32 unknown348;    // Inferred role: sky parameter; original member name unknown.
  f32 unknown34c;    // Inferred role: sky parameter; original member name unknown.
  f32 unknown350;    // Inferred role: sky parameter blended by updateCloudParams; original member name unknown.
  f32 unknown354;    // Inferred role: sky parameter blended by updateCloudParams; original member name unknown.
  u8 _358[0x360 - 0x358];
  f32 unknown360; // Inferred role: model color; original member name unknown.
  f32 unknown364; // Inferred role: model color; original member name unknown.
  f32 unknown368; // Inferred role: model color; original member name unknown.
  f32 unknown36c; // Inferred role: model color; original member name unknown.
  f32 unknown370; // Inferred role: model color; original member name unknown.
  f32 unknown374; // Inferred role: model color; original member name unknown.
  f32 unknown378; // Inferred role: model color blended by updateCloudParams; original member name unknown.
  f32 unknown37c; // Inferred role: model color blended by updateCloudParams; original member name unknown.
  f32 unknown380; // Inferred role: original member name unknown.
  f32 unknown384; // Inferred role: original member name unknown.
  u8 _388[0x3cc - 0x388];
  f32 unknown3cc; // Inferred role: depth range; original member name unknown.
  f32 unknown3d0; // Inferred role: sky scale; original member name unknown.
  u8 _3d4[0x3e0 - 0x3d4];
  f32 unknown3e0; // Inferred role: model color; original member name unknown.
  f32 unknown3e4; // Inferred role: model color; original member name unknown.
  f32 unknown3e8; // Inferred role: model color; original member name unknown.
  f32 unknown3ec; // Inferred role: light color and model color; original member name unknown.
  f32 unknown3f0; // Inferred role: light color and model color; original member name unknown.
  f32 unknown3f4; // Inferred role: light color and model color; original member name unknown.
  u8 _3f8[0x400 - 0x3f8];
  f32 unknown400; // Inferred role: light direction and model color; original member name unknown.
  f32 unknown404; // Inferred role: light direction and model color; original member name unknown.
  f32 unknown408; // Inferred role: light direction and model color; original member name unknown.
  u8 _40c[0x420 - 0x40c];
  grlib::CGLibRenderTarget *unknown420; // Inferred role: main render target; original member name unknown.
  u8 _428[0x438 - 0x428];
  grlib::CGLibDepthBuffer *unknown438;  // Inferred role: main depth buffer; original member name unknown.
  grlib::CGLibRenderTarget *unknown440; // Inferred role: second render target; original member name unknown.
  u8 _448[0x458 - 0x448];
  grlib::CGLibRenderTarget *unknown458; // Inferred role: third render target; original member name unknown.

  grlib::CGLibDblUniformBlock unknown460; // Inferred role: calc uniform; original member name unknown.
  u16 unknown498;                         // Inferred role: tile state index; original member name unknown.
  u8 _49a[0x49c - 0x49a];
  unknown001 unknown49c[2][3]; // Inferred role: tiled cache states; original member name unknown.
};

static_assert(offsetof(CloudCalcParams, unknown00) == 0x00, "");
static_assert(offsetof(CloudCalcParams, unknown10) == 0x10, "");
static_assert(offsetof(CloudCalcParams, unknown50) == 0x50, "");
static_assert(offsetof(CloudCalcParams, unknown90) == 0x90, "");
static_assert(offsetof(CloudCalcParams, unknownd0) == 0xd0, "");
static_assert(offsetof(CloudCalcParams, unknown110) == 0x110, "");
static_assert(offsetof(CloudCalcParams, unknown150) == 0x150, "");
static_assert(offsetof(CloudCalcParams, unknown170) == 0x170, "");
static_assert(offsetof(CloudCalcParams, unknown180) == 0x180, "");
static_assert(offsetof(CloudCalcParams, unknown188) == 0x188, "");
static_assert(offsetof(CloudCalcParams, unknown194) == 0x194, "");
static_assert(offsetof(CloudCalcParams, unknown19c) == 0x19c, "");
static_assert(offsetof(CloudCalcParams, unknown1b8) == 0x1b8, "");
static_assert(offsetof(CloudCalcParams, unknown1d0) == 0x1d0, "");
static_assert(offsetof(CloudCalcParams, unknown1d4) == 0x1d4, "");
static_assert(offsetof(CloudCalcParams, unknown1d8) == 0x1d8, "");
static_assert(offsetof(CloudCalcParams, unknown1dc) == 0x1dc, "");
static_assert(offsetof(CloudCalcParams, unknown1e0) == 0x1e0, "");
static_assert(offsetof(CloudCalcParams, unknown230) == 0x230, "");
static_assert(offsetof(CloudCalcParams, unknown254) == 0x254, "");
static_assert(offsetof(CloudCalcParams, unknown26c) == 0x26c, "");
static_assert(offsetof(CloudCalcParams, unknown270) == 0x270, "");
static_assert(offsetof(CloudCalcParams, unknown274) == 0x274, "");
static_assert(offsetof(CloudCalcParams, unknown278) == 0x278, "");
static_assert(offsetof(CloudCalcParams, unknown27c) == 0x27c, "");
static_assert(offsetof(CloudCalcParams, unknown2f0) == 0x2f0, "");
static_assert(offsetof(CloudCalcParams, unknown314) == 0x314, "");
static_assert(offsetof(CloudCalcParams, unknown320) == 0x320, "");
static_assert(offsetof(CloudCalcParams, unknown324) == 0x324, "");
static_assert(offsetof(CloudCalcParams, unknown328) == 0x328, "");
static_assert(offsetof(CloudCalcParams, unknown338) == 0x338, "");
static_assert(offsetof(CloudCalcParams, unknown33c) == 0x33c, "");
static_assert(offsetof(CloudCalcParams, unknown350) == 0x350, "");
static_assert(offsetof(CloudCalcParams, unknown354) == 0x354, "");
static_assert(offsetof(CloudCalcParams, unknown378) == 0x378, "");
static_assert(offsetof(CloudCalcParams, unknown37c) == 0x37c, "");
static_assert(offsetof(CloudCalcParams, unknown2fc) == 0x2fc, "");
static_assert(offsetof(CloudCalcParams, unknown318) == 0x318, "");
static_assert(offsetof(CloudCalcParams, unknown32c) == 0x32c, "");
static_assert(offsetof(CloudCalcParams, unknown340) == 0x340, "");
static_assert(offsetof(CloudCalcParams, unknown360) == 0x360, "");
static_assert(offsetof(CloudCalcParams, unknown380) == 0x380, "");
static_assert(offsetof(CloudCalcParams, unknown384) == 0x384, "");
static_assert(offsetof(CloudCalcParams, unknown3cc) == 0x3cc, "");
static_assert(offsetof(CloudCalcParams, unknown3d0) == 0x3d0, "");
static_assert(offsetof(CloudCalcParams, unknown3e0) == 0x3e0, "");
static_assert(offsetof(CloudCalcParams, unknown400) == 0x400, "");
static_assert(offsetof(CloudCalcParams, unknown420) == 0x420, "");
static_assert(offsetof(CloudCalcParams, unknown438) == 0x438, "");
static_assert(offsetof(CloudCalcParams, unknown440) == 0x440, "");
static_assert(offsetof(CloudCalcParams, unknown458) == 0x458, "");
static_assert(offsetof(CloudCalcParams, unknown460) == 0x460, "");
static_assert(offsetof(CloudCalcParams, unknown498) == 0x498, "");
static_assert(offsetof(CloudCalcParams, unknown49c) == 0x49c, "");
// unknown49c ends at 0x4e4; the alignas(16) Mat44 members round sizeof up to 0x4f0.
static_assert(sizeof(CloudCalcParams) == 0x4f0, "");

} // namespace cloud
