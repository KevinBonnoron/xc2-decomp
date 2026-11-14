#include "gf/menu/object/gf_menu_obj_field_skill.h"

#include "gf/game/gf_game_voice.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_field_skill_list.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_vec2.h"
#include "mm_mtl/delegate.h" // IWYU pragma: keep
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

namespace gf {

// Inferred role: skip call id; original name unknown.
constexpr u32 unknown001 = 0x32;

// Inferred role: main call id; original name unknown.
constexpr u32 unknown002 = 0x31;

// Inferred role: skill info call id; original name unknown.
constexpr u32 unknown003 = 0x33;

// Inferred role: skill info close call id; original name unknown.
constexpr u32 unknown004 = 0x34;

// Inferred role: result call id; original name unknown.
constexpr u32 unknown005 = 0x35;

// Inferred role: result close call id; original name unknown.
constexpr u32 unknown006 = 0x36;

// Inferred role: total call id; original name unknown.
constexpr u32 unknown007 = 0x37;

// Inferred role: total close call id; original name unknown.
constexpr u32 unknown008 = 0x38;

// Inferred role: ui event type, enables or disables the input; original name unknown.
constexpr u16 unknown009 = 0x10b;

GfMenuObjFieldSkill::~GfMenuObjFieldSkill() {
  unknown50 = nullptr;
  unknown38 = nullptr;
  unknown40 = nullptr;
  unknown28 = nullptr;
  unknown30 = nullptr;
  mm::mtl::safeRelease(unknown48);
}

void GfMenuObjFieldSkill::finalize() { GfMenuObject::finalize(); }

void GfMenuObjFieldSkill::update() {
  if (unknown68 != nullptr && GfGameVoice::getResult(unknown68) > CV_RESULT_UNKNOWN_2) {
    unknown68 = nullptr;
  }
  unknown70.unknown003();
  GfMenuObject::update();
}

bool GfMenuObjFieldSkill::seqWaitVoice() {
  if (unknown68 != nullptr) {
    return false;
  }
  ui::UIObjectAcc acc(unknown18, "LAY_main");
  GfMenuObject::termCallContext(acc.unknown10);
  return true;
}

void GfMenuObjFieldSkill::applyImageParam(u32 handle) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    ui::UIObjectAcc blade(acc.unknown10, "IMG_blade");
    ui::UIObjectAcc shadow(acc.unknown10, "IMG_blade_shadow");
    u32 id = GfMenuReference::getReferenceBladeID(5);
    acc.setLayout(blade.unknown10, "character");
    acc.setLayout(shadow.unknown10, "character");
    GfMenuObjUtil::ImageParam param;
    if (GfMenuObjUtil::getImageParam(1, id, param, 1)) {
      mm::Vec2 scale;
      blade.getScale(scale);
      scale.x = param.unknown04 * scale.x;
      scale.y = param.unknown04 * scale.y;
      blade.setScale(scale);
      GfMenuObjUtil::addPos(blade.unknown10, param.unknown00, param.unknown02);
      shadow.getScale(scale);
      scale.x = param.unknown04 * scale.x;
      scale.y = param.unknown04 * scale.y;
      shadow.setScale(scale);
      GfMenuObjUtil::addPos(shadow.unknown10, param.unknown00 + 10, param.unknown02 + 10);
    }
  }
}

void GfMenuObjFieldSkill::close(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCStart(context)) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown002));
    if (acc.isValid() && !acc.isTerm()) {
      ui::EventData event;
      event.unknown00 = GfMenuTypes::unknown003_34;
      GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
      GfMenuObject::startCallContext(context, unknown002, acc.unknown10);
    }
  }
}

void GfMenuObjFieldSkill::attachSkip(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCStart(context)) {
    unknown152(context, unknown001);
  }
}

void GfMenuObjFieldSkill::setSkipInput(GfMenuCallContext *context, bool skip) {
  if (GfMenuObjUtil::checkCCNext(context, unknown001)) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
    if (acc.isValid() && !acc.isTerm()) {
      ui::EventData event;
      event.unknown00 = 0x10b;
      event.unknown08 = skip;
      GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
    }
  }
}

