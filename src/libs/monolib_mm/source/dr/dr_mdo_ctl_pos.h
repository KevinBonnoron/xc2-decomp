#pragma once
#include <stddef.h>

#include "dr/dr_mdl_obj.h"
#include "dr/dr_res_mdo_inst_anm_obj.h"
#include "types.h"

namespace ml {

class DrMdoCtlPos : public DrMdlObj {
public:
  void callZpreePassRenderPosAll();
  void callRenderPosAll();
  void callRefractionRenderPosAll();
  void callThicknessRenderFirstPosAll();
  void callThicknessRenderSecondPosAll();
  void callGBuffRenderPosAll();
  void callLightPrePassRenderPosAll();
  void callAlphaRenderPosAll();
  void callSpAlphaRenderPosAll();

  u8 _190[0x1e8 - 0x190];
  DrResMdoInstAnmObj m_instAnmObj;
};

static_assert(offsetof(DrMdoCtlPos, m_instAnmObj) == 0x1e8, "");

} // namespace ml
