#include "gf/field/gf_field_lod.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_game_flag.h"

namespace gf {

constexpr int unknown002 = 0x9631; // Inferred role: first game flag of the anim reverse states; original name unknown.
constexpr int unknown003 = 0x9230; // Inferred role: first game flag of the fade states; original name unknown.

int GfFieldLod::findBdatIdByLodId(u16 lodId) const {
  for (u64 i = 0; i < 0x400; i++) {
    if (unknown08[i] == lodId) {
      return unknown808 + static_cast<int>(i);
    }
  }
  return unknown808 - 1;
}

bool GfFieldLod::isAnimReverse(int bdatId) const { return GfGameFlag::getLocal(1, bdatId + unknown002 - unknown808) != 0; }

bool GfFieldLod::isFadeOut(int bdatId) const {
  int top = unknown808;
  return GfGameFlag::getLocal(1, bdatId + unknown003 - top) == 0;
}

bool GfFieldLod::isAnimReverseOfInit(int bdatId) { return Bdat::getFlagVal(GfDataBdat::getFP(BDAT_FLD_LODLIST), "flag", bdatId, "AnimReverse") != 0; }

bool GfFieldLod::isVisibleOfInit(int bdatId) { return Bdat::getFlagVal(GfDataBdat::getFP(BDAT_FLD_LODLIST), "flag", bdatId, "Visible") != 0; }

} // namespace gf
