#include "gf/menu/object/gf_menu_obj_compass.h"

#include <math.h>

#include "bdat.h"
#include "fw/fw_transform.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/game/gf_game_manager.h"
#include "gf/gf_allocator.h"
#include "gf/gf_info.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/gf_menu_flag.h"
#include "gf/menu/gf_menu_location.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/object/gf_obj_acc.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/rtti.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/plugin/ui_object_number_plugin.h"
#include "ui/plugin/ui_object_text_plugin.h"
#include "ui/ui_object.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"
#include "ui/ui_util.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x42;
// Inferred role: second attached call id; original name unknown.
constexpr u32 unknown002 = 0x43;

// Inferred role: control of the battle frame and opened flag when the compass is closed; original name unknown.
static const GfMenuObjCompass::MainListener::unknown005 unknown006 = {-1, 0};

mm::mtl::FixedVector<GfMenuObjCompass::IconObj, 32> GfMenuObjCompass::m_IconObjList;

GfMenuObjCompass::GfMenuObjCompass(u32 handle) : GfMenuObject(handle) { m_IconObjList.clear(); }

GfMenuObjCompass::~GfMenuObjCompass() { ; }

void GfMenuObjCompass::finalize() { GfMenuObject::finalize(); }

void GfMenuObjCompass::update() {
  GfObjAcc leader(GfGameManager::getPartyLeaderDriver());
  if (leader.isValid()) {
    f32 leaderHeight = leader.getWorldTransform().unknown00.y;
    // Declared before the IMG_center accessor: the game's stack puts the locator data above it (0x71004414c8).
    GfMenuLocation::LocatorData data;
    ui::UIObjectAcc center(unknown18, "IMG_center");
    if (center.isValid()) {
      {
        mm::mtl::FixStr<32> name;
        name.format("LAY_outside@%02d", 1);
        GfMenuObjUtil::setChildDisp(unknown18, name.c_str(), false);
      }
      // A word, not a bool: the game tests it with cbnz; a bool compiles to 442 instructions instead of 439.
      u32 isAreaShown = 0;
      for (IconObj *icon = m_IconObjList.begin(); icon != m_IconObjList.end(); ++icon) {
        ui::UIObjectAcc acc(icon->unknown00);
        if (!GfMenuLocation::getLocatorData(icon->m_locatorParam.unknown00, icon->m_locatorParam.unknown02, data, 0, false)) {
          if (icon->unknown0c != 0) {
            icon->unknown0c--;
          } else {
            acc.setDisp(false);
          }
          continue;
        }
        icon->unknown0c = 2;
        if (data.unknown18) {
          mm::mtl::FixStr<32> layerName;
          if (!isAreaShown) {
            ui::UIObjectAcc areas(unknown18, "LAY_outsides");
            layerName.format("LAY_outside@%02d", 1);
            GfMenuObjUtil::setChildDisp(areas.unknown10, layerName.c_str(), true);
            u8 *mapList = GfDataBdat::getFP(BDAT_FLD_MAPLIST);
            u8 *mapInfo = GfDataBdat::getFP(BDAT_FLD_MAPINFO);
            mm::mtl::FixStr<32> name;
            name.format("TXT_area@%02d", 1);
            ui::UIObjectAcc text(areas.searchChild(name.c_str()));
            ui::UIObject *object = ui::UIUtil::getObject(text.unknown10);
            if (object != nullptr && object->unknowne0 != nullptr) {
              ui::UIObjectTextPlugin *plugin = mm::mtl::dynamicCast<ui::UIObjectTextPlugin>(object->unknowne0);
              if (plugin != nullptr && data.unknown1c >= Bdat::getIdTop(mapList) && data.unknown1c <= Bdat::getIdEnd(mapList)) {
                u32 nameId = Bdat::getVal(mapList, "nameID", data.unknown1c).valueU16;
                if (nameId >= Bdat::getIdTop(mapInfo) && nameId <= Bdat::getIdEnd(mapInfo)) {
                  plugin->setText(ui::UIStr(mapInfo, nameId));
                }
              }
            }
            u32 image = GfMenuBdat::getIconImageIndex(data.unknown14);
            if (image < 3) {
              name.format("IMG_icon_outside@%02d", 1);
              ui::UIObjectAcc outside(areas.searchChild(name.c_str()));
              outside.setImageIndex(image);
            }
            isAreaShown = 1;
          }
          acc.setDisp(false);
          continue;
        }
        mm::Vec3 direction;
        GfMenuObjUtil::convViewSpace(direction, data.unknown00);
        direction.y = 0.0f;
        direction.unknown001();
        mm::Vec3 target = GfInfo::m_camTgt;
        GfMenuObjUtil::convViewSpace(target, GfInfo::m_camPos + (target - GfInfo::m_camPos));
        // A near zero direction leaves the icon as it is: the game neither shows nor hides it.
        if (target.unknown003()) {
          continue;
        }
        target.unknown001();
        f32 dot = target.x * direction.x + target.y * direction.y + target.z * direction.z;
        if (dot < 0.0f) {
          dot = 0.0f;
          if (icon->m_locatorParam.unknown00 >= 2) {
            acc.setDisp(false);
            continue;
          }
        }
        acc.setDisp(true);
        // Read here, before the range test, as the game does (the load comes right after the setDisp call).
        f32 posY = data.unknown00.y;
        int distance = data.unknown20;
        if (icon->m_locatorParam.unknown04 != 0 && distance > icon->m_locatorParam.unknown04) {
          acc.setDisp(false);
          continue;
        }
        f32 ratio = dot * 0.5f;
        u32 mark = 2;
        if (fabsf(leaderHeight - posY) > 5.0f) {
          mark = posY > leaderHeight ? 0 : 1;
        }
        if (direction.x > 0.0f) {
          ratio = (0.5f - ratio) + 0.5f;
        }
        ui::UIObjectAcc frame(center.unknown10);
        mm::Rect<s16> rect;
        mm::Pnt<s16> pos;
        s16 width;
        s16 height;
        acc.getSize(true, width, height);
        frame.getRect(rect, ui::UIObjectAcc::RECT_SCALED);
        rect.width -= width;
        rect.height -= height;
        pos.x = rect.x + width / 2 + static_cast<s16>(ratio * rect.width);
        pos.y = height / 2 + rect.y;
        acc.setPosCenter(pos);
        {
          ui::UIObjectAcc image(acc.searchChild("IMG_icon"));
          image.setImageIndex(GfMenuBdat::getIconImageIndex(data.unknown14));
          ui::UIObjectAcc markImage(acc.searchChild("IMG_icon_pos"));
          markImage.setImageIndex(mark);
        }
        ui::UIObjectAcc length(acc.searchChild("TXT_len"));
        // Two calls: the game merges them into one after setting the argument in each arm (a select gives other code).
        if (distance != 0) {
          length.setAlpha(1.0f);
        } else {
          length.setAlpha(0.0f);
        }
        ui::UIObjectNumberPlugin *plugin = ui::UIObjectNumberPlugin::getPlugin(length.unknown10);
        if (plugin != nullptr) {
          plugin->setNumber(distance);
        }
      }
      GfMenuObject::update();
    }
  }
}

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

void GfMenuObjCompass::addLocator(const LocatorParam &param) {
  u32 handle = getAttachedObject(unknown002);
  if (ui::UIObjectAcc(handle).isValid()) {
    if (!ui::UIObjectAcc(handle).isTerm()) {
      ui::UIObjectAcc root(handle);
      ui::UIObjectAcc icon(root.duplicateChild("LAY_icon"));
      if (icon.isValid()) {
        icon.setDispPriority(icon.getDispPriority() + 4 - param.unknown00);
        {
          ui::UIObjectAcc length(icon.searchChild("TXT_len"));
          if (length.isValid()) {
            ui::UIObjectNumberPlugin *plugin = ui::UIObjectNumberPlugin::create(length.unknown10);
            if (plugin != nullptr) {
              plugin->release();
            }
          }
        }
        IconObj obj;
        obj.unknown00 = icon.unknown10;
        obj.m_locatorParam = param;
        obj.unknown0c = 2;
        m_IconObjList.push_back(obj);
      }
    }
  }
}

void GfMenuObjCompass::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  attachExternalCall(unknown001, main.unknown10);
  attachExternalCall(unknown002, main.unknown10);
// __LINE__ must be 83 as in the original file: it is the line argument of operator new.
#line 83
  MainListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
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
