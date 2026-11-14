#include "gf/field/gf_field_map_gimmick.h"

#include "bdat.h"
#include "dr/dr_man.h"
#include "framework/script/script_manager.h"
#include "framework/sound/sound_manager.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/field/gf_field_lod.h"
#include "gf/field/gf_field_sound.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "gf/menu/gf_menu_common_window_param.h"
#include "gf/menu/gf_menu_field_skill.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/object/component/gimmick/gf_com_behavior_gmk.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "gf/scom/gf_scom_obj.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_grave.h"
#include "gmk/gmk_jump.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_map_gimmick.h"
#include "gmk/gmk_warp.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/array.h"

namespace gf {

constexpr u32 OBJ_UNKNOWN_7_2 = 7;                                       // Inferred role: obj attribute targetable; original name unknown.
constexpr u16 COMMON_UNKNOWN_51 = 0x33;                                  // Inferred role: common window grave; original name unknown.
const ml::FILE_PRIO FILE_PRIO_UNKNOWN_7 = static_cast<ml::FILE_PRIO>(7); // Inferred role: gmk tutorial file prio; original name unknown.

AFieldSeq::AFieldSeq(const GfSetupParam &) : unknown08(unknown020), unknown10(nullptr), m_end(false), unknown21(false) {}

void AFieldSeq::gevMapjump(GEV event, const MapjumpCallbackInfo &) {
  if (event == GEV_UNKNOWN_1) {
    dispose();
  }
}

gmk::AGmkBase *AFieldSeq::findBindedGmk() const { return gmk::getBindedGmkInst(unknown08); }

void AFieldSeq::create(GF_OBJ_HANDLE *handle) {
  dispose();
  this->unknown08 = handle;
  unknown10 = &AFieldSeq::seqCheckFs;
}

void AFieldSeq::dispose() {
  m_end = false;
  unknown21 = false;
  unknown08 = unknown020;
  unknown10 = nullptr;
}

void AFieldSeq::update(f32 deltaTime) {
  if (unknown08 != unknown020 && unknown10) {
    (this->*unknown10)(deltaTime);
  }
}

void AFieldSeq::setTargetable(bool isTargetable) {
  GfObj *obj = GfObjUtil::getObj(unknown08);
  if (obj != nullptr) {
    if (isTargetable) {
      obj->unknown110 |= OBJ_UNKNOWN_7_2;
    } else {
      obj->unknown110 &= ~OBJ_UNKNOWN_7_2;
    }
  }
}

bool AFieldSeq::isTargetable() const {
  GfObj *obj = GfObjUtil::getObj(unknown08);
  return obj != nullptr ? (obj->unknown110 >> 2) & 1 : false;
}

void AFieldSeq::seqWaitUIEnd(f32) {
  if (GfMenuFieldSkill::isRunning()) {
    return;
  }

  if (unknown21) {
    GfObjAcc acc(unknown08);
    if (acc.isValid()) {
      GfComBehaviorGmk *behavior = acc.getObj()->getComponent<GfComBehaviorGmk>();
      if (behavior != nullptr) {
        behavior->disposeMenuObj();
      }
    }
    onFsSucceeded();
  } else {
    onFsFailed();
  }
  unknown10 = nullptr;
  m_end = true;
}

void GfFieldMapGimmick::BdatInfo::create(CBdatWrapper bdat, int id) {
  unknown00 = bdat.getValCheck("OP_Condition", id, gmk::BDAT_TYPE_UNKNOWN_2);
  unknown06 = gmk::BootedGmkCond(bdat, id, "OP_");
  unknown0a = gmk::ScenarioFlagCond(bdat, id, "OP_");
  unknown0e = gmk::QuestFlagCond(bdat, id, "OP_");
  unknown18.unknown08 = static_cast<u16>(bdat.getValCheck("OP_Time", id, gmk::BDAT_TYPE_UNKNOWN_2));
  unknown28.unknown08 = bdat.getValCheck("OP_weather", id, gmk::BDAT_TYPE_UNKNOWN_1);
  unknown02 = bdat.getValCheck("camGim_ATR", id, gmk::BDAT_TYPE_UNKNOWN_1);
  unknown03 = Bdat::getFlagVal(bdat.unknown00, "flag", id, "gmkCamPos") != 0;
  unknown04 = Bdat::getFlagVal(bdat.unknown00, "flag", id, "nowaitGmkCam") != 0;
}

bool GfFieldMapGimmick::BdatInfo::isCondMatched() const {
  if (unknown00 != 0 && !GfGameCond::isGameCond(unknown00)) {
    return false;
  }
  if (unknown06.isEnable() && !unknown06.isMatch()) {
    return false;
  }
  if (unknown0a.isEnable() && !unknown0a.isMatch()) {
    return false;
  }
  if (unknown0e.isEnable() && !unknown0e.isMatch()) {
    return false;
  }
  if (unknown18.isEnable() && !unknown18.isMatch()) {
    return false;
  }
  if (unknown28.isEnable() && !unknown28.isMatch()) {
    return false;
  }
  return true;
}

GfFieldMapGimmick::GfFieldMapGimmick(const GfSetupParam &param)
    : AFieldSeq(param), unknownb0(nullptr), unknown210(nullptr), unknown220(nullptr), unknown230(0), unknown234(0), unknown238(nullptr), unknown248(0.0f), unknown24c(0.0f), unknown4d0(0) {}

void GfFieldMapGimmick::setDispOfParty(bool isDisp, bool isExceptMover) {
  GF_OBJ_HANDLE *mover = GfGameManager::getControlMover();
  for (u32 i = 0; i < 3; i++) {
    GF_OBJ_HANDLE *driver = GfGameParty::getHandleDriver(i);
    if (!isExceptMover || mover != driver) {
      GfObjAcc(driver).setDisp(OBJDISP_UNKNOWN_4, isDisp);
    }
    GF_OBJ_HANDLE *blade = GfGameParty::getHandleBlade(i, -1);
    if (!isExceptMover || mover != blade) {
      GfObjAcc(blade).setDisp(OBJDISP_UNKNOWN_4, isDisp);
    }
  }
}

void GfFieldMapGimmick::create(GF_OBJ_HANDLE *handle) {
  AFieldSeq::create(handle);
  gmk::AGmkBase *gmk = findBindedGmk();
  if (gmk != nullptr) {
    CBdatWrapper bdat = gmk->unknown004();
    int id = gmk->unknown20.unknown18;
    unknown30.create(bdat, id);
    if (!isTargetable() || unknown30.isCondMatched()) {
      {
        gmk::GmkAcc::CreateInfo accInfo;
        accInfo.validate(*gmk);
        unknown68.create(accInfo);
      }
      const char *camName = reinterpret_cast<const char *>(bdat.getValCheck("gmkCamName", id, gmk::BDAT_TYPE_UNKNOWN_7));
      if (camName == nullptr || *camName == '\0') {
        return;
      }
      gmk::GmkCamera::CreateInfo camInfo;
      camInfo.unknown00 = camName;
      if (unknown30.unknown02 != 0) {
        camInfo.unknown104 = unknown30.unknown02;
      }
      camInfo.unknown105 = false;
      if (unknown30.unknown03) {
        if (unknown234 > 0) {
          camInfo.validateTransform(static_cast<u16>(unknown234));
        } else {
          camInfo.validateTransform(unknown08);
        }
      }
      unknownb0.create(camInfo);
      unknown210 = &GfFieldMapGimmick::seqCamera_waitToLoaded;
      return;
    }
    MenuCommonWindowParam param;
    param.unknown10 = GfDataBdat::getFP(BDAT_FLD_HELPMS);
    param.unknown18 = static_cast<u16>(bdat.getValCheck("missMSG_ID", id, gmk::BDAT_TYPE_UNKNOWN_2));
    GfPlayFactory::createCommonMessage(param);
  }
  dispose();
  m_end = true;
}

void GfFieldMapGimmick::seqCamera_waitToLoaded(f32) {
  if (unknownb0.isLoaded()) {
    unknown210 = &GfFieldMapGimmick::seqCamera_waitToEnd;
  }
}

void GfFieldMapGimmick::dispose() {
  clearSe();
  unknown238 = nullptr;
  unknown230 = 0;
  unknown234 = 0;
  unknown220 = nullptr;
  unknown210 = nullptr;
  unknownb0.dispose();
  AFieldSeq::dispose();
}

void GfFieldMapGimmick::clearSe() {
  for (u32 i = 0; i < 5; i++) {
    unknown250[i].dispose();
  }
  if (unknown4d0 != 0) {
    if (fw::SoundManager::get()->isLoop(unknown4d0)) {
      fw::SoundManager::get()->stopSe(unknown4d0, 0.0f);
    }
    unknown4d0 = 0;
  }
}

bool GfFieldMapGimmick::isEnd() const { return AFieldSeq::isEnd() && !unknown210 && !unknown220 && !unknown238; }

void GfFieldMapGimmick::update(f32 deltaTime) {
  if (unknown08 == unknown020) {
    return;
  }
  bool isEnded = isEnd();
  if (unknownb0.unknown10.unknown00.length() > 0) {
    unknownb0.update(deltaTime);
    if (unknown210) {
      (this->*unknown210)(deltaTime);
    }
    if (unknown210 == &GfFieldMapGimmick::seqCamera_waitToLoaded) {
      return;
    }
  }
  AFieldSeq::update(deltaTime);
  if (unknown220) {
    (this->*unknown220)(deltaTime);
  }
  if (unknown238) {
    (this->*unknown238)(deltaTime);
  }
  if (!isEnded && isEnd()) {
    setSolvedMapGimmick();
  }
}

void GfFieldMapGimmick::setSolvedMapGimmick() {
  if (unknown21) {
    const gmk::GmkMapGimmick *gmk = static_cast<const gmk::GmkMapGimmick *>(unknown68.unknown38);
    if (gmk != nullptr) {
      SCOM_QUEST_GIMMICK::createMapGimmick(gmk->unknown20.unknown18, 0.0f);
      gmk->setSolved();
    }
  }
}

void GfFieldMapGimmick::onFsSucceeded() {
  if (unknownb0.unknown10.unknown00.length() > 0) {
    unknownb0.play();
  }
  unknown230 = 1;
  unknown220 = &GfFieldMapGimmick::seqLod_init;
  unknown238 = &GfFieldMapGimmick::seqMapObj_init;
}

void GfFieldMapGimmick::seqLod_init(f32) {
  const gmk::AGmkBase *gmk = unknown68.unknown38;
  u8 *bdat = gmk->getBindedBdatFp();
  int id = gmk->unknown20.unknown18;
  mm::mtl::FixStr<32> name;
  name.format("G%d_LODmodel", unknown230);
  unknown234 = static_cast<u16>(Bdat::getValCheck(bdat, name.c_str(), id, gmk::BDAT_TYPE_UNKNOWN_2));
  if (unknown234 == 0) {
    unknown220 = nullptr;
    if (unknown30.unknown04) {
      setSolvedMapGimmick();
    }
    return;
  }
  name.format("G%d_LODanime_play", unknown230);
  u8 play = Bdat::getValCheck(bdat, name.c_str(), id, gmk::BDAT_TYPE_UNKNOWN_1);
  u32 switchId = 0;
  switch (play) {
  case 0:
    GfFieldLod::get()->setFade(unknown234, false, false);
    unknown220 = &GfFieldMapGimmick::seqLod_waitToElapseTime;
    break;
  case 4:
    switchId = 1;
    break;
  case 5:
    switchId = 2;
    break;
  case 6:
    switchId = 3;
    break;
  default: {
    bool isSkip = false;
    bool isReverse = false;
    switch (play) {
    case 2:
      isReverse = true;
      break;
    case 3:
      isSkip = true;
      break;
    }
    if (GfFieldLod::get()->setAnimReverse(unknown234, isReverse, isSkip)) {
      gmk::applyLodFade(unknown234, isSkip);
      unknown220 = &GfFieldMapGimmick::seqLod_waitToEndAnim;
    } else {
      static_cast<const gmk::GmkMapGimmick *>(gmk)->validateEffectWithoutLodControl(unknown234, false);
      unknown220 = &GfFieldMapGimmick::seqLod_waitToElapseTime;
    }
    break;
  }
  }
  if (switchId != 0) {
    GfFieldLod::get()->setLodSwitchId(unknown234, switchId);
    unknown220 = &GfFieldMapGimmick::seqLod_waitToElapseTime;
  }
  name.format("nextwait%d", unknown230);
  unknown248 = static_cast<s16>(Bdat::getValCheck(bdat, name.c_str(), id, gmk::BDAT_TYPE_UNKNOWN_5));
  unknown24c = 0.0f;
  name.format("G%d_LOD_SE", unknown230);
  s16 seId = Bdat::getValCheck(bdat, name.c_str(), id, gmk::BDAT_TYPE_UNKNOWN_2);
  if (seId != 0) {
    gmk::GmkCtrlVolSe::CreateInfo info;
    name.format("G%d_LOD_SE_type", unknown230);
    if (Bdat::getFlagVal(bdat, "flag", id, name.c_str()) != 0) {
      info.unknown00 = GfFieldSound::get()->getMapPack();
    } else {
      info.unknown00 = GfFieldSound::get()->getCommonPack();
    }
    name.format("G%d_LOD_size", unknown230);
    u8 distance = Bdat::getValCheck(bdat, name.c_str(), id, gmk::BDAT_TYPE_UNKNOWN_1);
    info.unknown08 = seId;
    info.unknown10 = distance;
    info.unknown14 = distance;
    info.unknown20 = gmk->unknown08.unknown08->unknown00;
    unknown250[unknown230 - 1].create(info);
  }
}

void GfFieldMapGimmick::onFsFailed() { unknown210 = nullptr; }

void GfFieldMapGimmick::seqCamera_waitToEnd(f32) {
  if (unknownb0.isEnd()) {
    unknown210 = nullptr;
  }
}

void GfFieldMapGimmick::seqLod_waitToElapseTime(f32 deltaTime) {
  unknown24c += deltaTime;
  if (unknown24c < unknown248) {
    return;
  }
  if (unknown230 < 5) {
    unknown230++;
    unknown220 = &GfFieldMapGimmick::seqLod_init;
  } else {
    unknown220 = nullptr;
    if (unknown30.unknown04) {
      setSolvedMapGimmick();
    }
  }
}

void GfFieldMapGimmick::seqLod_waitToEndAnim(f32) {
  if (GfFieldLod::get()->isPlayAnimEnd(unknown234)) {
    unknown220 = &GfFieldMapGimmick::seqLod_waitToElapseTime;
  }
}

void GfFieldMapGimmick::seqMapObj_nextwait(f32 deltaTime) {
  unknown24c += deltaTime;
  if (unknown24c < unknown248) {
    return;
  }
  unknown238 = nullptr;
  if (unknown30.unknown04) {
    setSolvedMapGimmick();
  }
}

GfFieldGrave::GfFieldGrave(const GfSetupParam &) : unknown10(unknown020), unknown20(nullptr) {}

void GfFieldGrave::gevMapjump(GEV event, const MapjumpCallbackInfo &) {
  if (event == GEV_UNKNOWN_1) {
    dispose();
  }
}

void GfFieldGrave::create(GF_OBJ_HANDLE *handle) {
  dispose();
  this->unknown10 = handle;
  GfMenuManager::openCommonWindow(COMMON_UNKNOWN_51);
  unknown20 = &GfFieldGrave::seqWaitToSelect;
}

void GfFieldGrave::seqWaitToSelect(f32) {
  if (!GfMenuManager::isOpenCommonWindow()) {
    s16 result = GfMenuManager::getCommonWindowResult();
    if (result == 0) {
      gmk::GmkGrave *grave = static_cast<gmk::GmkGrave *>(gmk::getBindedGmkInst(unknown10));
      if (grave == nullptr) {
        dispose();
      } else {
        grave->reqPopEnemy();
      }
    }
    unknown20 = nullptr;
    m_end = true;
  }
}

void GfFieldGrave::dispose() {
  if (GfMenuManager::isOpenCommonWindow()) {
    GfMenuManager::closeCommonWindow();
  }
  m_end = false;
  unknown10 = unknown020;
  unknown20 = nullptr;
}

void GfFieldGrave::update(f32 deltaTime) {
  if (unknown20) {
    (this->*unknown20)(deltaTime);
  }
}

void GfFieldJump::onFsSucceeded() {
  gmk::GmkJump *jump = static_cast<gmk::GmkJump *>(gmk::getBindedGmkInst(unknown08));
  if (jump != nullptr) {
    GfObj *obj = GfObjUtil::getObj(unknown08);
    if (obj != nullptr) {
      obj->unknown110 |= OBJ_UNKNOWN_7;
    }
    GfObj *mover = GfObjUtil::getObj(GfGameManager::getControlMover());
    if (mover != nullptr) {
      GfObj *self = GfObjUtil::getObj(unknown08);
      if (self != nullptr) {
        switch (jump->getBdatInfo()->unknown02) {
        case 0: {
          MsgPcFieldNotifyWallJump message;
          message.unknown10 = jump->unknown097()->unknown00[1];
          message.unknown20 = jump->getBindedBdatFp();
          message.unknown28 = jump->unknown20.unknown18;
          message.unknown2c = jump->unknown20.unknown18;
          self->sendMessage(mover, message);
          return;
        }
        case 1: {
          MsgPcFieldNotifyBigJump message;
          message.unknown10 = jump->unknown097()->unknown00[1];
          message.unknown20 = jump->unknown097()->unknown00[1].unknown0c;
          message.unknown24 = jump->unknown097()->unknown20;
          message.unknown28 = jump->unknown097()->unknown24;
          message.unknown30 = jump->getBindedBdatFp();
          message.unknown38 = jump->unknown20.unknown18;
          message.unknown3c = jump->unknown20.unknown18;
          self->sendMessage(mover, message);
          return;
        }
        default:
          break;
        }
      }
    }
  }
  dispose();
}

void GfFieldWarp::onFsSucceeded() {
  gmk::GmkWarp *warp = static_cast<gmk::GmkWarp *>(gmk::getBindedGmkInst(unknown08));
  if (warp != nullptr) {
    GfObj *obj = GfObjUtil::getObj(unknown08);
    if (obj != nullptr) {
      obj->unknown110 |= OBJ_UNKNOWN_7_2;
    }
    GfObj *mover = GfObjUtil::getObj(GfGameManager::getControlMover());
    if (mover != nullptr) {
      GfObj *self = GfObjUtil::getObj(unknown08);
      if (self != nullptr) {
        MsgPcFieldNotifyWarp message;
        const gmk::GmkWarp::unknown004 *points = warp->unknown005();
        const f32 *position = unknown08 == warp->unknown50[0] ? points[1].unknown00 : points[0].unknown00;
        message.unknown10.x = position[0];
        message.unknown10.y = position[1];
        message.unknown10.z = position[2];
        message.unknown20 = unknown08 == warp->unknown50[0] ? points[1].unknown0c : points[0].unknown0c;
        message.unknown28 = warp->getBindedBdatFp();
        message.unknown30 = warp->unknown20.unknown18;
        message.unknown34 = warp->unknown20.unknown18;
        self->sendMessage(mover, message);
        return;
      }
    }
  }
  dispose();
}

void GfFieldGmkTutorial::build(const GfSetupParam &) {
  // __LINE__ must be 1226 as in the original file: its value changes the instruction order.
#line 1226
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfFieldGmkTutorial();
}

void GfFieldGmkTutorial::destroy() {
  GfFieldGmkTutorial *gmkTutorial = get();
  gmkTutorial->dispose();
  delete gmkTutorial;
}

void GfFieldGmkTutorial::dispose() {
  unknown50 = 0;
  unknown0c.clear();
}

void GfFieldGmkTutorial::create(const char *name, u32 tutorial) {
  dispose();
  unknown0c = name;
  this->unknown50 = tutorial;
  fw::ScriptManager::get()->loadScript(unknown08, name, FILE_PRIO_UNKNOWN_7);
  fw::ScriptManager::get()->unknown20[unknown08].start();
}

bool GfFieldGmkTutorial::isEnd() const { return fw::ScriptManager::get()->unknown20[unknown08].isFinish(); }

void GfFieldGmkTutorial::gevMapjump(GEV event, const MapjumpCallbackInfo &) {
  if (event == GEV_UNKNOWN_1) {
    dispose();
  }
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfFieldMapGimmick>::~PtrSingleton();
