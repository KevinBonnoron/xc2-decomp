#include "event/seq_manager.h"

#include "event/cmd_param.h"
#include "event/cmd_variable.h"
#include "event/debug_manager.h"
#include "event/effect_manager.h"
#include "event/env_manager.h"
#include "event/fade_ctrl.h"
#include "event/fade_manager.h"
#include "event/fade_planner.h"
#include "event/frame_manager.h"
#include "event/lipsync_manager.h"
#include "event/manager.h"
#include "event/memory_manager.h"
#include "event/motstm_manager.h"
#include "event/mstxt_manager.h"
#include "event/object_chara.h"
#include "event/object_manager.h"
#include "event/object_party_list.h"
#include "event/res_manager.h"
#include "event/se_manager.h"
#include "event/skip_manager.h"
#include "event/status_manager.h"
#include "event/ui_manager.h"
#include "event/volume_manager.h"
#include "fw/fw_debug.h"
#include "gf/data/gf_data_map.h"
#include "gf/data/gf_object_type.h"
#include "gf/event/gf_event.h"
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
    mm::mtl::Singleton<VolumeManager>::get().startSeamlessVolume(seq->unknown2710.unknown9c);
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
    mm::mtl::Singleton<UIManager>::getPtr()->setDispNowLoading(static_cast<int>(seq->unknown2710.unknown54) >= 2);
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
  unknown200.push_back(&unknown10, param);
}

void SeqManager::login() {
  unknown2850 = 1;
  ml::DevSetting::setAutoSleepExtended(static_cast<ml::SleepExtendType>(1));
  unknown170 &= ~FLAG_UNKNOWN_3;
}

void SeqManager::logout() {
  ml::DevSetting::setAutoSleepExtended(static_cast<ml::SleepExtendType>(0));
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
  if (unknown200.isExist(&unknown48)) {
    return false;
  }
  if (unknown200.isExist(&unknown58)) {
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
  fw::debug::drawFont(30, height - 85, unknown002[static_cast<int>(unknown2710.unknown54)]);
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

template void CmdQueue<SeqManager::QUEUE_UNKNOWN_32, 0>::push_back(ICmd *cmd, const CmdParam &param);
template CmdQueue<SeqManager::QUEUE_UNKNOWN_32, 0>::~CmdQueue();

} // namespace event
