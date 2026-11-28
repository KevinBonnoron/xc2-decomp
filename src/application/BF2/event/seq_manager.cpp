#include "event/seq_manager.h"

#include "event/bgm_manager.h"
#include "event/capture_manager.h"
#include "event/chara_obj.h"
#include "event/cmd_param.h"
#include "event/cmd_variable.h"
#include "event/cs_snd_manager.h"
#include "event/debug_manager.h"
#include "event/effect_manager.h"
#include "event/env_manager.h"
#include "event/fade_ctrl.h"
#include "event/fade_manager.h"
#include "event/fade_planner.h"
#include "event/frame_manager.h"
#include "event/hide_manager.h"
#include "event/light_manager.h"
#include "event/lipsync_manager.h"
#include "event/manager.h"
#include "event/mdlstm_manager.h"
#include "event/memory_manager.h"
#include "event/motstm_manager.h"
#include "event/movie_manager.h"
#include "event/mstxt_manager.h"
#include "event/object_chara.h"
#include "event/object_list.h"
#include "event/object_manager.h"
#include "event/object_party_list.h"
#include "event/offscr_manager.h"
#include "event/outsider_field.h"
#include "event/outsider_manager.h"
#include "event/quest_manager.h"
#include "event/res_manager.h"
#include "event/se_manager.h"
#include "event/seamless_manager.h"
#include "event/select_manager.h"
#include "event/shake_manager.h"
#include "event/skip_manager.h"
#include "event/status_manager.h"
#include "event/text_manager.h"
#include "event/ui_manager.h"
#include "event/voice_manager.h"
#include "event/volume_manager.h"
#include "fw/fw_debug.h"
#include "gf/data/gf_data_map.h"
#include "gf/data/gf_object_type.h"
#include "gf/event/gf_event.h"
#include "gf/game/gf_game_pad.h"
#include "gf/gf_pause.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_util.h"
#include "gf/request/gf_req_command.h"
#include "gf/request/gf_req_manager.h"
#include "gf/scom/gf_scom_script.h"
#include "gf/script/gf_script_manager.h"
#include "ml/dev_graph.h"
#include "ml/dev_setting.h"
#include "ml/scn.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/bitflag.h"
#include "scn/scn_render_dr_sys_parm_acc.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

constexpr u32 CATEGORY_UNKNOWN_5 = 5;    // Inferred role: category capture; original name unknown.
constexpr u32 SCRIPT_SLOT_UNKNOWN_2 = 2; // Inferred role: script slot event; original name unknown.

// Inferred role: names of the sequence categories; original name unknown.
static const char *const unknown002[] = {"NONE", "TEV", "FEV", "SEV", "CS ", "MOV"};

ICmd::RESULT SeqManager::play_start::update(const Param &param) {
  if (param.getFrame() <= 0) {
    gf::SCOM_SCRIPT::create(SCRIPT_SLOT_UNKNOWN_2, param.val(1).getStr(), false);
    SeqManager *seq = static_cast<SeqManager *>(param.val(0).getUserdata());
    seq->unknown170 &= ~FLAG_UNKNOWN_2;
    seq->unknown178 = "play start";
  }
  if (gf::GfScriptManager::isScriptLoadError(SCRIPT_SLOT_UNKNOWN_2)) {
    gf::GfScriptManager::destroyScript(SCRIPT_SLOT_UNKNOWN_2);
    static_cast<SeqManager *>(param.val(0).getUserdata())->unknown170 |= FLAG_UNKNOWN_0;
  }
  return RESULT_UNKNOWN_0;
}

ICmd::RESULT SeqManager::start::update(const Param &param) {
  if (param.getFrame() <= 0) {
    static_cast<SeqManager *>(param.val(0).getUserdata())->unknown178 = "start";
  }
  return RESULT_UNKNOWN_1;
}

ICmd::RESULT SeqManager::start_notice::update(const Param &param) {
  if (param.getFrame() <= 0) {
    static_cast<SeqManager *>(param.val(0).getUserdata())->unknown178 = "start notice";
  }
  int eventId = param.val(1).getS32();
  if (eventId != 0) {
    gf::GfEvent::callEventPlay(gf::GEV_UNKNOWN_9, eventId);
  }
  return RESULT_UNKNOWN_1;
}

ICmd::RESULT SeqManager::exec_fadeout::update(const Param &param) {
  bool isSkip = param.val(1).getBool();
  if (param.getFrame() <= 0) {
    SeqManager *seq = static_cast<SeqManager *>(param.val(0).getUserdata());
    mm::mtl::Singleton<FadeManager>::getPtr()->request(FadePlanner::TYPE_UNKNOWN_2);
    mm::mtl::Singleton<VolumeManager>::get().startSeamlessVolume(seq->m_seqInfo.unknown9c);
    seq->unknown178 = "exec fadeout";
  }
  bool isFading = mm::mtl::Singleton<FadeManager>::getPtr()->isFading();
  RESULT result = static_cast<RESULT>(!isFading);
  if (isSkip && !isFading) {
    mm::mtl::Singleton<FadeManager>::getPtr()->playEventSkip(false, 30);
    mm::mtl::Singleton<SkipManager>::getPtr()->skip(false, 0.0f);
    result = RESULT_UNKNOWN_1;
  }
  return result;
}

ICmd::RESULT SeqManager::start_fadeout::update(const Param &param) {
  if (param.getFrame() <= 0) {
    SeqManager *seq = static_cast<SeqManager *>(param.val(0).getUserdata());
    mm::mtl::Singleton<FadeManager>::getPtr()->request(FadePlanner::TYPE_UNKNOWN_0);
    mm::mtl::Singleton<VolumeManager>::get().startSeamlessVolume(seq->m_seqInfo.unknown7c);
    if (!param.val(1).getBool()) {
      mm::mtl::Singleton<BgmManager>::getPtr()->playDefaultBgm(param.val(2).getS32());
    }
    seq->unknown178 = "start fadeout";
  }
  return static_cast<RESULT>(!mm::mtl::Singleton<FadeManager>::getPtr()->isFading());
}

