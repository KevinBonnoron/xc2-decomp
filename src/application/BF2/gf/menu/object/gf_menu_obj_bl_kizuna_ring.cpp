#include "gf/menu/object/gf_menu_obj_bl_kizuna_ring.h"

#include "gf/data/gf_data_achievement.h"
#include "gf/data/gf_data_blade.h"
#include "gf/game/gf_game_voice.h"
#include "gf/game/kizunaring/gf_kizunaring_manager.h"
#include "gf/game/kizunaring/gf_kizunaring_util.h"
#include "gf/game/quest/gf_quest_util.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_achievement_adapter.h"
#include "gf/menu/adapter/gf_menu_adapter_manager.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/request/gf_req_scom.h"
#include "gf/sound/gf_sound.h"
#include "gf/util/gf_item_util.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_list_info.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x6a;

// Inferred role: menu id; original name unknown.
constexpr u32 unknown002 = 0x22;

// Inferred role: nodes per ring of the pointer index; original name unknown.
constexpr u32 KIZUNARING_UNKNOWN_10 = 10;

GfMenuObjBlKizunaRing::GfMenuObjBlKizunaRing(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(false), unknown39(false), unknown3c(0), unknown40(-1), unknown48(nullptr), unknown50(0), unknown58(nullptr),
      unknown198(0), unknown1a0(this), unknown430(0), unknown434(0), unknown438(0), unknown43c(0), unknown440(nullptr), unknown448(nullptr), unknown450(0), unknown454(0), unknown458(nullptr),
      unknown460(0), unknown468(reinterpret_cast<GF_SCOM_HANDLE *>(-1)) {
  unknown58 = GfMenuCallContext::create();
}

GfMenuObjBlKizunaRing::~GfMenuObjBlKizunaRing() {
  mm::mtl::safeRelease(unknown58);
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown440);
  mm::mtl::safeRelease(unknown448);
}

void GfMenuObjBlKizunaRing::initialize() {
  {
    GfMenuTypes::Param layerParam;
    if (getFSLayerParam(unknown20, layerParam)) {
      unknown438 = layerParam.get<OpenParam>().unknown00;
      unknown43c = layerParam.get<OpenParam>().unknown04;
      removeFSLayerParam(unknown20);
    } else {
      unknown438 = 0;
    }
  }
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
// __LINE__ must be 191 as in the original file: it is the line argument of operator new.
#line 191
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
  attachExternalCall(unknown001, main);
  u32 ring = acc.searchChild("LAY_kizunaring");
// __LINE__ must be 197 as in the original file: it is the line argument of operator new.
#line 197
  RingListener *ringListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) RingListener(this);
  ringListener->addRef();
  ui::UIEventManager::get()->registObjectListener(ring, ringListener);
  if (ringListener != nullptr) {
    ringListener->release();
  }
  u32 ringBase = acc.searchChild("LAY_kizunaring_base");
// __LINE__ must be 201 as in the original file: it is the line argument of operator new.
#line 201
  RingPadListener *ringPadListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) RingPadListener(this);
  ringPadListener->addRef();
  ui::UIEventManager::get()->registObjectListener(ringBase, ringPadListener);
  if (ringPadListener != nullptr) {
    ringPadListener->release();
  }
  u32 skillInfo = acc.searchChild("LAY_skillinfo");
// __LINE__ must be 205 as in the original file: it is the line argument of operator new.
#line 205
  SkillDetailListener *skillDetailListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SkillDetailListener(this);
  skillDetailListener->addRef();
  ui::UIEventManager::get()->registObjectListener(skillInfo, skillDetailListener);
  if (skillDetailListener != nullptr) {
    skillDetailListener->release();
  }
  u32 skillStockInfo = acc.searchChild("LAY_skillstock_info");
