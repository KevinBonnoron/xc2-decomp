#pragma once
#include "gmk/gmk_form.h"
#include "gmk/gmk_list.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace gmk {

template <typename FORM_PC, typename FORM_PCNPC> bool GmkForm::create(const FORM_PC &formPc) {
  dispose();
  unknown00 = formPc.getData()->unknown14 - formPc.getData()->unknown10 + 1;
  if (unknown00 > MAX_NUM) {
    unknown00 = MAX_NUM;
  } else if (unknown00 == 0) {
    return false;
  }
  const typename FORM_PC::Data *data = formPc.getData();
  unknown10[0] = data->unknown001();
  unknown70[0] = data->unknown0c;
  for (u32 i = 1; i < unknown00; i++) {
    const IGmkList *list = formPc.getBindedFormPcnpcList();
    u32 index = formPc.getData()->unknown10 + i - 1;
    list->getInstNum();
    const typename FORM_PCNPC::Data *memberData = static_cast<const FORM_PCNPC *>(list->getInst(index))->getData();
    unknown10[i] = memberData->unknown001();
    unknown70[i] = memberData->unknown0c;
  }
  validatePosRotY();
  return true;
}

} // namespace gmk