ICmd::RESULT SeqManager::end_wait::update(const Param &param) {
  if (param.getFrame() <= 0) {
    mm::mtl::Singleton<ObjectManager>::getPtr()->clear();
    mm::mtl::Singleton<MdlstmManager>::getPtr()->clear();
    gf::GfScriptManager::destroyScript(SCRIPT_SLOT_UNKNOWN_2);
    gf::GfEvent::callEventPlay(gf::GEV_UNKNOWN_8, 0);
    static_cast<SeqManager *>(param.val(0).getUserdata())->unknown178 = "end wait";
  }
  if (!unknown08) {
    return RESULT_UNKNOWN_0;
  }
  if (!gf::GfScriptManager::isScriptFinish(SCRIPT_SLOT_UNKNOWN_2) && gf::GfScriptManager::isScriptActive(SCRIPT_SLOT_UNKNOWN_2)) {
    return RESULT_UNKNOWN_0;
  }
  if (mm::mtl::Singleton<MemoryManager>::getPtr()->isActive()) {
    return RESULT_UNKNOWN_0;
  }
  return static_cast<RESULT>(param.getFrame() > 1);
}

ICmd::RESULT SeqManager::start_change::update(const Param &param) {
  if (param.getFrame() <= 0) {
    static_cast<SeqManager *>(param.val(0).getUserdata())->unknown178 = "start change";
  }
  if (param.val(1).getS32() != 0 && !mm::mtl::Singleton<StatusManager>::getPtr()->changeFromBdat(param.val(1).getS32())) {
    return RESULT_UNKNOWN_0;
  }
  return RESULT_UNKNOWN_1;
}

ICmd::RESULT SeqManager::start_env_seam::update(const Param &param) {
  if (param.getFrame() <= 0) {
    int eventId = param.val(1).getS32();
    mm::mtl::Singleton<EnvManager>::getPtr()->loadTransferEnvironment(eventId);
    static_cast<SeqManager *>(param.val(0).getUserdata())->unknown178 = "start envseam";
  }
  return RESULT_UNKNOWN_1;
}

ICmd::RESULT SeqManager::start_capture_wait::update(const Param &param) {
  if (param.getFrame() <= 0) {
    static_cast<SeqManager *>(param.val(0).getUserdata())->unknown178 = "start capture wait";
  }
  return param.getFrame() >= 30 ? RESULT_UNKNOWN_1 : RESULT_UNKNOWN_0;
}