// __LINE__ must be 215 as in the original file: it is the line argument of operator new.
#line 215
  BladeSkillInfoListener *bladeSkillInfoListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) BladeSkillInfoListener(this);
  bladeSkillInfoListener->addRef();
  ui::UIEventManager::get()->registObjectListener(skillStockInfo, bladeSkillInfoListener);
  if (bladeSkillInfoListener != nullptr) {
    bladeSkillInfoListener->release();
  }
  ui::UISelectObjList::CreateParam param;
  param.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
  unknown28 = ui::UISelectObjList::create(param);
  unknown440 = GfMenuCallContext::create();
  unknown448 = GfMenuItemList::create();
  ui::UIListInfoBase::SetupParam itemParam;
  unknown448->setup(getAllocator(ALLOCATOR_UNKNOWN_0), itemParam);
  unknown48 = GfMenuCallContext::create();
  disableInput(acc.searchChild("LAY_kizunaring"));
  disableInput(acc.searchChild("LAY_kizunaring_base"));
  GfMenuObject::initialize();
}

void GfMenuObjBlKizunaRing::registOpenParam(const OpenParam &param) {
  GfMenuTypes::Param layerParam;
  OpenParam &data = layerParam.get<OpenParam>();
  data.unknown00 = param.unknown00;
  data.unknown04 = param.unknown04;
  GfMenuFullScreen::registLayerParam(getMenuLayerID(unknown002), layerParam);
}

void GfMenuObjBlKizunaRing::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBlKizunaRing::update() {
  unknown1a0.unknown003();
  GfMenuObject::update();
}

void GfMenuObjBlKizunaRing::openForMercenary(u32 handle, u32 blade, u16 group) {
  OpenParam param;
  param.unknown00 = 1;
  param.unknown04 = blade;
  registOpenParam(param);
  changeFSSubLayer(handle, group, getMenuLayerID(unknown002), true);
}

bool GfMenuObjBlKizunaRing::isLockPos(int index) { return index % 10 == 0; }

bool GfMenuObjBlKizunaRing::isScreenLR(u32 screen) { return screen < 4; }

void GfMenuObjBlKizunaRing::setupMain(ui::UIObjectAcc &acc) {
  GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("IMG_face@01"), 3, 0, false);
  u32 background = acc.searchChild("IMG_bl_name_bg");
  u32 name = acc.searchChild("TXT_bl_name");
  GfMenuCharDataAdapter::createFromReferenceBlade(name, 2, 0, false);
  GfMenuObjUtil::FitOption option;
  GfMenuObjUtil::createFitPlugin(background, name, 42, 16, option);
}

void GfMenuObjBlKizunaRing::setupCircle(ui::UIObjectAcc &) {}

void GfMenuObjBlKizunaRing::setupBladeSkillInfo(ui::UIObjectAcc &acc) {
  GfMenuAchievementAdapter::createFromReferenceBlade(acc.searchChild("TXT_stocknum"), 16, 0, 0, 0, true);
  GfMenuAchievementAdapter::createFromReferenceBlade(acc.searchChild("TXT_stockmax"), 17, 0, 0, 0, false);
}

void GfMenuObjBlKizunaRing::setupSkillSimple(ui::UIObjectAcc &acc) {
  GfMenuAdapterManager::beginAddAfter();
  GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild("TXT_skillname"), 2, 0, 0, 1, false);
  GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild("IMG_skillicon"), 11, 0, 0, 1, false);
  GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild("IMG_skachicon"), 12, 0, 0, 1, false);
  GfMenuAdapterManager::endAddAfter();
}

void GfMenuObjBlKizunaRing::setupSkillDetail(ui::UIObjectAcc &acc) {
  GfMenuAdapterManager::beginAddAfter();
  GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild("TXT_questtitle"), 22, 0, 0, 1, false);
  GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild("TXT_questtitle2"), 23, 0, 0, 1, false);
  GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild("TXT_achinum"), 18, 0, 0, 1, false);
  GfMenuAchievementAdapter *count = GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild("TXT_achimax"), 19, 0, 0, 1, false);
  if (count != nullptr) {
    count->unknown24 = acc.searchChild("LAY_count");
  }
  GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild("LAY_neta"), 25, 0, 0, 1, false);
  mm::mtl::FixStr<32> name;
  for (u32 i = 1; i != 3; i++) {
    name.format("TXT_questinfo2@%02d", i);
    GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild(name.c_str()), 3, 0, 0, 1, false);
    name.format("TXT_skillname@%02d", i);
    GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild(name.c_str()), 2, 0, 0, 1, false);
    name.format("IMG_skill_icon@%02d", i);
    GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild(name.c_str()), 11, 0, 0, 1, false);
    name.format("IMG_skill_base@%02d", i);
    GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild(name.c_str()), 12, 0, 0, 1, false);
    name.format("IMG_idea_icon@%02d", i);
    GfMenuAchievementAdapter *idea = GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild(name.c_str()), 21, 0, 0, 1, false);
    if (idea != nullptr) {
      name.format("LAY_idea@%02d", i);
      idea->unknown24 = acc.searchChild(name.c_str());
    }
  }
  GfMenuAdapterManager::endAddAfter();
}

