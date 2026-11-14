#include "event/ui_manager.h"

#include <stddef.h>

#include "event/curve.h"
#include "event/debug_manager.h"
#include "event/dof_manager.h"
#include "event/fade_ctrl.h"
#include "event/fade_manager.h"
#include "event/frame_manager.h"
#include "event/mstxt_manager.h"
#include "event/skip_manager.h"
#include "event/status_manager.h"
#include "framework/object/updatable_object.h"
#include "gf/game/gf_game_util.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_field_skill.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/object/gf_menu_obj_balloon.h"
#include "gf/menu/object/gf_menu_obj_blade_create.h"
#include "gf/menu/object/gf_menu_obj_blade_name.h"
#include "gf/menu/object/gf_menu_obj_chapter_telop.h"
#include "gf/menu/object/gf_menu_obj_event_skip.h"
#include "gf/menu/object/gf_menu_obj_fade.h"
#include "gf/menu/object/gf_menu_obj_opening_telop.h"
#include "gf/menu/object/gf_menu_obj_shop.h"
#include "gf/menu/object/gf_menu_obj_staffroll.h"
#include "gf/menu/object/gf_menu_obj_zone_telop.h"
#include "minigame/tora/minigame_tora.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/singleton.h"
#include "ui/input/ui_input_manager.h"

