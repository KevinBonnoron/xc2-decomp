#include "gf/menu/object/gf_menu_obj_lvup_select.h"

#include "gf/data/gf_bdat_btl.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/reference_object.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x57;
// Inferred role: common window of the level up confirmation; original name unknown.
constexpr u16 unknown002 = 0xa7;

GfMenuObjLvupSelect::GfMenuObjLvupSelect(u32 handle) : GfMenuObject(handle), unknown28(this), unknown2b8(false), unknown2d8(nullptr) {
  unknown2c8 = unknown160();
  unknown2d0 = unknown160();
  unknown2d8 = GfMenuCallContext::create();
}

GfMenuObjLvupSelect::~GfMenuObjLvupSelect() {
  mm::mtl::safeRelease(unknown2d8);
  unknown2d0 = nullptr;
  unknown2c8 = nullptr;
}

void GfMenuObjLvupSelect::finalize() { GfMenuObject::finalize(); }

void GfMenuObjLvupSelect::update() {
  unknown28.unknown003();
  GfMenuObject::update();
}

void GfMenuObjLvupSelect::updateBonusExp() {
  u32 driver = GfMenuReference::getReferenceDriverID(0);
  if (driver != 0) {
    DataParamAcc acc(OBJECT_TYPE_DRIVER, driver, GIMMICK_TYPE_NONE);
    if (acc.isValid()) {
      u32 battleExp;
      u32 exp = acc.getExp();
      u32 level = acc.getLevel(false);
      u32 virtualLevel = GfMenuReference::getDriverVirtualLevel();
      if (level < virtualLevel) {
        battleExp = acc.getBattleExp();
        GfBdatBtl *bdatBattle = GfBdatBtl::get();
        for (u32 i = 0; i < virtualLevel - level; i++) {
          u32 growExp = bdatBattle->getGrowLevelExp(level + i + 1);
          exp = battleExp + exp - growExp;
          battleExp = 0;
        }
      }
      unknown2d0->unknown0c = exp;
    }
  }
}

bool GfMenuObjLvupSelect::seqConfirmLevelUp() {
  if (!unknown2b8) {
    GfMenuManager::openCommonWindow(unknown002);
    unknown2b8 = true;
    return false;
  }
  if (!GfMenuManager::isOpenCommonWindow()) {
    s16 result = GfMenuManager::getCommonWindowResult();
    if (result == 0) {
      unknown28.unknown002(&GfMenuObjLvupSelect::seqExecLevelUp);
    } else {
      enableFSInput(4);
    }
    unknown2b8 = false;
    return true;
  }
  return false;
}

void GfMenuObjLvupSelect::openLevelSelect(GfMenuCallContext *context, u32 level) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid() && GfMenuObjUtil::checkCCStart(context)) {
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_33;
    event.unknown08 = 0;
    event.unknown0c = level;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
    GfMenuObject::startCallContext(context, unknown001, acc.unknown10);
  }
}

void GfMenuObjLvupSelect::openLevelup(GfMenuCallContext *context, u32 level, u32 levelMax) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid() && GfMenuObjUtil::checkCCStart(context)) {
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_33;
    event.unknown08 = 0;
    event.unknown0c = level;
    event.unknown10 = levelMax;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
    GfMenuObject::startCallContext(context, unknown001, acc.unknown10);
  }
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjLvupSelect>(const mm::mtl::Delegate<bool()> *);
