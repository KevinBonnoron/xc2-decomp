#include "event/form_manager.h"

#include "bdat.h"
#include "fw/fw_coli_check.h"
#include "mm_math/mm_vec3.h"

namespace event {

FormManager::FormManager() {}

void FormManager::adjestPosY(mm::Vec3 &position) {
  mm::Vec3 result = position;
  mm::Vec3 start;
  start.x = position.x;
  start.y = position.y + 1.0f;
  start.z = position.z;
  if (fw::ColiCheck::getSnapPos(result, start, 6.0f, 0xffffffff)) {
    position = result;
  }
}

u32 FormManager::getReplaceNum(u32 id) const {
  unsigned char *bdat = Bdat::getFP("EVT_formation");
  u32 end = Bdat::getIdTop(bdat) + Bdat::getIdCount(bdat);
  u32 count = 0;
  if (id < end) {
    for (count = 0; id + count < end; count++) {
      u32 row = id + count;
      const char *name = Bdat::getVal(bdat, "name", row).valueString;
      if (row > id && name[0] != '\0') {
        break;
      }
    }
  }
  return count;
}

void FormManager::OnEventProc(MSG_TYPE type) {}

} // namespace event