void GfMenuObjFieldSkill::openSkillInfo(GfMenuCallContext *context, u8, const OpenSkillInfoParam &param) {
  if (GfMenuObjUtil::checkCCStart(context)) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown003));
    if (acc.isValid() && !acc.isTerm()) {
      ui::UIObjectAcc info(acc.searchChild("LAY_blade_info"));
      if (info.isValid()) {
        ui::EventData event;
        event.unknown00 = GfMenuTypes::unknown003_33;
        event.unknown08_u16 = param.unknown00_0;
        event.unknown0a = param.unknown00_16;
        event.unknown0c = param.unknown0c;
        GfMenuObject::sendEvent(info.unknown10, event, 0.0f);
        GfMenuObject::startCallContext(context, unknown003, info.unknown10);
      }
    }
  }
}

void GfMenuObjFieldSkill::closeSkillInfo(GfMenuCallContext *context, u8) {
  if (GfMenuObjUtil::checkCCNext(context, unknown003)) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown004));
    if (acc.isValid() && !acc.isTerm()) {
      ui::UIObjectAcc info(acc.searchChild("LAY_blade_info"));
      if (info.isValid()) {
        ui::EventData event;
        event.unknown00 = GfMenuTypes::unknown003_34;
        ui::UIManager::get()->requestObjectEvent(info.unknown10, event, 0.0f);
      }
      GfMenuObject::nextCallContext(context, unknown004);
    }
  }
}

void GfMenuObjFieldSkill::openResult(GfMenuCallContext *context, const OpenResultParam &param) {
  if (GfMenuObjUtil::checkCCStart(context)) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown005));
    if (acc.isValid() && !acc.isTerm()) {
      ui::UIObjectAcc result(acc.searchChild("LAY_result"));
      ui::EventData event;
      event.unknown00 = GfMenuTypes::unknown003_33;
      event.unknown0c = 0;
      event.unknown08 = param.unknown00;
      if (event.unknown08 == 0 && param.unknown08 != nullptr && param.unknown10 != 0) {
        ui::UIStr text(param.unknown08, param.unknown10);
        event.unknown0c = GfMenuObject::registString(text);
      }
      event.unknown10 = param.unknown14;
      GfMenuObject::sendEvent(result.unknown10, event, 0.0f);
      GfMenuObject::startCallContext(context, unknown005, result.unknown10);
    }
  }
}

void GfMenuObjFieldSkill::closeResult(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCNext(context, unknown005)) {
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_34;
    ui::UIManager::get()->requestObjectEvent(context->unknown14, event, 0.0f);
    GfMenuObject::nextCallContext(context, unknown006);
  }
}

void GfMenuObjFieldSkill::closeTotalInfo(GfMenuCallContext *context) {
  if (context != nullptr && context->unknown10 == unknown007) {
    ui::EventData event;
    event.unknown00 = 0x101;
    ui::UIManager::get()->requestObjectEvent(context->unknown14, event, 0.0f);
    GfMenuObject::nextCallContext(context, unknown008);
  }
}

void GfMenuObjFieldSkill::addTotalSkillLevel(u8 skill, u8 level) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown007));
  if (acc.isValid() && !acc.isTerm()) {
    ui::EventData event;
    event.unknown00 = 0x102;
    event.unknown0c = 0;
    event.unknown08_u16 = skill;
    event.unknown0a = level;
    ui::UIManager::get()->requestObjectEvent(acc.unknown10, event, 0.0f);
  }
}

void GfMenuObjFieldSkill::setCurrentTotalSkill(u8 skill) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown007));
  if (acc.isValid() && !acc.isTerm()) {
    ui::EventData event;
    event.unknown00 = 0x103;
    event.unknown08_u16 = skill;
    ui::UIManager::get()->requestObjectEvent(acc.unknown10, event, 0.0f);
  }
}

