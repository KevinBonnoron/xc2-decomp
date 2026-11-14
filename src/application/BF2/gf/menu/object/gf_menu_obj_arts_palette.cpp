#include "gf/menu/object/gf_menu_obj_arts_palette.h"

#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_battle_adapter.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/object/gf_menu_obj_blade_change.h"
#include "gf/menu/object/gf_menu_obj_special_gauge.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_vec2.h"
#include "mm_mtl/fixstr.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: battle state read by GfMenuManager::isBattleState, normal; original name unknown.
constexpr u32 BATTLE_STATE_UNKNOWN_0 = 0;
constexpr u32 BATTLE_STATE_UNKNOWN_1 = 1;

// Inferred role: range effect state and arts info display flag when the palette is reset; original name unknown.
static const GfMenuObjArtsPalette::MainListener::unknown006 unknown007 = {0, 1};

// Inferred role: ui event type; original name unknown.
constexpr u16 unknown003 = 0x10b;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown004 = 0x101;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown005 = 0x100;

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x27;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x10a;

GfMenuObjArtsPalette::GfMenuObjArtsPalette(u32 handle) : GfMenuObject(handle), unknown40(this), unknown2d0(this), unknown560(this), unknown808(this) {
  for (u32 i = 0; i < 3; i++) {
    unknown24[i] = -1;
  }
  unknown7f0[0] = &unknown40;
  unknown7f0[1] = &unknown2d0;
  unknown7f0[2] = &unknown560;
  for (u32 i = 0; i < 3; i++) {
    unknown30[i] = 0;
  }
}

void GfMenuObjArtsPalette::finalize() { GfMenuObject::finalize(); }

void GfMenuObjArtsPalette::push(unsigned int slot) { unknown149(unknown001, unknown002, slot); }

void GfMenuObjArtsPalette::startChainAttack() { unknown157(unknown001, unknown003, 1); }

void GfMenuObjArtsPalette::exitChainAttack() { unknown144(unknown001, unknown003); }

void GfMenuObjArtsPalette::close() { unknown145(unknown001, unknown004); }

void GfMenuObjArtsPalette::open() { unknown145(unknown001, unknown005); }

void GfMenuObjArtsPalette::pushReverseBtn(u32 button) { unknown149(unknown001, 0x10d, button); }

void GfMenuObjArtsPalette::reverse(bool isReverse) { unknown150(unknown001, 0x10c, isReverse); }