namespace event {

static constexpr s32 SKIP_UNKNOWN_14 = 14;            // Inferred role: skip wait frames; original name unknown.
static constexpr s32 SKIP_UNKNOWN_11 = 11;            // Inferred role: skip open frame; original name unknown.
static constexpr s32 PAD_ENABLE_WAIT_UNKNOWN_40 = 40; // Inferred role: pad enable wait frames; original name unknown.
static constexpr u32 COMMON_WINDOW_UNKNOWN_73 = 73;   // Inferred role: first common window opened behind a fade; original name unknown.
static constexpr u32 COMMON_WINDOW_UNKNOWN_153 = 153; // Inferred role: last common window opened behind a fade; original name unknown.
static constexpr s32 COMMON_WAIT_UNKNOWN_30 = 30;     // Inferred role: common window wait frames; original name unknown.

void UIManager::setPadDisable(bool isDisable) {
  if (isDisable) {
    ui::UIInputManager::get()->disable();
    unknown10 = (unknown10 & ~(FLAG_UNKNOWN_20 | FLAG_UNKNOWN_21)) | FLAG_UNKNOWN_20;
  } else {
    unknown2a0 = PAD_ENABLE_WAIT_UNKNOWN_40;
    unknown10 = (unknown10 & ~(FLAG_UNKNOWN_20 | FLAG_UNKNOWN_21)) | FLAG_UNKNOWN_21;
  }
}

UIManager::UIManager()
    : unknown10(0), unknown14(0), unknown18(0), unknown1c(true), unknown20(nullptr), unknown28(nullptr), unknown30(nullptr), m_payoffUI(0), unknown40(nullptr), unknown48(nullptr), unknown50(nullptr),
      unknown58(0), unknown60(nullptr), unknown68(nullptr), unknown290(nullptr) {}

void UIManager::logout() {
  if ((unknown14 & DISP_FLAG_UNKNOWN_0) != 0) {
    gf::GfMenuObjFade::dispLoading(false, 0);
  }
  unknown14 = 0;
}

void UIManager::clear() {
  if ((unknown10 & (FLAG_UNKNOWN_20 | FLAG_UNKNOWN_21)) != 0) {
    ui::UIInputManager::get()->enable();
  }
  if ((unknown10 & FLAG_UNKNOWN_19) != 0) {
    if (unknown290 != nullptr) {
      unknown290->setTerminate();
    }
    unknown290 = nullptr;
  }
  if ((unknown10 & FLAG_UNKNOWN_114688) != 0) {
    mm::mtl::Singleton<DofManager>::getPtr()->stop();
    unknown70.clear();
    unknown180.clear();
  }
  if ((unknown10 & FLAG_UNKNOWN_13) != 0) {
    gf::GfMenuManager::closeStaffroll();
  }
  if ((unknown10 & FLAG_UNKNOWN_12) != 0) {
    gf::GfMenuManager::closeOpeningTelop();
  }
  if ((unknown10 & FLAG_UNKNOWN_11) != 0) {
    gf::GfMenuObjZoneTelop::close(0.0f);
    mm::mtl::safeRelease(unknown68);
  }
  if ((unknown10 & FLAG_UNKNOWN_10) != 0) {
    gf::GfMenuObjChapterTelop::close(0);
    mm::mtl::safeRelease(unknown60);
  }
  if ((unknown10 & FLAG_UNKNOWN_8) != 0) {
    mm::mtl::safeRelease(unknown50);
  }
  if ((unknown10 & FLAG_UNKNOWN_7) != 0) {
    gf::GfMenuObjBladeName::close();
    mm::mtl::safeRelease(unknown48);
  }
  if ((unknown10 & FLAG_UNKNOWN_6) != 0) {
    gf::GfMenuObjBalloon::close(unknown40, true);
    mm::mtl::safeRelease(unknown40);
  }
  if ((unknown10 & FLAG_UNKNOWN_5) != 0) {
    gf::GfMenuObjBalloon::close(unknown30, true);
    mm::mtl::safeRelease(unknown30);
  }
  if ((unknown10 & FLAG_UNKNOWN_4) != 0) {
    gf::GfMenuObjShop::close(unknown28);
    mm::mtl::safeRelease(unknown28);
  }
  if ((unknown10 & FLAG_UNKNOWN_1) != 0) {
    gf::GfMenuManager::closeCommonWindow();
  }
  if ((unknown10 & FLAG_UNKNOWN_0) != 0) {
    gf::GfMenuObjEventSkip::close();
    mm::mtl::safeRelease(unknown20);
  }
  unknown10 = 0;
}

void UIManager::update() {
  if ((unknown10 & (FLAG_UNKNOWN_8 | FLAG_UNKNOWN_9)) == FLAG_UNKNOWN_8 && unknown58-- <= 0) {
    unknown10 |= FLAG_UNKNOWN_9;
  }
  if ((unknown10 & FLAG_UNKNOWN_8) != 0 && unknown50->isTerm()) {
    mm::mtl::safeRelease(unknown50);
    unknown10 &= ~FLAG_UNKNOWN_8;
    if ((unknown10 & FLAG_UNKNOWN_9) != 0) {
      unknown10 &= ~FLAG_UNKNOWN_9;
    }
  }
  if ((unknown10 & FLAG_UNKNOWN_10) != 0 && unknown60->isTerm()) {
    mm::mtl::safeRelease(unknown60);
    unknown10 &= ~FLAG_UNKNOWN_10;
  }
  if ((unknown10 & FLAG_UNKNOWN_11) != 0 && unknown68->isTerm()) {
    mm::mtl::safeRelease(unknown68);
    unknown10 &= ~FLAG_UNKNOWN_11;
  }
  if (unknown180.isPlay()) {
    unknown180.update(1.0f);
    mm::mtl::Singleton<DofManager>::getPtr()->play(1, 0.1f, 1.0f, 2.0f, 1.0f, 0.1f, unknown180.getValue(), 0, false, "homuriUI");
  } else if (unknown70.isPlay()) {
    unknown70.update(1.0f);
    mm::mtl::Singleton<DofManager>::getPtr()->play(1, 0.1f, 1.0f, 2.0f, 1.0f, 0.1f, unknown70.getValue(), 0, false, "homuriUI");
  }
  if ((unknown10 & FLAG_UNKNOWN_21) != 0 && unknown2a0-- <= 0) {
    if ((unknown10 & FLAG_UNKNOWN_20) != 0) {
      ui::UIInputManager::get()->disable();
    } else {
      ui::UIInputManager::get()->enable();
    }
    unknown10 &= ~FLAG_UNKNOWN_21;
  }
}

void UIManager::render() {}

void UIManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_UNKNOWN_2:
    logout();
    break;
  case MSG_TYPE_UNKNOWN_4:
  case MSG_TYPE_UNKNOWN_12:
    clear();
    break;
  case MSG_TYPE_UNKNOWN_14:
    update();
    break;
  default:
    break;
  }
}

