#include "event/ui_manager.h"

#include <stddef.h>

#include "event/debug_manager.h"
#include "event/dof_manager.h"
#include "event/fade_ctrl.h"
#include "event/fade_manager.h"
#include "event/frame_manager.h"
#include "event/mstxt_manager.h"
#include "event/skip_manager.h"
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

static constexpr s32 SKIP_WAIT_FRAMES = 14;
static constexpr s32 SKIP_OPEN_FRAME = 11;
static constexpr s32 PAD_ENABLE_WAIT_FRAMES = 40;

void UIManager::setPadDisable(bool isDisable) {
  if (isDisable) {
    ui::UIInputManager::get()->disable();
    unknown10 = (unknown10 & ~(FLAG_PAD_DISABLE | FLAG_PAD_ENABLE_WAIT)) | FLAG_PAD_DISABLE;
  } else {
    unknown2a0 = PAD_ENABLE_WAIT_FRAMES;
    unknown10 = (unknown10 & ~(FLAG_PAD_DISABLE | FLAG_PAD_ENABLE_WAIT)) | FLAG_PAD_ENABLE_WAIT;
  }
}

UIManager::UIManager()
    : unknown10(0), unknown14(0), unknown18(0), unknown1c(true), unknown20(nullptr), unknown28(nullptr), unknown30(nullptr), m_payoffUI(0), unknown40(nullptr), unknown48(nullptr), unknown50(nullptr),
      unknown58(0), unknown60(nullptr), unknown68(nullptr), unknown290(nullptr) {}

void UIManager::logout() {
  if ((unknown14 & DISP_FLAG_NOW_LOADING) != 0) {
    gf::GfMenuObjFade::dispLoading(false, 0);
  }
  unknown14 = 0;
}

void UIManager::clear() {
  if ((unknown10 & (FLAG_PAD_DISABLE | FLAG_PAD_ENABLE_WAIT)) != 0) {
    ui::UIInputManager::get()->enable();
  }
  if ((unknown10 & FLAG_MINIGAME) != 0) {
    if (unknown290 != nullptr) {
      unknown290->setTerminate();
    }
    unknown290 = nullptr;
  }
  if ((unknown10 & FLAG_HOMURA_HIKARI) != 0) {
    mm::mtl::Singleton<DofManager>::getPtr()->stop();
    unknown70.clear();
    unknown180.clear();
  }
  if ((unknown10 & FLAG_STAFFROLL) != 0) {
    gf::GfMenuManager::closeStaffroll();
  }
  if ((unknown10 & FLAG_OPENING_TELOP) != 0) {
    gf::GfMenuManager::closeOpeningTelop();
  }
  if ((unknown10 & FLAG_ZONE_TELOP) != 0) {
    gf::GfMenuObjZoneTelop::close(0.0f);
    mm::mtl::safeRelease(unknown68);
  }
  if ((unknown10 & FLAG_AVAN_TITLE) != 0) {
    gf::GfMenuObjChapterTelop::close(0);
    mm::mtl::safeRelease(unknown60);
  }
  if ((unknown10 & FLAG_CHAP_TELOP) != 0) {
    mm::mtl::safeRelease(unknown50);
  }
  if ((unknown10 & FLAG_BLADE_NAME) != 0) {
    gf::GfMenuObjBladeName::close();
    mm::mtl::safeRelease(unknown48);
  }
  if ((unknown10 & FLAG_REWARD) != 0) {
    gf::GfMenuObjBalloon::close(unknown40, true);
    mm::mtl::safeRelease(unknown40);
  }
  if ((unknown10 & FLAG_PAYOFF) != 0) {
    gf::GfMenuObjBalloon::close(unknown30, true);
    mm::mtl::safeRelease(unknown30);
  }
  if ((unknown10 & FLAG_SHOP) != 0) {
    gf::GfMenuObjShop::close(unknown28);
    mm::mtl::safeRelease(unknown28);
  }
  if ((unknown10 & FLAG_COMMON) != 0) {
    gf::GfMenuManager::closeCommonWindow();
  }
  if ((unknown10 & FLAG_SKIP) != 0) {
    gf::GfMenuObjEventSkip::close();
    mm::mtl::safeRelease(unknown20);
  }
  unknown10 = 0;
}