void GfMenuObjArtsPalette::initialize() {
  ui::UIObjectAcc acc(unknown18);
  if (acc.isValid()) {
    ui::UIObjectAcc main(acc.unknown10, "LAY_main");
    if (main.isValid()) {
// __LINE__ must be 190 as in the original file: it is the line argument of operator new.
#line 190
      MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
      mainListener->addRef();
      ui::UIEventManager::get()->registObjectListener(main.unknown10, mainListener);
      if (mainListener != nullptr) {
        mainListener->release();
      }
      attachExternalCall(unknown001, main.unknown10);
      mm::mtl::FixStr<32> name;
      GfMenuCharDataAdapter *elemIcon = GfMenuCharDataAdapter::createFromPartyBlade(main.searchChild("IMG_elem_icon"), 0x2a, 0, -1, true, false, false);
      if (elemIcon != nullptr) {
        elemIcon->unknown24 = main.searchChild("IMG_elem_eff");
      }
      GfMenuCharDataAdapter::createFromPartyBlade(main.searchChild("IMG_elem_range_icon"), 0x2a, 0, -1, true, false, false);
      GfMenuBattleAdapter::create(main.searchChild("LAY_elem_range_icon"), 0x16);
      addDispEventCondition(main.unknown10, "LAY_elem_range_icon", 2, 0, false);
      GfMenuCharDataAdapter *elemEffect = GfMenuCharDataAdapter::createFromPartyBlade(main.searchChild("IMG_elem_eff"), 0x3a, 0, -1, true, false, false);
      if (elemEffect != nullptr) {
        elemEffect->setColorMode(0);
        elemEffect->unknown24 = main.searchChild("LAY_elem_range");
      }
      GfMenuCharDataAdapter *elemRange = GfMenuCharDataAdapter::createFromPartyBlade(main.searchChild("IMG_elem_range"), 0x3a, 0, -1, true, false, false);
      if (elemRange != nullptr) {
        elemRange->setColorMode(1);
      }
      {
        GfMenuObjUtil::CtrlParam param;
        param.unknown08 = 0x80000;
        param.unknown2c = 0.8f;
        param.unknown00 = 1.5f;
        param.unknown10 = true;
        param.unknown0c = 3;
        GfMenuObjUtil::startCtrl(main.unknown10, param, "IMG_elem_eff");
      }
      for (u32 slot = 1; slot < 4; slot++) {
        u32 index = slot - 1;
        name.format("IMG_recast@%02d", slot);
        ui::UIObjectAcc recast(main.unknown10, name.c_str());
        if (recast.isValid()) {
          GfMenuBattleAdapter *adapter = GfMenuBattleAdapter::create(recast.unknown10, 0);
          adapter->unknown30 = index;
          adapter->setNumberInterpolateMode(0.25f);
          recast.startAnimation("start", true);
        }
        addNumberEventCondition(main.unknown10, name.c_str(), 0, index, 1.0f);
        name.format("IMG_icon_type@%02d", slot);
        GfMenuBattleAdapter *type = GfMenuBattleAdapter::create(main.searchChild(name.c_str()), 3);
        if (type != nullptr) {
          type->unknown30 = index;
        }
        name.format("IMG_icon_enhance@%02d", slot);
        GfMenuBattleAdapter *enhance = GfMenuBattleAdapter::create(main.searchChild(name.c_str()), 4);
        if (enhance != nullptr) {
          enhance->unknown30 = index;
        }
        name.format("IMG_icon_react@%02d", slot);
        GfMenuBattleAdapter *react = GfMenuBattleAdapter::create(main.searchChild(name.c_str()), 5);
        if (react != nullptr) {
          react->unknown30 = index;
        }
        name.format("IMG_icon_range@%02d", slot);
        GfMenuBattleAdapter *range = GfMenuBattleAdapter::create(main.searchChild(name.c_str()), 6);
        if (range != nullptr) {
          range->unknown30 = index;
        }
        name.format("IMG_icon_disable@%02d", slot);
        GfMenuBattleAdapter *disable = GfMenuBattleAdapter::create(main.searchChild(name.c_str()), 10);
        if (disable != nullptr) {
          disable->unknown30 = index;
          disable->setDispReverseMode(true);
          ui::UIObjectAcc(main.searchChild(name.c_str())).setAlpha(0.0f);
          addDispEventCondition(main.unknown10, name.c_str(), 1, index, false);
        }
        name.format("LAY_arts_info@%02d", slot);
        ui::UIObjectAcc info(main.unknown10, name.c_str());
        name.format("TXT_arts_name@%02d", slot);
        GfMenuBattleAdapter *artsName = GfMenuBattleAdapter::create(main.searchChild(name.c_str()), 7);
        if (artsName != nullptr) {
          artsName->unknown30 = index;
          artsName->unknown24 = info.unknown10;
        }
        name.format("TXT_arts_info@%02d", slot);
        GfMenuBattleAdapter *artsInfo = GfMenuBattleAdapter::create(main.searchChild(name.c_str()), 8);
        if (artsInfo != nullptr) {
          artsInfo->unknown30 = index;
        }
        name.format("LAY_arts_info_text@%02d", slot);
        ui::UIObjectAcc text(info.unknown10, name.c_str());
        GfMenuObjUtil::FitOption fit;
        fit.unknown02 = true;
        name.format("IMG_arts_info_bg@%02d", slot);
        GfMenuObjUtil::createFitPlugin(main.searchChild(name.c_str()), text.unknown10, 0x30, 0, fit);
      }
      main.setDispChild(false, "LAY_spsign");
// __LINE__ must be 321 as in the original file: it is the line argument of operator new.
#line 321
      ReverseListener *reverseListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ReverseListener(this);
      reverseListener->addRef();
      ui::UIEventManager::get()->registObjectListener(main.searchChild("LAY_reverse"), reverseListener);
      if (reverseListener != nullptr) {
        reverseListener->release();
      }
      GfMenuObject::initialize();
    }
  }
}