bool UIManager::openSkip(bool &isSkip) {
  if ((unknown10 & FLAG_UNKNOWN_0) == 0) {
    unknown10 |= FLAG_UNKNOWN_0;
    unknown29c = SKIP_UNKNOWN_14;
  } else {
    if (unknown29c == SKIP_UNKNOWN_11) {
      unknown20 = gf::GfMenuCallContext::create();
      gf::GfMenuObjEventSkip::open(unknown20);
    }
    if ((unknown29c < 0 || unknown29c-- == 0) && unknown20->isTerm()) {
      gf::GfMenuCallContext::GfMenuResult result = {};
      unknown20->popResult(result);
      mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_UNKNOWN_1, false);
      unknown10 &= ~FLAG_UNKNOWN_0;
      mm::mtl::safeRelease(unknown20);
      unknown29c = -1;
      isSkip = result.unknown04 == 0;
      return true;
    }
  }
  mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_UNKNOWN_1, true);
  return false;
}

void UIManager::closeSkip() {
  if ((unknown10 & FLAG_UNKNOWN_0) != 0) {
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_UNKNOWN_1, false);
    gf::GfMenuObjEventSkip::close();
    mm::mtl::safeRelease(unknown20);
    unknown10 &= ~FLAG_UNKNOWN_0;
  }
}

bool UIManager::isOpenSkipUI() const { return (unknown10 & FLAG_UNKNOWN_0) != 0; }

bool UIManager::openCommonUI(u32 window) {
  bool isFade = window >= COMMON_WINDOW_UNKNOWN_73 && window <= COMMON_WINDOW_UNKNOWN_153;
  if ((unknown10 & FLAG_UNKNOWN_2) == 0) {
    bool isSkip = mm::mtl::Singleton<SkipManager>::getPtr()->isSkip();
    if (isFade) {
      mm::mtl::Singleton<FadeManager>::getPtr()->play(true, 40, FadeCtrl::PRIO_LOW, nullptr);
    }
    unknown298 = isSkip ? 0 : COMMON_WAIT_UNKNOWN_30;
    unknown10 |= FLAG_UNKNOWN_2;
  }
  bool isOpen = true;
  if (!isFade || (!mm::mtl::Singleton<FadeManager>::getPtr()->isFading() && unknown298-- <= 0)) {
    if ((unknown10 & FLAG_UNKNOWN_1) == 0) {
      gf::GfMenuManager::openCommonWindow(window);
      unknown10 |= FLAG_UNKNOWN_1;
    }
    isOpen = gf::GfMenuManager::isOpenCommonWindow();
  }
  if (isOpen) {
    mm::mtl::Singleton<SkipManager>::getPtr()->skip(false, 0.0f);
    mm::mtl::Singleton<SkipManager>::getPtr()->setSkipVolume(false);
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_UNKNOWN_4, true);
    return false;
  }
  mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_UNKNOWN_4, false);
  unknown10 &= ~(FLAG_UNKNOWN_1 | FLAG_UNKNOWN_2);
  return true;
}

bool UIManager::isOpenCommonUI() const { return (unknown10 & (FLAG_UNKNOWN_1 | FLAG_UNKNOWN_2)) != 0; }

bool UIManager::execFieldSkill(u32 fieldSkill, bool &isSuccess) {
  if ((unknown10 & FLAG_UNKNOWN_3) == 0) {
    unknown1c = gf::GfGameUtil::evalSumFs(fieldSkill, 0);
    unknown10 |= FLAG_UNKNOWN_3;
  }
  if (gf::GfMenuFieldSkill::isRunning()) {
    mm::mtl::Singleton<SkipManager>::getPtr()->skip(false, 0.0f);
    mm::mtl::Singleton<SkipManager>::getPtr()->setSkipVolume(false);
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_UNKNOWN_5, true);
    return false;
  }
  mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_UNKNOWN_5, false);
  unknown10 &= ~FLAG_UNKNOWN_3;
  isSuccess = unknown1c;
  return true;
}

bool UIManager::isFieldSkill() const { return (unknown10 & FLAG_UNKNOWN_3) != 0; }

bool UIManager::openShopUI(u32 shop, bool &isBought) {
  if ((unknown10 & FLAG_UNKNOWN_4) == 0) {
    unknown28 = gf::GfMenuCallContext::create();
    gf::GfMenuObjShop::OpenParam param;
    param.unknown00 = shop;
    gf::GfMenuObjShop::open(unknown28, param);
    unknown10 |= FLAG_UNKNOWN_4;
  }
  if (!unknown28->isTerm()) {
    mm::mtl::Singleton<SkipManager>::getPtr()->skip(false, 0.0f);
    mm::mtl::Singleton<SkipManager>::getPtr()->setSkipVolume(false);
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_UNKNOWN_6, true);
    return false;
  }
  gf::GfMenuCallContext::GfMenuResult result = {};
  unknown28->popResult(result);
  mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_UNKNOWN_6, false);
  unknown10 &= ~FLAG_UNKNOWN_4;
  mm::mtl::safeRelease(unknown28);
  isBought = result.unknown04 == 1;
  return true;
}

