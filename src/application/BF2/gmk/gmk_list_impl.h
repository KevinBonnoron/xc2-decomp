#pragma once
#include "bdat.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_list.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace gmk {

template <typename T, typename BDAT_INFO, u32 MAGIC, u32 VERSION, typename GOB>
bool TGmkList<T, BDAT_INFO, MAGIC, VERSION, GOB>::initGmkBdatInfo(BDAT_INFO &bdatInfo, int &index, const AGmkBase &gmk) {
  if (createInfo.unknown114.empty()) {
    return false;
  }
  const char *name = gmk.unknown08.unknown10->unknown00;
  if (name == nullptr || name[0] == '\0') {
    return false;
  }
  u8 *bdat = getBindedBdatFp();
  int top = Bdat::getIdTop(bdat);
  int end = top + Bdat::getIdCount(bdat);
  int found = -1;
  for (int id = top; id < end; id++) {
    const char *rowName = reinterpret_cast<const char *>(Bdat::getValCheck(bdat, "name", id, BDAT_TYPE_STRING));
    if (rowName == nullptr) {
      continue;
    }
    if (__builtin_strcmp(rowName, name) == 0) {
      found = id;
      break;
    }
  }
  if (found >= 0) {
    index = found;
    bdatInfo.create(getBindedBdatFp(), found, gmk);
    return true;
  }
  return false;
}

} // namespace gmk
