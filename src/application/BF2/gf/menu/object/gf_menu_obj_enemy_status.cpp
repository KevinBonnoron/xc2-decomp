#include "gf/menu/object/gf_menu_obj_enemy_status.h"

#include "bdat.h"
#include "gf/data/gf_object_type.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_adapter.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/adapter/gf_menu_gfobj_adapter.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_property.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/fixstr.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x10;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x101;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown003 = 0x100;
// Inferred role: attached display call id; original name unknown.
constexpr u32 unknown004 = 0x14;
// Inferred role: ui event type, moves an element in its start layout; original name unknown.
constexpr u16 unknown007 = 0x105;
// Inferred role: ui event type, plays the level name effect; original name unknown.
constexpr u16 unknown008 = 0x10a;
// Inferred role: ui event type, pulses the reaction icon; original name unknown.
constexpr u16 unknown009 = 3;
// Inferred role: ui event type, hides the arts name; original name unknown.
constexpr u16 unknown010 = 0xc;
// Inferred role: ui event type, updates the reaction, the arts name or the combo debuff; original name unknown.
constexpr u16 unknown011 = 0xd;
// Inferred role: attached call id; original name unknown.
constexpr u32 unknown014 = 0x15;

// Inferred role: no control running on the reaction icon and the pulse effect; original name unknown.
static const GfMenuObjEnemyStatus::MainListener::unknown006 unknown012 = {-1, -1};

// Inferred role: moves an element from the position of a layout of the screen with a control; original name unknown.
static void unknown013(u32 handle, u32 elem, u32 index) {
  ui::UIObjectAcc acc(handle);
  ui::UIObjectAcc layout(elem);
  if (acc.isValid() && layout.isValid()) {
    mm::mtl::FixStr<16> name;
    name.format("elem_%02d", index);
    mm::Rect<s16> rect;
    if (acc.getLayoutRect(name.c_str(), rect)) {
      GfMenuObjUtil::CtrlParam param;
      param.unknown00 = 0.25f;
      param.unknown08 = 0x80;
      param.unknown0c = 1;
      param.unknown26.x = rect.x;
      param.unknown26.y = rect.y;
      GfMenuObjUtil::startCtrl(layout.unknown10, param, nullptr);
    }
  }
}

// Inferred role: keeps a created adapter in the list of the adapters following the enemy, when there is room; original name unknown.
static void unknown015(GfMenuObjEnemyStatus *status, unknown135 *adapter) {
  if (adapter != nullptr && status->unknown30.unknown00.size() != status->unknown30.unknown00.capacity()) {
    status->unknown30.unknown00.push_back(adapter);
  }
}

// Inferred role: same as unknown015 for the sites where the game tests the adapter before its conversion to the list element; original name unknown.
template <typename T> static void unknown016(GfMenuObjEnemyStatus *status, T *adapter) {
  if (adapter != nullptr && status->unknown30.unknown00.size() != status->unknown30.unknown00.capacity()) {
    status->unknown30.unknown00.push_back(adapter);
  }
}

GfMenuObjEnemyStatus::GfMenuObjEnemyStatus(u32 handle) : GfMenuObject(handle), unknown28(unknown020), unknown100(-1) {}

GfMenuObjEnemyStatus::~GfMenuObjEnemyStatus() {}

