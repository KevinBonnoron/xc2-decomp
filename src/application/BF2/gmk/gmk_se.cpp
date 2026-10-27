#include "gmk/gmk_se.h"

#include <math.h>

#include "bdat.h"
#include "framework/debug/debug_draw.h"
#include "framework/sound/sound_manager.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/field/gf_field_sound.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_active_list.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep
#include "gmk/gmk_set.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec3.h"

namespace gmk {

template bool TGmkList<GmkSe, GmkSe::BdatInfo, 1162104403u, 2u, GmkSeGob>::initGmkBdatInfo(GmkSe::BdatInfo &, int &, const AGmkBase &);
template bool TGmkList<GmkSeLine, GmkSe::BdatInfo, 1313621331u, 2u, GmkSeLineGobCustom>::initGmkBdatInfo(GmkSe::BdatInfo &, int &, const AGmkBase &);
template bool TGmkList<GmkSeLinePoint, GmkSeLinePoint::BdatInfo, 1414548563u, 1u, GmkSeLinePointGobCustom>::initGmkBdatInfo(GmkSeLinePoint::BdatInfo &, int &, const AGmkBase &);

template class TGmkActiveList<GmkSe>;
template class TGmkActiveList<GmkSeLine>;

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

void GmkSe::dispose() {
  disposeInst(true);
  AGmkBase::dispose();
}

void GmkSe::disposeInst(bool isFadeOut) {
  if (unknownF4 != 0) {
    fw::SoundManager::get()->stopSe(unknownF4, isFadeOut ? 1.0f : 0.0f);
    unknownF4 = 0;
    if (intoNode() && TGmkActiveList<GmkSe>::get() != nullptr) {
      TGmkActiveList<GmkSe>::get()->unknown08.erase(this);
    }
  }
}

void GmkSe::updateInActiveList(f32 deltaTime) {
  if (unknownF4 == 0) {
    return;
  }
  unknownF8 += deltaTime;
  if (unknownF8 < 1.0f || unknown100) {
    return;
  }
  const Data *data = getData();
  if (data->unknown00 <= 0.0f || gf::GfGameManager::getControlMover() == gf::INVALID_HANDLE) {
    return;
  }
  const mm::Vec3 &playerPos = gf::GfObjUtil::getObj(gf::GfGameManager::getControlMover())->getComponent<gf::GfComTransform>()->getPosition();
  const mm::Vec3 &pos = AGmkBase::unknown08.unknown08->unknown00;
  mm::Vec3 diff = pos - playerPos;
  unknownFC = sqrtf(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
  const BdatInfo *info = getBdatInfo();
  f32 volume;
  if (data->unknown00 <= unknownFC) {
    volume = info->unknown05 * 0.01f;
  } else if (unknownFC <= data->unknown04) {
    volume = info->unknown04 * 0.01f;
  } else {
    f32 rate = 0.0f;
    if (data->unknown04 < data->unknown00) {
      rate = (data->unknown00 - unknownFC) / (data->unknown00 - data->unknown04);
    }
    f32 range = (info->unknown04 - info->unknown05) * 0.01f;
    mm::clampRef(range, 0.0f, 1.0f);
    f32 minVolume = info->unknown05 * 0.01f;
    volume = rate * range + minVolume;
  }
  if (gf::GfGameManager::isRoom()) {
    volume = volume * (info->unknown08 * 0.01f);
  }
  fw::SoundManager::get()->setVolume(unknownF4, volume, 0.0f);
}

void GmkSe::debugDraw() const {
  if (!isValid() || !unknownF0) {
    return;
  }
  mm::Vec3 position = AGmkBase::unknown08.unknown08->unknown00;
  mm::Mat44 matrix;
  unknown001(matrix, position);
  const Data *data = getData();
  fw::debug::drawCircleLine(matrix, data->unknown04, mm::Col4::blue);
  fw::debug::drawCircleLine(matrix, data->unknown00, mm::Col4::red);
}

void GmkSe::createGmkPhantom() {
  if (canCreateGameEntity() && static_cast<u32>(AGmkBase::unknown08.unknown10->unknown0c - SHAPE_TYPE_SPHERE) < 3) {
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
  const GmkSet *set = AGmkBase::unknown08.unknown00->getCreateInfo().unknown08;
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

void GmkSeLine::dispose() {
  disposeInst(true);
  AGmkBase::dispose();
}

void GmkSeLine::disposeInst(bool isFadeOut) {
  if (unknown5C != 0) {
    fw::SoundManager::get()->stopSe(unknown5C, isFadeOut ? 1.0f : 0.0f);
    unknown5C = 0;
    if (intoNode() && TGmkActiveList<GmkSeLine>::get() != nullptr) {
      TGmkActiveList<GmkSeLine>::get()->unknown08.erase(this);
    }
  }
}

GmkSeLine::GmkSeLine() : IntrusiveListNode(), unknown58(false), unknown59(false), unknown5C(0), unknown60(0.0f), unknown64(0), unknown68(false) {}

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
