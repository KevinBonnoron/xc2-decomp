#include "event/seq_manager.h"

#include "event/cmd_variable.h"
#include "event/debug_manager.h"
#include "event/env_manager.h"
#include "event/fade_manager.h"
#include "event/manager.h"
#include "event/motstm_manager.h"
#include "event/mstxt_manager.h"
#include "event/object_manager.h"
#include "event/skip_manager.h"
#include "event/status_manager.h"
#include "gf/event/gf_event.h"
#include "gf/request/gf_req_command.h"
#include "gf/request/gf_req_manager.h"
#include "gf/scom/gf_scom_script.h"
#include "gf/script/gf_script_manager.h"
#include "ml/dev_setting.h"
#include "ml/scn.h"
#include "scn/scn_render_dr_sys_parm_acc.h"

namespace event {

constexpr u32 CATEGORY_CAPTURE = 5;
constexpr u32 SCRIPT_SLOT_EVENT = 2;

ICmd::RESULT SeqManager::play_start::update(const Param &param) {
  if (param.getFrame() <= 0) {
    gf::SCOM_SCRIPT::create(SCRIPT_SLOT_EVENT, param.val(1).getStr(), false);
    SeqManager *seq = static_cast<SeqManager *>(param.val(0).getUserdata());
    seq->unknown170 &= ~FLAG_NEXT;
    seq->unknown178 = "play start";
  }
  if (gf::GfScriptManager::isScriptLoadError(SCRIPT_SLOT_EVENT)) {
    gf::GfScriptManager::destroyScript(SCRIPT_SLOT_EVENT);
    static_cast<SeqManager *>(param.val(0).getUserdata())->unknown170 |= FLAG_SCRIPT_ERROR;
  }
  return RESULT_WAIT;
}

ICmd::RESULT SeqManager::start::update(const Param &param) {
  if (param.getFrame() <= 0) {
    static_cast<SeqManager *>(param.val(0).getUserdata())->unknown178 = "start";
  }
  return RESULT_END;
}

ICmd::RESULT SeqManager::start_notice::update(const Param &param) {
  if (param.getFrame() <= 0) {
    static_cast<SeqManager *>(param.val(0).getUserdata())->unknown178 = "start notice";
  }
  int eventId = param.val(1).getS32();
  if (eventId != 0) {
    gf::GfEvent::callEventPlay(gf::GEV_EVENT_END, eventId);
  }
  return RESULT_END;
}

ICmd::RESULT SeqManager::start_change::update(const Param &param) {
  if (param.getFrame() <= 0) {
    static_cast<SeqManager *>(param.val(0).getUserdata())->unknown178 = "start change";
  }
  if (param.val(1).getS32() != 0 && !mm::mtl::Singleton<StatusManager>::getPtr()->changeFromBdat(param.val(1).getS32())) {
    return RESULT_WAIT;
  }
  return RESULT_END;
}

ICmd::RESULT SeqManager::start_env_seam::update(const Param &param) {
  if (param.getFrame() <= 0) {
    int eventId = param.val(1).getS32();
    mm::mtl::Singleton<EnvManager>::getPtr()->loadTransferEnvironment(eventId);
    static_cast<SeqManager *>(param.val(0).getUserdata())->unknown178 = "start envseam";
  }
  return RESULT_END;
}

ICmd::RESULT SeqManager::start_capture_wait::update(const Param &param) {
  if (param.getFrame() <= 0) {
    static_cast<SeqManager *>(param.val(0).getUserdata())->unknown178 = "start capture wait";
  }
  return param.getFrame() >= 30 ? RESULT_END : RESULT_WAIT;
}

ICmd::RESULT SeqManager::start_streaming1::update(const Param &param) {
  if (param.getFrame() <= 0) {
    static_cast<SeqManager *>(param.val(0).getUserdata())->unknown178 = "start stream1";
  }
  return RESULT_END;
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
    return RESULT_WAIT;
  }
  return RESULT_END;
}

ICmd::RESULT SeqManager::end_env_seam::update(const Param &param) {
  if (param.getFrame() <= 0) {
    mm::mtl::Singleton<EnvManager>::getPtr()->loadTransferEnvironment(1);
    static_cast<SeqManager *>(param.val(0).getUserdata())->unknown178 = "end envseam";
  }
  return RESULT_END;
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
  return RESULT_END;
}

ICmd::RESULT SeqManager::end_notice::update(const Param &param) {
  if (param.getFrame() <= 0) {
    static_cast<SeqManager *>(param.val(0).getUserdata())->unknown178 = "end notice";
  }
  int eventId = param.val(1).getS32();
  if (eventId != 0) {
    gf::GfEvent::callEventPlay(static_cast<gf::GEV>(10), eventId);
  }
  return RESULT_END;
}

ICmd::RESULT SeqManager::end::update(const Param &param) {
  if (param.getFrame() <= 0) {
    SeqManager *seq = static_cast<SeqManager *>(param.val(0).getUserdata());
    seq->unknown170 |= FLAG_END;
    seq->unknown178 = "end";
  }
  return RESULT_END;
}

void SeqManager::clear() {
  unknown170 = 0;
  unknown178 = "";
  unknown200.clear();
}

void SeqManager::login() {
  unknown2850 = 1;
  ml::DevSetting::setAutoSleepExtended(static_cast<ml::SleepExtendType>(1));
  unknown170 &= ~FLAG_LOGIN;
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
  return link.unknown54 == CATEGORY_CAPTURE;
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

void SeqManager::setDisp(bool isDisp) {
  if (isDisp) {
    unknown174 |= DISP_FLAG_DISP;
  } else {
    unknown174 &= ~DISP_FLAG_DISP;
  }
}

bool SeqManager::isDisp() const { return (unknown174 & DISP_FLAG_DISP) != 0; }

template void CmdQueue<SeqManager::QUEUE_COUNT, 0>::push_back(ICmd *cmd, const CmdParam &param);
template CmdQueue<SeqManager::QUEUE_COUNT, 0>::~CmdQueue();

} // namespace event