void GfMenuObjBlKizunaRing::setupRing(ui::UIObjectAcc &acc) {
  mm::mtl::FixStr<32> name;
  GfMenuAdapterManager::beginAddAfter();
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 10; j++) {
      name.format("IMG_node_icon@%02d", i + j * 5 + 1);
      if (acc.searchChild(name.c_str()) != 0) {
        GfMenuAchievementAdapter::createFromReferenceBlade(acc.searchChild(name.c_str()), 11, 0, j == 0 ? 9 : j - 1, i + 1, true);
        name.format("IMG_node_base@%02d", i + j * 5 + 1);
        if (acc.searchChild(name.c_str()) != 0) {
          GfMenuAchievementAdapter *base = GfMenuAchievementAdapter::createFromReferenceBlade(acc.searchChild(name.c_str()), 12, 0, j == 0 ? 9 : j - 1, i + 1, true);
          name.format("IMG_node_frame@%02d", i + j * 5 + 1);
          base->unknown24 = acc.searchChild(name.c_str());
        }
      }
    }
  }
  for (u16 level = 1; level <= 5; level++) {
    name.format("IMG_lock_icon@%02d", level);
    GfMenuAchievementAdapter::createFromReferenceBlade(acc.searchChild(name.c_str()), 24, 0, 9, level, true);
  }
  GfMenuAdapterManager::endAddAfter();
}

void GfMenuObjBlKizunaRing::refreshRing(ui::UIObjectAcc &acc) {
  u32 blade = GfMenuReference::getReferenceBladeID(0);
  mm::mtl::FixStr<32> name;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 10; j++) {
      name.format("IMG_node_icon@%02d", i + j * 5 + 1);
      ui::UIObjectAcc icon(acc.searchChild(name.c_str()));
      if (icon.isValid()) {
        name.format("IMG_node_base@%02d", i + j * 5 + 1);
        ui::UIObjectAcc base(acc.searchChild(name.c_str()));
        if (base.isValid()) {
          u32 state = GfKizunaringBlade::getReleaseAchievement(blade, j == 0 ? 9 : j - 1, i + 1);
          if (state == 0 || state == 1) {
            icon.setMulColor("white");
            base.setMulColor("gray");
          } else if (state == 4 || state == 5) {
            icon.setMulColor("white");
            base.setMulColor("white");
          } else {
            icon.setMulColor("black");
            base.setMulColor("gray");
          }
        }
      }
    }
  }
}

void GfMenuObjBlKizunaRing::setupRingList(ui::UIObjectAcc &acc, ui::UISelectObjList *list) {
  mm::mtl::FixStr<32> name;
  list->clear();
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 10; j++) {
      name.format("LAY_spot@%02d", i + j * 5 + 1);
      u32 spot = acc.searchChild(name.c_str());
      if (spot != 0) {
        list->addObject(spot);
      }
    }
  }
}

void GfMenuObjBlKizunaRing::movePointer(u32 handle, int index, ui::UISelectObjList *list) {
  setupInputSelection(handle, index, list->getSize());
  mm::Pnt<s16> pos;
  {
    ui::UIObjectAcc acc(list->getContents(index));
    acc.getPosCenter(pos);
  }
  changePointerPos(handle, pos);
}