// 0x710012b90c: the exec command. The game inlines the bodies of many manager methods here. Where a value (a category, a flag byte) is loaded before the guard of
// a singleton, the call is written in both arms of an `if` (`if (x) getPtr()->f(true); else getPtr()->f(false);`): SimplifyCFG hoists the guard of the two
// identical getPtr() above the test, and the inlined `f` of each arm gives the select of the game (the call form `f(x)` loads x after the guard).
ICmd::RESULT SeqManager::exec::update(const Param &param) {
  SeqManager *seq = static_cast<SeqManager *>(param.val(0).getUserdata());
  // The game loads the parameters 1, 2, 3 and 5 before the frame test (0x710012b938 to 0x710012b948) and the parameter 4 at the start of the first frame, keeping it on the stack
  // until the volume reset (0x710012b964); the locals place these loads (ruling 2; the parameter locals and isDispJiji inlined at their uses give 3801 instructions against 3804).
  bool isWaitPause = param.val(1).getBool();
  bool isFadeIn = param.val(2).getBool();
  bool isBgmSync = param.val(3).getBool();
  bool isCapture = param.val(5).getBool();
  if (param.getFrame() <= 0) {
    bool isResetVolume = param.val(4).getBool();
    if (!Manager::get()->isEndFadeOut() && (__builtin_strcmp(seq->m_seqInfo.unknown04.c_str(), "bf01010100") == 0 || __builtin_strcmp(seq->m_seqInfo.unknown04.c_str(), "bf00001001") == 0 ||
                                            __builtin_strcmp(seq->m_seqInfo.unknown04.c_str(), "bf00002001") == 0 || __builtin_strcmp(seq->m_seqInfo.unknown04.c_str(), "bf00003001") == 0 ||
                                            __builtin_strcmp(seq->m_seqInfo.unknown04.c_str(), "bf00004001") == 0 || __builtin_strcmp(seq->m_seqInfo.unknown04.c_str(), "bf00005001") == 0 ||
                                            __builtin_strcmp(seq->m_seqInfo.unknown04.c_str(), "bf00006001") == 0 || __builtin_strcmp(seq->m_seqInfo.unknown04.c_str(), "bf00007001") == 0 ||
                                            __builtin_strcmp(seq->m_seqInfo.unknown04.c_str(), "bf00008001") == 0 || __builtin_strcmp(seq->m_seqInfo.unknown04.c_str(), "bf00009001") == 0 ||
                                            __builtin_strcmp(seq->m_seqInfo.unknown04.c_str(), "bf00010001") == 0)) {
      seq->unknown170 |= FLAG_UNKNOWN_9;
      ml::DevSetting::setAutoSleepExtended(static_cast<ml::SleepExtendType>(0));
    }
    if (__builtin_strcmp(seq->m_seqInfo.unknown04.c_str(), "bf10400100") == 0) {
      mm::mtl::Singleton<SeqManager>::getPtr()->unknown2850 = 2;
      ml::DevSetting::setAutoSleepExtended(static_cast<ml::SleepExtendType>(mm::mtl::Singleton<SeqManager>::getPtr()->unknown2850));
    }
    gf::GfEvent::callEventPlay(gf::GEV_UNKNOWN_13, seq->m_seqInfo.unknown48);
    mm::mtl::Singleton<ObjectManager>::getPtr()->getCurrent()->setActive(nullptr);
    if (seq->m_seqInfo.unknown54 > 1) {
      u32 group = HideManager::GRP_TYPE_PC | HideManager::GRP_TYPE_PC_WEAPON | HideManager::GRP_TYPE_BLADE | HideManager::GRP_TYPE_FIELD_OBJ | HideManager::GRP_TYPE_COLLECTION |
                  HideManager::GRP_TYPE_SALVAGE | HideManager::GRP_TYPE_PRECIOUS | HideManager::GRP_TYPE_TBOX | HideManager::GRP_TYPE_JUMP | HideManager::GRP_TYPE_WARP;
      if (!seq->m_seqInfo.unknownc2) {
        group |= HideManager::GRP_TYPE_NPC;
      }
      if (!seq->m_seqInfo.unknownc3) {
        group |= HideManager::GRP_TYPE_ENEMY | HideManager::GRP_TYPE_EN_WEAPON;
      }
      if (!seq->m_seqInfo.unknownc4) {
        group |= HideManager::GRP_TYPE_MOB;
      }
      if (!seq->m_seqInfo.unknownc5) {
        group |= HideManager::GRP_TYPE_MAP;
      }
      // The category is above 1 here: the game compares it with `ne 2` (0x710012bbbc), which `> 2` gives after correlated value propagation, `!= 2` gives `eq`.
      if (seq->m_seqInfo.unknown54 > 2) {
        group |= HideManager::GRP_TYPE_DMG_EFFECT | HideManager::GRP_TYPE_DMG_SE;
      }
      mm::mtl::Singleton<HideManager>::getPtr()->defineGroup(static_cast<HideManager::GRP_TYPE>(group));
      mm::mtl::Singleton<HideManager>::getPtr()->hideGroup(true);
      mm::mtl::FixedVector<u32, HideManager::DEFINE_LIST_UNKNOWN_256> primaryList;
      mm::mtl::Singleton<ObjectManager>::getPtr()->listupObject(primaryList, 6, false);
      mm::mtl::Singleton<ObjectManager>::getPtr()->listupObject(primaryList, 3, true);
      mm::mtl::Singleton<ObjectManager>::getPtr()->listupObject(primaryList, 4, true);
      mm::mtl::FixedVector<u32, HideManager::DEFINE_LIST_UNKNOWN_256> secondaryList;
      mm::mtl::Singleton<ObjectManager>::getPtr()->listupObject(secondaryList, 5, false);
      mm::mtl::Singleton<HideManager>::getPtr()->defineList(primaryList, secondaryList);
      mm::mtl::Singleton<HideManager>::getPtr()->hideList(true);
    }
    if (seq->m_seqInfo.unknown54 >= 2 && seq->m_seqInfo.unknown54 <= 4 && seq->m_seqInfo.unknowncc) {
      // 0x7e: all bits but the npc, 0x7f: all of them, 0x5e: all but the npc and the mob (OutsiderManager::OBJ_TYPE).
      OutsiderManager::OBJ_TYPE targets = static_cast<OutsiderManager::OBJ_TYPE>(seq->m_seqInfo.unknownc8 == 2 ? 0x7f : seq->m_seqInfo.unknownc8 == 1 ? 0x7e : 0x5e);
      mm::mtl::Singleton<OutsiderManager>::getPtr()->defineTgt(targets);
      // The game loads the five values (0x710012c25c) before the guard of the second getPtr(); in the argument list the loads follow the guard (3806 instructions against 3804; ruling 2).
      OutsiderField::TYPE fieldType = static_cast<OutsiderField::TYPE>(seq->m_seqInfo.unknownd0);
      mm::Vec3 fieldPos(seq->m_seqInfo.unknownd4, seq->m_seqInfo.unknownd8, seq->m_seqInfo.unknowndc);
      f32 fieldRadius = seq->m_seqInfo.unknowne0;
      mm::mtl::Singleton<OutsiderManager>::getPtr()->defineFld(fieldType, fieldPos, fieldRadius);
      mm::mtl::Singleton<OutsiderManager>::getPtr()->setActive(true);
    }
    if (seq->m_seqInfo.unknown54 < 3) {
      ObjectManager *objectManager = mm::mtl::Singleton<ObjectManager>::getPtr();
      if (objectManager->m_objectList != nullptr) {
        // Loaded before the guard of the TextManager singleton (0x710012c428); written at the call the member chain gives 3816 instructions against 3804 (ruling 2).
        ObjectChara *chara = objectManager->m_objectList->m_objectChara;
        if (chara != nullptr) {
          mm::mtl::Singleton<TextManager>::getPtr()->setDefaultTalkerMode(true, chara->getCharaObj());
        }
      }
    }
    if (seq->m_seqInfo.unknown54 == 3) {
      mm::mtl::Singleton<ShakeManager>::get().setIdleShake(true);
    } else {
      mm::mtl::Singleton<ShakeManager>::get().setIdleShake(false);
    }
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipVolume() && !mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
      mm::mtl::Singleton<SkipManager>::getPtr()->setSkipVolume(false);
    }
    if (mm::mtl::Singleton<CsSndManager>::getPtr()->isPlay()) {
      mm::mtl::Singleton<CsSndManager>::getPtr()->setSyncFrameOffset(mm::mtl::Singleton<FrameManager>::getPtr()->getTotalFrame() - mm::mtl::Singleton<CsSndManager>::getPtr()->getStartedTotalFrame());
    }
    if (mm::mtl::Singleton<MovieManager>::getPtr()->unknown10 & MovieManager::FLAG_UNKNOWN_2) {
      mm::mtl::Singleton<MovieManager>::getPtr()->stop();
    }
    if (mm::mtl::Singleton<UIManager>::getPtr()->isAvanTitleUI()) {
      mm::mtl::Singleton<UIManager>::getPtr()->closeAvanTitleUI(0);
    }
    if (mm::mtl::Singleton<UIManager>::getPtr()->isZoneTelopUI()) {
      mm::mtl::Singleton<UIManager>::getPtr()->closeZoneTelopUI();
    }
    if (seq->m_seqInfo.unknown115 && !(seq->unknown170 & FLAG_UNKNOWN_9)) {
      mm::mtl::Singleton<CsSndManager>::getPtr()->playAuto(seq->m_seqInfo.unknown04.c_str());
    }
    if (seq->m_seqInfo.unknown54 == CATEGORY_UNKNOWN_5) {
      mm::mtl::Singleton<MovieManager>::getPtr()->playAuto(seq->m_seqInfo.unknown04.c_str(), false, false);
    }
    mm::mtl::Singleton<FrameManager>::getPtr()->setMakeCaptureFrame(isCapture);
    if (seq->m_seqInfo.unknown54 < 3) {
      mm::mtl::Singleton<VoiceManager>::getPtr()->setMultipleMode(false);
    } else {
      mm::mtl::Singleton<VoiceManager>::getPtr()->setMultipleMode(true);
    }
    if ((seq->unknown170 & FLAG_UNKNOWN_2) && (seq->unknown2844 > 2) != (seq->m_seqInfo.unknown54 > 2)) {
      mm::mtl::Singleton<DebugManager>::getPtr()->playMessage("bgm change point");
      // The flag byte is loaded before the guards, and BgmManager::getPtr() is evaluated twice before the test (guards at 0x710012ccd8 and 0x710012cd3c); the
      // arms use the instance without a guard of their own (ruling 5 for the second call). `getPtr()->f()` in each arm gives 3789 instructions against 3804.
      bool isOpBgm = seq->m_seqInfo.unknownc0;
      BgmManager *bgm = mm::mtl::Singleton<BgmManager>::getPtr();
      mm::mtl::Singleton<BgmManager>::getPtr();
      if (!isOpBgm) {
        bgm->playDefaultBgm(-1.0f);
      } else {
        bgm->clear();
      }
    }
    seq->unknown2844 = seq->m_seqInfo.unknown54;
    // The game sets the bit with the flag word itself: through BgmManager::setHandOver the select has the other polarity (0x710012cf1c).
    if (seq->m_seqInfo.unknownc1) {
      mm::mtl::Singleton<BgmManager>::getPtr()->unknown10 |= BgmManager::FLAG_UNKNOWN_0;
    } else {
      mm::mtl::Singleton<BgmManager>::getPtr()->unknown10 &= ~BgmManager::FLAG_UNKNOWN_0;
    }
    if (!mm::mtl::Singleton<CaptureManager>::getPtr()->unknown10.test(CaptureManager::FLAG_UNKNOWN_0) || mm::mtl::Singleton<CaptureManager>::getPtr()->unknown18 == 0) {
      if (seq->m_seqInfo.unknownf8 > 0 || seq->m_seqInfo.unknownfc > 0) {
        mm::mtl::Singleton<EnvManager>::getPtr()->setColorFilter(EnvManager::COLORFILTER_TYPE_UNKNOWN_1, seq->m_seqInfo.unknownf8, seq->m_seqInfo.unknownfc, 0.0f);
      } else {
        mm::mtl::Singleton<EnvManager>::getPtr()->setColorFilter(EnvManager::COLORFILTER_TYPE_UNKNOWN_0, -1, -1, 0.0f);
      }
    }
    // The game loads the flag before the loop (ruling 2); read in the loop it gives 3803 instructions against 3804.
    bool isDispJiji = seq->m_seqInfo.unknownf0;
    for (u32 i = 0; i < mm::mtl::Singleton<ObjectManager>::getPtr()->getCharaCount(); i++) {
      mm::mtl::Singleton<ObjectManager>::getPtr()->getChara(i)->getCharaObj()->setDispJiji(isDispJiji);
    }
    // Loaded once before the loop (ruling 2); read in the loop the function has 3808 instructions against 3804.
    u32 wpnDisp = seq->m_seqInfo.unknownf4;
    for (u32 i = 0; i < mm::mtl::Singleton<ObjectManager>::getPtr()->getCharaCount(); i++) {
      mm::mtl::Singleton<ObjectManager>::getPtr()->getChara(i)->getCharaObj()->setHideWeapon(WPNHIDEID_UNKNOWN_0, wpnDisp == 1, false);
      mm::mtl::Singleton<ObjectManager>::getPtr()->getChara(i)->getCharaObj()->setHideWeapon(WPNHIDEID_UNKNOWN_0, wpnDisp == 1, true);
    }
    mm::mtl::Singleton<LightManager>::getPtr()->clearEvtLight();
    if (*seq->m_seqInfo.unknown108 != '\0') {
      mm::mtl::Singleton<LightManager>::getPtr()->playEvtLight(seq->m_seqInfo.unknown108);
    }
    mm::mtl::Singleton<LightManager>::getPtr()->clearOffScrLight();
    for (u32 i = 1; i < OffscrManager::SCREEN_UNKNOWN_4; i++) {
      if (mm::mtl::Singleton<OffscrManager>::getPtr()->isScreenExist(i)) {
        mm::mtl::Singleton<LightManager>::getPtr()->playOffScrLight(i);
      }
    }
    if (seq->m_seqInfo.unknown54 >= 2 && seq->m_seqInfo.unknown54 <= 4) {
      mm::mtl::Singleton<EnvManager>::getPtr()->setAutoResetSceneEnable(true);
    } else {
      mm::mtl::Singleton<EnvManager>::getPtr()->setAutoResetSceneEnable(false);
    }
    if (seq->m_seqInfo.unknown54 >= 2 && seq->m_seqInfo.unknown54 <= 4) {
      mm::mtl::Singleton<EnvManager>::getPtr()->resetScene();
    }
    mm::mtl::Singleton<UIManager>::getPtr()->setDispNowLoading(false);
    if (seq->m_seqInfo.unknown54 < 3 || __builtin_strcmp(seq->m_seqInfo.unknown04.c_str(), "bf08030100") == 0) {
      mm::mtl::Singleton<SkipManager>::getPtr()->setSkipFastEnable(false);
    } else {
      mm::mtl::Singleton<SkipManager>::getPtr()->setSkipFastEnable(true);
    }
    mm::mtl::Singleton<FadeManager>::getPtr()->request(FadePlanner::TYPE_UNKNOWN_1);
    mm::mtl::Singleton<VolumeManager>::get().endSeamlessVolume(seq->m_seqInfo.unknown88);
    if (isResetVolume) {
      for (u32 i = 0; i < VolumeManager::CATE_COUNT; i++) {
        mm::mtl::Singleton<VolumeManager>::get().resetCategoryVolume(static_cast<VolumeManager::CATE>(i), seq->m_seqInfo.unknown88);
      }
    }
    unknown14 = 0;
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
      unknown14 = 3;
    }
    unknown09 = false;
    unknown10 = -1;
    seq->unknown178 = "exec";
  }
  if ((seq->unknown170 & FLAG_UNKNOWN_9) && param.getFrame() > 0) {
    if (mm::mtl::Singleton<UIManager>::getPtr()->startNewGameWait()) {
      seq->unknown170 &= ~FLAG_UNKNOWN_9;
      if (seq->m_seqInfo.unknown115) {
        mm::mtl::Singleton<CsSndManager>::getPtr()->playAuto(seq->m_seqInfo.unknown04.c_str());
      }
    }
  }
  bool isUIBusy = mm::mtl::Singleton<SelectManager>::getPtr()->isActive() || mm::mtl::Singleton<QuestManager>::getPtr()->isActive() || mm::mtl::Singleton<UIManager>::getPtr()->isOpenCommonUI() ||
                  mm::mtl::Singleton<UIManager>::getPtr()->isFieldSkill() || mm::mtl::Singleton<UIManager>::getPtr()->isOpenShopUI() || mm::mtl::Singleton<UIManager>::getPtr()->isOpenPayoffUI() ||
                  mm::mtl::Singleton<UIManager>::getPtr()->isOpenRewardUI() || mm::mtl::Singleton<UIManager>::getPtr()->isOpenHomuraHikariUI() ||
                  mm::mtl::Singleton<UIManager>::getPtr()->isNewGameWait() || mm::mtl::Singleton<UIManager>::getPtr()->isOpenMinigame();
  // The game compares the three names (0x710012e374) before the switch on the state; inlined at its only use the test gives 3802 instructions against 3804 (ruling 1).
  bool isNoSkip = __builtin_strcmp(seq->m_seqInfo.unknown04.c_str(), "bf10470100") == 0 || __builtin_strcmp(seq->m_seqInfo.unknown04.c_str(), "bf10480100") == 0 ||
                  __builtin_strcmp(seq->m_seqInfo.unknown04.c_str(), "bf10500100") == 0;
  switch (unknown14) {
  case 0:
    if (!isUIBusy && !isNoSkip && !unknown08 && unknown10 < 0 && seq->m_seqInfo.unknown54 > 1) {
      if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
        if (!(mm::mtl::Singleton<MovieManager>::getPtr()->unknown10 & MovieManager::FLAG_UNKNOWN_7) && gf::GfGamePad::isEventPause()) {
          ml::DevSetting::setAutoSleepExtended(static_cast<ml::SleepExtendType>(0));
          unknown14 = 1;
        }
      }
    }
    break;
  case 1:
    if (!isUIBusy && !unknown08) {
      bool isSkipAll = false;
      if (mm::mtl::Singleton<UIManager>::getPtr()->openSkip(isSkipAll)) {
        if (!isSkipAll) {
          ml::DevSetting::setAutoSleepExtended(static_cast<ml::SleepExtendType>(mm::mtl::Singleton<SeqManager>::getPtr()->unknown2850));
          unknown10 = 35;
          unknown14 = 0;
        } else {
          mm::mtl::Singleton<SkipManager>::getPtr()->setSkipVolume(true);
          mm::mtl::Singleton<FadeManager>::getPtr()->playEventSkip(true, 30);
          ml::DevSetting::setAutoSleepExtended(static_cast<ml::SleepExtendType>(mm::mtl::Singleton<SeqManager>::getPtr()->unknown2850));
          unknown14 = 2;
        }
      }
      break;
    }
    mm::mtl::Singleton<UIManager>::getPtr()->closeSkip();
    ml::DevSetting::setAutoSleepExtended(static_cast<ml::SleepExtendType>(mm::mtl::Singleton<SeqManager>::getPtr()->unknown2850));
    unknown14 = 0;
    break;
  case 2:
    if (!mm::mtl::Singleton<FadeManager>::getPtr()->isSkipFading()) {
      mm::mtl::Singleton<SkipManager>::getPtr()->skip(true, -1.0f);
      unknown14 = 3;
    }
    break;
  case 3:
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
      break;
    }
    mm::mtl::Singleton<FadeManager>::getPtr()->playEventSkip(false, 30);
    unknown14 = 0;
    break;
  }
  if (unknown10 >= 0) {
    unknown10--;
  }
  if (!unknown09 && seq->m_seqInfo.unknown54 >= 3 && seq->m_seqInfo.unknown54 <= 4 && Manager::get()->getStartPageID() <= mm::mtl::Singleton<FrameManager>::getPtr()->getPageID()) {
    if (!mm::mtl::Singleton<SeamlessManager>::getPtr()->isActiveSeamPoint()) {
      mm::mtl::Singleton<SeamlessManager>::getPtr()->readNextSeamPoint(Manager::get()->getSceneName());
      unknown09 = true;
    }
  }
  if (unknown0a && Manager::get()->getStartPageID() <= mm::mtl::Singleton<FrameManager>::getPtr()->getPageID()) {
    if (mm::mtl::Singleton<FrameManager>::getPtr()->getMaxFrame() - unknown0c <= mm::mtl::Singleton<FrameManager>::getPtr()->getFrame()) {
      mm::mtl::Singleton<FadeManager>::getPtr()->request(FadePlanner::TYPE_UNKNOWN_2);
      mm::mtl::Singleton<VolumeManager>::get().startSeamlessVolume(seq->m_seqInfo.unknown9c);
      unknown0a = false;
    }
  }
  if (isCapture && mm::mtl::Singleton<FrameManager>::getPtr()->isCaptureFrame()) {
    mm::mtl::Singleton<MovieManager>::getPtr()->captureScreen(true);
  }
  if (unknown08 && unknown14 != 2) {
    if (!mm::mtl::Singleton<FadeManager>::getPtr()->isFading() && !mm::mtl::Singleton<UIManager>::getPtr()->isOpenChapTelopUI()) {
      if (mm::mtl::Singleton<FrameManager>::getPtr()->isPause(FrameManager::PAUSE_TYPE_UNKNOWN_17_2)) {
        mm::mtl::Singleton<FrameManager>::getPtr()->pauseClearAll();
      }
      if (!isWaitPause || !gf::GfPause::isPause(1)) {
        if (isBgmSync && unknown14 > 2) {
          if (mm::mtl::Singleton<BgmManager>::getPtr()->unknown10 & BgmManager::FLAG_UNKNOWN_1) {
            mm::mtl::Singleton<BgmManager>::getPtr()->setSyncFrame(mm::mtl::Singleton<FrameManager>::getPtr()->getTotalFrame() - mm::mtl::Singleton<BgmManager>::getPtr()->getStartedTotalFrame());
          }
        }
        if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
          mm::mtl::Singleton<BgmManager>::getPtr()->cancelOverTime();
        }
        if (isFadeIn) {
          mm::mtl::Singleton<FadeManager>::getPtr()->playEventSkip(false, 30);
          mm::mtl::Singleton<SkipManager>::getPtr()->skip(false, 0.0f);
        }
        if (seq->m_seqInfo.unknown100 != 0) {
          mm::mtl::Singleton<EnvManager>::getPtr()->saveTransferEnvironment(seq->m_seqInfo.unknown48, seq->m_seqInfo.unknown100);
        }
        return RESULT_UNKNOWN_1;
      }
    }
  }
  return RESULT_UNKNOWN_0;
}

