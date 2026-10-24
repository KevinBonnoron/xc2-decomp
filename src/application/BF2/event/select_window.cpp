#include "event/select_window.h"

#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_npc.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/object/gf_menu_obj_balloon.h"
#include "gf/object/gf_obj_handle.h"
#include "mm_mtl/fixed_vector.h"

namespace event {

static constexpr int MENU_OFFSET_SELECT = 1;

SelectWindow::SelectWindow() : flags(), result(0), context(nullptr) {}

void SelectWindow::clear() {
  closeContext();
  flags.clear();
}

void SelectWindow::update() {
  if (!isOpen()) {
    return;
  }
  gf::GfMenuCallContext::GfMenuResult menuResult;
  if (context->popResult(menuResult) && menuResult.unknown04 == 2) {
    closeContext();
    result = menuResult.unknown00 + 1;
    flags.clear();
  }
}

void SelectWindow::close() {
  closeContext();
  flags.clear();
}

void SelectWindow::open(SELECT_TYPE type, int textId, const int *selectIds, size_t count, u8 *bdat, gf::GF_OBJ_HANDLE *handle) {
  if (textId <= 0) {
    result = 1;
    return;
  }
  context = gf::GfMenuCallContext::create();
  if (type == SELECT_TYPE_BALLOON) {
    gf::GfMenuObjBalloon::OpenSelectParam param;
    param.unknown00 = bdat;
    param.unknown08 = textId;
    param.unknown20 = handle;
    gf::GfMenuBdat::getMenuOffset(MENU_OFFSET_SELECT, param.unknown30);
    param.unknown50 = bdat;
    for (size_t i = 0; i < count && i < param.unknown58.capacity(); i++) {
      param.unknown58.push_back(selectIds[i]);
    }
    if (handle != gf::INVALID_HANDLE) {
      gf::DataParamAcc paramAcc(handle);
      switch (paramAcc.getObjType()) {
      case gf::OBJECT_TYPE_DRIVER:
        gf::GfDataDriver::getName(param.unknown10, param.unknown18, paramAcc.isValid() && paramAcc.getObjType() == gf::OBJECT_TYPE_DRIVER ? paramAcc.getBdatId() : 0);
        break;
      case gf::OBJECT_TYPE_BLADE:
        gf::GfDataBlade::getName(param.unknown10, param.unknown18, paramAcc.isValid() ? paramAcc.getBdatId() : 0);
        break;
      case gf::OBJECT_TYPE_ENEMY:
        gf::GfDataEnemy::getName(param.unknown10, param.unknown18, paramAcc.isValid() ? paramAcc.getBdatId() : 0);
        break;
      case gf::OBJECT_TYPE_NPC:
        gf::GfDataNpc::getName(param.unknown10, param.unknown18, paramAcc.isValid() ? paramAcc.getBdatId() : 0);
        break;
      }
    }
    gf::GfMenuObjBalloon::openEventSelect(context, param);
  } else if (type == SELECT_TYPE_BOX) {
    gf::GfMenuObjBalloon::OpenSelectBoxParam param;
    param.unknown00 = bdat;
    param.unknown08 = textId;
    param.unknown10 = bdat;
    for (size_t i = 0; i < count && i < param.unknown18.capacity(); i++) {
      param.unknown18.push_back(selectIds[i]);
    }
    gf::GfMenuObjBalloon::openEventSelectBox(context, param);
  }
  flags.set(FLAG_OPEN);
}

int SelectWindow::getResult() {
  if (!isOpen()) {
    return result;
  }
  return 0;
}

} // namespace event
