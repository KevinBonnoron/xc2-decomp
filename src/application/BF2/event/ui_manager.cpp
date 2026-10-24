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
    flags = (flags & ~(FLAG_PAD_DISABLE | FLAG_PAD_ENABLE_WAIT)) | FLAG_PAD_DISABLE;
  } else {
    padWait = PAD_ENABLE_WAIT_FRAMES;
    flags = (flags & ~(FLAG_PAD_DISABLE | FLAG_PAD_ENABLE_WAIT)) | FLAG_PAD_ENABLE_WAIT;
  }
}

UIManager::UIManager()
    : flags(0), dispFlags(0), state(0), isFieldSkillSuccess(true), skipContext(nullptr), shopContext(nullptr), payoffContext(nullptr), payoffResult(0), rewardContext(nullptr),
      bladeNameContext(nullptr), chapTelopContext(nullptr), chapTelopWait(0), avanTitleContext(nullptr), zoneTelopContext(nullptr), minigame(nullptr) {}

void UIManager::logout() {
  if ((dispFlags & DISP_FLAG_NOW_LOADING) != 0) {
    gf::GfMenuObjFade::dispLoading(false, 0);
  }
  dispFlags = 0;
}

void UIManager::clear() {
  if ((flags & (FLAG_PAD_DISABLE | FLAG_PAD_ENABLE_WAIT)) != 0) {
    ui::UIInputManager::get()->enable();
  }
  if ((flags & FLAG_MINIGAME) != 0) {
    if (minigame != nullptr) {
      minigame->setTerminate();
    }
    minigame = nullptr;
  }
  if ((flags & FLAG_HOMURA_HIKARI) != 0) {
    mm::mtl::Singleton<DofManager>::getPtr()->stop();
    homuraAnm.clear();
    hikariAnm.clear();
  }
  if ((flags & FLAG_STAFFROLL) != 0) {
    gf::GfMenuManager::closeStaffroll();
  }
  if ((flags & FLAG_OPENING_TELOP) != 0) {
    gf::GfMenuManager::closeOpeningTelop();
  }
  if ((flags & FLAG_ZONE_TELOP) != 0) {
    gf::GfMenuObjZoneTelop::close(0.0f);
    mm::mtl::safeRelease(zoneTelopContext);
  }
  if ((flags & FLAG_AVAN_TITLE) != 0) {
    gf::GfMenuObjChapterTelop::close(0);
    mm::mtl::safeRelease(avanTitleContext);
  }
  if ((flags & FLAG_CHAP_TELOP) != 0) {
    mm::mtl::safeRelease(chapTelopContext);
  }
  if ((flags & FLAG_BLADE_NAME) != 0) {
    gf::GfMenuObjBladeName::close();
    mm::mtl::safeRelease(bladeNameContext);
  }
  if ((flags & FLAG_REWARD) != 0) {
    gf::GfMenuObjBalloon::close(rewardContext, true);
    mm::mtl::safeRelease(rewardContext);
  }
  if ((flags & FLAG_PAYOFF) != 0) {
    gf::GfMenuObjBalloon::close(payoffContext, true);
    mm::mtl::safeRelease(payoffContext);
  }
  if ((flags & FLAG_SHOP) != 0) {
    gf::GfMenuObjShop::close(shopContext);
    mm::mtl::safeRelease(shopContext);
  }
  if ((flags & FLAG_COMMON) != 0) {
    gf::GfMenuManager::closeCommonWindow();
  }
  if ((flags & FLAG_SKIP) != 0) {
    gf::GfMenuObjEventSkip::close();
    mm::mtl::safeRelease(skipContext);
  }
  flags = 0;
}