ICmd::RESULT SeqManager::start_streaming1::update(const Param &param) {
  if (param.getFrame() <= 0) {
    static_cast<SeqManager *>(param.val(0).getUserdata())->unknown178 = "start stream1";
  }
  return RESULT_UNKNOWN_1;
}

ICmd::RESULT SeqManager::end_eff::update(const Param &param) {
  if (param.getFrame() <= 0) {
    static_cast<SeqManager *>(param.val(0).getUserdata())->unknown178 = "end eff";
  }
  bool isUsing = mm::mtl::Singleton<ObjectManager>::getPtr()->isUsingEffect();
  mm::mtl::Singleton<ObjectManager>::getPtr()->stopEffect();
  return static_cast<RESULT>(!isUsing);
}

ICmd::RESULT SeqManager::end_stream::update(const Param &param) {
  if (param.getFrame() <= 0) {
    mm::mtl::Singleton<MotstmManager>::getPtr()->stop();
  }
  return static_cast<RESULT>(!mm::mtl::Singleton<MotstmManager>::getPtr()->isBusy());
}

ICmd::RESULT SeqManager::start_loading::update(const Param &param) {
  if (param.getFrame() <= 0) {
    SeqManager *seq = static_cast<SeqManager *>(param.val(0).getUserdata());
    mm::mtl::Singleton<UIManager>::getPtr()->setDispNowLoading(seq->m_seqInfo.unknown54 >= 2);
    seq->unknown178 = "start loading";
  }
  if (!unknown08) {
    return RESULT_UNKNOWN_0;
  }
  if (mm::mtl::Singleton<ResManager>::getPtr()->isLoading() || mm::mtl::Singleton<EffectManager>::getPtr()->isLoading() || mm::mtl::Singleton<SeManager>::get().isLoading() ||
      mm::mtl::Singleton<LipsyncManager>::getPtr()->isLoading() || mm::mtl::Singleton<MstxtManager>::getPtr()->isLoading()) {
    return RESULT_UNKNOWN_0;
  }
  if (mm::mtl::Singleton<ObjectManager>::getPtr()->isLoading()) {
    return RESULT_UNKNOWN_0;
  }
  return RESULT_UNKNOWN_1;
}