void GfMenuObjBlKizunaRing::dispDetail(ui::UIObjectAcc &acc, u32 blade) {
  int line = GfMenuReference::getReferenceNumber(0);
  int level = GfMenuReference::getReferenceNumber(1);
  u16 type = GfMenuTypes::unknown003_33;
  if (GfKizunaringBlade::getReleaseAchievement(blade, GfMenuReference::getReferenceNumber(0), GfMenuReference::getReferenceNumber(1)) == 0) {
    type = GfMenuTypes::unknown003_34;
  }
  ACHIEVEMENT_TYPE achievementType;
  u32 index;
  if (GfDataAchievement::getAchievementType(achievementType, index, GfMenuReference::getReferenceNumber(0))) {
    if (achievementType == ACHIEVEMENT_TYPE_UNKNOWN_3 && line == 9 && level == 1) {
      type = GfMenuTypes::unknown003_34;
    }
  }
  unknown164(acc.searchChild("LAY_skillinfo"), type);
}

int GfMenuObjBlKizunaRing::getAchievementList(mm::mtl::FixedVector<Achievement, 50> &list, u32 &count, u32 &flags) {
  u32 blade = GfMenuReference::getReferenceBladeID(0);
  list.clear();
  for (int i = 4; i >= 0; i--) {
    u32 level = i + 1;
    for (int line = 9; line >= 0; line--) {
      if (GfKizunaringBlade::getReleaseAchievement(blade, line, level) == 3) {
        if (line == 9) {
          for (int other = 8; other >= 0; other--) {
            if (GfKizunaringBlade::getReleaseAchievement(blade, other, level) == 1) {
              list.push_back(Achievement(other, level, 1));
            }
          }
          if (i < 4) {
            list.push_back(Achievement(9, i + 2, 1));
          }
          count = 1;
          flags |= 1;
        } else {
          count = 2;
          flags |= 2;
        }
        list.push_back(Achievement(line, level, 3));
      }
    }
  }
  return list.size();
}

bool GfMenuObjBlKizunaRing::procAchieve(u32 handle, GfMenuObjBlKizunaRing *object) {
  object->unknown50 = 0;
  object->unknown454 = 0;
  if (getAchievementList(object->unknown60, object->unknown50, object->unknown454) == 0) {
    return false;
  }
  object->unknown430 = 1;
  object->unknown434 = 0;
  object->unknown1a0.unknown005();
  object->unknown1a0.unknown002(&GfMenuObjBlKizunaRing::seqAchieve);
  if (object->unknown438 == 0) {
    GfMenuObjMainMenu2::disableCharChange();
  }
  ui::UIObjectAcc cursor(handle, "IMG_kizunacursor");
  cursor.setDisp(false);
  {
    ui::UIObjectAcc acc(handle);
    disableInput(acc.searchChild("LAY_kizunaring_base"));
  }
  if (object->unknown438 == 0) {
    GfMenuObjMainMenu2::setCloseKeyEnable(false);
  }
  return true;
}

bool GfMenuObjBlKizunaRing::seqComplete() {
  u32 blade = GfMenuReference::getReferenceBladeID(0);
  if (GfDataBlade::isKizunaringComplete(blade)) {
    return true;
  }
  if (GfDataBlade::getKizunaringMax(blade) > GfDataBlade::getKizunaringCompleteNum(blade)) {
    return true;
  }
  ui::UIObjectAcc acc(unknown18);
  ui::UIObjectAcc complete(acc.searchChild("LAY_complete"));
  switch (unknown434) {
  case 0: {
    complete.setDisp(true);
    ui::UIObjectAcc image(complete.searchChild("IMG_complete"));
    image.startAnimation("fade_in", false);
    ui::UIObjectAcc text(complete.searchChild("TXT_complete"));
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x10000000;
    param.unknown50 = "mnu89_complete_telop";
    param.unknown58 = "fade_in";
    param.unknown14 = 10;
    GfMenuObjUtil::startCtrl(text.unknown10, param, nullptr);
    GfMenuObjUtil::playJingle(0x10);
    unknown468 = SCOM_FIELD_VOICE::createAchievementAll(blade);
    unknown434++;
    break;
  }
  case 1: {
    ui::UIObjectAcc image(complete.searchChild("IMG_complete"));
    if (!image.isPlayingAnimation()) {
      complete.setDisp(false);
      unknown448->clear();
      GfQuestReward reward;
      if (!GfKizunaringUtil::getCompleteKizunaringReward(reward, blade)) {
        return true;
      }
      for (u32 i = 8; i < 12; i++) {
        u16 item = reward.unknown00[i].unknown44;
        if (item != 0) {
          MenuItemInfo info;
          info.unknown00 = GfItemUtil::getType(item);
          info.unknown04 = item;
          info.unknown08 = reward.unknown00[i].m_developZone;
          unknown448->addContents(info);
        }
      }
      unknown440->reset();
      GfMenuObjCommonText::openGetItem(unknown440, unknown448);
      unknown434++;
    }
    break;
  }
  case 2:
    if (!GfReqSmallCom::get()->isValid(unknown468) && unknown440->isTerm()) {
      GfDataBlade::setKizunaringComplete(blade);
      unknown434 = 0;
      return true;
    }
    break;
  }
  return false;
}

