#pragma once
#include <stddef.h>

#include "dr/dr_mdl_obj.h"
#include "dr/dr_res_mdo_inst_anm_obj.h"
#include "types.h"

namespace ml {

class DrMdoCtlPos : public DrMdlObj {
public:
  void callDisplistPrePsssRender(int param);
  void callDisplistRender(int param);
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
  DrResMdoInstAnmObj unknown1e8; // Inferred role: inst anm object; original member name unknown.
};

static_assert(offsetof(DrMdoCtlPos, unknown1e8) == 0x1e8, "");

} // namespace ml
