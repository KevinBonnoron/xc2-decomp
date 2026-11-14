#include "gf/menu/object/gf_menu_obj_mainmenu2bg.h"

#include "gf/field/gf_field_time.h"
#include "gf/gf_allocator.h"
#include "gf/menu/object/gf_menu_obj_world_map.h"
#include "mm_math/mm_pnt.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x60;

// Inferred role: far background object and the world map whose condition shows it, 0 for always; original type name unknown.
struct unknown002 {
  const char *unknown00; // Inferred role: object name; original member name unknown.
  u32 unknown08;         // Inferred role: world map; original member name unknown.
};

static_assert(offsetof(unknown002, unknown08) == 0x08, "");
static_assert(sizeof(unknown002) == 0x10, "");

// Inferred role: far background objects; original name unknown.
static const unknown002 unknown003[13] = {{"IMG_bg_far", 0},
                                          {"IMG_bg_symbol@01", 0},
                                          {"IMG_bg_symbol@02", 14},
                                          {"IMG_bg_symbol@03", 12},
                                          {"IMG_bg_symbol@04", 12},
                                          {"IMG_bg_symbol@06", 9},
                                          {"IMG_bg_symbol@07", 10},
                                          {"IMG_bg_cloud@12", 0},
                                          {"IMG_bg_symbol@08", 13},
                                          {"IMG_bg_symbol@09", 6},
                                          {"IMG_bg_symbol@10", 3},
                                          {"IMG_bg_symbol@11", 0},
                                          {"IMG_bg_cloud@11", 0}};

int GfMenuObjMainMenu2BG::s_ThemaIndex = -1;
GfMenuObjMainMenu2BG::GfMenuObjMainMenu2BG(u32 handle) : GfMenuObject(handle), unknown24(0), unknown28(nullptr), unknown30(nullptr) {}

GfMenuObjMainMenu2BG::~GfMenuObjMainMenu2BG() {
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown28);
}

void GfMenuObjMainMenu2BG::initialize() {
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
// __LINE__ must be 119 as in the original file: it is the line argument of operator new.
#line 119
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
  attachExternalCall(unknown001, main);
  GfMenuObject::initialize();
  {
    ui::UISelectObjList::CreateParam param;
    param.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
    unknown28 = ui::UISelectObjList::create(param);
    unknown28->pickupObject(acc.searchChild("LAY_bg2"), "LAY_bg2@%02d", 1);
  }
  ui::UISelectObjList::CreateParam param;
  param.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
  unknown30 = ui::UISelectObjList::create(param);
  for (u32 i = 0; i < 13; i++) {
    unknown30->addObject(acc.searchChild(unknown003[i].unknown00));
  }
  int thema;
  if (GfFieldTime::get() == nullptr) {
    thema = 3;
  } else {
    u32 hour = GfFieldTime::get()->getHour();
    if (hour >= 5 && hour < 15) {
      thema = 1;
    } else if (hour >= 15 && hour < 21) {
      thema = 2;
    } else {
      thema = 3;
    }
  }
  if (s_ThemaIndex != thema) {
    s_ThemaIndex = thema;
  }
  for (u32 i = 0; i < unknown30->getSize(); i++) {
    ui::UIObjectAcc object(unknown30->getObject(i));
    if (unknown003[i].unknown08 != 0) {
      mm::Pnt<s16> pos;
      object.setDisp(GfMenuObjWorldMap::chkMapCond(unknown003[i].unknown08, &pos));
    }
    object.setImageIndex(s_ThemaIndex);
  }
}

void GfMenuObjMainMenu2BG::finalize() { GfMenuObject::finalize(); }

void GfMenuObjMainMenu2BG::setupMainMenuBG(ui::UIObjectAcc &) {}

void GfMenuObjMainMenu2BG::update() {
  for (u32 i = 0; i < unknown30->getSize(); i++) {
    ui::UIObjectAcc acc(unknown30->getObject(i));
    if (!acc.isStreaming()) {
      acc.setAlpha(1.0f);
      acc.startAnimationFromIndex(1, false);
      unknown30->delObject(acc.unknown10);
    }
  }
  GfMenuObject::update();
}

void GfMenuObjMainMenu2BG::move(GfMenuCallContext *, u32 index, const OpenMainMenuBg &param) {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    if (!ui::UIObjectAcc(handle).isTerm()) {
      ui::EventData event;
      event.unknown00 = 0x101;
      event.unknown08 = param.unknown00;
      event.unknown0c = param.unknown08;
      event.unknown10 = param.unknown04;
      event.unknown14 = index;
      ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
    }
  }
}

} // namespace gf
