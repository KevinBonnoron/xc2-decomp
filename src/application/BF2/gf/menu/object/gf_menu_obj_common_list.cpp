#include "gf/menu/object/gf_menu_obj_common_list.h"

#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_rect.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/plugin/ui_object_fit_plugin.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_util.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x24;

// Inferred role: background images of the list rows; original name unknown.
static const char *const unknown002[] = {"IMG_list01_bg", "IMG_list02_bg", "IMG_list03_bg", "IMG_list04_bg", "IMG_list05_bg", "IMG_list06_bg", "IMG_list07_bg", "IMG_list08_bg", "IMG_list09_bg"};

GfMenuObjCommonList::GfMenuObjCommonList(u32 handle) : GfMenuObject(handle) {}

GfMenuObjCommonList::~GfMenuObjCommonList() { ; }

void GfMenuObjCommonList::setupPlugin(u32 handle) {
  u32 list = ui::UIUtil::searchChild(handle, "LAY_list");
  if (!ui::UIUtil::isValid(list)) {
    return;
  }
  u32 window = ui::UIUtil::searchChild(handle, "IMG_win");
  if (!ui::UIUtil::isValid(window)) {
    return;
  }
  ui::UIObjectFitPlugin *plugin = ui::UIObjectFitPlugin::create(window, list, 20, 20);
  if (plugin != nullptr) {
    plugin->release();
  }
}

void GfMenuObjCommonList::finalize() { GfMenuObject::finalize(); }

void GfMenuObjCommonList::update() { GfMenuObject::update(); }

void GfMenuObjCommonList::open(GfMenuCallContext *context, const OpenParam &param) {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    if (!ui::UIObjectAcc(handle).isTerm()) {
      startCallContext(context, unknown001, handle);
      ui::UIObjectAcc acc(handle);
      if (param.unknown00 == 0) {
        acc.setPos(mm::Pnt<s16>(param.unknown10.x, param.unknown10.y));
      } else {
        ui::UIObjectAcc base(param.unknown00);
        if (base.isValid()) {
          mm::Rect<s16> rect;
          base.getLayoutRect(param.unknown08, rect);
          mm::Pnt<s16> pos;
          pos.x = rect.x;
          pos.y = rect.y;
          acc.setPos(pos);
        }
      }
      ui::EventData event;
      event.unknown0c = 0;
      event.unknown00 = GfMenuTypes::unknown003_33;
      event.unknown08 = param.unknown18 << 8 | param.unknown1c;
      sendEvent(handle, event, 0.0f);
    }
  }
}

void GfMenuObjCommonList::moveCursor(u32 handle, int index) {
  ui::UIObjectAcc row(handle, unknown002[index]);
  ui::UIObjectAcc cursor(handle, "IMG_cursor");
  if (row.isValid() && cursor.isValid()) {
    GfMenuObjUtil::setDockPos(cursor.unknown10, row.unknown10, 0, true);
  }
}

void GfMenuObjCommonList::close() { unknown143(unknown001, GfMenuTypes::unknown003_34); }

} // namespace gf