void GfMenuObjEnemyStatus::initialize() {
  ui::UIObjectAcc acc(unknown18);
  attachExternalCall(unknown004, unknown18);
  u32 main = acc.searchChild("LAY_main");
  if (ui::UIObjectAcc(main).isValid()) {
    attachExternalCall(unknown001, main);
    attachExternalCall(unknown014, main);
// __LINE__ must be 102 as in the original file: it is the line argument of operator new.
#line 102
    MainListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
    listener->addRef();
    ui::UIEventManager::get()->registObjectListener(main, listener);
    if (listener != nullptr) {
      listener->release();
    }
  }
  {
    ui::UIObjectAcc img(acc.searchChild("IMG_bg"));
    unknown016(this, GfMenuGfObjAdapter::create(img.unknown10, 0x20, unknown020, true));
  }
  {
    ui::UIObjectAcc img(acc.searchChild("IMG_hpgauge"));
    if (img.isValid()) {
      GfMenuGfObjAdapter *adapter = GfMenuGfObjAdapter::create(img.unknown10, 0, unknown020, true);
      if (adapter != nullptr) {
        adapter->setNumberInterpolateMode(0.25f);
        unknown015(this, adapter);
      }
      unknown015(this, GfMenuGfObjAdapter::create(img.unknown10, 1, unknown020, true));
      img.setExtType(1);
    }
  }
  unknown015(this, GfMenuGfObjAdapter::create(acc.searchChild("IMG_acticon"), 0xb, unknown020, true));
  {
    ui::UIObjectAcc img(acc.searchChild("IMG_linkicon"));
    if (img.isValid()) {
      unknown015(this, GfMenuGfObjAdapter::create(img.unknown10, 0xc, unknown020, true));
      img.setImageIndex(1);
    }
  }
  unknown015(this, GfMenuGfObjAdapter::create(acc.searchChild("TXT_lv"), 7, unknown020, true));
  unknown015(this, GfMenuCharDataAdapter::createFromGfObj(acc.searchChild("TXT_name"), 2, unknown020, false));
  unknown016(this, GfMenuGfObjAdapter::create(acc.searchChild("LAY_arts_name"), 9, unknown020, true));
  addNumberEventCondition(main, "LAY_arts_name", 5, 0);
  {
    ui::UIObjectAcc elem(acc.unknown10, "LAY_elem2");
// __LINE__ must be 178 as in the original file: it is the line argument of operator new.
#line 178
    ElemListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ElemListener(this);
    listener->addRef();
    ui::UIEventManager::get()->registObjectListener(elem.unknown10, listener);
    if (listener != nullptr) {
      listener->release();
    }
    unknown015(this, GfMenuGfObjAdapter::create(elem.unknown10, 0x14, unknown020, true));
    addDispEventCondition(elem.unknown10, nullptr, 1, 0, false);
    unknown015(this, GfMenuGfObjAdapter::create(elem.searchChild("TXT_elem_eff"), 10, unknown020, true));
    unknown015(this, GfMenuGfObjAdapter::create(elem.searchChild("IMG_elem_lv_icon"), 0x15, unknown020, true));
    unknown015(this, GfMenuGfObjAdapter::create(elem.searchChild("IMG_elem_lv_icon_base"), 0x15, unknown020, true));
    {
      ui::UIObjectAcc time(elem.unknown10, "IMG_elem_time");
      unknown015(this, GfMenuGfObjAdapter::create(time.unknown10, 0x13, unknown020, true));
      unknown015(this, GfMenuGfObjAdapter::create(time.unknown10, 0x16, unknown020, true));
      time.setExtType(2);
    }
    {
      ui::UIObjectAcc suspend(elem.unknown10, "IMG_elem_time_suspend");
      unknown015(this, GfMenuGfObjAdapter::create(suspend.unknown10, 0x13, unknown020, true));
      suspend.setExtType(2);
      unknown015(this, GfMenuGfObjAdapter::create(elem.searchChild("LAY_elem_time_suspend"), 0x18, unknown020, true));
      addDispEventCondition(elem.unknown10, "LAY_elem_time_suspend", 2, 0, false);
    }
    {
      ui::UIObjectAcc debuff(acc.unknown10, "LAY_debuff");
      debuff.setDisp(false);
    }
  }
  unknown015(this, GfMenuGfObjAdapter::create(acc.searchChild("IMG_infoicon"), 4, unknown020, true));
  unknown015(this, GfMenuGfObjAdapter::create(acc.searchChild("IMG_reaction_icon"), 0xe, unknown020, true));
  unknown015(this, GfMenuGfObjAdapter::create(acc.searchChild("IMG_reaction_icon_eff"), 0xe, unknown020, true));
  addNumberEventCondition(main, "IMG_reaction_icon", 3, 0);
  addDispEventCondition(main, "IMG_reaction_icon", 3, 0, false);
  unknown015(this, GfMenuGfObjAdapter::create(acc.searchChild("TXT_reaction"), 0xf, unknown020, true));
  unknown015(this, GfMenuGfObjAdapter::create(acc.searchChild("IMG_reaction_gauge"), 0x10, unknown020, true));
  ui::UIObjectAcc(acc.searchChild("IMG_reaction_gauge")).setExtType(1);
  {
    ui::UIObjectAcc suspend(acc.unknown10, "IMG_reaction_time_suspend");
    unknown015(this, GfMenuGfObjAdapter::create(suspend.unknown10, 0x10, unknown020, true));
    suspend.setExtType(1);
    unknown015(this, GfMenuGfObjAdapter::create(acc.searchChild("LAY_reaction_time_suspend"), 0x11, unknown020, true));
    addDispEventCondition(main, "LAY_reaction_time_suspend", 4, 0, false);
  }
  GfMenuObjUtil::createFollowDispPlugin(acc.searchChild("LAY_reaction"), acc.searchChild("IMG_reaction_icon"));
  {
    ui::UIObjectAcc state(acc.unknown10, "LAY_state");
    GfMenuGfObjAdapter *adapter = GfMenuGfObjAdapter::create(acc.searchChild("IMG_state_weak_elem_icon"), 0x19, unknown020, true);
    adapter->unknown24 = acc.searchChild("LAY_state_weak_elem");
    unknown015(this, adapter);
  }
  {
    ui::UIObjectAcc debuff(acc.unknown10, "LAY_combo_debuff");
    unknown016(this, GfMenuGfObjAdapter::create(debuff.unknown10, 0x1f, unknown020, true));
    debuff.setDisp(false);
    addNumberEventCondition(main, "LAY_combo_debuff", 6, 0);
  }
  ui::UIObjectAcc elem(unknown18, "LAY_elem");
  if (elem.isValid()) {
    elem.setDisp(false);
  }
  GfMenuObject::initialize();
}

