#include "dr/dr_man.h"
#include "dr/dr_mdl_obj.h"
#include "dr/dr_res_mdo_inst_mdl_info.h"
#include "dr/dr_res_mdo_inst_mdl_obj.h"
#include "mm_math/mm_mat44.h"
#include "mm_mtl/fixstr.h"
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

void DrResMdoInstMdlInfo::update(DrResMdlInstMdlArg &arg) {
  if (unknown120 & (2 << DrMan::s_nDblIdx | 1)) {
    unknown120 |= 1;
    return;
  }
  const unknown001 *header = reinterpret_cast<const unknown001 *>(unknown118);
  arg.unknown20 = unknown10.c_str();
  arg.unknown28 = unknown118;
  arg.unknown40 = reinterpret_cast<const unknown761 *>(unknown118 + header->unknown00);
  for (int i = 0; i < header->unknown04; i++) {
    arg.unknown30 = reinterpret_cast<const char *>(unknown118 + arg.unknown40->unknown04);
    arg.unknown38 = unknown118 + arg.unknown40->unknown00;
    arg.unknown48 = reinterpret_cast<const unknown762 *>(unknown118 + header->unknown10) + arg.unknown40->unknown08;
    arg.unknown50 = reinterpret_cast<const mm::Mat44 *>(unknown118 + header->unknown0c) + arg.unknown40->unknown08;
    for (int j = 0; j < arg.unknown40->unknown0c; j++) {
      unknown08[j + arg.unknown40->unknown08].update(arg);
      arg.unknown50++;
      arg.unknown48++;
    }
    arg.unknown40++;
  }
}

} // namespace ml