bool GfMenuObjBlKizunaRing::seqAchieve() {
  ui::UIObjectAcc acc(unknown18);
  mm::mtl::FixStr<32> name;
  u32 blade = GfMenuReference::getReferenceBladeID(0);
  switch (unknown430) {
  case 1:
    if (unknown60.size() == 0) {
      if (getAchievementList(unknown60, unknown50, unknown454) == 0) {
        unknown430 = 0;
        sendEvent(acc.searchChild("LAY_main"), GfMenuTypes::unknown003_33, 0);
        return true;
      }
      unknown430 = 1;
    } else {
      Achievement achievement = unknown60.back();
      u32 index = achievement.unknown00 * 5 + (achievement.unknown02 - 1);
      if (achievement.unknown04 != 1 || index < 0x2d) {
        unknown198 = index;
        if (index <= 0x2c) {
          name.format("IMG_node_eff@%02d", index + 6);
        } else {
          name.format("IMG_lock_eff@%02d", index - 0x2c);
        }
        ui::UIObjectAcc effect(acc.searchChild(name.c_str()));
        effect.startAnimation(achievement.unknown04 == 1 ? "skill_open" : "skill_learn", false);
        if (achievement.unknown04 == 3) {
          GfMenuObjUtil::playSE(0xf);
          if (achievement.unknown00 != 9) {
            unknown460 = achievement.unknown00;
          }
        }
      }
      unknown430 = 2;
    }
    return false;
  case 2: {
    if (unknown198 <= 0x2c) {
      name.format("IMG_node_eff@%02d", unknown198 + 6);
    } else {
      name.format("IMG_lock_eff@%02d", unknown198 - 0x2c);
    }
    ui::UIObjectAcc effect(acc.searchChild(name.c_str()));
    if (unknown60.size() != 1 || !effect.isPlayingAnimation()) {
      Achievement achievement = unknown60.back();
      unknown60.pop_back();
      u32 index = unknown198;
      if (achievement.unknown04 == 3 && index > 0x2c) {
        const char *lines[] = {"linea", "lineb", "linec", "lined", "linee"};
        u32 line = index - 0x2d;
        if (line < 5) {
          ui::UIObjectAcc(acc.searchChild("IMG_kizunabg_eff")).startAnimation(lines[line], false);
        }
        GfMenuObjUtil::playSE(0x10);
      }
      if (achievement.unknown04 == 3) {
        GfKizunaringBlade::releaseAchievement(blade, achievement.unknown00, achievement.unknown02);
      } else {
        GfKizunaringBlade::orderAchievement(blade, achievement.unknown00, achievement.unknown02);
      }
      refreshRing(acc);
      unknown430 = 1;
    }
    return false;
  }
  default:
    return true;
  }
}

void GfMenuObjBlKizunaRing::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjBlKizunaRing::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjBlKizunaRing::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

bool GfMenuObjBlKizunaRing::attach(GfMenuCallContext *context) { return unknown151(context, unknown001); }

