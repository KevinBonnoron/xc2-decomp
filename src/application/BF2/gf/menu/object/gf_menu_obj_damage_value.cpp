#include "gf/menu/object/gf_menu_obj_damage_value.h"

#include <math.h>

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_field_pos_adapter.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "ml/rand.h"
#include "mm_math/mm_vec2.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/queue.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_str.h"

namespace gf {

// Inferred role: call id of the damage value object; original name unknown.
constexpr u32 unknown001 = 0x2c;

GfMenuObjDamageValue::GfMenuObjDamageValue(u32 handle) : GfMenuObject(handle) {}

GfMenuObjDamageValue::~GfMenuObjDamageValue() { GfMenuManyObjects::destroy<DamageInfo>(GfMenuManyObjects::unknown001_0); }

void GfMenuObjDamageValue::finalize() { GfMenuObject::finalize(); }

void GfMenuObjDamageValue::update() { GfMenuObject::update(); }

void GfMenuObjDamageValue::initialize() {
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
  if (ui::UIObjectAcc(main).isValid()) {
    attachExternalCall(unknown001, main);
// __LINE__ must be 84 as in the original file: it is the line argument of operator new.
#line 84
    ListListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ListListener(this);
    listener->addRef();
    ui::UIEventManager::get()->registObjectListener(main, listener);
    if (listener != nullptr) {
      listener->release();
    }
  }
  ui::UIObjectAcc(unknown18).setTerm();
  GfMenuObject::initialize();
  GfMenuManyObjects::unknown002<DamageInfo>(GfMenuManyObjects::unknown001_0, 32);
}

void GfMenuObjDamageValue::removeObject(ui::UIObjectAcc acc) {
  GfMenuManyObjects::remove<DamageInfo>(GfMenuManyObjects::unknown001_0, acc.unknown10);
  acc.setDisp(false);
  acc.setTerm();
}

// Inferred role: float of the "value" column of the damage value table at the given row, or the default when the table is missing, inlined seven times by setupScreen; original name unknown.
static f32 unknown002(u8 *bdat, int row, f32 fallback) {
  if (bdat != nullptr) {
    return Bdat::getVal(bdat, "value", row).valueF32;
  }
  return fallback;
}

// Inferred role: styles the outline copy of a damage text (black, shifted by 3 pixels, drawn one priority below the text, border weight -0.5), inlined seven times by setupScreen; original name
// unknown.
static void unknown003(ui::UIObjectAcc &outline) {
  outline.setMulColor("black");
  GfMenuObjUtil::addPos(outline.unknown10, 3, 3);
  outline.setIgnoreSize(true);
  outline.setDispPriority(outline.getDispPriority() - 1);
  outline.setBorderWeight(-0.5f);
}

// Inferred role: hides the miss, evade and level up texts, used by the four number cases of setupScreen; original name unknown.
static void unknown004(u32 handle) {
  GfMenuObjUtil::setChildDisp(handle, "TXT_miss", false);
  GfMenuObjUtil::setChildDisp(handle, "TXT_evade", false);
  GfMenuObjUtil::setChildDisp(handle, "TXT_levelup", false);
}

// 0x7100444ea0, 347 insns. The three helpers above are inlined (no game symbol). The `duplicateChild` that creates the outline accessor stays in each
// case instead of joining the style helper: a helper taking the layout and the child name, or one holding the `setText` too, creates the outline
// accessor in its own frame slot, so the slots of the layout, scale and outline accessors move (first difference at +0x30, `sp+72` against `sp+48`,
// 347 instructions both). The hides follow the `if` of each number case, the way the invalid number path of the game reaches them.
void GfMenuObjDamageValue::setupScreen(u32 handle, int type, int text, int target, int flags) {
  ui::UIObjectAcc number(handle, "TXT_num");
  ui::UIObjectAcc layout(handle, "LAY_damage");
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_DAMAGE_VALUE);
  switch (type) {
  case 0:
    if (number.isValid()) {
      number.setDisp(true);
      const char *color;
      f32 scale;
      if (target == 1) {
        color = "txt_party_dmg";
        scale = unknown002(bdat, 2, 0.7f);
      } else if (target == 2) {
        color = "txt_player_dmg";
        scale = unknown002(bdat, 3, 1.0f);
      } else {
        color = "txt_enemy_dmg";
        scale = unknown002(bdat, 1, 1.0f);
      }
      GfMenuObjUtil::setColMulandAdd(number.unknown10, color);
      u32 level = (flags >> 3) & 3;
      f32 levelScale = scale;
      if (level == 1) {
        levelScale = unknown002(bdat, 4, 1.5f);
      } else if (level == 2) {
        levelScale = unknown002(bdat, 5, 2.0f);
      } else if (level == 3) {
        levelScale = unknown002(bdat, 6, 4.0f);
      }
      f32 critScale = unknown002(bdat, 7, 2.0f);
      f32 size = (flags & 1) != 0 ? levelScale * critScale : levelScale;
      mm::Vec2 scaleXY(size, size);
      if (level == 0) {
        number.setScale(scaleXY);
      } else {
        layout.setScale(scaleXY);
      }
      GfMenuObject::setText(number.unknown10, text);
      ui::UIObjectAcc outline(layout.duplicateChild("TXT_num"));
      unknown003(outline);
    }
    unknown004(handle);
    break;
  case 1:
    if (number.isValid()) {
      number.setDisp(true);
      GfMenuObjUtil::setColMulandAdd(number.unknown10, target == 0 ? "txt_enemy_heal" : "txt_party_heal");
      f32 size = (flags & 1) != 0 ? 2.0f : 1.0f;
      mm::Vec2 scaleXY(size, size);
      number.setScale(scaleXY);
      GfMenuObject::setText(number.unknown10, text);
      ui::UIObjectAcc outline(layout.duplicateChild("TXT_num"));
      unknown003(outline);
    }
    unknown004(handle);
    break;
  case 2:
    GfMenuObject::releaseString(text);
    GfMenuObjUtil::setChildDisp(handle, "TXT_num", false);
    GfMenuObjUtil::setChildDisp(handle, "TXT_miss", true);
    GfMenuObjUtil::setChildDisp(handle, "TXT_evade", false);
    GfMenuObjUtil::setChildDisp(handle, "TXT_levelup", false);
    {
      ui::UIObjectAcc outline(layout.duplicateChild("TXT_miss"));
      unknown003(outline);
    }
    break;
  case 3:
    if (number.isValid()) {
      number.setDisp(true);
      GfMenuObjUtil::setColMulandAdd(number.unknown10, "txt_spikedmg");
      GfMenuObject::setText(number.unknown10, text);
      ui::UIObjectAcc outline(layout.duplicateChild("TXT_num"));
      unknown003(outline);
    }
    unknown004(handle);
    break;
  case 4:
    if (number.isValid()) {
      number.setDisp(true);
      GfMenuObjUtil::setColMulandAdd(number.unknown10, "txt_dotdmg");
      GfMenuObject::setText(number.unknown10, text);
      ui::UIObjectAcc outline(layout.duplicateChild("TXT_num"));
      unknown003(outline);
    }
    unknown004(handle);
    break;
  case 5:
    GfMenuObject::releaseString(text);
    GfMenuObjUtil::setChildDisp(handle, "TXT_num", false);
    GfMenuObjUtil::setChildDisp(handle, "TXT_miss", false);
    GfMenuObjUtil::setChildDisp(handle, "TXT_evade", true);
    GfMenuObjUtil::setChildDisp(handle, "TXT_levelup", false);
    {
      ui::UIObjectAcc outline(layout.duplicateChild("TXT_evade"));
      unknown003(outline);
    }
    break;
  case 6:
    GfMenuObject::releaseString(text);
    GfMenuObjUtil::setChildDisp(handle, "TXT_num", false);
    GfMenuObjUtil::setChildDisp(handle, "TXT_miss", false);
    GfMenuObjUtil::setChildDisp(handle, "TXT_evade", false);
    GfMenuObjUtil::setChildDisp(handle, "TXT_levelup", true);
    {
      ui::UIObjectAcc outline(layout.duplicateChild("TXT_levelup"));
      unknown003(outline);
    }
    break;
  }
  ui::UIObjectAcc background(handle, "IMG_spbg");
  if ((flags & 4) == 0) {
    background.setDisp(false);
  } else {
    background.setDisp(true);
    background.startAnimation("fadein", false);
  }
}

