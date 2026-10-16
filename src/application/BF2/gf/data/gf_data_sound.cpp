#include "gf/data/gf_data_sound.h"

#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"

namespace gf {

void GfDataSound::getFullPath(mm::mtl::FixStr<128> &path, const char *name) { path.format("sound/se/%s%s", name, ".xsp"); }

bool GfDataSound::getFootStepSePackFile(mm::mtl::FixedVector<const char *, 2> &files, u32 footStep) {
  switch (footStep) {
  case 1:
    files.push_back("se_mov_pc_default");
    break;
  case 2:
    files.push_back("se_fld_move_nopon");
    break;
  case 3:
    files.push_back("se_fld_move_large");
    break;
  case 4:
    files.push_back("se_fld_move_hana");
    break;
  case 6:
    files.push_back("se_fld_move_beast");
    break;
  case 7:
    files.push_back("se_fld_move_float");
    break;
  case 8:
    files.push_back("se_mov_pc_default");
    files.push_back("se_mov_pc_beast");
    break;
  }

  return !files.empty();
}

const char *GfDataSound::getSeFileByWeaponType(u32 weaponType) {
  static const char *const seFiles[] = {
      "",
      "se_btl_dr_sworda",
      "se_btl_dr_lsword",
      "se_btl_dr_wring",
      "se_btl_dr_toraa",
      "se_btl_dr_torab",
      "se_btl_dr_torac",
      "se_btl_dr_wsword",
      "se_btl_dr_gsword",
      "se_btl_dr_wsickle",
      "se_btl_dr_tomahawk",
      "se_btl_dr_lance",
      "se_btl_dr_ecannon",
      "se_btl_dr_shammer",
      "se_btl_dr_katana",
      "se_btl_dr_bitball",
      "se_btl_dr_kcrow",
      "se_btl_dr_swordd",
      "se_btl_dr_lkatana",
      "se_btl_dr_tonfa",
  };

  if (weaponType >= sizeof(seFiles) / sizeof(seFiles[0])) {
    return "";
  }

  return seFiles[weaponType];
}

} // namespace gf
