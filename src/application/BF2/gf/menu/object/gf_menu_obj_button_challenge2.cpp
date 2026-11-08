#include "gf/menu/object/gf_menu_obj_button_challenge2.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/rtti.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_manager.h"
#include "ui/event/ui_event_data.h"
#include "ui/shape/ui_shape.h"
#include "ui/shape/ui_shape_ring.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x4b;

// Inferred helper: casts a shape to the ring shape when it is one; original name unknown.
static ui::UIShapeRing *unknown003(ui::UIShape *shape) { return shape != nullptr ? mm::mtl::dynamicCast<ui::UIShapeRing>(shape) : nullptr; }

GfMenuObjButtonChallenge2::~GfMenuObjButtonChallenge2() {
  if (unknown3e0.ctrl != nullptr) {
    ui::UICtrlManager::get()->delUpdater(unknown3e0);
  }
  unknown3e0.ctrl = nullptr;
  if (unknown428.ctrl != nullptr) {
    ui::UICtrlManager::get()->delUpdater(unknown428);
  }
  unknown428.ctrl = nullptr;
  if (unknown470.ctrl != nullptr) {
    ui::UICtrlManager::get()->delUpdater(unknown470);
  }
  unknown470.ctrl = nullptr;
}

void GfMenuObjButtonChallenge2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjButtonChallenge2::update() {
  unknown0a0.unknown003();
  GfMenuObject::update();
}

bool GfMenuObjButtonChallenge2::isValidParam(const OpenParam &param) {
  if (param.unknown00 == 0) {
    return false;
  }
  if (param.unknown08.size() == 0) {
    return false;
  }
  bool isValid = true;
  int total = 0;
  for (u32 i = 0; i < param.unknown08.size(); i++) {
    const unknown002 &challenge = param.unknown08[i];
    if (challenge.unknown00 < 1 || challenge.unknown00 > 5 || challenge.unknown02 == 0) {
      isValid = false;
      break;
    }
    total += challenge.unknown02;
    if (challenge.unknown01 < 1 || challenge.unknown01 > 2) {
      isValid = false;
      break;
    }
    if (challenge.unknown01 == 1 && challenge.unknown04 == 0) {
      isValid = false;
      break;
    }
    if (challenge.unknown01 == 2 && (challenge.unknown08 == 0 || challenge.unknown0a == 0)) {
      isValid = false;
      break;
    }
  }
  return isValid && total == 100;
}

void GfMenuObjButtonChallenge2::dispRelationHUD(bool) {}

void GfMenuObjButtonChallenge2::open(GfMenuCallContext *context, unsigned int challenge, bool isDispButton, bool isSound) {
  OpenParam param;
  importOpenParam(param, challenge);
  param.unknown50.unknown00 = isDispButton;
  param.unknown50.unknown01 = isSound;
  open(context, param, 0);
}

void GfMenuObjButtonChallenge2::open(GfMenuCallContext *context, unsigned int challenge, const OptionParam &option) {
  OpenParam param;
  importOpenParam(param, challenge);
  param.unknown50 = option;
  open(context, param, 0);
}

void GfMenuObjButtonChallenge2::openSequence(GfMenuCallContext *context, unsigned int challenge, bool isDispButton, bool isSound) {
  u32 id = Bdat::getVal(GfDataBdat::getFP(BDAT_MNU_BTN_CHALLENGE_SEQ), "challenge01", challenge).valueU16;
  if (id != 0) {
    OpenParam param;
    importOpenParam(param, id);
    param.unknown50.unknown00 = isDispButton;
    param.unknown50.unknown01 = isSound;
    open(context, param, challenge);
  }
}

void GfMenuObjButtonChallenge2::openSequence(GfMenuCallContext *context, unsigned int challenge, const OptionParam &option) {
  u32 id = Bdat::getVal(GfDataBdat::getFP(BDAT_MNU_BTN_CHALLENGE_SEQ), "challenge01", challenge).valueU16;
  if (id != 0) {
    OpenParam param;
    importOpenParam(param, id);
    param.unknown50 = option;
    open(context, param, challenge);
  }
}

u32 GfMenuObjButtonChallenge2::getResultPoint() const {
  u32 point = unknown98;
  if (unknown90 != 0) {
    point = unknown98 / (unknown94 + 1);
  }
  return point;
}

void GfMenuObjButtonChallenge2::resume(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCNext(context, unknown001)) {
    unknown144(unknown001, 0x101);
  }
}

void GfMenuObjButtonChallenge2::close(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCNext(context, unknown001)) {
    unknown144(unknown001, GfMenuTypes::unknown003_34);
  }
}

void GfMenuObjButtonChallenge2::setSpeedFactor(GfMenuCallContext *context, f32 speedFactor) {
  if (GfMenuObjUtil::checkCCNext(context, unknown001)) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
    if (acc.isValid()) {
      ui::EventData event;
      event.unknown0c = 0;
      event.unknown00 = 0x102;
      event.unknown08_f32 = speedFactor;
      GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
    }
  }
}

void GfMenuObjButtonChallenge2::stopSeqCtrl() {
  for (int *ctrl = unknown330.begin(); ctrl != unknown330.end(); ctrl++) {
    GfMenuObjUtil::stopCtrl(*ctrl);
  }
  unknown330.clear();
}

