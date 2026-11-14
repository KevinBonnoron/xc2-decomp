#include "gf/menu/object/gf_menu_obj_arts_palette2.h"

#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_battle_adapter.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/adapter/gf_menu_gfobj_adapter.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {
class GfMenuCallContext;

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x28;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x101;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown003 = 0x100;

// Inferred role: battle state read by GfMenuManager::isBattleState, normal; original name unknown.
constexpr u32 BATTLE_STATE_UNKNOWN_0 = 0;

// Inferred role: cursor display state and selection flag when the palette is reset; original name unknown.
static const GfMenuObjArtsPalette2::MainListener::unknown004 unknown005 = {0, 0};

GfMenuObjArtsPalette2::GfMenuObjArtsPalette2(u32 handle) : GfMenuObject(handle), unknown24(-1), unknown28(nullptr), unknown30(nullptr), unknown38_u64(0), unknown40(0), unknown44(0) {}

GfMenuObjArtsPalette2::~GfMenuObjArtsPalette2() {
  unknown50 = nullptr;
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
}

void GfMenuObjArtsPalette2::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (main.isValid()) {
// __LINE__ must be 105 as in the original file: it is the line argument of operator new.
#line 105
    MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
    mainListener->addRef();
    ui::UIEventManager::get()->registObjectListener(main.unknown10, mainListener);
    if (mainListener != nullptr) {
      mainListener->release();
    }
    attachExternalCall(unknown001, main.unknown10);
    {
      ui::UISelectObjList::CreateParam createParam = {};
      createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
      unknown28 = ui::UISelectObjList::create(createParam);
    }
    for (u32 blade = 0; blade < 3; blade++) {
      mm::mtl::FixStr<32> name;
      name.format("IMG_bl_icon@%02d", blade + 1);
      GfMenuCharDataAdapter::createFromPartyBlade(main.searchChild(name.c_str()), 3, 0, blade, true, false, false);
      unknown28->addObject(main.searchChild(name.c_str()));
      name.format("IMG_bl_bg@%02d", blade + 1);
      GfMenuGfObjAdapter::createFromPartyBlade(main.searchChild(name.c_str()), 0x27, 0, blade, true, false);
      addDispEventCondition(main.unknown10, name.c_str(), 4, blade, false);
      for (u32 column = 1; column < 4; column++) {
        u32 arts = blade * 3 + column - 1;
        name.format("LAY_bl_arts_icon@%02d%02d", column, blade + 1);
        unknown28->addObject(main.searchChild(name.c_str()));
        name.format("IMG_bl_arts_icon@%02d%02d", column, blade + 1);
        unknown28->addObject(main.searchChild(name.c_str()));
        name.format("IMG_bl_arts_recast@%02d%02d", column, blade + 1);
        ui::UIObjectAcc recast(main.unknown10, name.c_str());
        if (recast.isValid()) {
          GfMenuBattleAdapter *adapter = GfMenuBattleAdapter::create(recast.unknown10, 0);
          if (adapter != nullptr) {
            adapter->unknown30 = arts;
            adapter->setNumberInterpolateMode(0.25f);
            recast.startAnimation("start", true);
          }
        }
        addNumberEventCondition(main.unknown10, name.c_str(), 0, arts, 1.0f);
        name.format("IMG_bl_arts_icon_elem@%02d%02d", column, blade + 1);
        GfMenuBattleAdapter *elem = GfMenuBattleAdapter::create(main.searchChild(name.c_str()), 2);
        if (elem != nullptr) {
          elem->unknown30 = arts;
        }
        name.format("IMG_bl_arts_icon_type@%02d%02d", column, blade + 1);
        GfMenuBattleAdapter *type = GfMenuBattleAdapter::create(main.searchChild(name.c_str()), 3);
        if (type != nullptr) {
          type->unknown30 = arts;
        }
        name.format("IMG_bl_arts_icon_enhance@%02d%02d", column, blade + 1);
        GfMenuBattleAdapter *enhance = GfMenuBattleAdapter::create(main.searchChild(name.c_str()), 4);
        if (enhance != nullptr) {
          enhance->unknown30 = arts;
        }
        name.format("IMG_bl_arts_icon_react@%02d%02d", column, blade + 1);
        GfMenuBattleAdapter *react = GfMenuBattleAdapter::create(main.searchChild(name.c_str()), 5);
        if (react != nullptr) {
          react->unknown30 = arts;
        }
        name.format("IMG_bl_arts_icon_range@%02d%02d", column, blade + 1);
        GfMenuBattleAdapter *range = GfMenuBattleAdapter::create(main.searchChild(name.c_str()), 6);
        if (range != nullptr) {
          range->unknown30 = arts;
        }
        name.format("IMG_bl_arts_disable@%02d%02d", column, blade + 1);
        GfMenuBattleAdapter *disable = GfMenuBattleAdapter::create(main.searchChild(name.c_str()), 10);
        if (disable != nullptr) {
          disable->unknown30 = arts;
          disable->setDispReverseMode(true);
        }
        name.format("IMG_bl_arts_recast_max@%02d%02d", column, blade + 1);
        main.setDispChild(false, name.c_str());
      }
      name.format("LAY_bl_sp@%02d", blade + 1);
      unknown28->addObject(main.searchChild(name.c_str()));
      for (u32 level = 0; level < 5; level++) {
        name.format("IMG_bl_sp_lv@%02d%02d", level, blade + 1);
        ui::UIObjectAcc special(main.unknown10, name.c_str());
        if (special.isValid()) {
          GfMenuGfObjAdapter *adapter = GfMenuGfObjAdapter::createFromPartyBlade(special.unknown10, 0x23, 0, blade, true, false);
          if (adapter != nullptr) {
            adapter->unknown70 = level;
            adapter->setNumberInterpolateMode(0.25f);
            special.startAnimation("start", true);
            addNumberEventCondition(main.unknown10, name.c_str(), 5, blade * 5 + level, 1.0f);
          }
        }
      }
      name.format("IMG_bl_sp_lv_num@%02d", blade + 1);
      GfMenuGfObjAdapter::createFromPartyBlade(main.searchChild(name.c_str()), 0x24, 0, blade, true, false);
      addNumberEventCondition(main.unknown10, name.c_str(), 2, blade, 0.0f);
      name.format("IMG_bl_recast_bar@%02d", blade + 1);
      ui::UIObjectAcc bar(main.unknown10, name.c_str());
      GfMenuGfObjAdapter::createFromPartyBlade(bar.unknown10, 0x25, 0, blade, true, false);
      bar.setExtType(1);
      addNumberEventCondition(main.unknown10, name.c_str(), 1, blade, 1.0f);
    }
    {
      ui::UIObjectAcc party(main.unknown10, "LAY_party_gauge");
      for (u32 member = 0; member < 3; member++) {
        mm::mtl::FixStr<32> name;
        name.format("IMG_party_gauge@%02d", member + 1);
        ui::UIObjectAcc gauge(party.unknown10, name.c_str());
        if (gauge.isValid()) {
          GfMenuBattleAdapter *adapter = GfMenuBattleAdapter::create(party.searchChild(name.c_str()), 0xc);
          if (adapter != nullptr) {
            gauge.setExtType(1);
            gauge.setAddColor("yellow");
            adapter->unknown30 = member;
          }
          addNumberEventCondition(main.unknown10, name.c_str(), 3, member, 1.0f);
        }
      }
    }
    {
      ui::UICtrlCursorSelect::CursorSetting setting;
      ui::UIObjectAcc cursor(main.unknown10, "IMG_bl_arts_cursor");
      setting.unknown18 = 5;
      setting.setType(0);
      unknown30 = ui::UICtrlCursorSelect::create(cursor.unknown10, setting, unknown28);
      if (unknown30 != nullptr) {
        setupInputSelectionFromList(main.unknown10, *unknown28);
        setupPadLineSelection(main.unknown10, 5);
      }
      cursor.setMulColor("unuse");
    }
    unknown50 = unknown160();
    unknown50->unknown165(-1);
    unknown50->unknown166(9);
    unknown50->unknown162(-1);
    GfMenuBattleAdapter *detailName = GfMenuBattleAdapter::createFromReferenceIndex(main.searchChild("TXT_arts_detail_name"), unknown50, 7);
    if (detailName != nullptr) {
      detailName->unknown24 = main.searchChild("LAY_arts_detail");
    }
    GfMenuBattleAdapter::createFromReferenceIndex(main.searchChild("TXT_arts_detail_summary"), unknown50, 8);
    GfMenuObject::initialize();
  }
}