void UIManager::update() {
  if ((flags & (FLAG_CHAP_TELOP | FLAG_CHAP_TELOP_WAIT)) == FLAG_CHAP_TELOP && chapTelopWait-- <= 0) {
    flags |= FLAG_CHAP_TELOP_WAIT;
  }
  if ((flags & FLAG_CHAP_TELOP) != 0 && chapTelopContext->isTerm()) {
    mm::mtl::safeRelease(chapTelopContext);
    flags &= ~FLAG_CHAP_TELOP;
    if ((flags & FLAG_CHAP_TELOP_WAIT) != 0) {
      flags &= ~FLAG_CHAP_TELOP_WAIT;
    }
  }
  if ((flags & FLAG_AVAN_TITLE) != 0 && avanTitleContext->isTerm()) {
    mm::mtl::safeRelease(avanTitleContext);
    flags &= ~FLAG_AVAN_TITLE;
  }
  if ((flags & FLAG_ZONE_TELOP) != 0 && zoneTelopContext->isTerm()) {
    mm::mtl::safeRelease(zoneTelopContext);
    flags &= ~FLAG_ZONE_TELOP;
  }
  if (hikariAnm.isPlay()) {
    hikariAnm.update(1.0f);
    mm::mtl::Singleton<DofManager>::getPtr()->play(1, 0.1f, 1.0f, 2.0f, 1.0f, 0.1f, hikariAnm.getValue(), 0, false, "homuriUI");
  } else if (homuraAnm.isPlay()) {
    homuraAnm.update(1.0f);
    mm::mtl::Singleton<DofManager>::getPtr()->play(1, 0.1f, 1.0f, 2.0f, 1.0f, 0.1f, homuraAnm.getValue(), 0, false, "homuriUI");
  }
  if ((flags & FLAG_PAD_ENABLE_WAIT) != 0 && padWait-- <= 0) {
    if ((flags & FLAG_PAD_DISABLE) != 0) {
      ui::UIInputManager::get()->disable();
    } else {
      ui::UIInputManager::get()->enable();
    }
    flags &= ~FLAG_PAD_ENABLE_WAIT;
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
  if ((flags & FLAG_SKIP) == 0) {
    flags |= FLAG_SKIP;
    skipWait = SKIP_WAIT_FRAMES;
  } else {
    if (skipWait == SKIP_OPEN_FRAME) {
      skipContext = gf::GfMenuCallContext::create();
      gf::GfMenuObjEventSkip::open(skipContext);
    }
    if ((skipWait < 0 || skipWait-- == 0) && skipContext->isTerm()) {
      gf::GfMenuCallContext::GfMenuResult result = {};
      skipContext->popResult(result);
      mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_SKIP, false);
      flags &= ~FLAG_SKIP;
      mm::mtl::safeRelease(skipContext);
      skipWait = -1;
      isSkip = result.type == 0;
      return true;
    }
  }
  mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_SKIP, true);
  return false;
}

void UIManager::closeSkip() {
  if ((flags & FLAG_SKIP) != 0) {
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_SKIP, false);
    gf::GfMenuObjEventSkip::close();
    mm::mtl::safeRelease(skipContext);
    flags &= ~FLAG_SKIP;
  }
}

bool UIManager::isOpenSkipUI() const { return (flags & FLAG_SKIP) != 0; }

bool UIManager::isOpenCommonUI() const { return (flags & (FLAG_COMMON | FLAG_COMMON_FADE)) != 0; }

bool UIManager::execFieldSkill(u32 fieldSkill, bool &isSuccess) {
  if ((flags & FLAG_FIELD_SKILL) == 0) {
    isFieldSkillSuccess = gf::GfGameUtil::evalSumFs(fieldSkill, 0);
    flags |= FLAG_FIELD_SKILL;
  }
  if (gf::GfMenuFieldSkill::isRunning()) {
    mm::mtl::Singleton<SkipManager>::getPtr()->skip(false, 0.0f);
    mm::mtl::Singleton<SkipManager>::getPtr()->setSkipVolume(false);
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_FIELD_SKILL, true);
    return false;
  }
  mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_FIELD_SKILL, false);
  flags &= ~FLAG_FIELD_SKILL;
  isSuccess = isFieldSkillSuccess;
  return true;
}

bool UIManager::isFieldSkill() const { return (flags & FLAG_FIELD_SKILL) != 0; }

bool UIManager::openShopUI(u32 shop, bool &isBought) {
  if ((flags & FLAG_SHOP) == 0) {
    shopContext = gf::GfMenuCallContext::create();
    gf::GfMenuObjShop::OpenParam param;
    param.shop = shop;
    gf::GfMenuObjShop::open(shopContext, param);
    flags |= FLAG_SHOP;
  }
  if (!shopContext->isTerm()) {
    mm::mtl::Singleton<SkipManager>::getPtr()->skip(false, 0.0f);
    mm::mtl::Singleton<SkipManager>::getPtr()->setSkipVolume(false);
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_SHOP_UI, true);
    return false;
  }
  gf::GfMenuCallContext::GfMenuResult result = {};
  shopContext->popResult(result);
  mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_SHOP_UI, false);
  flags &= ~FLAG_SHOP;
  mm::mtl::safeRelease(shopContext);
  isBought = result.type == 1;
  return true;
}

bool UIManager::isOpenShopUI() const { return (flags & FLAG_SHOP) != 0; }

