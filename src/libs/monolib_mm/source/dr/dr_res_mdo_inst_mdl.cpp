#include "dr/dr_man.h"
#include "dr/dr_mdl_obj.h"
#include "dr/dr_res_mdo_inst_mdl_info.h"
#include "dr/dr_res_mdo_inst_mdl_obj.h"
#include "types.h"

namespace ml {

DrResMdoInstMdlObj::DrResMdoInstMdlObj() : unknown00(nullptr), unknown08(0) {}

DrResMdoInstMdlObj::~DrResMdoInstMdlObj() {
  if (unknown00 != nullptr) {
    unknown00->setDeleteCall(DrMan::s_nDblStockIdx);
    unknown00 = nullptr;
  }
}

void DrResMdoInstMdlObj::releaseWork() {
  if (unknown00 != nullptr) {
    unknown00->setDeleteCall(DrMan::s_nDblStockIdx);
    unknown00 = nullptr;
  }
}

void DrResMdoInstMdlObj::releaseCall() {
  if (unknown00 != nullptr) {
    unknown00->setDeleteCall(DrMan::s_nDblStockIdx);
  }
}

DrResMdoInstMdlInfo::DrResMdoInstMdlInfo() : unknown120(0) {
  unknown00 = 0;
  unknown08 = nullptr;
}

DrResMdoInstMdlInfo::~DrResMdoInstMdlInfo() {
  for (int i = 0; i < unknown00; i++) {
    unknown08[i].releaseWork();
  }
  unknown00 = 0;
}

void DrResMdoInstMdlInfo::releaseWork() {
  for (int i = 0; i < unknown00; i++) {
    unknown08[i].releaseWork();
  }
  unknown00 = 0;
}

int DrResMdoInstMdlInfo::calcWorkSize(const u8 *resource) {
  const unknown001 *header = reinterpret_cast<const unknown001 *>(resource);
  return header->unknown08 * sizeof(DrResMdoInstMdlObj) + sizeof(DrResMdoInstMdlInfo);
}

void DrResMdoInstMdlInfo::release(DrResMdoInstMdlInfo *&info) {
  info->releaseWork();
  info = nullptr;
}

void DrResMdoInstMdlInfo::releaseCall() {
  for (int i = 0; i < unknown00; i++) {
    unknown08[i].releaseCall();
  }
  unknown00 = 0;
  unknown120 |= 2 << DrMan::s_nDblStockIdx;
}

} // namespace ml