void GfMenuObjEnemyStatus::finalize() { GfMenuObject::finalize(); }

void GfMenuObjEnemyStatus::update() {
  GF_OBJ_HANDLE *target = GfMenuManager::getTargetObjHandle();
  if (unknown28 != target) {
    for (u32 i = 0; i < unknown30.unknown00.size(); i++) {
      unknown30.unknown00[i]->changeGfObj(target);
    }
    {
      ui::UIObjectAcc acc(unknown18, "LAY_main");
      GfObjAcc obj(unknown28);
      ui::EventData event;
      event.unknown00 = unknown008;
      if (unknown28 == unknown020) {
        event.unknown08 = 1;
      } else {
        event.unknown08 = obj.getType() != OBJECT_TYPE_ENEMY;
      }
      GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
    }
    unknown28 = target;
  }
  GfMenuObject::update();
}

void GfMenuObjEnemyStatus::close() { GF_MENU_REQUEST_EVENT(unknown001, unknown002); }

void GfMenuObjEnemyStatus::open(const OpenParam &) { GF_MENU_REQUEST_EVENT(unknown001, unknown003); }

void GfMenuObjEnemyStatus::disp(bool isDisp) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown004));
  if (acc.isValid() && !acc.isTerm()) {
    acc.setDisp(isDisp);
  }
}