void GfMenuObjArtsPalette::dispInfo(bool isDisp) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid() && !acc.isTerm()) {
    acc.setDispChild(isDisp, "LAY_arts_info");
    GfMenuObjBladeChange::dispInfo(isDisp);
  }
}

GfMenuObjArtsPalette::~GfMenuObjArtsPalette() { ; }

void GfMenuObjArtsPalette::update() {
  unknown7f0[0]->unknown003();
  unknown7f0[1]->unknown003();
  unknown7f0[2]->unknown003();
  unknown808.unknown003();
  GfMenuObject::update();
}

void GfMenuObjArtsPalette::updateArtsIconDisp(u32 slot) {
  mm::mtl::FixStr<32> name;
  name.format("LAY_arts_icon@%02d", slot + 1);
  ui::UIObjectAcc icon(unknown18, name.c_str());
  if ((unknown30[slot] & 3) == 3) {
    icon.setMulColor("white");
  } else {
    icon.setMulColor("gray");
  }
}

int GfMenuObjArtsPalette::ctrlPalletteDisp(bool isDisp, u32 type) {
  ui::UIObjectAcc palette(unknown18, "LAY_palette");
  mm::mtl::FixStr<32> name;
  f32 time;
  if (type == 1) {
    time = 0.1f;
  } else if (type == 0) {
    time = GfMenuObjUtil::getParamMenu()->unknown18;
  } else {
    time = 0.0f;
  }
  ui::UIObjectAcc info(palette.unknown10, "LAY_arts_info");
  int ctrl;
  if (isDisp) {
    for (u32 slot = 1; slot < 4; slot++) {
      name.format("LAY_arts_icon@%02d", slot);
      ui::UIObjectAcc icon(palette.unknown10, name.c_str());
      GfMenuObjUtil::CtrlParam iconParam;
      iconParam.unknown08 = 0x100000;
      iconParam.unknown30 = 1.0f;
      iconParam.unknown04 = 8;
      iconParam.unknown2c = 0.0f;
      iconParam.unknown00 = time;
      ctrl = GfMenuObjUtil::startCtrl(icon.unknown10, iconParam, nullptr);
      name.format("LAY_arts_st@%02d", slot);
      palette.setDispChild(false, name.c_str());
      name.format("LAY_arts_info@%02d", slot);
      GfMenuObjUtil::CtrlParam infoParam;
      infoParam.unknown08 = 2;
      infoParam.unknown00 = time;
      GfMenuObjUtil::startCtrl(palette.unknown10, infoParam, name.c_str());
    }
    GfMenuObjUtil::CtrlParam elemParam;
    elemParam.unknown08 = 2;
    elemParam.unknown00 = time;
    GfMenuObjUtil::startCtrl(palette.unknown10, elemParam, "LAY_elem_eff");
    GfMenuObjUtil::startCtrl(palette.unknown10, elemParam, "IMG_elem_icon");
    GfMenuObjUtil::startCtrl(palette.unknown10, elemParam, "LAY_elem_range");
  } else {
    for (u32 slot = 1; slot < 4; slot++) {
      name.format("LAY_arts_icon@%02d", slot);
      ui::UIObjectAcc icon(palette.unknown10, name.c_str());
      GfMenuObjUtil::CtrlParam iconParam;
      iconParam.unknown08 = 0x100000;
      iconParam.unknown30 = 1.0f;
      iconParam.unknown04 = 9;
      iconParam.unknown2c = 1.0f;
      iconParam.unknown00 = time;
      ctrl = GfMenuObjUtil::startCtrl(icon.unknown10, iconParam, nullptr);
      name.format("LAY_arts_st@%02d", slot);
      palette.setDispChild(true, name.c_str());
      name.format("LAY_arts_info@%02d", slot);
      GfMenuObjUtil::CtrlParam infoParam;
      infoParam.unknown08 = 1;
      infoParam.unknown00 = time;
      GfMenuObjUtil::startCtrl(info.unknown10, infoParam, name.c_str());
    }
    GfMenuObjUtil::CtrlParam elemParam;
    elemParam.unknown08 = 1;
    elemParam.unknown00 = time;
    GfMenuObjUtil::startCtrl(palette.unknown10, elemParam, "LAY_elem_eff");
    GfMenuObjUtil::startCtrl(palette.unknown10, elemParam, "IMG_elem_icon");
    GfMenuObjUtil::startCtrl(palette.unknown10, elemParam, "LAY_elem_range");
  }
  return ctrl;
}

