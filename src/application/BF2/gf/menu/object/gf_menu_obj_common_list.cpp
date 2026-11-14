#include "gf/menu/object/gf_menu_obj_common_list.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_rect.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/plugin/ui_object_fit_plugin.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"
#include "ui/ui_util.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x24;

// Inferred role: background images of the list rows; original name unknown.
static const char *const unknown002[] = {"IMG_list01_bg", "IMG_list02_bg", "IMG_list03_bg", "IMG_list04_bg", "IMG_list05_bg", "IMG_list06_bg", "IMG_list07_bg", "IMG_list08_bg", "IMG_list09_bg"};

// Inferred role: text of the list rows; original name unknown.
static const char *const unknown003[] = {
    "TXT_list01_txt", "TXT_list02_txt", "TXT_list03_txt", "TXT_list04_txt", "TXT_list05_txt", "TXT_list06_txt", "TXT_list07_txt", "TXT_list08_txt", "TXT_list09_txt"};

// Inferred role: list rows; original name unknown.
static const char *const unknown004[] = {"LAY_list01", "LAY_list02", "LAY_list03", "LAY_list04", "LAY_list05", "LAY_list06", "LAY_list07", "LAY_list08", "LAY_list09"};

GfMenuObjCommonList::GfMenuObjCommonList(u32 handle) : GfMenuObject(handle) {}

GfMenuObjCommonList::~GfMenuObjCommonList() { ; }

void GfMenuObjCommonList::initialize() {
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
  if (ui::UIObjectAcc(main).isValid()) {
// __LINE__ must be 112 as in the original file: it is the line argument of operator new.
#line 112
    ListListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ListListener(this);
    listener->addRef();
    ui::UIEventManager::get()->registObjectListener(main, listener);
    if (listener != nullptr) {
      listener->release();
    }
    attachExternalCall(unknown001, main);
    setupPlugin(unknown18);
  }
  GfMenuObject::initialize();
}

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

void GfMenuObjCommonList::ListListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    unknown0c = 0;
    return;
  case 2:
    GfMenuObject::termCallContext(handle);
    acc.setTerm();
    return;
  case 6:
    moveCursor(handle, event.unknown08);
    return;
  case 8:
    if (event.unknown0c == 1) {
      GfMenuObject::addResultCallContext(handle, event.unknown08 + 1, 0);
      close();
    } else if (event.unknown0c == 2) {
      GfMenuObject::addResultCallContext(handle, 0, 0);
      close();
    }
    GfMenuObjUtil::playSECommonFromInput(event.unknown0c);
    return;
  case GfMenuTypes::unknown003_33: {
    u32 id = event.unknown08 >> 8 & 0xff;
    u8 *bdat = Bdat::getFP("MNU_CmnList");
    if (bdat == nullptr) {
      return;
    }
    if (Bdat::getArrayVal(bdat, "item", id, 0).valueS16 == 0) {
      return;
    }
    int count = 1;
    while (count < 9 && Bdat::getArrayVal(bdat, "item", id, count).valueS16 != 0) {
      count++;
    }
    u8 selected = event.unknown08;
    int row = mm::clamp(selected - 1, 0, count - 1);
    moveCursor(handle, row);
    for (int i = 0; i < 9; i++) {
      bool disp = false;
      if (i < count) {
        u32 nameId = Bdat::getArrayVal(bdat, "item", id, i).valueU16;
        u16 text = GfMenuObject::registString(ui::UIStr(GfDataBdat::getFP(BDAT_MENU_CMNWINDOW), nameId));
        GfMenuObjUtil::setChildText(handle, unknown003[i], text);
        disp = true;
      }
      GfMenuObjUtil::setChildDisp(handle, unknown004[i], disp);
    }
    GfMenuObject::setupInputSelection(handle, row, count);
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown04 = 0;
    param.unknown00 = 4;
    GfMenuObjUtil::startPresetCtrl(handle, param);
    acc.setDisp(true);
    break;
  }
  case GfMenuTypes::unknown003_34: {
    GfMenuObject::termCallContext(handle);
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown00 = 4;
    param.unknown04 = 1;
    GfMenuObjUtil::startPresetCtrl(handle, param);
    break;
  }
  default:
    break;
  }
  ui::UIObjectListener::reciveEvent(event, handle);
}

} // namespace gf