void GfMenuObjArtsPalette2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjArtsPalette2::update() {
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::disableInput(acc.searchChild("LAY_main"));
  acc.setAlpha(0.0f);
  GfMenuObject::update();
}

void GfMenuObjArtsPalette2::close() { unknown146(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjArtsPalette2::open() { unknown146(unknown001, GfMenuTypes::unknown003_33); }

void GfMenuObjArtsPalette2::resetSelection() { unknown146(unknown001, unknown002); }

void GfMenuObjArtsPalette2::attachCallContext(GfMenuCallContext *context) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid() && !acc.isTerm() && GfMenuObjUtil::checkCCStart(context)) {
    GfMenuObject::startCallContext(context, unknown001, acc.unknown10);
  }
}

void GfMenuObjArtsPalette2::setArtsSelection(GfMenuCallContext *context, bool isSelection) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid() && !acc.isTerm() && GfMenuObjUtil::checkCCNext(context, unknown001)) {
    ui::EventData event;
    event.unknown0c = 0;
    event.unknown00 = unknown003;
    event.unknown08 = isSelection;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
  }
}

void GfMenuObjArtsPalette2::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    unknown0c = -1;
    unknown10 = unknown005;
    break;
  case 6: {
    u32 index = event.unknown08;
    if (index == 0xffffffff) {
      break;
    }
    u32 row = index / 5;
    u32 column = index % 5;
    u32 kind;
    if (column == 0) {
      kind = 0;
    } else if (column < 4) {
      kind = 1;
    } else {
      kind = 2;
    }
    unknown20->unknown40 = kind;
    if (row != unknown20->unknown38) {
      GfMenuObject::addResultCallContext(acc.unknown10, 0, row);
      unknown20->unknown38 = row;
    }
    if (kind == 1) {
      int number = row * 3 + column - 1;
      unknown20->unknown50->unknown162(number);
    } else {
      unknown20->unknown50->unknown162(-1);
    }
    unknown20->unknown28->setIndex(index);
    break;
  }
  case 8: {
    u64 params = event.unknown08_u64;
    u32 button = params;
    if (params >> 32 != 1 || unknown10.unknown04 != 1) {
      break;
    }
    u64 selection = unknown20->unknown38_u64;
    switch (unknown20->unknown40) {
    case 0:
      if (static_cast<u32>(selection >> 32) != static_cast<u32>(selection)) {
        GfMenuObject::addResultCallContext(acc.unknown10, 3, 0);
      }
      break;
    case 1: {
      u32 column = button % 5 - 1;
      u32 slot = static_cast<u32>(selection) * 3 + column;
      if (GfMenuReference::isArtsPaletteEnable(slot) && unknown20->unknown48.test(slot)) {
        GfMenuObject::addResultCallContext(acc.unknown10, 1, column);
      }
      break;
    }
    case 2:
      if (unknown20->unknown4c.test(static_cast<u32>(selection))) {
        GfMenuObject::addResultCallContext(acc.unknown10, 2, 0);
      }
      break;
    }
    break;
  }
  case 0xd: {
    u64 params = event.unknown08_u64;
    u32 slot = event.unknown10;
    mm::mtl::FixStr<32> name;
    int type = params;
    u32 step = params >> 32;
    switch (step) {
    case 0: {
      u32 column = slot % 3 + 1;
      u32 row = slot / 3 + 1;
      name.format("IMG_bl_arts_recast@%02d%02d", column, row);
      ui::UIObjectAcc recast(acc.unknown10, name.c_str());
      name.format("IMG_bl_arts_recast_max@%02d%02d", column, row);
      ui::UIObjectAcc recastMax(acc.unknown10, name.c_str());
      name.format("IMG_recast_eff@%02d%02d", column, row);
      ui::UIObjectAcc effect(acc.unknown10, name.c_str());
      if (type == 1) {
        GfMenuObjUtil::playSE(0x25);
        recastMax.setDisp(true);
        recast.setDisp(false);
        unknown20->unknown48.set(slot, true);
        GfMenuObjUtil::CtrlParam param;
        param.unknown08 = 0x80002;
        param.unknown00 = 0.5f;
        param.unknown2c = 1.0f;
        param.unknown0c = 2;
        param.unknown14 = 10;
        GfMenuObjUtil::startCtrl(effect.unknown10, param, nullptr);
      } else {
        recastMax.setDisp(false);
        unknown20->unknown48.set(slot, false);
      }
    }
    // The game's case 0 falls into the default code: the compare with step 4 is executed after it.
    default:
      if (type == 5 && step == 4) {
        unknown20->unknown3c = slot;
      }
      break;
    case 2:
      name.format("IMG_bl_sp_lv_num@%02d", slot + 1);
      {
        bool isDisp = type != 1;
        ui::UIObjectAcc(acc.unknown10, name.c_str()).setDisp(isDisp);
        unknown20->unknown4c.set(slot, isDisp);
      }
      break;
    case 1:
      name.format("TXT_bl_recast_full@%02d", slot + 1);
      ui::UIObjectAcc(acc.unknown10, name.c_str()).setDisp(type == 1);
      break;
    case 3: {
      name.format("IMG_party_gauge@%02d", slot + 1);
      ui::UIObjectAcc gauge(acc.unknown10, name.c_str());
      name.format("IMG_party_gauge_icon@%02d", slot + 1);
      ui::UIObjectAcc icon(acc.unknown10, name.c_str());
      if (type == 1) {
        gauge.setAddColor("cyan");
        icon.setDisp(true);
        if (slot == 2 && unknown20->unknown24 == -1) {
          GfMenuObjUtil::CtrlParam param;
          param.unknown08 = 0x40000000;
          param.unknown00 = 1.0f;
          param.unknown10 = true;
          param.unknown0c = 4;
          param.unknown14 = 8;
          param.unknown38 = 1.0f;
          unknown20->unknown24 = GfMenuObjUtil::startCtrl(acc.searchChild("LAY_party_gauge_bar"), param, nullptr);
        }
      } else {
        gauge.setAddColor("yellow");
        icon.setDisp(false);
        if (unknown20->unknown24 != -1) {
          GfMenuObjUtil::stopCtrl(unknown20->unknown24);
          unknown20->unknown24 = -1;
        }
      }
      break;
    }
    case 5: {
      mm::mtl::FixStr<32> level;
      level.format("IMG_bl_sp_lv@%02d%02d", slot % 5, slot / 5);
      if (type == 1) {
        GfMenuObjUtil::playSE(0x25);
        acc.setDispChild(false, level.c_str());
      } else {
        acc.setDispChild(true, level.c_str());
      }
      break;
    }
    }
    break;
  }
  case 0x21:
    if (GfMenuManager::isBattleState(BATTLE_STATE_UNKNOWN_0) && unknown10.unknown00 == 0) {
      GfMenuObjUtil::PresetCtrlParam param;
      param.unknown10 = 0;
      param.unknown00 = 3;
      param.unknown0d = true;
      param.unknown08 = unknown0c;
      unknown0c = GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
      unknown10.unknown00 = 1;
      GfMenuObject::enableInput(acc.unknown10);
    }
    break;
  case 0x22:
    if (unknown10.unknown00 == 1) {
      GfMenuObjUtil::PresetCtrlParam param;
      param.unknown10 = 0;
      param.unknown00 = 3;
      param.unknown04 = 1;
      param.unknown0d = true;
      param.unknown08 = unknown0c;
      unknown0c = GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
      unknown10.unknown00 = 0;
      GfMenuObject::disableInput(acc.unknown10);
    }
    break;
  case unknown003: {
    int isSelection = event.unknown08;
    ui::UIObjectAcc cursor(acc.unknown10, "IMG_bl_arts_cursor");
    if (isSelection == 1) {
      cursor.setMulColor("select");
      GfMenuObject::addResultCallContext(acc.unknown10, 0, unknown20->unknown38);
    } else {
      cursor.setMulColor("unuse");
    }
    unknown10.unknown04 = event.unknown08;
    break;
  }
  case unknown002:
    unknown20->unknown28->setIndex(0);
    unknown20->unknown38 = 0;
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
