#include "gf/menu/object/gf_menu_obj_damage_buff.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"
#include "ui/ui_util.h"

namespace gf {

// Inferred role: call id passed to getAttachedObject in close(); taken from the game disassembly, original name unknown.
constexpr u32 unknown001 = 0x2d;

// Inferred role: message ids of the resistance names, indexed by the resistance type minus one; original name unknown.
static const u32 unknown002[] = {1, 2};

// Inferred role: add color names of the screen, indexed by the buff kind; original name unknown.
static const char *const unknown003[] = {"dmg_buff", "dmg_debuff", "dmg_combo"};

GfMenuObjDamageBuff::GfMenuObjDamageBuff(u32 handle) : GfMenuObject(handle) {}

GfMenuObjDamageBuff::~GfMenuObjDamageBuff() { GfMenuManyObjects::destroy<DamageInfo>(GfMenuManyObjects::unknown001_1); }

void GfMenuObjDamageBuff::finalize() { GfMenuObject::finalize(); }

void GfMenuObjDamageBuff::close(u32 handle) {
  ui::UIObjectAcc root(getAttachedObject(unknown001));
  if (!root.isValid()) {
    return;
  }
  if (root.isTerm()) {
    return;
  }
  ui::UIObjectAcc acc(handle);
  if (!acc.isValid()) {
    return;
  }
  if (!acc.isDuplicate()) {
    return;
  }
  // The game builds a third temporary here and destroys it before sendEvent; using acc moves the destructor after the call.
  ui::EventData event;
  event.unknown00 = GfMenuTypes::unknown003_34;
  event.unknown08_u16 = ui::UIObjectAcc(handle).getDuplicateIndex();
  sendEvent(root.unknown10, event, 0.0f);
}

void GfMenuObjDamageBuff::closeUniteCombo(u32 handle) {
  ui::UIObjectAcc root(getAttachedObject(unknown001));
  if (!root.isValid()) {
    return;
  }
  if (root.isTerm()) {
    return;
  }
  ui::UIObjectAcc acc(handle);
  if (!acc.isValid()) {
    return;
  }
  if (!acc.isDuplicate()) {
    return;
  }
  ui::EventData event;
  event.unknown00 = GfMenuTypes::unknown003_257;
  event.unknown08_u16 = ui::UIObjectAcc(handle).getDuplicateIndex();
  sendEvent(root.unknown10, event, 0.0f);
}

void GfMenuObjDamageBuff::removeObject(ui::UIObjectAcc acc) {
  GfMenuManyObjects::remove<DamageInfo>(GfMenuManyObjects::unknown001_1, acc.unknown10);
  acc.setDisp(false);
  acc.setTerm();
}

void GfMenuObjDamageBuff::closeAll() {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    if (!ui::UIObjectAcc(handle).isTerm()) {
      GfMenuManyObjects::closeAll<DamageInfo>(GfMenuManyObjects::unknown001_1, &GfMenuObjDamageBuff::close);
    }
  }
}

void GfMenuObjDamageBuff::setupPlugin(u32 handle) {
  u32 item = ui::UIUtil::searchChild(handle, "LAY_buff_item");
  if (ui::UIUtil::isValid(item)) {
    u32 background = ui::UIUtil::searchChild(handle, "IMG_bg");
    if (ui::UIUtil::isValid(background)) {
      GfMenuObjUtil::FitOption option;
      GfMenuObjUtil::createFitPlugin(background, item, 0x18, 8, option);
    }
  }
}

void GfMenuObjDamageBuff::setupScreen(u32 handle, int color, int resist, int name, int) {
  GfMenuObjUtil::setChildText(handle, "TXT_name", name);
  if (resist != 0) {
    u8 *damageBuff = GfDataBdat::getFP(BDAT_MNU_MSG_DAMAGE_BUFF);
    int index = unknown002[resist - 1];
    u8 *menuMs = GfDataBdat::getFP(BDAT_MENU_MS);
    u32 id = Bdat::getVal(damageBuff, "name", index).valueU16;
    ui::UIObjectAcc acc(handle, "TXT_resist");
    acc.setText(ui::UIStr(menuMs, id));
  }
  GfMenuObjUtil::setChildDisp(handle, "TXT_resist", resist != 0);
  const char *addColor;
  if (static_cast<u32>(color) < 3) {
    addColor = unknown003[color];
  } else {
    addColor = "white";
  }
  GfMenuObjUtil::setChildAddColor(handle, "IMG_bg", addColor);
}

void GfMenuObjDamageBuff::update() { GfMenuObject::update(); }

} // namespace gf

template void gf::GfMenuManyObjects::remove<gf::GfMenuObjDamageBuff::DamageInfo>(u32, u32);
template void mm::mtl::Queue<gf::GfMenuObjDamageBuff::DamageInfo>::push_back(const gf::GfMenuObjDamageBuff::DamageInfo &);
template void mm::mtl::Queue<gf::GfMenuObjDamageBuff::DamageInfo>::expand(size_t, size_t);
