#include "gf/menu/gf_menu_bdat.h"

namespace gf {

u8 *GfMenuBdat::s_BdatArray[7];

u8 *GfMenuBdat::getFP(u32 bdat) {
  if (bdat < 7) {
    return s_BdatArray[bdat];
  }
  return nullptr;
}

} // namespace gf