bool UIManager::isOpenShopUI() const { return (unknown10 & FLAG_UNKNOWN_4) != 0; }

bool UIManager::openPayoffUI(const char *title, const mm::mtl::FixedVector<u32, 16> &values, const mm::mtl::FixedVector<const char *, 16> &names, const char *message) {
  if (!mm::mtl::Singleton<MstxtManager>::getPtr()->isLoaded()) {
    return true;
  }
  if ((unknown10 & FLAG_UNKNOWN_5) == 0) {
    u8 *bdat = mm::mtl::Singleton<MstxtManager>::getPtr()->getFp();
    unknown30 = gf::GfMenuCallContext::create();
    gf::GfMenuObjBalloon::OpenSelectMoneyParam param;
    param.unknown00 = bdat;
    if (title != nullptr && *title != '\0') {
      int textId = mm::mtl::Singleton<MstxtManager>::getPtr()->getSeatID(title);
      if (textId >= 0) {
        param.unknown08 = textId;
      }
    }
    for (size_t i = 0; i < values.size() && i < param.unknown10.capacity(); i++) {
      param.unknown10.push_back(values[i]);
    }
    for (size_t i = 0; i < names.size() && i < param.unknown28.capacity(); i++) {
      if (names[i] != nullptr && *names[i] != '\0') {
        int nameId = mm::mtl::Singleton<MstxtManager>::getPtr()->getSeatID(names[i]);
        if (nameId >= 0) {
          param.unknown28.push_back(nameId);
        }
      }
    }
    if (message != nullptr && *message != '\0') {
      int messageId = mm::mtl::Singleton<MstxtManager>::getPtr()->getSeatID(message);
      if (messageId >= 0) {
        param.unknown0c = messageId;
      }
    }
    gf::GfMenuObjBalloon::openEventSelectMoney(unknown30, param);
    unknown10 |= FLAG_UNKNOWN_5;
  }
  if (!unknown30->isTerm()) {
    mm::mtl::Singleton<SkipManager>::getPtr()->skip(false, 0.0f);
    mm::mtl::Singleton<SkipManager>::getPtr()->setSkipVolume(false);
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_UNKNOWN_7, true);
    return false;
  }
  gf::GfMenuCallContext::GfMenuResult result = {};
  unknown30->popResult(result);
  mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_UNKNOWN_7, false);
  unknown10 &= ~FLAG_UNKNOWN_5;
  mm::mtl::safeRelease(unknown30);
  int index = -1;
  for (size_t i = 0; i < values.size(); i++) {
    if (values[i] == static_cast<u32>(result.unknown00)) {
      index = i;
      break;
    }
  }
  m_payoffUI = index >= 0 ? index + 1 : 0;
  return true;
}

u32 UIManager::getPayoffUI() const { return m_payoffUI; }

bool UIManager::isOpenPayoffUI() const { return (unknown10 & FLAG_UNKNOWN_5) != 0; }

bool UIManager::openRewardUI(u32 item) {
  bool isOpen = true;
  if ((unknown10 & FLAG_UNKNOWN_6) == 0) {
    unknown40 = gf::GfMenuCallContext::create();
    gf::GfMenuObjBalloon::OpenGetItemParam param;
    param.unknown00 = item;
    isOpen = gf::GfMenuObjBalloon::openGetItem(unknown40, param);
    unknown10 |= FLAG_UNKNOWN_6;
  }
  if (isOpen && !unknown40->isTerm()) {
    mm::mtl::Singleton<SkipManager>::getPtr()->skip(false, 0.0f);
    mm::mtl::Singleton<SkipManager>::getPtr()->setSkipVolume(false);
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_UNKNOWN_8, true);
    return false;
  }
  mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_UNKNOWN_8, false);
  unknown10 &= ~FLAG_UNKNOWN_6;
  mm::mtl::safeRelease(unknown40);
  return true;
}

bool UIManager::isOpenRewardUI() const { return (unknown10 & FLAG_UNKNOWN_6) != 0; }

