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
  if (context->popResult(menuResult) && menuResult.type == 2) {
    closeContext();
    result = menuResult.value + 1;
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
    param.bdat = bdat;
    param.textId = textId;
    param.handle = handle;
    gf::GfMenuBdat::getMenuOffset(MENU_OFFSET_SELECT, param.offset);
    param.selectBdat = bdat;
    for (size_t i = 0; i < count && i < param.selectIds.capacity(); i++) {
      param.selectIds.push_back(selectIds[i]);
    }
    if (handle != gf::INVALID_HANDLE) {
      gf::DataParamAcc paramAcc(handle);
      switch (paramAcc.getObjType()) {
      case gf::OBJECT_TYPE_DRIVER:
        gf::GfDataDriver::getName(param.nameBdat, param.nameId, paramAcc.isValid() && paramAcc.getObjType() == gf::OBJECT_TYPE_DRIVER ? paramAcc.getBdatId() : 0);
        break;
      case gf::OBJECT_TYPE_BLADE:
        gf::GfDataBlade::getName(param.nameBdat, param.nameId, paramAcc.isValid() ? paramAcc.getBdatId() : 0);
        break;
      case gf::OBJECT_TYPE_ENEMY:
        gf::GfDataEnemy::getName(param.nameBdat, param.nameId, paramAcc.isValid() ? paramAcc.getBdatId() : 0);
        break;
      case gf::OBJECT_TYPE_NPC:
        gf::GfDataNpc::getName(param.nameBdat, param.nameId, paramAcc.isValid() ? paramAcc.getBdatId() : 0);
        break;
      }
    }
    gf::GfMenuObjBalloon::openEventSelect(context, param);
  } else if (type == SELECT_TYPE_BOX) {
    gf::GfMenuObjBalloon::OpenSelectBoxParam param;
    param.bdat = bdat;
    param.textId = textId;
    param.selectBdat = bdat;
    for (size_t i = 0; i < count && i < param.selectIds.capacity(); i++) {
      param.selectIds.push_back(selectIds[i]);
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
