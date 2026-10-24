#include "event/text_window.h"

#include "event/text_manager.h"
#include "fw/fw_debug.h"
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
#include "ml/dev_graph.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/reference_object.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

TextWindow::TextWindow() : unknown08(0), unknown218(gf::INVALID_HANDLE), unknown220(nullptr) {}

void TextWindow::clear() {
  if (unknown220 != nullptr) {
    gf::GfMenuObjBalloon::close(unknown220, true);
    mm::mtl::safeRelease(unknown220);
  }
  unknown110 = "";
  unknown0c = "";
  unknown218 = gf::INVALID_HANDLE;
  unknown08 = 0;
}

void TextWindow::update() {
  if (!isDisp()) {
    return;
  }
  if ((unknown08 & FLAG_CLOSE) == 0) {
    gf::GfMenuCallContext::GfMenuResult result = {};
    if (unknown220->popResult(result) && result.unknown04 == 1) {
      unknown08 |= FLAG_CLOSE;
      unknown228 = 4;
    }
  }
  if ((unknown08 & FLAG_CLOSE) != 0) {
    if (unknown228-- > 0 && !TextManager::get().isCutChangeFrame()) {
      return;
    }
    erase();
    unknown08 &= ~FLAG_WRITE;
  }
}

void TextWindow::erase() {
  if (unknown220 != nullptr) {
    bool isImmediate = !TextManager::get().isCutChangeFrame();
    gf::GfMenuObjBalloon::close(unknown220, isImmediate);
    mm::mtl::safeRelease(unknown220);
  }
}

void TextWindow::render() {
  if (!isDisp()) {
    return;
  }
  s32 height = ml::DevGraph::getRootHeight();
  s32 y = height - 200;
  s32 width = ml::DevGraph::getRootWidth() - 500;
  fw::debug::drawSquare2D(mm::Rect<s32>(250, y, width, 60), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<s32>(250, y, width, 60), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFont(260, height - 190, "TEXTWIN");
  fw::debug::drawFont(335, height - 190, "[%s]", unknown0c.c_str());
  fw::debug::drawFont(265, height - 175, unknown110.c_str());
}

void TextWindow::write(const char *text, const char *name, u8 *bdat, u32 textId, gf::GF_OBJ_HANDLE *handle) {
  if (bdat == nullptr || *text == '\0') {
    hide();
    return;
  }
  if (unknown220 == nullptr || this->unknown218 != handle) {
    erase();
    unknown220 = gf::GfMenuCallContext::create();
    gf::GfMenuObjBalloon::OpenParam param;
    param.unknown00 = bdat;
    param.unknown08 = textId;
    param.unknown20 = handle;
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
    gf::DataParamAcc paramAcc(handle);
    gf::GfMenuBdat::getMenuOffset(paramAcc.getMenuOffset(), param.unknown30);
    gf::GfMenuObjBalloon::openEvent(unknown220, param);
  } else {
    gf::GfMenuObjBalloon::NextParam param;
    param.unknown00 = bdat;
    param.unknown08 = textId;
    gf::GfMenuObjBalloon::nextEvent(unknown220, param);
  }
  this->unknown110 = text;
  this->unknown0c = name;
  this->unknown218 = handle;
  unknown08 = (unknown08 & ~(FLAG_WRITE | FLAG_CLOSE)) | FLAG_WRITE;
}

bool TextWindow::isWriting() const { return (unknown08 & (FLAG_WRITE | FLAG_CLOSE)) == FLAG_WRITE; }

} // namespace event