void GfMenuObjArtsPalette::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 0x100:
    if (GfMenuManager::isBattleState(BATTLE_STATE_UNKNOWN_0)) {
      if (unknown10.unknown00 == 0) {
        GfMenuObjUtil::PresetCtrlParam param;
        param.unknown10 = 0;
        param.unknown00 = 0;
        param.unknown04 = 0;
        param.unknown0d = true;
        param.unknown08 = unknown0c;
        unknown0c = GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
        unknown10.unknown00 = 1;
        GfMenuObject::enableInput(acc.unknown10);
      }
      ui::UIObjectAcc range(acc.unknown10, "IMG_elem_range");
      range.startAnimation("loop", false);
      range.setDisp(true);
      unknown20->unknown808.unknown005();
    }
    break;
  case 0x101:
    if (unknown10.unknown00 == 1) {
      GfMenuObjUtil::PresetCtrlParam param;
      param.unknown00 = 0;
      param.unknown04 = 1;
      param.unknown0d = true;
      param.unknown08 = unknown0c;
      param.unknown10 = 10;
      unknown0c = GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
      unknown10.unknown00 = 0;
      GfMenuObject::disableInput(acc.unknown10);
      ui::UIObjectAcc range(acc.unknown10, "IMG_elem_range");
      range.stopAnimation();
      range.setDisp(false);
      unknown20->unknown808.unknown005();
    }
    break;
  case 0x10a: {
    u32 slot = event.unknown08;
    if (unknown10.unknown00 == 1) {
      if (GfMenuReference::isArtsPaletteEnable(slot) && GfMenuReference::getArtsPaletteInfo(slot).unknown04 == 1.0f) {
        GfMenuObjUtil::playSE(0x23);
        unknown20->unknown30[slot] |= 4;
      } else {
        GfMenuObjUtil::playSE(0x24);
      }
    }
    break;
  }
  case 0x10b:
    unknown20->ctrlPalletteDisp(event.unknown08 == 1, 0);
    break;
  case 0x10c: {
    int isReverse = event.unknown08;
    int ctrl = unknown20->ctrlPalletteDisp(isReverse == 1, 1);
    if (ctrl != -1) {
      GfMenuObject::hookCtrlEvent(acc.unknown10, ctrl);
    }
    if (isReverse == 1) {
      GfMenuObject::sendOpenEvent(acc.searchChild("LAY_reverse"), 0, 0.0f);
    } else {
      acc.setDispChild(true, "IMG_frame");
      GfMenuObject::sendCloseEvent(acc.searchChild("LAY_reverse"), 0, 0.0f);
    }
    GfMenuObjSpecialGauge::reverse(isReverse == 1);
    break;
  }
  case 0x10d:
    GfMenuObject::sendEvent(acc.searchChild("LAY_reverse"), event, 0.0f);
    break;
  case 0xd: {
    int type = event.unknown08;
    int step = event.unknown0c;
    u32 slot = event.unknown10;
    mm::mtl::FixStr<32> name;
    name.format("LAY_arts_icon@%02d", slot + 1);
    ui::UIObjectAcc icon(acc.unknown10, name.c_str());
    switch (step) {
    case 0: {
      name.format("LAY_recast@%02d", slot + 1);
      ui::UIObjectAcc recast(acc.unknown10, name.c_str());
      name.format("IMG_arts_eff@%02d", slot + 1);
      ui::UIObjectAcc effect(acc.unknown10, name.c_str());
      if (type == 1) {
        GfMenuObjUtil::playSE(0x22);
        recast.setDisp(false);
        if (effect.isValid() && unknown20->unknown24[slot] == -1) {
          effect.setDisp(true);
          unknown20->unknown7f0[slot]->unknown005();
          unknown20->unknown7f0[slot]->addAnimJob(effect.unknown10, "standbye");
        }
        unknown20->unknown30[slot] |= 1;
      } else {
        if ((unknown20->unknown30[slot] & 4) == 0) {
          effect.setDisp(false);
        } else {
          effect.startAnimation("select", false);
          unknown20->unknown30[slot] &= ~4;
        }
        recast.setDisp(true);
        unknown20->unknown7f0[slot]->unknown005();
        if (unknown20->unknown24[slot] != -1) {
          GfMenuObjUtil::stopCtrl(unknown20->unknown24[slot]);
          unknown20->unknown24[slot] = -1;
        }
        unknown20->unknown30[slot] &= ~1;
      }
      unknown20->updateArtsIconDisp(slot);
      break;
    }
    case 1:
      if (type == 5) {
        unknown20->unknown30[slot] |= 2;
      } else {
        unknown20->unknown30[slot] &= ~2;
      }
      unknown20->updateArtsIconDisp(slot);
      break;
    case 2:
      if (type == 5) {
        {
          ui::UIObjectAcc range(acc.unknown10, "IMG_elem_range");
          unknown20->unknown808.addAnimJob(range.unknown10, "start");
          unknown20->unknown808.addAnimJob(range.unknown10, "loop");
        }
        ui::UIObjectAcc rangeIcon(acc.unknown10, "IMG_elem_range_icon");
        GfMenuObjUtil::CtrlParam param;
        param.unknown08 = 0x10000000;
        param.unknown11 = true;
        param.unknown04 = 1;
        param.unknown50 = "mnu004_range_anim_elem";
        param.unknown58 = "start";
        param.unknown14 = 12;
        int ctrl = GfMenuObjUtil::startCtrl(rangeIcon.unknown10, param, nullptr);
        GfMenuObject::hookCtrlEvent(acc.unknown10, ctrl);
      } else {
        {
          ui::UIObjectAcc range(acc.unknown10, "IMG_elem_range");
          range.startAnimation("loop", false);
          unknown20->unknown808.unknown005();
        }
        ui::UIObjectAcc rangeIcon(acc.unknown10, "IMG_elem_range_icon");
        int ctrl = GfMenuObjUtil::getCtrlID(rangeIcon.unknown10);
        if (ctrl != -1) {
          GfMenuObjUtil::stopCtrl(ctrl);
        }
      }
      break;
    }
    break;
  }
  case 1:
    acc.setDisp(false);
    unknown0c = -1;
    unknown10 = unknown007;
    GfMenuObject::disableInput(acc.unknown10);
    break;
  case 3:
    if (event.unknown08 == 1) {
      ui::UIObjectAcc icon(acc.unknown10, "IMG_elem_range_icon");
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 0x10000000;
      param.unknown50 = "mnu004_range_anim_elem";
      param.unknown58 = "loop";
      param.unknown11 = true;
      param.unknown10 = true;
      param.unknown14 = 8;
      GfMenuObjUtil::startCtrl(icon.unknown10, param, nullptr);
    } else if (event.unknown08 == 8) {
      acc.setDispChild(false, "IMG_frame");
    } else if (event.unknown08 == 10) {
      if (!GfMenuManager::isBattleState(BATTLE_STATE_UNKNOWN_1)) {
        unknown20->unknown30[0] &= ~4;
        unknown20->unknown30[1] &= ~4;
        unknown20->unknown30[2] &= ~4;
      }
    }
    break;
  case 8:
    if (event.unknown0c == 9) {
      int isDisp = unknown10.unknown04;
      GfMenuObjArtsPalette::dispInfo(isDisp == 0);
      unknown10.unknown04 = isDisp == 0;
    }
    break;
  case 0xc:
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjArtsPalette::ReverseListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    acc.setDisp(false);
    u32 count;
    {
      mm::mtl::FixStr<32> name;
      count = acc.countChild("LAY_reverse_icon@%02d", 1);
      for (u32 i = 0; i < count; i++) {
        name.format("LAY_reverse_icon@%02d", i + 1);
        ui::UIObjectAcc icon(acc.unknown10, name.c_str());
        GfMenuBattleAdapter *adapter = GfMenuBattleAdapter::create(icon.unknown10, 0x17);
        if (adapter != nullptr) {
          adapter->unknown30 = i;
        }
        icon.setScale(mm::Vec2(0.0f, 1.0f));
      }
    }
    unknown0c = count;
    ui::UIObjectAcc frame(acc.unknown10, "IMG_reverse_frame");
    frame.setMulColor(mm::Col3(0.78f, 1.0f, 0.78f));
    break;
  }
  case 3:
    if (event.unknown08 == 1) {
      acc.setDispChild(true, "IMG_reverse_frame");
    } else if (event.unknown08 == 2) {
      acc.setDisp(false);
    }
    break;
  case 0x21: {
    mm::mtl::FixStr<32> name;
    acc.setDisp(true);
    if (unknown0c > 0) {
      int ctrl = -1;
      for (int i = 1; i <= unknown0c; i++) {
        name.format("LAY_reverse_icon@%02d", i);
        ui::UIObjectAcc icon(acc.unknown10, name.c_str());
        GfMenuObjUtil::CtrlParam param;
        param.unknown08 = 0x100000;
        param.unknown30 = 1.0f;
        param.unknown04 = 1;
        param.unknown2c = 1.0f;
        param.unknown11 = true;
        param.unknown00 = 0.1f;
        ctrl = GfMenuObjUtil::startCtrl(icon.unknown10, param, nullptr);
      }
      if (ctrl != -1) {
        GfMenuObject::hookCtrlEvent(acc.unknown10, ctrl);
      }
    }
    break;
  }
  case 0x22: {
    mm::mtl::FixStr<32> name;
    if (unknown0c > 0) {
      int ctrl = -1;
      for (int i = 1; i <= unknown0c; i++) {
        name.format("LAY_reverse_icon@%02d", i);
        ui::UIObjectAcc icon(acc.unknown10, name.c_str());
        GfMenuObjUtil::CtrlParam param;
        param.unknown08 = 0x100000;
        param.unknown30 = 1.0f;
        param.unknown2c = 0.0f;
        param.unknown00 = 0.1f;
        param.unknown04 = 2;
        ctrl = GfMenuObjUtil::startCtrl(icon.unknown10, param, nullptr);
      }
      if (ctrl != -1) {
        GfMenuObject::hookCtrlEvent(acc.unknown10, ctrl);
      }
    }
    acc.setDispChild(false, "IMG_reverse_frame");
    break;
  }
  case 0x10d: {
    u32 button = event.unknown08;
    if (GfMenuReference::isReversePaletteBtnState(button, 1)) {
      mm::mtl::FixStr<32> name;
      name.format("IMG_reverse_icon@%02d", button + 1);
      ui::UIObjectAcc icon(acc.unknown10, name.c_str());
      icon.setAddColor("black");
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 0x40040000;
      param.unknown38 = 1.0f;
      param.unknown00 = 0.15f;
      param.unknown2c = 0.1f;
      param.unknown11 = true;
      param.unknown0c = 4;
      GfMenuObjUtil::startCtrl(icon.unknown10, param, nullptr);
    }
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjArtsPalette, 4>>(const mm::mtl::Delegate<bool()> *);
template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjArtsPalette, 8>>(const mm::mtl::Delegate<bool()> *);
