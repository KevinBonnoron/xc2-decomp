#include "gmk/gmk_se.h"

#include "bdat.h"
#include "framework/debug/debug_draw.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/field/gf_field_sound.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_set.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_vec3.h"

namespace gmk {

void GmkSe::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown00 = Bdat::getFlagVal(bdat.unknown00, "flag", id, "se_type") != 0;
  unknown01 = Bdat::getFlagVal(bdat.unknown00, "flag", id, "play_once") != 0;
  unknown02 = bdat.getValCheck("seName", id, BDAT_TYPE_U16);
  unknown04 = bdat.getValCheck("volumeMAX", id, BDAT_TYPE_U8);
  unknown05 = bdat.getValCheck("volumeMIN", id, BDAT_TYPE_U8);
  unknown0a = ScenarioFlagCond(bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_U16), bdat.getValCheck("ScenarioFlagMax", id, BDAT_TYPE_U16));
  unknown0e = QuestFlagCond(bdat.getValCheck("QuestFlag", id, BDAT_TYPE_U16), bdat.getValCheck("QuestFlagMin", id, BDAT_TYPE_U8), bdat.getValCheck("QuestFlagMax", id, BDAT_TYPE_U8));
  unknown06 = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  u16 popTime = bdat.getValCheck("SEpopTime", id, BDAT_TYPE_U16);
  unknown18.unknown08 = popTime;
  unknown28.unknown08 = bdat.getValCheck("wtrSEType", id, BDAT_TYPE_U8);
  unknown38 = BootedGmkCond(bdat, id, nullptr);
  unknown3c = BootedGmkCond(bdat, id, "OP_");
  unknown08 = bdat.getValCheck("InRoom_volume", id, BDAT_TYPE_U8);
}

bool GmkSe::BdatInfo::isPopCondMatched() const {
  if (unknown0a.isEnable() && !unknown0a.isMatch()) {
    return false;
  }
  if (unknown0e.isEnable() && !unknown0e.isMatch()) {
    return false;
  }
  if (unknown06 != 0 && !gf::GfGameCond::isGameCond(unknown06)) {
    return false;
  }
  if (unknown18.isEnable() && !unknown18.isMatch()) {
    return false;
  }
  if (unknown28.isEnable() && !unknown28.isMatch()) {
    return false;
  }
  if (unknown38.isEnable() && !unknown38.isMatch()) {
    return false;
  }
  if (unknown3c.isEnable() && unknown3c.isMatch()) {
    return false;
  }
  return true;
}

fw::SoundPack *GmkSe::BdatInfo::getSoundPack() const {
  if (unknown00) {
    return gf::GfFieldSound::get()->getMapPack();
  }
  return gf::GfFieldSound::get()->getCommonPack();
}

GmkType GmkSeLinePoint::getGmkType() const { return GMK_TYPE; }

bool GmkSeLinePoint::isValid() const { return unknown08.unknown00 != nullptr && unknown20.unknown08 != nullptr; }

GmkType GmkSe::getGmkType() const { return GMK_TYPE; }

void GmkSe::createGmkPhantom() {
  if (canCreateGameEntity() && static_cast<u32>(unknown08.unknown10->unknown0c - SHAPE_TYPE_SPHERE) < 3) {
    unknown60.create(*this, nullptr, false);
  }
}

bool GmkSe::canPopInst() const {
  if (unknownF4 != 0) {
    return false;
  }
  if (!unknownF0) {
    return false;
  }
  if (unknown60.unknown78 != nullptr && !unknown60.unknown83) {
    return false;
  }
  return true;
}

bool GmkSe::canDepopInst() const {
  if (unknownF4 != 0) {
    if (!unknownF0) {
      return true;
    }
    if (unknown60.unknown78 != nullptr && !unknown60.unknown83) {
      return true;
    }
  }
  return false;
}

GmkType GmkSeLine::getGmkType() const { return GMK_TYPE; }

void GmkSeLine::debugDraw() const {
  if (!isValid()) {
    return;
  }
  u32 pointNum = getPointNum();
  if (pointNum == 0) {
    return;
  }
  mm::Vec3 prevPos;
  mm::Vec3 currentPos;
  mm::Col4 color = unknown58 ? mm::Col4::yellow : mm::Col4::gray;
  for (u32 i = 1; i < pointNum; i++) {
    const AGmkBase *prev = getPoint(i - 1);
    if (prev == nullptr) {
      continue;
    }
    prevPos = *reinterpret_cast<const mm::Vec3 *>(prev->unknown20.unknown08);
    const AGmkBase *current = getPoint(i);
    if (current == nullptr) {
      continue;
    }
    currentPos = *reinterpret_cast<const mm::Vec3 *>(current->unknown20.unknown08);
    fw::debug::drawLine(prevPos, currentPos, color);
  }
}

const AGmkBase *GmkSeLine::getPoint(u32 index) const {
  const GmkSet *set = unknown08.unknown00->getCreateInfo().unknown08;
  if (set == nullptr) {
    return nullptr;
  }
  IGmkList *list = set->unknown1b8[GMK_TYPE_SE_LINE_POINT];
  if (list == nullptr) {
    return nullptr;
  }
  u32 instNum = list->getInstNum();
  u32 listIndex = getData()->unknown0c + index;
  if (instNum <= listIndex) {
    return nullptr;
  }
  const AGmkBase *point = list->getInst(listIndex);
  if (point == nullptr) {
    return nullptr;
  }
  return point->getGmkType() == GMK_TYPE_SE_LINE_POINT ? point : nullptr;
}

bool GmkSeLine::getPointPos(mm::Vec3 &position, u32 index) const {
  const AGmkBase *point = getPoint(index);
  if (point == nullptr) {
    return false;
  }
  const mm::Vec3 *pointPos = reinterpret_cast<const mm::Vec3 *>(point->unknown20.unknown08);
  position = *pointPos;
  return true;
}

GmkSeLine::GmkSeLine() : unknown48(), unknown58(false), unknown59(false), unknown5C(0), unknown60(0.0f), unknown64(0), unknown68(false) {}

int GmkSeLine::getPointNum() const { return getData()->unknown1c - getData()->unknown0c; }

bool GmkSeLine::isPlayerInsideAabb() const {
  if (gf::GfGameManager::getControlMover() == gf::INVALID_HANDLE) {
    return false;
  }
  const mm::Vec3 &position = gf::GfObjUtil::getObj(gf::GfGameManager::getControlMover())->getComponent<gf::GfComTransform>()->getPosition();
  const Data *data = getData();
  return data->unknown00 <= position.x && position.x < data->unknown10 && data->unknown04 <= position.y && position.y < data->unknown14 && data->unknown08 <= position.z &&
         position.z < data->unknown18;
}

bool GmkSeLine::canPopInst() const {
  if (unknown5C == 0 && unknown58) {
    return isPlayerInsideAabb();
  }
  return false;
}

bool GmkSeLine::canDepopInst() const {
  if (unknown5C != 0) {
    if (!unknown58) {
      return true;
    }
    return !isPlayerInsideAabb();
  }
  return false;
}

} // namespace gmk
