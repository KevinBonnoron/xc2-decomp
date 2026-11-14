#include "gf/menu/object/gf_menu_obj_fade.h"

#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixstr.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjFade::GfMenuObjFade(u32 handle) : GfMenuObject(handle), unknown24(0), unknown28(0) {}

GfMenuObjFade::~GfMenuObjFade() { ; }

void GfMenuObjFade::finalize() { GfMenuObject::finalize(); }

void GfMenuObjFade::update() { GfMenuObject::update(); }

// Inferred role: finds the image of a fade layer, 0 when the index is out of range; original name unknown.
static u32 unknown001(u32 handle, u8 index) {
  u32 result = 0;
  if (index < 3) {
    mm::mtl::FixStr<32> name;
    name.format("IMG_fade%02d", index);
    result = ui::UIObjectAcc(handle).searchChild(name.c_str());
  }
  return result;
}

void GfMenuObjFade::start(const StartParam &param) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3b));
  if (acc.isValid() && !acc.isTerm() && param.unknown00 < 3) {
    ui::UIObjectAcc fade(unknown001(acc.unknown10, param.unknown00));
    if (fade.isValid()) {
      ui::EventData event;
      event.unknown00 = 0x100;
      event.unknown08_u16 = param.unknown02;
      event.unknown0a = param.unknown04 * 255.0f;
      event.unknown0c_u16 = param.unknown08 * 255.0f;
      event.unknown0e = param.unknown0c * 255.0f;
      event.unknown10_u16 = param.unknown10 * 255.0f;
      event.unknown12 = param.unknown00;
      ui::UIManager::get()->requestObjectEvent(fade.unknown10, event, 0.0f);
    }
  }
}

// Inferred helper: shows or hides a child layer of the fade object unless it is terminating; original name unknown.
static inline void unknown002(const char *name, bool disp, u16 type) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3b));
  if (acc.isValid() && !acc.isTerm()) {
    ui::EventData event;
    event.unknown0c = 0;
    event.unknown00 = disp ? 0x21 : 0x22;
    event.unknown08 = type;
    GfMenuObject::sendEvent(acc.searchChild(name), event, 0.0f);
  }
}

void GfMenuObjFade::dispLoading(bool disp, u16 type) { unknown002("LAY_loading", disp, type); }

void GfMenuObjFade::dispSaving(bool disp, u16 type) { unknown002("LAY_saving", disp, type); }

void GfMenuObjFade::LoadingListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    break;
  case GfMenuTypes::unknown003_33:
    if (unknown20->unknown28++ <= 0) {
      f32 time = static_cast<int>(event.unknown08) * 0.033333335f;
      if (time == 0.0f) {
        acc.setDisp(true);
      } else {
        GfMenuObjUtil::CtrlParam param;
        param.unknown08 = 1;
        param.unknown00 = time;
        GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
      }
    }
    break;
  case GfMenuTypes::unknown003_34:
    if (--unknown20->unknown28 <= 0) {
      unknown20->unknown28 = 0;
      f32 time = static_cast<int>(event.unknown08) * 0.033333335f;
      if (time == 0.0f) {
        acc.setDisp(false);
      } else {
        GfMenuObjUtil::CtrlParam param;
        param.unknown08 = 2;
        param.unknown00 = time;
        GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
      }
    }
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
