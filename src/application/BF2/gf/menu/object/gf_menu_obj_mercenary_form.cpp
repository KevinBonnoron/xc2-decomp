#include "gf/menu/object/gf_menu_obj_mercenary_form.h"

#include "gf/menu/gf_menu_types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

void GfMenuObjMercenaryForm::sendOpenEvent(u32 handle, int type, f32 delay) {
  if (handle == 0) {
    handle = ui::UIObjectAcc(unknown18, "LAY_form_main").unknown10;
  }
  ui::EventData event;
  event.unknown08 = type;
  event.unknown0c = 0;
  event.unknown00 = GfMenuTypes::unknown003_33;
  GfMenuObject::sendEvent(handle, event, delay);
}

void GfMenuObjMercenaryForm::sendCloseEvent(u32 handle, int type, f32 delay) {
  if (handle == 0) {
    handle = ui::UIObjectAcc(unknown18, "LAY_form_main").unknown10;
  }
  ui::EventData event;
  event.unknown08 = type;
  event.unknown0c = 0;
  event.unknown00 = GfMenuTypes::unknown003_34;
  GfMenuObject::sendEvent(handle, event, delay);
}

void GfMenuObjMercenaryForm::finalize() { GfMenuObject::finalize(); }

} // namespace gf