void GfMenuObjFieldSkill::undoTotalSkillLevel(u8 skill) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown007));
  if (acc.isValid() && !acc.isTerm()) {
    ui::EventData event;
    event.unknown00 = 0x10c;
    event.unknown08_u16 = skill;
    ui::UIManager::get()->requestObjectEvent(acc.unknown10, event, 0.0f);
  }
}

void GfMenuObjFieldSkill::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObject::disableInput(acc.unknown10);
    break;
  case 8:
    if (event.unknown0c == 1) {
      GfMenuObject::addResultCallContext(acc.unknown10, 2, 0);
      GfMenuObject::disableInput(acc.unknown10);
    }
    break;
  case GfMenuTypes::unknown003_34:
    GfMenuObject::disableInput(acc.unknown10);
    sendCloseEvent(acc.searchChild("LAY_blade"), 0, 0.0f);
    sendCloseEvent(acc.searchChild("LAY_base"), 0, 0.0f);
    sendCloseEvent(acc.searchChild("LAY_request"), 0, 0.0f);
    sendCloseEvent(acc.searchChild("LAY_blade_info"), 0, 0.0f);
    sendCloseEvent(acc.searchChild("LAY_blade_result"), 0, 0.0f);
    sendCloseEvent(acc.searchChild("LAY_input"), 0, 0.0f);
    unknown20->unknown60 = acc.unknown10;
    break;
  case 0x10b:
    if (event.unknown08 == 1) {
      GfMenuObject::enableInput(acc.unknown10);
    } else {
      GfMenuObject::disableInput(acc.unknown10);
    }
    break;
  case 0x10d:
    unknown20->unknown70.unknown005();
    unknown20->unknown70.unknown002(&GfMenuObjFieldSkill::seqWaitVoice);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjFieldSkill::BladeListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    unknown0c = 0;
    break;
  case 3:
    if (event.unknown08 == 1) {
      acc.setDisp(true);
      applyImageParam(acc.unknown10);
      GfMenuObjUtil::CtrlParam param;
      param.unknown004("fade_in_l");
      param.unknown14 = 8;
      GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    } else if (event.unknown08 == 2) {
      ui::UIObjectAcc blade(acc.unknown10, "IMG_blade");
      ui::UIObjectAcc shadow(acc.unknown10, "IMG_blade_shadow");
      blade.setImageIndex(0);
      shadow.setImageIndex(0);
    }
    break;
  case GfMenuTypes::unknown003_33:
    acc.setDisp(true);
    if (unknown0c == 0) {
      applyImageParam(acc.unknown10);
      GfMenuObjUtil::CtrlParam param;
      param.unknown004("fade_in_l");
      param.unknown14 = 8;
      GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
      unknown0c = 1;
    } else {
      GfMenuObjUtil::CtrlParam param;
      param.unknown004("fade_out_r");
      param.unknown04 = 1;
      param.unknown14 = 10;
      GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    }
    break;
  case GfMenuTypes::unknown003_34:
    if (unknown0c == 1) {
      GfMenuObjUtil::CtrlParam param;
      param.unknown004("fade_out_l");
      param.unknown14 = 10;
      param.unknown04 = 2;
      GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
      unknown0c = 0;
    }
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjFieldSkill::InputListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObject::disableInput(acc.unknown10);
    break;
  case 8:
    if (event.unknown0c == 1) {
      GfMenuObject::addResultCallContext(acc.unknown10, 2, 0);
      GfMenuObject::disableInput(acc.unknown10);
    }
    break;
  case GfMenuTypes::unknown003_34:
    GfMenuObject::disableInput(acc.unknown10);
    GfMenuObject::termCallContext(acc.unknown10);
    break;
  case unknown009:
    if (event.unknown08 == 1) {
      GfMenuObject::enableInput(acc.unknown10);
    } else {
      GfMenuObject::disableInput(acc.unknown10);
    }
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}
} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjFieldSkill>(const mm::mtl::Delegate<bool()> *);
