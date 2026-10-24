#pragma once
#include <stddef.h>

#include "dr/dr_mdl_obj.h"
#include "dr/dr_res_mdo_inst_anm_obj.h"
#include "types.h"

namespace ml {

struct MdsSeamEtcPosData {
  u32 unknown00;    // Inferred role: object name offset; original member name unknown.
  u32 unknown04;    // Inferred role: eff name offset; original member name unknown.
  f32 unknown08;    // Inferred role: range; original member name unknown.
  u32 unknown0c;    // Inferred role: matrix max; original member name unknown.
  u32 unknown10;    // Inferred role: matrix offset; original member name unknown.
  f32 unknown14[2]; // Inferred role: near clips; original member name unknown.
  f32 unknown1c[2]; // Inferred role: far clips; original member name unknown.
  u32 unknown24;    // Inferred role: groups offset; original member name unknown.
};

static_assert(offsetof(MdsSeamEtcPosData, unknown10) == 0x10, "");
static_assert(offsetof(MdsSeamEtcPosData, unknown14) == 0x14, "");
static_assert(offsetof(MdsSeamEtcPosData, unknown1c) == 0x1c, "");
static_assert(offsetof(MdsSeamEtcPosData, unknown24) == 0x24, "");

struct DrSeamEtcPos {
  const MdsSeamEtcPosData *unknown00; // Inferred role: data; original member name unknown.
  bool unknown08;                     // Inferred role: always disp; original member name unknown.
};

static_assert(sizeof(DrSeamEtcPos) == 0x10, "");

struct DrSeamEtcPosList {
  DrSeamEtcPos *unknown00; // Inferred role: objs; original member name unknown.
  u32 unknown08;           // Inferred role: object max; original member name unknown.
};

class DrMdoCtlSeam : public DrMdlObj {
public:
  u8 _190[0x698 - 0x190];
  DrResMdoInstAnmObj unknown698; // Inferred role: inst anm object; original member name unknown.
  u8 _6a8[0x6c8 - 0x6a8];
  DrSeamEtcPosList unknown6c8; // Inferred role: etc pos list; original member name unknown.
};

static_assert(offsetof(DrMdoCtlSeam, unknown698) == 0x698, "");
static_assert(offsetof(DrMdoCtlSeam, unknown6c8) == 0x6c8, "");

class DrMdoCtlSeamAll : public DrMdoCtlSeam {
public:
  bool isReadSafe() const;
  void callZPrePassSeamAll();
  void callThicknessFirstSeamAll();
  void callThicknessSecondSeamAll();
  void callRenderSeamAll();
  void callGBuffRenderSeamAll();
  void callLightPrePassRenderSeamAll();
  void callAlphaRenderSeamAll();
  void callSpAlphaRenderSeamAll();
  void callRefractionRenderSeamAll();
  void callRenderSeamEnvMap();
  void callGBuffRenderSeamEnvMap();
  void callLightPrePassRenderSeamEnvMap();
  void callAlphaRenderSeamEnvMap();
  void callSpAlphaRenderSeamEnvMap();
  void callRefractionRenderSeamEnvMap();
};

} // namespace ml