ICmd::RESULT SeqManager::start_other::update(const Param &param) {
  if (param.getFrame() <= 0) {
    u32 num = param.val(1).getS32();
    unknown08.clear();
    for (u32 i = 1; i < 4; i++) {
      if (num <= mm::mtl::Singleton<ObjectManager>::getPtr()->getCharaCount()) {
        break;
      }
      gf::GF_OBJ_HANDLE *handle = mm::mtl::Singleton<ObjectPartyList>::getPtr()->getDriver(i);
      if (gf::GfObjUtil::getObj(handle) != nullptr) {
        gf::GfObjAcc acc(handle);
        u32 id = acc.getBdatId();
        if (mm::mtl::Singleton<ObjectManager>::getPtr()->searchByID(gf::OBJECT_TYPE_PC, id) == nullptr) {
          mm::mtl::FixStr<64> name;
          name.format("other%d", i);
          unknown08.push_back(mm::mtl::Singleton<ObjectManager>::getPtr()->createGfObjPcByWalkID(name.c_str(), i, 0));
        }
      }
    }
    for (u32 i = 1; i < 4; i++) {
      if (num <= mm::mtl::Singleton<ObjectManager>::getPtr()->getCharaCount()) {
        break;
      }
      gf::GF_OBJ_HANDLE *handle = mm::mtl::Singleton<ObjectPartyList>::getPtr()->getBlade(i);
      if (gf::GfObjUtil::getObj(handle) != nullptr) {
        gf::GfObjAcc acc(handle);
        u32 id = acc.getBdatId();
        if (mm::mtl::Singleton<ObjectManager>::getPtr()->searchByID(gf::OBJECT_TYPE_BLADE, id) == nullptr) {
          mm::mtl::FixStr<64> name;
          name.format("other_bl%d", i);
          unknown08.push_back(mm::mtl::Singleton<ObjectManager>::getPtr()->createGfObjBlByWalkID(name.c_str(), i, 0));
        }
      }
    }
    static_cast<SeqManager *>(param.val(0).getUserdata())->unknown178 = "start other";
  }
  while (!unknown08.empty()) {
    if (unknown08.front()->isLoading()) {
      return RESULT_UNKNOWN_0;
    }
    unknown08.erase(unknown08.begin());
  }
  return RESULT_UNKNOWN_1;
}

