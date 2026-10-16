#include "event/form_manager.h"

#include "bdat.h"

namespace event {

FormManager::FormManager() {}

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