void GfMenuObjEnemyStatus::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case unknown003:
    acc.setDisp(true);
    break;
  case 1: {
    ui::UIObjectAcc arts(acc.unknown10, "LAY_arts_name");
    arts.setDisp(false);
    unknown0c = 0;
    unknown10 = unknown012;
    acc.setDisp(false);
    break;
  }
  case unknown002:
    acc.setDisp(false);
    break;
  case GfMenuTypes::unknown003_259: {
    ui::UIObjectAcc elem(acc.searchDuplicatedChild("IMG_elem", event.unknown08_u16));
    if (elem.isValid()) {
      acc.setLayout(elem.unknown10, "elem_start");
      unknown013(acc.unknown10, elem.unknown10, event.unknown0a);
      elem.setImageIndex(event.unknown0c_u16);
    }
    break;
  }
  case GfMenuTypes::unknown003_260: {
    ui::UIObjectAcc elem(acc.searchDuplicatedChild("IMG_elem", event.unknown08_u16));
    if (elem.isValid()) {
      GfMenuObjUtil::CtrlParam param;
      param.unknown00 = 0.5f;
      param.unknown08 = 0x42;
      param.unknown0c = 1;
      param.unknown14 = 1;
      param.unknown20 = 0x20;
      GfMenuObjUtil::startCtrl(elem.unknown10, param, nullptr);
      GfMenuObject::termCallContext(elem.unknown10);
    }
    break;
  }
  case unknown007: {
    ui::UIObjectAcc elem(acc.searchDuplicatedChild("IMG_elem", event.unknown08_u16));
    if (elem.isValid()) {
      unknown013(acc.unknown10, elem.unknown10, event.unknown0a);
    }
    break;
  }
  case unknown008:
    if (event.unknown08 == 1) {
      ui::UIObjectAcc effect(acc.unknown10, "IMG_lv_name_eff");
      effect.startAnimation("start", false);
    }
    break;
  case unknown009:
    if (event.unknown08 == 1) {
      ui::UIObjectAcc effect(acc.unknown10, "IMG_reaction_icon_eff");
      effect.setAlpha(1.0f);
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 0x10000000;
      param.unknown50 = "pulse";
      param.unknown58 = "pulse";
      param.unknown10 = true;
      param.unknown18 = unknown10.unknown04;
      param.unknown11 = true;
      param.unknown14 = 4;
      unknown10.unknown04 = GfMenuObjUtil::startCtrl(effect.unknown10, param, nullptr);
    }
    break;
  case unknown010:
    if (unknown0c != 1) {
      ui::UIObjectAcc arts(acc.unknown10, "LAY_arts_name");
      arts.setDisp(false);
    }
    break;
  case unknown011: {
    u32 param0 = event.unknown08;
    u32 param3 = event.unknown14;
    switch (event.unknown0c) {
    case 5: {
      ui::UIObjectAcc arts(acc.unknown10, "LAY_arts_name");
      if (param3 != 0) {
        ui::UIStr name;
        GfObjProperty *property = GfObjUtil::getProperty(unknown20->unknown28);
        if (property != nullptr) {
          GfObjPropertyEnemy *enemy = property->getEnemy();
          if (enemy != nullptr && enemy->unknownc8 != 0 && enemy->unknownd0 != nullptr) {
            name.setupMstxt(enemy->unknownd0, enemy->unknownc8);
          }
        }
        if (name.isValid()) {
          arts.setDisp(true);
          unknown0c = 1;
          {
            ui::UIObjectAcc text(acc.unknown10, "TXT_artsname");
            text.setText(name);
            text.setDisp(true);
            GfMenuObjUtil::CtrlParam param;
            param.unknown08 = 0x10000000;
            param.unknown50 = "cmn_fade_emotion";
            param.unknown58 = "fade_in_select";
            param.unknown11 = true;
            GfMenuObjUtil::startCtrl(text.unknown10, param, nullptr);
          }
          ui::UIObjectAcc base(acc.unknown10, "IMG_arts_base");
          base.startAnimation("in", false);
        } else {
          arts.setDisp(false);
        }
      } else if (unknown0c == 1) {
        {
          ui::UIObjectAcc text(acc.unknown10, "TXT_artsname");
          text.setDisp(false);
        }
        {
          ui::UIObjectAcc base(acc.unknown10, "IMG_arts_base");
          base.startAnimation("out", false);
          GfMenuObject::hookAnimationEvent(acc.unknown10, base.unknown10);
        }
        unknown0c = 0;
      }
      break;
    }
    case 6: {
      ui::UIObjectAcc debuff(acc.unknown10, "LAY_combo_debuff");
      if (param3 != 0) {
        ui::UIObjectAcc text(debuff.unknown10, "TXT_combo_debuff");
        u8 nameId = Bdat::getVal(Bdat::getFP("BTL_ElementalEffect"), "Name", param3).valueU8;
        if (nameId != 0) {
          {
            ui::UIStr name(Bdat::getFP("btl_elementaleffect_ms"), nameId);
            text.setText(name);
          }
          ui::UIObjectAcc effect(debuff.unknown10, "IMG_combo_debuff_eff");
          effect.startAnimation("fade_in", false);
        }
        debuff.setDisp(true);
        debuff.setAlpha(1.0f);
      } else if (debuff.isDisp()) {
        GfMenuObjUtil::CtrlParam param;
        param.unknown08 = 2;
        param.unknown00 = 0.2f;
        param.unknown14 = 10;
        GfMenuObjUtil::startCtrl(debuff.unknown10, param, nullptr);
      }
      break;
    }
    case 3:
      if (acc.isDisp()) {
        {
          ui::UIObjectAcc reaction(acc.unknown10, "LAY_reaction");
          reaction.setAddColor("white");
          GfMenuObjUtil::CtrlParam param;
          param.unknown08 = 0x4000000;
          param.unknown00 = 0.5f;
          param.unknown40_col3 = GfMenuObjUtil::getPresetColor("black");
          GfMenuObjUtil::startCtrl(reaction.unknown10, param, nullptr);
        }
        GfMenuObjUtil::CtrlParam param;
        param.unknown08 = 0x10000000;
        param.unknown50 = "fadein";
        param.unknown58 = "label";
        param.unknown04 = 1;
        param.unknown18 = unknown10.unknown00;
        param.unknown11 = true;
        param.unknown14 = 4;
        int ctrl = GfMenuObjUtil::startCtrl(acc.unknown10, param, "IMG_reaction_icon");
        GfMenuObject::hookCtrlEvent(acc.unknown10, ctrl);
        unknown10.unknown00 = ctrl;
        if (unknown10.unknown04 != -1) {
          ui::UIObjectAcc(acc.unknown10, "IMG_reaction_icon_eff").setAlpha(0.0f);
          GfMenuObjUtil::suspendCtrl(unknown10.unknown04);
        }
        if ((param0 | 1) == 5) {
          GfMenuObjUtil::playSE(0x2e);
        }
      }
      break;
    case 4: {
      ui::UIObjectAcc suspend(acc.unknown10, "LAY_reaction_time_suspend");
      if (param0 == 5) {
        suspend.setDisp(true);
        suspend.setAlpha(0.0f);
        GfMenuObjUtil::CtrlParam param;
        param.unknown08 = 4;
        param.unknown00 = 0.5f;
        param.unknown3c = 1.0f;
        param.unknown10 = true;
        param.unknown0c = 3;
        GfMenuObjUtil::startCtrl(suspend.unknown10, param, nullptr);
      } else {
        int ctrl = GfMenuObjUtil::getCtrlID(suspend.unknown10);
        if (ctrl != -1) {
          GfMenuObjUtil::stopCtrl(ctrl);
          suspend.setDisp(false);
        }
      }
      break;
    }
    }
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjEnemyStatus::ElemListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    break;
  case unknown011: {
    u32 param0 = event.unknown08;
    switch (event.unknown0c) {
    case 1:
      if (param0 == 5) {
        acc.setAddColor("white");
        GfMenuObjUtil::CtrlParam param;
        param.unknown08 = 0x4000000;
        param.unknown00 = 0.5f;
        param.unknown40_col3 = GfMenuObjUtil::getPresetColor("black");
        GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
      }
      break;
    case 2: {
      ui::UIObjectAcc suspend(acc.unknown10, "LAY_elem_time_suspend");
      if (param0 == 5) {
        suspend.setDisp(true);
        suspend.setAlpha(0.0f);
        GfMenuObjUtil::CtrlParam param;
        param.unknown08 = 4;
        param.unknown00 = 0.5f;
        param.unknown3c = 1.0f;
        param.unknown10 = true;
        param.unknown0c = 3;
        unknown20->unknown100 = GfMenuObjUtil::startCtrl(suspend.unknown10, param, nullptr);
      } else if (unknown20->unknown100 != -1) {
        GfMenuObjUtil::stopCtrl(unknown20->unknown100);
        unknown20->unknown100 = -1;
        suspend.setDisp(false);
      }
      break;
    }
    }
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