// The startCtrl, removeObject and hookCtrlEvent sequence is written out five times (ruling 8, measured): the game's frame (0x7100444970, 432 bytes) holds
// one by-value UIObjectAcc copy slot per removeObject site (sp+0, 24, 48, 72, 96, 120 and 216). A file-local helper taking the target handle and the
// control parameters (`id = startCtrl(...); if (id == -1) removeObject(icon); else hookCtrlEvent(acc.unknown10, id);`) is inlined and merges those slots:
// frame 320 bytes, 273 instructions against the game's 332. The cases are in this source order (0x21, 0x22, 3, then default) because the alloca order of
// those slots and the block order only match so.
void GfMenuObjDamageValue::ListListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    break;
  case 0x21: {
    ui::UIObjectAcc icon(acc.searchDuplicatedChild("LAY_damage_root", event.unknown12));
    if (icon.isValid()) {
      icon.setDisp(true);
      setupScreen(icon.unknown10, event.unknown08, event.unknown0c, event.unknown10_u16, event.unknown14);
      u32 critical = (event.unknown14 >> 1) & 1;
      GfMenuObjUtil::CtrlParam ctrl;
      if ((event.unknown14 & 0x18) == 0) {
        ctrl.unknown00 = 0.5f;
        ctrl.unknown08 = critical * 0x20 + 0x20;
        ctrl.unknown20 = 0x3c;
        ctrl.unknown04 = critical | (event.unknown12 << 16) | 0x100;
        int id = GfMenuObjUtil::startCtrl(icon.unknown10, ctrl, nullptr);
        if (id == -1) {
          removeObject(icon);
        } else {
          hookCtrlEvent(acc.unknown10, id);
        }
      } else {
        mm::Vec2 scale;
        ui::UIObjectAcc layout(icon.searchChild("LAY_damage"));
        layout.getScale(scale);
        layout.setScale(mm::Vec2(0.0f, 0.0f));
        ctrl.unknown00 = 0.3f;
        ctrl.unknown08 = 0x80000;
        ctrl.unknown2c = scale.x;
        ctrl.unknown20 = 0;
        ctrl.unknown04 = critical | (event.unknown12 << 16) | 0x200;
        int id = GfMenuObjUtil::startCtrl(icon.searchChild("LAY_damage"), ctrl, nullptr);
        if (id == -1) {
          removeObject(icon);
        } else {
          hookCtrlEvent(acc.unknown10, id);
        }
      }
    }
    break;
  }
  case 0x22: {
    ui::UIObjectAcc icon(acc.searchDuplicatedChild("LAY_damage_root", event.unknown08_u16));
    if (icon.isValid()) {
      removeObject(icon);
    }
    break;
  }
  case 3: {
    u32 param = event.unknown08;
    if (param == 0) {
      break;
    }
    u32 index = param >> 16;
    ui::UIObjectAcc icon(acc.searchDuplicatedChild("LAY_damage_root", index));
    if (!icon.isValid()) {
      break;
    }
    switch ((param >> 8) & 0xff) {
    case 1: {
      GfMenuObjUtil::CtrlParam ctrl;
      ctrl.unknown00 = 0.25f;
      ctrl.unknown08 = (param & 0xff) == 1 ? 0x42 : 0x22;
      ctrl.unknown20 = 0xf;
      ctrl.unknown04 = (param & 0xff) | (index << 16) | 0x400;
      int id = GfMenuObjUtil::startCtrl(icon.unknown10, ctrl, nullptr);
      if (id == -1) {
        removeObject(icon);
      } else {
        hookCtrlEvent(acc.unknown10, id);
      }
      break;
    }
    case 2: {
      GfMenuObjUtil::CtrlParam ctrl;
      ctrl.unknown00 = 0.25f;
      ctrl.unknown04 = (param & 0xff) | (index << 16) | 0x300;
      ctrl.unknown08 = 0;
      int id = GfMenuObjUtil::startCtrl(icon.unknown10, ctrl, nullptr);
      if (id == -1) {
        removeObject(icon);
      } else {
        hookCtrlEvent(acc.unknown10, id);
      }
      break;
    }
    case 3: {
      GfMenuObjUtil::CtrlParam ctrl;
      ctrl.unknown00 = 0.25f;
      ctrl.unknown08 = 2;
      ctrl.unknown20 = 0xf;
      ctrl.unknown04 = (param & 0xff) | (index << 16) | 0x400;
      int id = GfMenuObjUtil::startCtrl(icon.unknown10, ctrl, nullptr);
      if (id == -1) {
        removeObject(icon);
      } else {
        hookCtrlEvent(acc.unknown10, id);
      }
      break;
    }
    case 4:
      removeObject(icon);
      break;
    }
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

// Inferred role: whether a damage value position equals a queued one on one axis (within 1e-6), inlined three times by open (0x7100445578); original name
// unknown. The queued value is the first argument because the game loads the queued float first and then subtracts it from the position
// (`ldr s0,[queued]; ldr s1,[position]; fsub s0,s1,s0`). Written in the expression, `fabsf(position.x - queued.x)` loads the position first (the first difference is
// the `ldr` of the queued float against the load of the position float) and `fabsf(queued.x - position.x)` swaps the operands of the `fsub`; a helper taking the two
// Vec3 in either order costs an instruction more (282 against 281).
static bool unknown005(f32 queued, f32 position) { return fabsf(position - queued) <= 0.000001f; }

// 0x7100445578, 281 insns. Every failure returns 0 (the failures share one `mov w19,wzr` block before the epilogue, the object test goes straight to the
// epilogue with x19 == 0); only the success path returns the handle.
u32 GfMenuObjDamageValue::open(const OpenParam &param) {
  if (GfMenuObjUtil::isMenuObjectFull()) {
    return 0;
  }
  u32 object = getAttachedObject(unknown001);
  if (!ui::UIObjectAcc(object).isValid()) {
    return 0;
  }
  if (ui::UIObjectAcc(object).isTerm()) {
    return 0;
  }
  u32 handle = ui::UIObjectAcc(object).duplicateChild("LAY_damage_root");
  if (!ui::UIObjectAcc(handle).isValid()) {
    return 0;
  }
  ui::EventData event;
  event.unknown00 = GfMenuTypes::unknown003_33;
  event.unknown08 = param.unknown00;
  {
    mm::mtl::FixStr<128> number;
    number.format("%d", param.unknown04);
    event.unknown0c = registString(ui::UIStr(number.c_str(), true));
  }
  event.unknown10_u16 = param.unknown08;
  event.unknown12 = ui::UIObjectAcc(handle).getDuplicateIndex();
  event.unknown14 = param.unknown10 | (param.unknown11 != 0) << 1 | (param.unknown12 != 0) << 2 | (param.unknown0c != 0 ? (param.unknown0c & 3) << 3 : 0);
  sendEvent(object, event, 0.0f);
  mm::Vec3 position = param.unknown20;
  typedef mm::mtl::Queue<DamageInfo> DamageQueue;
  for (u32 i = 0; i < static_cast<DamageQueue *>(GfMenuManyObjects::get()->unknown10[GfMenuManyObjects::unknown001_0])->size(); i++) {
    DamageQueue *queue = static_cast<DamageQueue *>(GfMenuManyObjects::get()->unknown10[GfMenuManyObjects::unknown001_0]);
    if (!GfMenuManyObjects::get()->unknown50[GfMenuManyObjects::unknown001_0] && queue != nullptr && queue->size() != 0) {
      const DamageInfo &info = (*queue)[i];
      if (unknown005(info.unknown10.x, position.x) && unknown005(info.unknown10.y, position.y) && unknown005(info.unknown10.z, position.z)) {
        position.x += (ml::mtRand(8) - 4) * 0.6f;
        position.y += (ml::mtRand(8) - 4) * 0.3f;
        position.z += (ml::mtRand(8) - 4) * 0.6f;
        break;
      }
    }
  }
  GfMenuManyObjects::unknown003(GfMenuManyObjects::unknown001_0, DamageInfo(handle, position), close);
  GfMenuFieldPosAdapter::create(ui::UIObjectAcc(handle).searchChild("LAY_damage"), position);
  return handle;
}

void GfMenuObjDamageValue::close(u32 handle) {
  ui::UIObjectAcc root(getAttachedObject(unknown001));
  if (root.isValid() && !root.isTerm()) {
    ui::UIObjectAcc acc(handle);
    if (acc.isValid() && acc.isDuplicate()) {
      ui::EventData event;
      event.unknown00 = GfMenuTypes::unknown003_34;
      event.unknown08_u16 = acc.getDuplicateIndex();
      sendEvent(root.unknown10, event, 0.0f);
    }
  }
}

void GfMenuObjDamageValue::closeAll() {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    if (!ui::UIObjectAcc(handle).isTerm()) {
      GfMenuManyObjects::closeAll<DamageInfo>(GfMenuManyObjects::unknown001_0, close);
    }
  }
}

} // namespace gf

template void gf::GfMenuManyObjects::remove<gf::GfMenuObjDamageValue::DamageInfo>(u32, u32);
template void mm::mtl::Queue<gf::GfMenuObjDamageValue::DamageInfo>::push_back(const gf::GfMenuObjDamageValue::DamageInfo &);
template void mm::mtl::Queue<gf::GfMenuObjDamageValue::DamageInfo>::expand(size_t, size_t);
