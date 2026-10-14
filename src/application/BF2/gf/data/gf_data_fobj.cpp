#include "gf/data/gf_data_fobj.h"
#include "bdat.h"

namespace gf {

const char *GfDataFobj::getFobjModelName(u32 fobj) {
  u8 *bdat = Bdat::getFP("RSC_dropitemList");
  const char *modelName = nullptr;
  if (bdat != nullptr) {
    modelName = reinterpret_cast<const char *>(Bdat::getValCheck(bdat, "mdo", fobj, 7));
  }

  if (modelName == nullptr) {
    modelName = "";
  }

  return modelName;
}

} // namespace gf