void UIManager::openBladeNameUI() {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
    return;
  }
  mm::mtl::safeRelease(unknown48);
  unknown48 = gf::GfMenuCallContext::create();
  gf::GfMenuObjBladeCreate::openCreatedBladeName(unknown48);
  unknown10 |= FLAG_UNKNOWN_7;
}

bool UIManager::openChapTelopUI(u32 chapter) {
  if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkip() && (unknown10 & FLAG_UNKNOWN_8) == 0) {
    unknown50 = gf::GfMenuCallContext::create();
    gf::GfMenuObjChapterTelop::openEndTelop(unknown50, chapter);
    unknown58 = 1;
    mm::mtl::Singleton<FadeManager>::getPtr()->play(true, 0, FadeCtrl::PRIO_LOW, nullptr);
    unknown10 |= FLAG_UNKNOWN_8;
  }
  return true;
}

bool UIManager::isOpenChapTelopUI() const { return (unknown10 & FLAG_UNKNOWN_8) != 0; }

void UIManager::openAvanTitleUI(u32 title) {
  if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkip() && (unknown10 & FLAG_UNKNOWN_10) == 0) {
    unknown60 = gf::GfMenuCallContext::create();
    gf::GfMenuObjChapterTelop::openAvanTitle(unknown60, title);
    unknown10 |= FLAG_UNKNOWN_10;
  }
}

void UIManager::closeAvanTitleUI(int title) {
  if ((unknown10 & FLAG_UNKNOWN_10) != 0) {
    gf::GfMenuObjChapterTelop::close(title);
    mm::mtl::safeRelease(unknown60);
    unknown10 &= ~FLAG_UNKNOWN_10;
  }
}

bool UIManager::isAvanTitleUI() const { return (unknown10 & FLAG_UNKNOWN_10) != 0; }

void UIManager::openZoneTelopUI(u32 zone) {
  if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkip() && (unknown10 & FLAG_UNKNOWN_11) == 0) {
    unknown68 = gf::GfMenuCallContext::create();
    gf::GfMenuObjZoneTelop::open(unknown68, zone);
    unknown10 |= FLAG_UNKNOWN_11;
  }
}

void UIManager::closeZoneTelopUI() {
  if ((unknown10 & FLAG_UNKNOWN_11) != 0) {
    gf::GfMenuObjZoneTelop::close(0.0f);
    mm::mtl::safeRelease(unknown68);
    unknown10 &= ~FLAG_UNKNOWN_11;
  }
}

bool UIManager::isZoneTelopUI() const { return (unknown10 & FLAG_UNKNOWN_11) != 0; }

void UIManager::startOpeningTelop() {
  if ((unknown10 & FLAG_UNKNOWN_12) == 0) {
    gf::GfMenuManager::openOpeningTelop();
    unknown10 |= FLAG_UNKNOWN_12;
  }
}

void UIManager::openOpeningTelopUI(OPTELOP_TYPE type, u32 telop) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
    return;
  }
  startOpeningTelop();
  switch (type) {
  case OPTELOP_TYPE_UNKNOWN_0:
    gf::GfMenuObjOpeningTelop::openCenter(telop);
    break;
  case OPTELOP_TYPE_UNKNOWN_1:
    gf::GfMenuObjOpeningTelop::openLeft(telop);
    break;
  case OPTELOP_TYPE_UNKNOWN_2:
    gf::GfMenuObjOpeningTelop::openRight(telop);
    break;
  }
}

void UIManager::closeOpeningTelopUI(OPTELOP_TYPE type) {
  switch (type) {
  case OPTELOP_TYPE_UNKNOWN_0:
    gf::GfMenuObjOpeningTelop::closeCenter();
    break;
  case OPTELOP_TYPE_UNKNOWN_1:
    gf::GfMenuObjOpeningTelop::closeLeft();
    break;
  case OPTELOP_TYPE_UNKNOWN_2:
    gf::GfMenuObjOpeningTelop::closeRight();
    break;
  }
}

void UIManager::openStaffroll() {
  if ((unknown10 & FLAG_UNKNOWN_13) == 0) {
    gf::GfMenuManager::openStaffroll();
    unknown10 |= FLAG_UNKNOWN_13;
  }
}

void UIManager::startStaffrollUI(f32 frame, int type) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
    return;
  }
  openStaffroll();
  gf::GfMenuObjStaffroll::start(frame / 30.0f, type);
}