void UIManager::update() {
  if ((unknown10 & (FLAG_CHAP_TELOP | FLAG_CHAP_TELOP_WAIT)) == FLAG_CHAP_TELOP && unknown58-- <= 0) {
    unknown10 |= FLAG_CHAP_TELOP_WAIT;
  }
  if ((unknown10 & FLAG_CHAP_TELOP) != 0 && unknown50->isTerm()) {
    mm::mtl::safeRelease(unknown50);
    unknown10 &= ~FLAG_CHAP_TELOP;
    if ((unknown10 & FLAG_CHAP_TELOP_WAIT) != 0) {
      unknown10 &= ~FLAG_CHAP_TELOP_WAIT;
    }
  }
  if ((unknown10 & FLAG_AVAN_TITLE) != 0 && unknown60->isTerm()) {
    mm::mtl::safeRelease(unknown60);
    unknown10 &= ~FLAG_AVAN_TITLE;
  }
  if ((unknown10 & FLAG_ZONE_TELOP) != 0 && unknown68->isTerm()) {
    mm::mtl::safeRelease(unknown68);
    unknown10 &= ~FLAG_ZONE_TELOP;
  }
  if (unknown180.isPlay()) {
    unknown180.update(1.0f);
    mm::mtl::Singleton<DofManager>::getPtr()->play(1, 0.1f, 1.0f, 2.0f, 1.0f, 0.1f, unknown180.getValue(), 0, false, "homuriUI");
  } else if (unknown70.isPlay()) {
    unknown70.update(1.0f);
    mm::mtl::Singleton<DofManager>::getPtr()->play(1, 0.1f, 1.0f, 2.0f, 1.0f, 0.1f, unknown70.getValue(), 0, false, "homuriUI");
  }
  if ((unknown10 & FLAG_PAD_ENABLE_WAIT) != 0 && unknown2a0-- <= 0) {
    if ((unknown10 & FLAG_PAD_DISABLE) != 0) {
      ui::UIInputManager::get()->disable();
    } else {
      ui::UIInputManager::get()->enable();
    }
    unknown10 &= ~FLAG_PAD_ENABLE_WAIT;
  }
}

void UIManager::render() {}

void UIManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_UPDATE_SEQUENCE:
    logout();
    break;
  case MSG_TYPE_INIT:
  case MSG_TYPE_CLEAR:
    clear();
    break;
  case MSG_TYPE_UPDATE:
    update();
    break;
  default:
    break;
  }
}

bool UIManager::openSkip(bool &isSkip) {
  if ((unknown10 & FLAG_SKIP) == 0) {
    unknown10 |= FLAG_SKIP;
    unknown29c = SKIP_WAIT_FRAMES;
  } else {
    if (unknown29c == SKIP_OPEN_FRAME) {
      unknown20 = gf::GfMenuCallContext::create();
      gf::GfMenuObjEventSkip::open(unknown20);
    }
    if ((unknown29c < 0 || unknown29c-- == 0) && unknown20->isTerm()) {
      gf::GfMenuCallContext::GfMenuResult result = {};
      unknown20->popResult(result);
      mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_SKIP, false);
      unknown10 &= ~FLAG_SKIP;
      mm::mtl::safeRelease(unknown20);
      unknown29c = -1;
      isSkip = result.unknown04 == 0;
      return true;
    }
  }
  mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_SKIP, true);
  return false;
}

void UIManager::closeSkip() {
  if ((unknown10 & FLAG_SKIP) != 0) {
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_SKIP, false);
    gf::GfMenuObjEventSkip::close();
    mm::mtl::safeRelease(unknown20);
    unknown10 &= ~FLAG_SKIP;
  }
}

bool UIManager::isOpenSkipUI() const { return (unknown10 & FLAG_SKIP) != 0; }

bool UIManager::isOpenCommonUI() const { return (unknown10 & (FLAG_COMMON | FLAG_COMMON_FADE)) != 0; }

bool UIManager::execFieldSkill(u32 fieldSkill, bool &isSuccess) {
  if ((unknown10 & FLAG_FIELD_SKILL) == 0) {
    unknown1c = gf::GfGameUtil::evalSumFs(fieldSkill, 0);
    unknown10 |= FLAG_FIELD_SKILL;
  }
  if (gf::GfMenuFieldSkill::isRunning()) {
    mm::mtl::Singleton<SkipManager>::getPtr()->skip(false, 0.0f);
    mm::mtl::Singleton<SkipManager>::getPtr()->setSkipVolume(false);
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_FIELD_SKILL, true);
    return false;
  }
  mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_FIELD_SKILL, false);
  unknown10 &= ~FLAG_FIELD_SKILL;
  isSuccess = unknown1c;
  return true;
}

bool UIManager::isFieldSkill() const { return (unknown10 & FLAG_FIELD_SKILL) != 0; }

