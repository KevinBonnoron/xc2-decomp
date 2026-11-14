#include "dr/dr_mdo_morphing.h"

#include "dr/dr_man.h"
#include "dr/dr_mdo_mat.h"
#include "dr/dr_res_etc_params.h"
#include "dr/dr_res_mdo_morp_obj.h"
#include "dr/dr_res_mdo_vertex.h"
#include "dr/dr_res_shd.h"
#include "dr/dr_shd_data_list.h"
#include "dr/dr_shd_data_obj.h"
#include "dr/dr_shd_man.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_ctl_vertex.h"
#include "grlib/cglib_one_uniform_block.h"
#include "grlib/cglib_polygon.h"
#include "grlib/cglib_uniform_array.h"

namespace ml {

DrMdoMorphing::DrMdoMorphing(MdoWrkMatRes *matRes, DrResMdoMorpObj *morpObj, DrResEtcPamObj *pamObj) : unknown00(matRes), unknown08(morpObj), unknown10(pamObj) {}

DrMdoMorphing::~DrMdoMorphing() {}

void DrMdoMorphing::updateParms() {
  if (unknown08->unknown00 != 0) {
    return;
  }
  unknown1c = -1;
  for (u32 i = 0; i < unknown08->unknown10; i++) {
    DrResMdoMorpObj::unknown004 &entry = unknown08->unknown08[i];
    u32 description = entry.unknown18->unknown08;
    if ((description & 0xffff) == 7) {
      entry.unknown00 = unknown10->unknown10[description >> 16].getParams();
    }
  }
}

void DrMdoMorphing::resetDefVertex() {
  const u8 *base = reinterpret_cast<const u8 *>(unknown00->unknownc8->unknown28);
  const unknown051 *mofBlend = reinterpret_cast<const unknown051 *>(base + unknown00->unknownc8->unknown28->unknown28);
  const unknown137 *entry = reinterpret_cast<const unknown137 *>(base + mofBlend->unknown04);
  const unknown050 *infos = reinterpret_cast<const unknown050 *>(base + mofBlend->infoOffset);
  DrShdDataList *list = DrMan::getIns()->unknown80->unknown00;
  grlib::CGLibPolygon::setRasterizer(1);
  DrResShdStreamOut *stmOut = list->getStmOutObj(5);
  int prevDeclaration = -1;
  for (int i = 0; i < mofBlend->unknown00; i++, entry++) {
    s8 declaration = entry->unknown10;
    if (declaration != prevDeclaration) {
      stmOut->unknown00->setDeclarationIdx(0, declaration);
      stmOut->setupStreamShader(0);
      prevDeclaration = declaration;
    }
    u32 next = entry->unknown04 + 1;
    grlib::CGLibCtlVertex::setUniformVertex((*unknown00->unknowna8)[next], 0x20, 0, 0, 0);
    (*unknown00->unknowna8)[entry->unknown04].setStorageBuffer(0);
    grlib::CGLibCtlVertex::renderVertex(GRL_PRIMITIVE_POINTS, infos[next].unknown04);
  }
  grlib::CGLibPolygon::setRasterizer(0);
  grlib::CGLibCtlShader::setMemoryBarrierBit(1);
}

void DrMdoMorphing::oldPosVertex() {
  const u8 *base = reinterpret_cast<const u8 *>(unknown00->unknownc8->unknown28);
  const unknown051 *mofBlend = reinterpret_cast<const unknown051 *>(base + unknown00->unknownc8->unknown28->unknown28);
  const unknown137 *entry = reinterpret_cast<const unknown137 *>(base + mofBlend->unknown04);
  const unknown050 *infos = reinterpret_cast<const unknown050 *>(base + mofBlend->infoOffset);
  DrShdDataList *list = DrMan::getIns()->unknown80->unknown00;
  grlib::CGLibPolygon::setRasterizer(1);
  DrResShdStreamOut *stmOut = list->getStmOutObj(8);
  stmOut->setupStreamShader(0);
  for (int i = 0; i < mofBlend->unknown00; i++, entry++) {
    u32 next = entry->unknown04 + 1;
    grlib::CGLibCtlVertex::setUniformVertex((*unknown00->unknowna8)[next], 0x20, 0, 0, 0);
    (*unknown00->unknowna8)[entry->unknown04].setStorageBuffer(0);
    grlib::CGLibCtlVertex::renderVertex(GRL_PRIMITIVE_POINTS, infos[next].unknown04);
  }
  grlib::CGLibPolygon::setRasterizer(0);
  grlib::CGLibCtlShader::setMemoryBarrierBit(1);
}

int DrMdoMorphing::isBlendCheck() const {
  int result = 0;
  int state = 0;
  for (u32 i = 0; i < unknown08->unknown10; i++) {
    const DrResMdoMorpObj::unknown004 &entry = unknown08->unknown08[i];
    if (entry.unknown04 == entry.unknown00) {
      if (entry.unknown00 != 0.0f) {
        state = 2;
        if (result == 1) {
          return 2;
        }
      }
    } else {
      if (state == 2) {
        return 2;
      }
      if (entry.unknown00 != 0.0f) {
        return 2;
      }
      result = 1;
    }
  }
  return result;
}

void DrMdoMorphing::parmsUpdate() {
  for (u32 i = 0; i < unknown08->unknown10; i++) {
    unknown08->unknown08[i].unknown04 = unknown08->unknown08[i].unknown00;
  }
}

} // namespace ml