bool UIManager::openPayoffUI(const char *title, const mm::mtl::FixedVector<u32, 16> &values, const mm::mtl::FixedVector<const char *, 16> &names, const char *message) {
  if (!mm::mtl::Singleton<MstxtManager>::getPtr()->isLoaded()) {
    return true;
  }
  if ((flags & FLAG_PAYOFF) == 0) {
    u8 *bdat = mm::mtl::Singleton<MstxtManager>::getPtr()->getFp();
    payoffContext = gf::GfMenuCallContext::create();
    gf::GfMenuObjBalloon::OpenSelectMoneyParam param;
    param.bdat = bdat;
    if (title != nullptr && *title != '\0') {
      int textId = mm::mtl::Singleton<MstxtManager>::getPtr()->getSeatID(title);
      if (textId >= 0) {
        param.textId = textId;
      }
    }
    for (size_t i = 0; i < values.size() && i < param.moneys.capacity(); i++) {
      param.moneys.push_back(values[i]);
    }
    for (size_t i = 0; i < names.size() && i < param.nameIds.capacity(); i++) {
      if (names[i] != nullptr && *names[i] != '\0') {
        int nameId = mm::mtl::Singleton<MstxtManager>::getPtr()->getSeatID(names[i]);
        if (nameId >= 0) {
          param.nameIds.push_back(nameId);
        }
      }
    }
    if (message != nullptr && *message != '\0') {
      int messageId = mm::mtl::Singleton<MstxtManager>::getPtr()->getSeatID(message);
      if (messageId >= 0) {
        param.messageId = messageId;
      }
    }
    gf::GfMenuObjBalloon::openEventSelectMoney(payoffContext, param);
    flags |= FLAG_PAYOFF;
  }
  if (!payoffContext->isTerm()) {
    mm::mtl::Singleton<SkipManager>::getPtr()->skip(false, 0.0f);
    mm::mtl::Singleton<SkipManager>::getPtr()->setSkipVolume(false);
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_PAYOFF_UI, true);
    return false;
  }
  gf::GfMenuCallContext::GfMenuResult result = {};
  payoffContext->popResult(result);
  mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_PAYOFF_UI, false);
  flags &= ~FLAG_PAYOFF;
  mm::mtl::safeRelease(payoffContext);
  int index = -1;
  for (size_t i = 0; i < values.size(); i++) {
    if (values[i] == static_cast<u32>(result.value)) {
      index = i;
      break;
    }
  }
  payoffResult = index >= 0 ? index + 1 : 0;
  return true;
}

u32 UIManager::getPayoffUI() const { return payoffResult; }

bool UIManager::isOpenPayoffUI() const { return (flags & FLAG_PAYOFF) != 0; }

bool UIManager::openRewardUI(u32 item) {
  bool isOpen = true;
  if ((flags & FLAG_REWARD) == 0) {
    rewardContext = gf::GfMenuCallContext::create();
    gf::GfMenuObjBalloon::OpenGetItemParam param;
    param.item = item;
    isOpen = gf::GfMenuObjBalloon::openGetItem(rewardContext, param);
    flags |= FLAG_REWARD;
  }
  if (isOpen && !rewardContext->isTerm()) {
    mm::mtl::Singleton<SkipManager>::getPtr()->skip(false, 0.0f);
    mm::mtl::Singleton<SkipManager>::getPtr()->setSkipVolume(false);
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_REWARD_UI, true);
    return false;
  }
  mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_REWARD_UI, false);
  flags &= ~FLAG_REWARD;
  mm::mtl::safeRelease(rewardContext);
  return true;
}

bool UIManager::isOpenRewardUI() const { return (flags & FLAG_REWARD) != 0; }

void UIManager::openBladeNameUI() {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
    return;
  }
  mm::mtl::safeRelease(bladeNameContext);
  bladeNameContext = gf::GfMenuCallContext::create();
  gf::GfMenuObjBladeCreate::openCreatedBladeName(bladeNameContext);
  flags |= FLAG_BLADE_NAME;
}

bool UIManager::openChapTelopUI(u32 chapter) {
  if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkip() && (flags & FLAG_CHAP_TELOP) == 0) {
    chapTelopContext = gf::GfMenuCallContext::create();
    gf::GfMenuObjChapterTelop::openEndTelop(chapTelopContext, chapter);
    chapTelopWait = 1;
    mm::mtl::Singleton<FadeManager>::getPtr()->play(true, 0, FadeCtrl::PRIO_LOW, nullptr);
    flags |= FLAG_CHAP_TELOP;
  }
  return true;
}