ICmd::RESULT SeqManager::start_weather::update(const Param &param) {
  if (param.getFrame() > 0) {
    return RESULT_UNKNOWN_1;
  }
  const char *clock = param.val(1).getStr();
  bool isClockStop = param.val(2).getBool();
  int weather = param.val(3).getS32();
  int cloud = param.val(4).getS32();
  if (*clock != '\0') {
    mm::mtl::Singleton<EnvManager>::getPtr()->setClock(clock);
  }
  if (isClockStop) {
    mm::mtl::Singleton<EnvManager>::getPtr()->setClockStop(true);
  }
  if (weather > 0) {
    mm::mtl::Singleton<EnvManager>::getPtr()->setMapWeatherID(static_cast<gf::WEATHERID>(weather), 0.0f);
  }
  if (cloud > 0) {
    mm::mtl::Singleton<EnvManager>::getPtr()->setCloudSea(static_cast<EVT_cloudtype>(cloud));
  }
  static_cast<SeqManager *>(param.val(0).getUserdata())->unknown178 = "start weather";
  return RESULT_UNKNOWN_1;
}

ICmd::RESULT SeqManager::start_streaming0::update(const Param &param) {
  SeqManager *seq = static_cast<SeqManager *>(param.val(0).getUserdata());
  bool isCapture = param.val(1).getBool();
  bool isGimmickWait = param.val(2).getBool();
  if (param.getFrame() <= 0) {
    const char *movie = param.val(3).getStr();
    mm::mtl::Singleton<MdlstmManager>::getPtr()->start();
    mm::mtl::Singleton<MotstmManager>::getPtr()->start();
    // The game (0x710012ac54) constructs the DebugManager singleton and loads its flag word after the guard but before
    // the null test of the movie name (guard, cbz, ldr w + tbnz #16); testing the flag inline puts the null test first.
    bool isMovieDebug = mm::mtl::Singleton<DebugManager>::getPtr()->isMovieDebug();
    if (movie != nullptr && !isMovieDebug && *movie != '\0') {
      mm::mtl::Singleton<MovieManager>::getPtr()->preloadAuto(movie, false);
    }
    if (isGimmickWait && !mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
      mm::mtl::Singleton<EnvManager>::getPtr()->startGimmickPopWait();
    }
    static_cast<SeqManager *>(param.val(0).getUserdata())->unknown178 = "start stream0";
  }
  if (seq->m_seqInfo.unknown54 >= 2) {
    mm::mtl::Singleton<SeamlessManager>::getPtr()->readFirstSeamPoint(Manager::get()->getSceneName());
  }
  if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    ml::ScnRenderDrSysParmAcc parmAcc(Manager::get()->getScn()->unknown38, 0);
    if (mm::mtl::Singleton<MovieManager>::getPtr()->isLoading() || mm::mtl::Singleton<MdlstmManager>::getPtr()->isLoadingPrio(99999.0f) ||
        mm::mtl::Singleton<MotstmManager>::getPtr()->isLoadingPrio(0.0f) || mm::mtl::Singleton<CsSndManager>::getPtr()->isLoading()) {
      return RESULT_UNKNOWN_0;
    }
    if (isCapture) {
      if (param.getFrame() <= 1) {
        return RESULT_UNKNOWN_0;
      }
      if (parmAcc.isSeamMapRead() && param.getFrame() < 900) {
        return RESULT_UNKNOWN_0;
      }
      if (parmAcc.isMdlAllMiddleTexStm() && param.getFrame() < 900) {
        return RESULT_UNKNOWN_0;
      }
    }
    if (isGimmickWait && mm::mtl::Singleton<EnvManager>::getPtr()->isGimmickPopWaiting() && param.getFrame() < 900) {
      return RESULT_UNKNOWN_0;
    }
  }
  mm::mtl::Singleton<EnvManager>::getPtr()->endGimmickPopWait();
  mm::mtl::Singleton<MovieManager>::getPtr()->captureScreen(false);
  return RESULT_UNKNOWN_1;
}