bool UIManager::openShopUI(u32 shop, bool &isBought) {
  if ((unknown10 & FLAG_SHOP) == 0) {
    unknown28 = gf::GfMenuCallContext::create();
    gf::GfMenuObjShop::OpenParam param;
    param.unknown00 = shop;
    gf::GfMenuObjShop::open(unknown28, param);
    unknown10 |= FLAG_SHOP;
  }
  if (!unknown28->isTerm()) {
    mm::mtl::Singleton<SkipManager>::getPtr()->skip(false, 0.0f);
    mm::mtl::Singleton<SkipManager>::getPtr()->setSkipVolume(false);
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_SHOP_UI, true);
    return false;
  }
  gf::GfMenuCallContext::GfMenuResult result = {};
  unknown28->popResult(result);
  mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_SHOP_UI, false);
  unknown10 &= ~FLAG_SHOP;
  mm::mtl::safeRelease(unknown28);
  isBought = result.unknown04 == 1;
  return true;
}

bool UIManager::isOpenShopUI() const { return (unknown10 & FLAG_SHOP) != 0; }

bool UIManager::openPayoffUI(const char *title, const mm::mtl::FixedVector<u32, 16> &values, const mm::mtl::FixedVector<const char *, 16> &names, const char *message) {
  if (!mm::mtl::Singleton<MstxtManager>::getPtr()->isLoaded()) {
    return true;
  }
  if ((unknown10 & FLAG_PAYOFF) == 0) {
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
    unknown10 |= FLAG_PAYOFF;
  }
  if (!unknown30->isTerm()) {
    mm::mtl::Singleton<SkipManager>::getPtr()->skip(false, 0.0f);
    mm::mtl::Singleton<SkipManager>::getPtr()->setSkipVolume(false);
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_PAYOFF_UI, true);
    return false;
  }
  gf::GfMenuCallContext::GfMenuResult result = {};
  unknown30->popResult(result);
  mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_PAYOFF_UI, false);
  unknown10 &= ~FLAG_PAYOFF;
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

bool UIManager::isOpenPayoffUI() const { return (unknown10 & FLAG_PAYOFF) != 0; }

bool UIManager::openRewardUI(u32 item) {
  bool isOpen = true;
  if ((unknown10 & FLAG_REWARD) == 0) {
    unknown40 = gf::GfMenuCallContext::create();
    gf::GfMenuObjBalloon::OpenGetItemParam param;
    param.unknown00 = item;
    isOpen = gf::GfMenuObjBalloon::openGetItem(unknown40, param);
    unknown10 |= FLAG_REWARD;
  }
  if (isOpen && !unknown40->isTerm()) {
    mm::mtl::Singleton<SkipManager>::getPtr()->skip(false, 0.0f);
    mm::mtl::Singleton<SkipManager>::getPtr()->setSkipVolume(false);
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_REWARD_UI, true);
    return false;
  }
  mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_REWARD_UI, false);
  unknown10 &= ~FLAG_REWARD;
  mm::mtl::safeRelease(unknown40);
  return true;
}

bool UIManager::isOpenRewardUI() const { return (unknown10 & FLAG_REWARD) != 0; }

void UIManager::openBladeNameUI() {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
    return;
  }
  mm::mtl::safeRelease(unknown48);
  unknown48 = gf::GfMenuCallContext::create();
  gf::GfMenuObjBladeCreate::openCreatedBladeName(unknown48);
  unknown10 |= FLAG_BLADE_NAME;
}

bool UIManager::openChapTelopUI(u32 chapter) {
  if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkip() && (unknown10 & FLAG_CHAP_TELOP) == 0) {
    unknown50 = gf::GfMenuCallContext::create();
    gf::GfMenuObjChapterTelop::openEndTelop(unknown50, chapter);
    unknown58 = 1;
    mm::mtl::Singleton<FadeManager>::getPtr()->play(true, 0, FadeCtrl::PRIO_LOW, nullptr);
    unknown10 |= FLAG_CHAP_TELOP;
  }
  return true;
}

bool UIManager::isOpenChapTelopUI() const { return (unknown10 & FLAG_CHAP_TELOP) != 0; }

void UIManager::openAvanTitleUI(u32 title) {
  if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkip() && (unknown10 & FLAG_AVAN_TITLE) == 0) {
    unknown60 = gf::GfMenuCallContext::create();
    gf::GfMenuObjChapterTelop::openAvanTitle(unknown60, title);
    unknown10 |= FLAG_AVAN_TITLE;
  }
}

void UIManager::closeAvanTitleUI(int title) {
  if ((unknown10 & FLAG_AVAN_TITLE) != 0) {
    gf::GfMenuObjChapterTelop::close(title);
    mm::mtl::safeRelease(unknown60);
    unknown10 &= ~FLAG_AVAN_TITLE;
  }
}

bool UIManager::isAvanTitleUI() const { return (unknown10 & FLAG_AVAN_TITLE) != 0; }

