#include "gf/menu/object/gf_menu_obj_compass.h"

#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/gf_menu_flag.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/plugin/ui_object_text_plugin.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x42;
// Inferred role: second attached call id; original name unknown.
constexpr u32 unknown002 = 0x43;

// Inferred role: control of the battle frame and opened flag when the compass is closed; original name unknown.
static const GfMenuObjCompass::MainListener::unknown005 unknown006 = {-1, 0};

mm::mtl::FixedVector<GfMenuObjCompass::unknown004, 32> GfMenuObjCompass::m_IconObjList;

GfMenuObjCompass::GfMenuObjCompass(u32 handle) : GfMenuObject(handle) { m_IconObjList.clear(); }

GfMenuObjCompass::~GfMenuObjCompass() { ; }

void GfMenuObjCompass::finalize() { GfMenuObject::finalize(); }

void GfMenuObjCompass::close() { unknown143(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjCompass::open() { unknown143(unknown001, GfMenuTypes::unknown003_33); }

void GfMenuObjCompass::dispInBattle(bool isDisp) {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    if (!ui::UIObjectAcc(handle).isTerm()) {
      ui::EventData event;
      event.unknown00 = 0x101;
      event.unknown08 = isDisp;
      sendEvent(handle, event, 0.0f);
    }
  }
}

void GfMenuObjCompass::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  attachExternalCall(unknown001, main.unknown10);
  attachExternalCall(unknown002, main.unknown10);
// __LINE__ must be 83 as in the original file: it is the line argument of operator new.
#line 83
  MainListener *listener = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) MainListener(this);
  listener->addRef();
  ui::UIEventManager::get()->registObjectListener(main.unknown10, listener);
  if (listener != nullptr) {
    listener->release();
  }
  GfMenuObject::initialize();
}

void GfMenuObjCompass::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    acc.setDisp(false);
    unknown0c = -1;
    unknown10 = unknown006;
    mm::mtl::FixStr<32> name;
    name.format("TXT_area@%02d", 1);
    ui::UIObjectAcc text(acc.searchChild(name.c_str()));
    ui::UIObjectTextPlugin *plugin = ui::UIObjectTextPlugin::create(text.unknown10);
    if (plugin != nullptr) {
      plugin->release();
    }
    break;
  }
  case GfMenuTypes::unknown003_33:
    if (GfMenuFlag::get1(0x1f) == 0 && unknown10.unknown04 == 0) {
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 1;
      param.unknown00 = 0.25f;
      int ctrl = GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
      unknown10.unknown04 = 1;
      unknown0c = ctrl;
    }
    break;
  case GfMenuTypes::unknown003_34:
    if (unknown10.unknown04 == 1) {
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 2;
      param.unknown00 = 0.25f;
      int ctrl = GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
      unknown10.unknown04 = 0;
      unknown0c = ctrl;
    }
    break;
  case GfMenuTypes::unknown003_257:
    if (event.unknown08 == 0) {
      if (unknown10.unknown00 != -1) {
        GfMenuObjUtil::stopCtrl(unknown10.unknown00);
        unknown10.unknown00 = -1;
      }
    } else if (unknown10.unknown00 == -1) {
      ui::UIObjectAcc frame(acc.unknown10, "LAY_frame");
      if (frame.isValid()) {
        GfMenuObjUtil::CtrlParam param;
        param.unknown08 = 0x2000000;
        param.unknown40 = 0.8f;
        param.unknown44 = 0.0f;
        param.unknown10 = true;
        param.unknown48 = 0.0f;
        param.unknown0c = 3;
        param.unknown14 = 8;
        param.unknown00 = 1.0f;
        unknown10.unknown00 = GfMenuObjUtil::startCtrl(frame.unknown10, param, nullptr);
      }
    }
    break;
  case GfMenuTypes::unknown003_258: {
    u16 image = event.unknown0a;
    ui::UIObjectAcc icon(acc.searchDuplicatedChild("IMG_icon", event.unknown08_u16));
    if (icon.isValid()) {
      icon.setImageIndex(GfMenuBdat::getIconImageIndex(image));
      icon.setDisp(true);
    }
    break;
  }
  case GfMenuTypes::unknown003_259: {
    ui::UIObjectAcc icon(acc.searchDuplicatedChild("IMG_icon", event.unknown08_u16));
    if (icon.isValid()) {
      icon.setTerm();
      GfMenuObject::termCallContext(icon.unknown10);
    }
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