ICmd::RESULT SeqManager::exec_grass::update(const Param &param) {
  ml::ScnRenderDrSysParmAcc parmAcc(Manager::get()->getScn()->unknown38, 0);
  if (param.getFrame() <= 0) {
    SeqManager *seq = static_cast<SeqManager *>(param.val(0).getUserdata());
    int type = param.val(1).getS32();
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipVolume() || mm::mtl::Singleton<DebugManager>::getPtr()->isPlayCancel()) {
      mm::mtl::Singleton<FadeManager>::getPtr()->play(true, 0, FadeCtrl::PRIO_LOW, 0);
      return RESULT_UNKNOWN_1;
    }
    parmAcc.setGlassBr(true, type);
    seq->unknown178 = "exec grass";
  }
  int endFrame = param.val(2).getS32();
  if (param.getFrame() == endFrame) {
    mm::mtl::Singleton<FadeManager>::getPtr()->play(true, 0, FadeCtrl::PRIO_LOW, 0);
  }
  if (param.getFrame() > endFrame + 1) {
    parmAcc.setGlassBr(false, 0);
    return RESULT_UNKNOWN_1;
  }
  return RESULT_UNKNOWN_0;
}

ICmd::RESULT SeqManager::start_areajump::update(const Param &param) {
  if (param.getFrame() <= 0) {
    gf::GfMapjumpInfo info(param.val(1).getS32());
    info.unknown101 = true;
    info.unknown102 = true;
    unknown08 = gf::GfReqCommand::reqMapjump(info);
    static_cast<SeqManager *>(param.val(0).getUserdata())->unknown178 = "start areajump";
  }
  return static_cast<RESULT>(!gf::GfReqManager::isValid(unknown08));
}

ICmd::RESULT SeqManager::end_areajump::update(const Param &param) {
  if (param.getFrame() <= 0) {
    gf::GfMapjumpInfo info(param.val(1).getS32());
    info.unknown101 = true;
    info.unknown102 = true;
    unknown08 = gf::GfReqCommand::reqMapjump(info);
    static_cast<SeqManager *>(param.val(0).getUserdata())->unknown178 = "end areajump";
  }
  return static_cast<RESULT>(!gf::GfReqManager::isValid(unknown08));
}

ICmd::RESULT SeqManager::end_change::update(const Param &param) {
  if (param.getFrame() <= 0) {
    unknown08 = false;
    static_cast<SeqManager *>(param.val(0).getUserdata())->unknown178 = "end change";
  }
  if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkip() && !unknown08) {
    mm::mtl::Singleton<FadeManager>::getPtr()->playEventSkip(false, 30);
    unknown08 = true;
  }
  int status = param.val(1).getS32();
  if (status != 0 && !mm::mtl::Singleton<DebugManager>::getPtr()->isPlayCancel() && !mm::mtl::Singleton<StatusManager>::getPtr()->changeFromBdat(status)) {
    return RESULT_UNKNOWN_0;
  }
  return RESULT_UNKNOWN_1;
}

ICmd::RESULT SeqManager::end_env_seam::update(const Param &param) {
  if (param.getFrame() <= 0) {
    mm::mtl::Singleton<EnvManager>::getPtr()->loadTransferEnvironment(1);
    static_cast<SeqManager *>(param.val(0).getUserdata())->unknown178 = "end envseam";
  }
  return RESULT_UNKNOWN_1;
}