void UIManager::openZoneTelopUI(u32 zone) {
  if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkip() && (unknown10 & FLAG_ZONE_TELOP) == 0) {
    unknown68 = gf::GfMenuCallContext::create();
    gf::GfMenuObjZoneTelop::open(unknown68, zone);
    unknown10 |= FLAG_ZONE_TELOP;
  }
}

void UIManager::closeZoneTelopUI() {
  if ((unknown10 & FLAG_ZONE_TELOP) != 0) {
    gf::GfMenuObjZoneTelop::close(0.0f);
    mm::mtl::safeRelease(unknown68);
    unknown10 &= ~FLAG_ZONE_TELOP;
  }
}

bool UIManager::isZoneTelopUI() const { return (unknown10 & FLAG_ZONE_TELOP) != 0; }

void UIManager::startOpeningTelop() {
  if ((unknown10 & FLAG_OPENING_TELOP) == 0) {
    gf::GfMenuManager::openOpeningTelop();
    unknown10 |= FLAG_OPENING_TELOP;
  }
}

void UIManager::openOpeningTelopUI(OPTELOP_TYPE type, u32 telop) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
    return;
  }
  startOpeningTelop();
  switch (type) {
  case OPTELOP_TYPE_CENTER:
    gf::GfMenuObjOpeningTelop::openCenter(telop);
    break;
  case OPTELOP_TYPE_LEFT:
    gf::GfMenuObjOpeningTelop::openLeft(telop);
    break;
  case OPTELOP_TYPE_RIGHT:
    gf::GfMenuObjOpeningTelop::openRight(telop);
    break;
  }
}

void UIManager::closeOpeningTelopUI(OPTELOP_TYPE type) {
  switch (type) {
  case OPTELOP_TYPE_CENTER:
    gf::GfMenuObjOpeningTelop::closeCenter();
    break;
  case OPTELOP_TYPE_LEFT:
    gf::GfMenuObjOpeningTelop::closeLeft();
    break;
  case OPTELOP_TYPE_RIGHT:
    gf::GfMenuObjOpeningTelop::closeRight();
    break;
  }
}

void UIManager::openStaffroll() {
  if ((unknown10 & FLAG_STAFFROLL) == 0) {
    gf::GfMenuManager::openStaffroll();
    unknown10 |= FLAG_STAFFROLL;
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

bool UIManager::isOpenHomuraHikariUI() const { return (unknown10 & FLAG_HOMURA_HIKARI) != 0; }

bool UIManager::startNewGameWait() {
  if (mm::mtl::Singleton<DebugManager>::getPtr()->isDisableNewGameWait()) {
    return true;
  }
  if ((unknown10 & FLAG_NEW_GAME_WAIT) == 0) {
    unknown10 |= FLAG_NEW_GAME_WAIT;
  }
  if ((unknown10 & FLAG_NEW_GAME_WAIT_END) == 0) {
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_NEW_GAME_WAIT, true);
    return false;
  }
  mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_NEW_GAME_WAIT, false);
  unknown10 &= ~FLAG_NEW_GAME_WAIT;
  return true;
}

void UIManager::finishNewGameWait() { unknown10 |= FLAG_NEW_GAME_WAIT_END; }

bool UIManager::isNewGameWait() const { return (unknown10 & FLAG_NEW_GAME_WAIT) != 0; }

bool UIManager::openMinigame() {
  if ((unknown10 & FLAG_MINIGAME) == 0) {
    unknown290 = minigame::tora::factory::create(nullptr);
    unknown10 |= FLAG_MINIGAME;
  }
  if (!unknown290->isTerminate()) {
    mm::mtl::Singleton<SkipManager>::getPtr()->skip(false, 0.0f);
    mm::mtl::Singleton<SkipManager>::getPtr()->setSkipVolume(false);
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_MINIGAME, true);
    return false;
  }
  mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_MINIGAME, false);
  unknown290->setTerminate();
  unknown290 = nullptr;
  unknown10 &= ~FLAG_MINIGAME;
  return true;
}

bool UIManager::isOpenMinigame() const { return (unknown10 & FLAG_MINIGAME) != 0; }

void UIManager::setDispNowLoading(bool isDisp) {
  if (isDisp) {
    if ((unknown14 & DISP_FLAG_NOW_LOADING) != 0) {
      return;
    }
    gf::GfMenuObjFade::dispLoading(true, 0);
    unknown14 |= DISP_FLAG_NOW_LOADING;
  } else {
    if ((unknown14 & DISP_FLAG_NOW_LOADING) == 0) {
      return;
    }
    gf::GfMenuObjFade::dispLoading(false, 0);
    unknown14 &= ~DISP_FLAG_NOW_LOADING;
  }
}

} // namespace event