bool UIManager::isOpenChapTelopUI() const { return (flags & FLAG_CHAP_TELOP) != 0; }

void UIManager::openAvanTitleUI(u32 title) {
  if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkip() && (flags & FLAG_AVAN_TITLE) == 0) {
    avanTitleContext = gf::GfMenuCallContext::create();
    gf::GfMenuObjChapterTelop::openAvanTitle(avanTitleContext, title);
    flags |= FLAG_AVAN_TITLE;
  }
}

void UIManager::closeAvanTitleUI(int title) {
  if ((flags & FLAG_AVAN_TITLE) != 0) {
    gf::GfMenuObjChapterTelop::close(title);
    mm::mtl::safeRelease(avanTitleContext);
    flags &= ~FLAG_AVAN_TITLE;
  }
}

bool UIManager::isAvanTitleUI() const { return (flags & FLAG_AVAN_TITLE) != 0; }

void UIManager::openZoneTelopUI(u32 zone) {
  if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkip() && (flags & FLAG_ZONE_TELOP) == 0) {
    zoneTelopContext = gf::GfMenuCallContext::create();
    gf::GfMenuObjZoneTelop::open(zoneTelopContext, zone);
    flags |= FLAG_ZONE_TELOP;
  }
}

void UIManager::closeZoneTelopUI() {
  if ((flags & FLAG_ZONE_TELOP) != 0) {
    gf::GfMenuObjZoneTelop::close(0.0f);
    mm::mtl::safeRelease(zoneTelopContext);
    flags &= ~FLAG_ZONE_TELOP;
  }
}

bool UIManager::isZoneTelopUI() const { return (flags & FLAG_ZONE_TELOP) != 0; }

void UIManager::startOpeningTelop() {
  if ((flags & FLAG_OPENING_TELOP) == 0) {
    gf::GfMenuManager::openOpeningTelop();
    flags |= FLAG_OPENING_TELOP;
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
  if ((flags & FLAG_STAFFROLL) == 0) {
    gf::GfMenuManager::openStaffroll();
    flags |= FLAG_STAFFROLL;
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

bool UIManager::isOpenHomuraHikariUI() const { return (flags & FLAG_HOMURA_HIKARI) != 0; }

bool UIManager::startNewGameWait() {
  if (mm::mtl::Singleton<DebugManager>::getPtr()->isDisableNewGameWait()) {
    return true;
  }
  if ((flags & FLAG_NEW_GAME_WAIT) == 0) {
    flags |= FLAG_NEW_GAME_WAIT;
  }
  if ((flags & FLAG_NEW_GAME_WAIT_END) == 0) {
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_NEW_GAME_WAIT, true);
    return false;
  }
  mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_NEW_GAME_WAIT, false);
  flags &= ~FLAG_NEW_GAME_WAIT;
  return true;
}

void UIManager::finishNewGameWait() { flags |= FLAG_NEW_GAME_WAIT_END; }

bool UIManager::isNewGameWait() const { return (flags & FLAG_NEW_GAME_WAIT) != 0; }

bool UIManager::openMinigame() {
  if ((flags & FLAG_MINIGAME) == 0) {
    minigame = minigame::tora::factory::create(nullptr);
    flags |= FLAG_MINIGAME;
  }
  if (!minigame->isTerminate()) {
    mm::mtl::Singleton<SkipManager>::getPtr()->skip(false, 0.0f);
    mm::mtl::Singleton<SkipManager>::getPtr()->setSkipVolume(false);
    mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_MINIGAME, true);
    return false;
  }
  mm::mtl::Singleton<FrameManager>::getPtr()->pause(FrameManager::PAUSE_TYPE_MINIGAME, false);
  minigame->setTerminate();
  minigame = nullptr;
  flags &= ~FLAG_MINIGAME;
  return true;
}

bool UIManager::isOpenMinigame() const { return (flags & FLAG_MINIGAME) != 0; }

void UIManager::setDispNowLoading(bool isDisp) {
  if (isDisp) {
    if ((dispFlags & DISP_FLAG_NOW_LOADING) != 0) {
      return;
    }
    gf::GfMenuObjFade::dispLoading(true, 0);
    dispFlags |= DISP_FLAG_NOW_LOADING;
  } else {
    if ((dispFlags & DISP_FLAG_NOW_LOADING) == 0) {
      return;
    }
    gf::GfMenuObjFade::dispLoading(false, 0);
    dispFlags &= ~DISP_FLAG_NOW_LOADING;
  }
}

} // namespace event
