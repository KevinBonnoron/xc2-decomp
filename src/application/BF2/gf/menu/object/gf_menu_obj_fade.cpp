#include "gf/menu/object/gf_menu_obj_fade.h"

#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_vec2.h"
#include "mm_mtl/fixstr.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_util.h"

namespace gf {

GfMenuObjFade::GfMenuObjFade(u32 handle) : GfMenuObject(handle), unknown24(0), unknown28(0) {}

GfMenuObjFade::~GfMenuObjFade() { ; }

void GfMenuObjFade::finalize() { GfMenuObject::finalize(); }

void GfMenuObjFade::update() { GfMenuObject::update(); }

// Inferred role: queues a game event with one parameter for the game listener; original name unknown.
static inline void unknown003(u32 handle, u16 type, u8 param) {
  ui::UIEventManager::EventInfo info;
  info.unknown00 = handle;
  info.unknown08.unknown0c = 0;
  info.unknown08.unknown00 = type;
  info.unknown08.unknown08 = param;
  ui::UIEventManager::get()->pushGameEvent(info);
}

void GfMenuObjFade::FadeListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    s16 width;
    s16 height;
    acc.getSize(false, width, height);
    mm::Vec2 scale;
    scale.x = static_cast<f32>(ui::UIUtil::getScreenWidth()) / static_cast<f32>(width);
    scale.y = static_cast<f32>(ui::UIUtil::getScreenHeight()) / static_cast<f32>(height);
    acc.setScale(scale);
    mm::Pnt<s16> center(ui::UIUtil::getScreenWidth() >> 1, ui::UIUtil::getScreenHeight() >> 1);
    acc.setPosCenter(center);
    acc.setAlpha(0.0f);
    unknown10 = -1;
    break;
  }
  case 3:
    unknown003(acc.unknown10, 0xb, unknown0c);
    unknown10 = -1;
    break;
  case 0x100: {
    u64 params = event.unknown08_u64;
    u32 params2 = event.unknown10;
    f32 time = static_cast<u32>(params & 0xffff) / 30.0f;
    f32 alpha = (params2 & 0xffff) / 255.0f;
    mm::Col3 color;
    color.r = static_cast<u32>((params >> 16) & 0xffff) / 255.0f;
    color.g = static_cast<u32>((params >> 32) & 0xffff) / 255.0f;
    color.b = static_cast<u32>(params >> 48) / 255.0f;
    unknown0c = params2 >> 16;
    acc.setAddColor(color);
    if (unknown10 != -1) {
      GfMenuObjUtil::stopCtrl(unknown10);
      unknown10 = -1;
    }
    if (time == 0.0f) {
      acc.setAlpha(alpha);
      unknown003(acc.unknown10, 0xb, unknown0c);
    } else {
      GfMenuObjUtil::CtrlParam param;
      bool isChange;
      {
        f32 current;
        acc.getAlpha(current);
        isChange = alpha != current;
      }
      if (isChange) {
        param.unknown08 = 4;
        param.unknown3c = alpha;
        param.unknown00 = time;
        unknown10 = GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
        unknown003(acc.unknown10, 10, unknown0c);
      } else {
        param.unknown00 = time;
        unknown003(acc.unknown10, 0xb, unknown0c);
      }
    }
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

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

} // namespace gf