void UIManager::endStaffroll() { gf::GfMenuObjStaffroll::fadeout(); }

bool UIManager::openHomuraHikariUI() {
  if ((unknown10 & FLAG_UNKNOWN_14) == 0) {
    unknown70.clear();
    unknown70.append(0.0f, 0.7f, CV_TYPE_UNKNOWN_1);
    unknown10 |= FLAG_UNKNOWN_14;
  }
  bool isEnd = false;
  if (unknown70.isEnd()) {
    if ((unknown10 & FLAG_UNKNOWN_15) == 0) {
      gf::GfMenuManager::openNameSelect();
      unknown10 |= FLAG_UNKNOWN_15;
    }
    if (!gf::GfMenuManager::isOpenNameSelect()) {
      if ((unknown10 & FLAG_UNKNOWN_16) == 0) {
        unknown180.clear();
        unknown180.append(0.0f, 0.7f, CV_TYPE_UNKNOWN_1);
        unknown180.append(15.0f, 0.0f, CV_TYPE_UNKNOWN_1);
        unknown10 |= FLAG_UNKNOWN_16;
      }
      isEnd = unknown180.isEnd();
    }
  }
  if (!isEnd) {
    mm::mtl::Singleton<SkipManager>::getPtr()->skip(false, 0.0f);
    mm::mtl::Singleton<SkipManager>::getPtr()->setSkipVolume(false);
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_UNKNOWN_11, true);
    return false;
  }
  if (mm::mtl::Singleton<StatusManager>::getPtr()->getHomuriFlag() == 0) {
    mm::mtl::Singleton<DebugManager>::getPtr()->playMessage("choice HOMURA");
  } else {
    mm::mtl::Singleton<DebugManager>::getPtr()->playMessage("choice HIKARI");
  }
  mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_UNKNOWN_11, false);
  mm::mtl::Singleton<DofManager>::getPtr()->stop();
  unknown70.clear();
  unknown180.clear();
  unknown10 &= ~FLAG_UNKNOWN_114688;
  return true;
}

bool UIManager::isOpenHomuraHikariUI() const { return (unknown10 & FLAG_UNKNOWN_114688) != 0; }

bool UIManager::startNewGameWait() {
  if (mm::mtl::Singleton<DebugManager>::getPtr()->isDisableNewGameWait()) {
    return true;
  }
  if ((unknown10 & FLAG_UNKNOWN_17) == 0) {
    unknown10 |= FLAG_UNKNOWN_17;
  }
  if ((unknown10 & FLAG_UNKNOWN_18) == 0) {
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_UNKNOWN_13, true);
    return false;
  }
  mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_UNKNOWN_13, false);
  unknown10 &= ~FLAG_UNKNOWN_17;
  return true;
}

void UIManager::finishNewGameWait() { unknown10 |= FLAG_UNKNOWN_18; }

bool UIManager::isNewGameWait() const { return (unknown10 & FLAG_UNKNOWN_17) != 0; }

bool UIManager::openMinigame() {
  if ((unknown10 & FLAG_UNKNOWN_19) == 0) {
    unknown290 = minigame::tora::factory::create(nullptr);
    unknown10 |= FLAG_UNKNOWN_19;
  }
  if (!unknown290->isTerminate()) {
    mm::mtl::Singleton<SkipManager>::getPtr()->skip(false, 0.0f);
    mm::mtl::Singleton<SkipManager>::getPtr()->setSkipVolume(false);
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_UNKNOWN_12, true);
    return false;
  }
  mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_UNKNOWN_12, false);
  unknown290->setTerminate();
  unknown290 = nullptr;
  unknown10 &= ~FLAG_UNKNOWN_19;
  return true;
}

bool UIManager::isOpenMinigame() const { return (unknown10 & FLAG_UNKNOWN_19) != 0; }

void UIManager::setDispNowLoading(bool isDisp) {
  if (isDisp) {
    if ((unknown14 & DISP_FLAG_UNKNOWN_0) != 0) {
      return;
    }
    gf::GfMenuObjFade::dispLoading(true, 0);
    unknown14 |= DISP_FLAG_UNKNOWN_0;
  } else {
    if ((unknown14 & DISP_FLAG_UNKNOWN_0) == 0) {
      return;
    }
    gf::GfMenuObjFade::dispLoading(false, 0);
    unknown14 &= ~DISP_FLAG_UNKNOWN_0;
  }
}

} // namespace event
