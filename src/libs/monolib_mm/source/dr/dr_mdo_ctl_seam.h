#pragma once
#include <stddef.h>

#include "dr/dr_mdl_obj.h"
#include "dr/dr_res_mdo_inst_anm_obj.h"
#include "types.h"

namespace ml {

struct MdsSeamEtcPosData {
  u32 objNameOffset;
  u32 effNameOffset;
  f32 range;
  u32 matrixMax;
  u32 matrixOffset;
  f32 nearClips[2];
  f32 farClips[2];
  u32 groupsOffset;
};

static_assert(offsetof(MdsSeamEtcPosData, matrixOffset) == 0x10, "");
static_assert(offsetof(MdsSeamEtcPosData, nearClips) == 0x14, "");
static_assert(offsetof(MdsSeamEtcPosData, farClips) == 0x1c, "");
static_assert(offsetof(MdsSeamEtcPosData, groupsOffset) == 0x24, "");

struct DrSeamEtcPos {
  const MdsSeamEtcPosData *data;
  bool isAlwaysDisp;
};

static_assert(sizeof(DrSeamEtcPos) == 0x10, "");

struct DrSeamEtcPosList {
  DrSeamEtcPos *objs;
  u32 objMax;
};

class DrMdoCtlSeam : public DrMdlObj {
public:
  u8 _190[0x698 - 0x190];
  DrResMdoInstAnmObj m_instAnmObj;
  u8 _6a8[0x6c8 - 0x6a8];
  DrSeamEtcPosList m_etcPosList;
};

static_assert(offsetof(DrMdoCtlSeam, m_instAnmObj) == 0x698, "");
static_assert(offsetof(DrMdoCtlSeam, m_etcPosList) == 0x6c8, "");

class DrMdoCtlSeamAll : public DrMdoCtlSeam {
public:
  bool isReadSafe() const;
};

} // namespace ml