bool GfMenuObjBlKizunaRing::seqWait() {
  ui::UIObjectAcc acc(unknown18);
  ui::UIObjectAcc base(acc.searchChild("LAY_kizunaring_base"));
  enableInput(base.unknown10);
  return true;
}

bool GfMenuObjBlKizunaRing::seqEnd() {
  ui::UIObjectAcc acc(unknown18);
  refreshRing(acc);
  ui::UIObjectAcc cursor(acc.searchChild("IMG_kizunacursor"));
  cursor.setDisp(true);
  cursor.startAnimation("loop", false);
  enableInput(acc.searchChild("LAY_kizunaring_base"));
  if (unknown438 == 0) {
    GfMenuObjMainMenu2::setCloseKeyEnable(true);
  }
  unknown140(acc.searchChild("LAY_kizunaring"), GfMenuTypes::unknown003_33, 0, 0.0f);
  return true;
}

bool GfMenuObjBlKizunaRing::seqWaitVoice() {
  u32 result = GfGameVoice::getResult(unknown458);
  if (result == CV_RESULT_UNKNOWN_1 || result == CV_RESULT_UNKNOWN_2) {
    return false;
  }
  ui::UIObjectAcc acc(unknown18);
  unknown140(acc.searchChild("LAY_main"), GfMenuTypes::unknown003_33, 0, 0.0f);
  return true;
}

void GfMenuObjBlKizunaRing::RingPadListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc owner(unknown20->unknown18);
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObject::setupInputSelection(handle, 0, 10);
    GfMenuObject::disableInput(handle);
    break;
  case 6:
    break;
  case 8: {
    int next;
    switch (event.unknown0c) {
    case 2:
      unknown140(owner.searchChild("LAY_main"), GfMenuTypes::unknown003_34, 0, 0.0f);
      GfMenuObject::disableInput(handle);
      if (unknown20->unknown438 == 0) {
        GfMenuObjMainMenu2::disableCharChange();
      }
      GfMenuObjUtil::playSECommonCancel();
      return;
    case 10: {
      int index = unknown20->unknown40;
      if (index < 0) {
        return;
      }
      u32 ring = index / KIZUNARING_UNKNOWN_10;
      u32 pos = index % KIZUNARING_UNKNOWN_10;
      if (pos < 5) {
        if (ring == 0) {
          return;
        }
        next = ring * KIZUNARING_UNKNOWN_10 - KIZUNARING_UNKNOWN_10 + pos;
      } else {
        if (ring + 1 > 4) {
          return;
        }
        next = (ring + 1) * KIZUNARING_UNKNOWN_10 + pos;
      }
      break;
    }
    case 9: {
      int index = unknown20->unknown40;
      if (index < 0) {
        return;
      }
      u32 ring = index / KIZUNARING_UNKNOWN_10;
      u32 pos = index % KIZUNARING_UNKNOWN_10;
      if (pos < 5) {
        if (ring + 1 > 4) {
          return;
        }
        next = (ring + 1) * KIZUNARING_UNKNOWN_10 + pos;
      } else {
        if (ring == 0) {
          return;
        }
        next = ring * KIZUNARING_UNKNOWN_10 - KIZUNARING_UNKNOWN_10 + pos;
      }
      break;
    }
    case 12: {
      int index = unknown20->unknown40;
      if (index < 0 || index % KIZUNARING_UNKNOWN_10 == 0) {
        return;
      }
      next = index - 1;
      break;
    }
    case 11: {
      int index = unknown20->unknown40;
      if (index < 0 || index % KIZUNARING_UNKNOWN_10 > 8) {
        return;
      }
      next = index + 1;
      break;
    }
    default:
      return;
    }
    GfMenuObject::changePointerPos(owner.searchChild("LAY_kizunaring"), mm::Pnt<s16>(0, 0));
    movePointer(owner.searchChild("LAY_kizunaring"), next, unknown20->unknown28);
    GfMenuObjUtil::playSECommonTab();
    unknown140(handle, 0x101, 0, 0.0f);
    break;
  }
  case 0x101:
    unknown20->unknown1a0.unknown005();
    unknown20->unknown1a0.unknown004(1);
    unknown20->unknown1a0.unknown002(&GfMenuObjBlKizunaRing::seqWait);
    GfMenuObject::disableInput(handle);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjBlKizunaRing::BladeSkillInfoListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc owner(unknown20->unknown18);
  ui::UIObjectAcc acc(handle);
  if (event.unknown00 == 1) {
    setupBladeSkillInfo(acc);
    acc.setDisp(true);
  } else {
    ui::UIObjectListener::reciveEvent(event, handle);
  }
}

