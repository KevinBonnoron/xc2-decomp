// No game string names this file: named after DrGlobalIBLPack, its own translation unit in the game (DrGlobalIBLMan calls its functions out of line).
#include "dr/dr_global_ibl_man.h"
#include "dr/dr_light_man.h"
#include "dr/dr_light_obj_global_ibl.h"
#include "dr/dr_man.h"
#include "dr/dr_shd_lgt_global_ibl.h"
#include "dr/dr_shd_lgt_man.h"
#include "grlib/cglib_vtl_mem_pool.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace ml {

void DrGlobalIBLPack::setup() {}

bool DrGlobalIBLPack::checkFileType(const void *data) {
  const u32 *header = static_cast<const u32 *>(data);
  if (header[0] == 0x4c424947) {
    return header[1] == 10100 || header[1] == 20000;
  }
  return false;
}

DrGlobalIBLPack::DrGlobalIBLPack(const void *data, int index) : unknown08(nullptr), unknown10(nullptr), unknown18(index), unknown20(data), unknown50(0), unknown54(0), unknown58(1) {}

DrGlobalIBLPack::~DrGlobalIBLPack() {
  for (u32 i = 0; i < unknown28.size(); i++) {
    if (unknown28[i] != nullptr) {
      delete unknown28[i];
      unknown28[i] = nullptr;
    }
  }
  unknown28.destroy();
  unknown60.release();
}

void DrGlobalIBLPack::release() {
  DrMan *man = DrMan::getIns();
  for (u32 i = 0; i < unknown28.size(); i++) {
    man->unknown588->unknowne8->unknown58->removeObj(unknown28[i], unknown18);
  }
}

void DrGlobalIBLPack::update() {
  DrMan *man = DrMan::getIns();
  if ((unknown50 ^ unknown54) & FLAG_UNKNOWN_0) {
    if (unknown50 & FLAG_UNKNOWN_0) {
      for (u32 i = 0; i < unknown28.size(); i++) {
        man->unknown588->unknowne8->unknown58->removeObj(unknown28[i], unknown18);
      }
    } else {
      for (u32 i = 0; i < unknown28.size(); i++) {
        man->unknown588->unknowne8->unknown58->addObj(unknown28[i], unknown18);
      }
    }
  }
  if (!(unknown50 & FLAG_UNKNOWN_0)) {
    for (u32 i = 0; i < unknown28.size(); i++) {
      unknown28[i]->update();
    }
  }
  unknown54 = unknown50;
}

} // namespace ml