bool GfMenuObjButtonChallenge2::seqStart() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  main.setDisp(true);
  unknown98 = 0;
  unknown80 = 0;
  unknown84 = 0;
  unknown88 = 0;
  unknown330.clear();
  unknown9c = 1.0f;
  GfMenuObject::enableInput(ui::UIObjectAcc(unknown18, "LAY_main").unknown10);
  unknown358 = false;
  unknown359 = false;
  unknown0a0.unknown002(&GfMenuObjButtonChallenge2::seqAppearCursor);
  return true;
}

void GfMenuObjButtonChallenge2::setupV2(const OpenParam &param) {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  mm::mtl::FixStr<32> name;
  if (unknown28.unknown08.size() == 0) {
    GfMenuObject::termCallContext(main.unknown10);
  } else {
    for (u32 i = 0; i < unknown28.unknown08.size(); i++) {
      name.format("LAY_challenge_v2@%02d", i + 1);
      GfMenuObject::sendOpenEvent(main.searchChild(name.c_str()), i, 0.0f);
    }
    unknown80 = 0;
    unknown84 = 0;
    unknown498 = 0;
    unknown49c = 0;
    unknown490 = 0;
    unknown494 = 0;
  }
}

bool GfMenuObjButtonChallenge2::seqEnd() {
  ui::UIObjectAcc acc(unknown18, "LAY_main");
  acc.setDisp(false);
  GfMenuObject::termCallContext(GfMenuObject::getAttachedObject(unknown001));
  return true;
}

void GfMenuObjButtonChallenge2::notifyChallengeResult() {
  if (!unknown359) {
    GfMenuObject::addResultCallContext(GfMenuObject::getAttachedObject(unknown001), 2, getResultPoint());
    unknown359 = true;
  }
}

bool GfMenuObjButtonChallenge2::getChallengeMashingWait(u32 &wait) {
  if (unknown80 >= unknown28.unknown08.size()) {
    return false;
  }
  if (unknown28.unknown08[unknown80].unknown01 == 2) {
    wait = unknown28.unknown08[unknown80].unknown0a;
    return true;
  }
  return false;
}

void GfMenuObjButtonChallenge2::setRingScaleV2(u32 index, f32 scale) {
  mm::mtl::FixStr<32> name;
  name.format("POL_ring_v2@%02d", index + 1);
  ui::UIShapeRing *ring = unknown003(ui::UIObjectAcc(unknown18, name.c_str()).getShape());
  if (ring != nullptr) {
    ring->setScale(scale);
  }
}

void GfMenuObjButtonChallenge2::setRingScale(f32 scale) {
  ui::UIShapeRing *ring = unknown003(ui::UIObjectAcc(unknown18, "POL_ring_v2@04").getShape());
  if (ring != nullptr) {
    ring->setScale(scale);
  }
}

void GfMenuObjButtonChallenge2::updateChallenge() {
  if (unknown348.size() != 0 && unknown80 < unknown28.unknown08.size()) {
    mm::Rect<s16> rect;
    {
      ui::UIObjectAcc acc(unknown18, "POL_ring_v2@04");
      acc.getRect(rect, ui::UIObjectAcc::RECT_SCALED);
    }
    if (rect.width != 0 && rect.height != 0) {
      int ringSize = static_cast<int>(unknown3b2 * unknown348.front() - unknown3b0);
      if (unknown28.unknown08[unknown80].unknown01 == 1 && ringSize < unknown3b0) {
        unknown80++;
      }
    }
  }
}

bool GfMenuObjButtonChallenge2::isSeqCtrlBusy() {
  int *ctrl = unknown330.begin();
  while (ctrl != unknown330.end()) {
    if (GfMenuObjUtil::isBusyCtrl(*ctrl)) {
      ctrl++;
    } else {
      unknown330.erase(ctrl);
    }
  }
  return !unknown330.empty();
}

void GfMenuObjButtonChallenge2::nextChallenge() {
  unknown80++;
  if (unknown80 == unknown28.unknown08.size()) {
    notifyChallengeResult();
    unknown0a0.unknown002(&GfMenuObjButtonChallenge2::seqCheckSequence);
  } else {
    setup(unknown28, unknown80, false);
    unknown0a0.unknown002(&GfMenuObjButtonChallenge2::seqAppearCursor);
  }
}

bool GfMenuObjButtonChallenge2::seqWaitRestartV2() {
  if (!unknown4a0) {
    return false;
  }
  setupV2(unknown28);
  unknown0a0.unknown002(&GfMenuObjButtonChallenge2::seqRunningV2);
  return true;
}

bool GfMenuObjButtonChallenge2::seqWaitMashingV2() {
  if (unknown80 < unknown28.unknown08.size()) {
    if (++unknown490 < unknown498) {
      return false;
    }
    unknown80++;
  }
  ui::UIObjectAcc acc(unknown18, "LAY_challenge_v2");
  mm::mtl::FixStr<32> name;
  ui::EventData event;
  event.unknown00 = 0x104;
  for (u32 i = 0; i < unknown28.unknown08.size(); i++) {
    name.format("LAY_challenge_v2@%02d", i + 1);
    GfMenuObject::sendEvent(acc.searchChild(name.c_str()), event, 0.0f);
  }
  notifyChallengeResult();
  return true;
}
} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjButtonChallenge2>(const mm::mtl::Delegate<bool()> *);
