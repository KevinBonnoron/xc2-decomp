#include "dr/dr_mdo_ctl_mpf_work.h"

#include "dr/dr_res_mdo_pnt_alpha.h"

namespace ml {

DrMdoCtlMpfWork::DrMdoCtlMpfWork() {}

int DrMdoCtlMpfWork::calcRenderListWork(int count, const MdsMpfObjData *data) {
  int size = count * 0x1d0;
  return size + DrResMdoPntAlphaMan::getWrkSize(0x80);
}

void DrMdoCtlMpfWork::changeMemWork(const MdsMpfObjData *data) { unknown38 = data; }

u16 DrMdoCtlMpfWork::getObjChk(int index) { return unknown20[index].unknown20; }

} // namespace ml
