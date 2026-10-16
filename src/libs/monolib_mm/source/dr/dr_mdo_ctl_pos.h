#pragma once
#include <stddef.h>

#include "dr/dr_mdl_obj.h"
#include "dr/dr_res_mdo_inst_anm_obj.h"
#include "types.h"

namespace ml {

class DrMdoCtlPos : public DrMdlObj {
public:
  u8 _164[0x1e8 - 0x164];
  DrResMdoInstAnmObj m_instAnmObj;
};

static_assert(offsetof(DrMdoCtlPos, m_instAnmObj) == 0x1e8, "");

} // namespace ml
