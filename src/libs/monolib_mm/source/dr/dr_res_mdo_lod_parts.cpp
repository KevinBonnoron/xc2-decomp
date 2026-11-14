#include "dr/dr_res_mdo_lod_parts.h"

namespace ml {

f32 DrResMdoLodParts::PIXEL_RATIO[4] = {0.04f, 0.007f, 0.003f, 0.001f};

DrResMdoLodParts::DrResMdoLodParts() : unknown00(0), unknown08(0), unknown10(1.0f), unknown14(0), unknown18(nullptr) {}

void DrResMdoLodParts::setup(const MdsMdlLodData *lodData) { unknown18 = lodData; }

void DrResMdoLodParts::calcPixel(const DrResMdlLodArg &arg, bool &isDisp) {
  u32 flags = unknown14;
  unknown14 &= ~0x30;
  if ((flags & 2) != 0 && !arg.unknown10) {
    if ((flags & 4) != 0) {
      isDisp = true;
      unknown14 |= 0x20;
    }
    return;
  }
  if (arg.unknown10) {
    if ((unknown14 & 2) != 0) {
      if ((unknown14 & 4) != 0) {
        unknown10 = 1.0f;
      } else {
        unknown10 = 0.0f;
      }
    }
    unknown14 &= ~0xe;
  }
  if (!isDisp && arg.unknown18 >= unknown18->unknown10) {
    isDisp = true;
    unknown14 |= 0x20;
  }
}

void DrResMdoLodParts::calcAutoPixel(const DrResMdlLodArg &arg, bool &isDisp) {
  u32 flags = unknown14;
  unknown14 &= ~0x30;
  if ((flags & 2) != 0 && !arg.unknown10) {
    if ((flags & 4) != 0) {
      isDisp = true;
      unknown14 |= 0x20;
    }
    return;
  }
  if (arg.unknown10) {
    if ((unknown14 & 2) != 0) {
      if ((unknown14 & 4) != 0) {
        unknown10 = 1.0f;
      } else {
        unknown10 = 0.0f;
      }
    }
    unknown14 &= ~0xe;
  }
  if (!isDisp && arg.unknown18 >= PIXEL_RATIO[unknown18->unknown15]) {
    isDisp = true;
    unknown14 |= 0x20;
  }
}

} // namespace ml

// The game builds these files in one unit with this one, in this order (0x710086e64c to 0x710088f99c): DrResEtcParams::getParams (0x710086e558) sits before this file's block, its other functions
// after DrResMdoAlpTbl's. The seam work files (dr_res_mdo_seam_wrk_base.cpp and the files it includes) inline functions of the files before them: DrResMdoPos::release (0x7100872660),
// DrResMdoSeamParmRead::setStockTexList, DrResMdoPntAlphaMan::setup and DrResMdoAlpTbl::updateInstace.
// clang-format off
#include "dr_res_mdo_lod_grp.cpp"
#include "dr_res_mdo_lod_obj.cpp"
#include "dr_res_mdo_alp_tbl.cpp"
#include "dr_res_etc_params.cpp"
#include "dr_res_mdo_mat.cpp"
#include "dr_res_mdo_shd_obj.cpp"
#include "dr_res_mdo_morp_obj.cpp"
#include "dr_res_mdo_pnt_alpha.cpp"
#include "dr_res_mdo_pos.cpp"
#include "dr_res_mdo_inst_anm_obj.cpp"
#include "dr_res_mdo_inst_mdl.cpp"
#include "dr_res_mdo_seam_coli.cpp"
#include "dr_res_mdo_seam_mem_man.cpp"
#include "dr_res_mdo_seam_parm_read.cpp"
#include "dr_res_mdo_seam_read.cpp"
#include "dr_res_mdo_seam_res.cpp"
#include "dr_res_mdo_vtx_mesh_obj.cpp"
#include "dr_res_mdo_seam_wrk_base.cpp"
// clang-format on