void GfMenuObjBlKizunaRing::SkillDetailListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc owner(unknown20->unknown18);
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    setupSkillDetail(acc);
    acc.setDisp(false);
    break;
  case GfMenuTypes::unknown003_33: {
    u32 blade = GfMenuReference::getReferenceBladeID(0);
    u32 line = GfMenuReference::getReferenceNumber(0);
    u32 level = GfMenuReference::getReferenceNumber(1);
    const char *layout = line < 4 || line == 9 ? "blskillinfo2_2" : "blskillinfo2_1";
    ui::UIObjectAcc main(owner.searchChild("LAY_main"));
    mm::Rect<s16> rect;
    main.getLayoutRect(layout, rect);
    mm::Pnt<s16> pos(rect.unknown00);
    acc.setPos(pos);
    ui::UIObjectAcc title(acc.searchChild("LAY_questtitle"));
    ui::UIObjectAcc title2(acc.searchChild("LAY_questtitle2"));
    ui::UIObjectAcc clear(acc.searchChild("LAY_clear"));
    ui::UIObjectAcc normal(acc.searchChild("LAY_normal"));
    ui::UIObjectAcc small(acc.searchChild("LAY_small"));
    u8 *bdat;
    u32 id;
    ui::UIObjectAcc icon(acc.searchChild("IMG_skill_icon@01"));
    ui::UIObjectAcc base(acc.searchChild("IMG_skill_base@01"));
    u32 state = GfKizunaringBlade::getReleaseAchievement(blade, line, level);
    if (state == 4 || state == 5) {
      title.setDisp(false);
      bool hasText = false;
      if (GfDataBlade::getTaskResultMessage(bdat, id, blade, line, level)) {
        ui::UIStr text(bdat, id);
        hasText = text.size() != 0;
      }
      title2.setDisp(hasText);
      clear.setDisp(false);
      if (hasText) {
        normal.setDisp(true);
        small.setDisp(false);
      } else {
        normal.setDisp(false);
        small.setDisp(true);
      }
      icon.setMulColor("white");
      base.setMulColor("white");
    } else {
      bool hasText = false;
      if (GfDataBlade::getTaskTitleMessage(bdat, id, blade, line, level)) {
        ui::UIStr text(bdat, id);
        hasText = text.size() != 0;
      }
      title.setDisp(hasText);
      title2.setDisp(false);
      clear.setDisp(true);
      if (hasText) {
        normal.setDisp(true);
        small.setDisp(false);
      } else {
        normal.setDisp(false);
        small.setDisp(true);
      }
      if (line == 9 || state == 0 || state == 1) {
        icon.setMulColor("white");
      } else {
        icon.setMulColor("black");
      }
      base.setMulColor("gray");
    }
    if (!unknown20->unknown39) {
      unknown20->unknown39 = true;
      GfMenuObject::hookCtrlEvent(handle, GfMenuObjUtil::setCommonFadeIn(handle, 1, 0));
    }
    break;
  }
  case GfMenuTypes::unknown003_34:
    if (unknown20->unknown39) {
      unknown20->unknown39 = false;
      GfMenuObject::hookCtrlEvent(handle, GfMenuObjUtil::setCommonFadeOut(handle, 2, 0));
    }
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}
} // namespace gf

template bool gf::GfMenuSequence<gf::GfMenuObjBlKizunaRing, 8>::wait();
template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjBlKizunaRing, 8>>(const mm::mtl::Delegate<bool()> *);
template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjBlKizunaRing>(const mm::mtl::Delegate<bool()> *);