ICmd::RESULT SeqManager::end_fadewait::update(const Param &param) {
  if (param.getFrame() <= 0) {
    static_cast<SeqManager *>(param.val(0).getUserdata())->unknown178 = "exec fadewait";
  }
  return static_cast<RESULT>(!mm::mtl::Singleton<FadeManager>::getPtr()->isFading());
}

ICmd::RESULT SeqManager::end_fadein::update(const Param &param) {
  if (param.getFrame() <= 0) {
    static_cast<SeqManager *>(param.val(0).getUserdata())->unknown178 = "end fadein";
  }
  return RESULT_UNKNOWN_1;
}

ICmd::RESULT SeqManager::end_notice::update(const Param &param) {
  if (param.getFrame() <= 0) {
    static_cast<SeqManager *>(param.val(0).getUserdata())->unknown178 = "end notice";
  }
  int eventId = param.val(1).getS32();
  if (eventId != 0) {
    gf::GfEvent::callEventPlay(gf::GEV_UNKNOWN_10, eventId);
  }
  return RESULT_UNKNOWN_1;
}

ICmd::RESULT SeqManager::end::update(const Param &param) {
  if (param.getFrame() <= 0) {
    SeqManager *seq = static_cast<SeqManager *>(param.val(0).getUserdata());
    seq->unknown170 |= FLAG_UNKNOWN_1;
    seq->unknown178 = "end";
  }
  return RESULT_UNKNOWN_1;
}

SeqManager::SeqManager() : unknown170(0), unknown174(0) {}

void SeqManager::clear() {
  unknown170 = 0;
  unknown178 = "";
  unknown200.clear();
}

void SeqManager::play(const char *name) {
  unknown178 = "";
  unknown200.clear();
  CmdParam param;
  param.val(0).setUserdata(this);
  param.val(1).setStr(mm::mtl::Singleton<MemoryManager>::getPtr()->createTxtbuf(name));
  unknown200.push_back(&m_play_start, param);
}

void SeqManager::login() {
  unknown2850 = 1;
  ml::DevSetting::setAutoSleepExtended(ml::SLEEP_EXTEND_TYPE_UNKNOWN_1);
  unknown170 &= ~FLAG_UNKNOWN_3;
}

void SeqManager::logout() {
  ml::DevSetting::setAutoSleepExtended(ml::SLEEP_EXTEND_TYPE_UNKNOWN_0);
  ml::ScnRenderDrSysParmAcc parmAcc(Manager::get()->getScn()->unknown38, 0);
  if (parmAcc.isGlassBr()) {
    parmAcc.setGlassBr(false, 0);
  }
}

bool SeqManager::checkWait3D(const SeqInfo &info) { return (Manager::get()->getPlayParam(2) | info.unknowne8) == 0; }

bool SeqManager::checkSyncBgm(const SeqInfo &info, bool isSync) {
  if (Manager::get()->isEndFadeOut() || info.unknowne4 == 0) {
    isSync = false;
  }
  return isSync;
}

bool SeqManager::checkCapture(const SeqInfo &info) {
  if (info.unknowne8 < 1) {
    return false;
  }
  SeqInfo link(info.unknowne8);
  return link.unknown54 == CATEGORY_UNKNOWN_5;
}

void SeqManager::update() { unknown200.update(); }

void SeqManager::nextEvent(int next) { unknown2840 = next; }

bool SeqManager::isSetupSceneEnd() const {
  if (unknown200.isExist(&m_start_loading)) {
    return false;
  }
  if (unknown200.isExist(&m_start_other)) {
    return false;
  }
  return !mm::mtl::Singleton<MstxtManager>::getPtr()->isLoading();
}

void SeqManager::render() {
  if (!(unknown174 & DISP_FLAG_UNKNOWN_0) || unknown200.isEmpty()) {
    return;
  }
  int width = ml::DevGraph::getRootWidth();
  fw::debug::drawSquare2D(mm::Rect<s32>(width - 180, 30, 170, 55), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<s32>(width - 180, 30, 170, 55), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFont(width - 175, 35, "EVENT");
  fw::debug::drawFont(width - 170, 50, "phase:");
  fw::debug::drawFont(width - 120, 50, unknown178.c_str());
  f32 frame = mm::mtl::Singleton<FrameManager>::getPtr()->getFrame();
  fw::debug::drawFont(width - 170, 65, "frame:");
  fw::debug::drawFont(width - 120, 65, "%.2f", frame);
  int height = ml::DevGraph::getRootHeight();
  fw::debug::drawSquare2D(mm::Rect<s32>(25, height - 90, 200, 25), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<s32>(25, height - 90, 200, 25), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFont(30, height - 85, unknown002[m_seqInfo.unknown54]);
  fw::debug::drawFont(75, height - 85, mm::mtl::Singleton<FrameManager>::getPtr()->getPageName());
}

void SeqManager::setDisp(bool isDisp) {
  if (isDisp) {
    unknown174 |= DISP_FLAG_UNKNOWN_0;
  } else {
    unknown174 &= ~DISP_FLAG_UNKNOWN_0;
  }
}

bool SeqManager::isDisp() const { return (unknown174 & DISP_FLAG_UNKNOWN_0) != 0; }

void SeqManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_UNKNOWN_1:
    login();
    break;
  case MSG_TYPE_UNKNOWN_2:
    logout();
    clear();
    break;
  case MSG_TYPE_UNKNOWN_4:
    init();
    break;
  case MSG_TYPE_UNKNOWN_5:
    setupScene();
    break;
  case MSG_TYPE_UNKNOWN_6:
    m_start_loading.unknown08 = true;
    break;
  case MSG_TYPE_UNKNOWN_7:
    startScene();
    break;
  case MSG_TYPE_UNKNOWN_9:
    m_exec.unknown08 = true;
    break;
  case MSG_TYPE_UNKNOWN_11:
    end();
    break;
  case MSG_TYPE_UNKNOWN_12:
    m_end_wait.unknown08 = true;
    break;
  case MSG_TYPE_UNKNOWN_15:
    update();
    break;
  case MSG_TYPE_UNKNOWN_17:
    render();
    break;
  default:
    break;
  }
}

template void CmdQueue<SeqManager::QUEUE_UNKNOWN_32, 0>::push_back(ICmd *cmd, const CmdParam &param);
template CmdQueue<SeqManager::QUEUE_UNKNOWN_32, 0>::~CmdQueue();

} // namespace event
