#include "gf/menu/object/gf_menu_obj_target_info.h"

#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_gfobj_adapter.h"
#include "gf/menu/adapter/gf_menu_pos_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_vec2.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/plugin/ui_object_dock_plugin.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

namespace gf {

// Inferred role: multiply color of the access name text; original name unknown.
static const mm::Col3 unknown001(1.0f, 176.0f / 255.0f, 222.0f / 255.0f);

// Inferred role: add color of the access name text; original name unknown.
static const mm::Col3 unknown002(131.0f / 255.0f, 48.0f / 255.0f, 146.0f / 255.0f);

GfMenuObjTargetInfo::GfMenuObjTargetInfo(u32 handle) : GfMenuObject(handle) {}

GfMenuObjTargetInfo::~GfMenuObjTargetInfo() { ; }

void GfMenuObjTargetInfo::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  attachExternalCall(0x11, main.unknown10);
  {
    ui::UIObjectAcc root(main.unknown10, "LAY_ene_root");
// __LINE__ must be 84 as in the original file: it is the line argument of operator new.
#line 84
    EnemyListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) EnemyListener(this);
    listener->addRef();
    ui::UIEventManager::get()->registObjectListener(root.unknown10, listener);
    if (listener != nullptr) {
      listener->release();
    }
    attachExternalCall(0xc, root.unknown10);
  }
  {
    ui::UIObjectAcc root(main.unknown10, "LAY_other_root");
// __LINE__ must be 95 as in the original file: it is the line argument of operator new.
#line 95
    OtherListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) OtherListener(this);
    listener->addRef();
    ui::UIEventManager::get()->registObjectListener(root.unknown10, listener);
    if (listener != nullptr) {
      listener->release();
    }
    attachExternalCall(0xd, root.unknown10);
  }
  {
    ui::UIObjectAcc root(main.unknown10, "LAY_symbol_root");
// __LINE__ must be 107 as in the original file: it is the line argument of operator new.
#line 107
    SymbolListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SymbolListener(this);
    listener->addRef();
    ui::UIEventManager::get()->registObjectListener(root.unknown10, listener);
    if (listener != nullptr) {
      listener->release();
    }
    attachExternalCall(0xe, root.unknown10);
  }
  GfMenuObject::initialize();
}

void GfMenuObjTargetInfo::finalize() { GfMenuObject::finalize(); }

void GfMenuObjTargetInfo::update() { GfMenuObject::update(); }

void GfMenuObjTargetInfo::disp(bool disp) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x11));
  if (acc.isValid()) {
    acc.setDisp(disp);
  }
}

void GfMenuObjTargetInfo::dispAllEnemy(bool disp) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0xc));
  if (acc.isValid()) {
    acc.setDisp(disp);
  }
}

void GfMenuObjTargetInfo::dispAllOther(bool disp) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0xd));
  if (acc.isValid()) {
    acc.setDisp(disp);
  }
}

void GfMenuObjTargetInfo::dispAllSymbol(bool disp) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0xe));
  if (acc.isValid()) {
    acc.setDisp(disp);
  }
}

void GfMenuObjTargetInfo::startOpen(u32 handle, u32 object, int param0, int param1) {
  ui::UIObjectAcc acc(object);
  if (acc.isDuplicate()) {
    ui::EventData event;
    event.unknown00 = 0x100;
    event.unknown08 = param0;
    event.unknown0c = param1;
    event.unknown10 = acc.getDuplicateIndex();
    ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
  }
}

void GfMenuObjTargetInfo::EnemyListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    break;
  case GfMenuTypes::unknown003_256: {
    ui::UIObjectAcc enemy(acc.searchDuplicatedChild("LAY_ene_main", event.unknown10));
    if (enemy.isValid()) {
      enemy.setDisp(true);
    }
    break;
  }
  case GfMenuTypes::unknown003_257: {
    ui::UIObjectAcc enemy(acc.searchDuplicatedChild("LAY_ene_main", event.unknown10));
    if (enemy.isValid()) {
      enemy.setTerm();
      GfMenuObject::termCallContext(enemy.unknown10);
    }
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjTargetInfo::OtherListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    break;
  case GfMenuTypes::unknown003_256: {
    ui::UIObjectAcc other(acc.searchDuplicatedChild("LAY_other_main", event.unknown10));
    if (other.isValid()) {
      s16 baseWidth = 0;
      {
        ui::UIObjectAcc base(other.unknown10, "IMG_other_base");
        s16 baseHeight;
        base.getSize(true, baseWidth, baseHeight);
      }
      {
        ui::UIObjectAcc text(other.unknown10, "LAY_other_info_text");
        ui::UIObjectAcc active(other.unknown10, "IMG_other_active");
        ui::UIObjectAcc access(other.unknown10, "IMG_other_access");
        s16 activeWidth;
        s16 activeHeight;
        s16 textWidth;
        s16 textHeight;
        text.updateLayoutSize();
        text.getSize(true, textWidth, textHeight);
        active.getSize(false, activeWidth, activeHeight);
        activeWidth -= baseWidth;
        f32 scale = static_cast<f32>(textWidth) / static_cast<f32>(activeWidth);
        if (scale <= 1.0f) {
          scale = 1.0f;
        }
        active.setScale(mm::Vec2(scale, 1.0f));
        access.setScale(mm::Vec2(scale, 1.0f));
        ui::UIObjectAcc base(other.unknown10, "IMG_other_base");
        s16 width;
        s16 height;
        base.getSize(true, width, height);
        GfMenuObjUtil::setDockPos(active.unknown10, base.unknown10, 2, true);
        GfMenuObjUtil::addPos(active.unknown10, -width, 0);
        GfMenuObjUtil::setDockPos(access.unknown10, base.unknown10, 2, true);
        GfMenuObjUtil::addPos(access.unknown10, -width, 0);
      }
      other.setDisp(true);
    }
    break;
  }
  case GfMenuTypes::unknown003_257: {
    ui::UIObjectAcc other(acc.searchDuplicatedChild("LAY_other_main", event.unknown10));
    if (other.isValid()) {
      other.setTerm();
      GfMenuObject::termCallContext(other.unknown10);
    }
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjTargetInfo::SymbolListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    break;
  case GfMenuTypes::unknown003_256: {
    ui::UIObjectAcc symbol(acc.searchDuplicatedChild("LAY_symbol_main", event.unknown10));
    if (symbol.isValid()) {
      s16 baseWidth = 0;
      {
        ui::UIObjectAcc base(symbol.unknown10, "IMG_symbol_base");
        s16 baseHeight;
        base.getSize(true, baseWidth, baseHeight);
      }
      {
        ui::UIObjectAcc name(symbol.unknown10, "TXT_symbol_name");
        ui::UIObjectAcc active(symbol.unknown10, "IMG_symbol_active");
        ui::UIObjectAcc access(symbol.unknown10, "IMG_symbol_access");
        s16 activeWidth;
        s16 activeHeight;
        s16 nameWidth;
        s16 nameHeight;
        name.getSize(true, nameWidth, nameHeight);
        active.getSize(false, activeWidth, activeHeight);
        activeWidth -= baseWidth;
        f32 scale = static_cast<f32>(nameWidth) / static_cast<f32>(activeWidth);
        if (scale <= 1.0f) {
          scale = 1.0f;
        }
        active.setScale(mm::Vec2(scale, 1.0f));
        access.setScale(mm::Vec2(scale, 1.0f));
        ui::UIObjectAcc base(symbol.unknown10, "IMG_symbol_base");
        s16 width;
        s16 height;
        base.getSize(true, width, height);
        GfMenuObjUtil::setDockPos(active.unknown10, base.unknown10, 2, true);
        GfMenuObjUtil::addPos(active.unknown10, -width, 0);
        GfMenuObjUtil::setDockPos(access.unknown10, base.unknown10, 2, true);
        GfMenuObjUtil::addPos(access.unknown10, -width, 0);
      }
      symbol.setDisp(true);
    }
    break;
  }
  case GfMenuTypes::unknown003_257: {
    ui::UIObjectAcc symbol(acc.searchDuplicatedChild("LAY_symbol_main", event.unknown10));
    if (symbol.isValid()) {
      symbol.setTerm();
      GfMenuObject::termCallContext(symbol.unknown10);
    }
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjTargetInfo::openEnemy(GfMenuCallContext *context, const OpenEnemyParam &param) {
  if (context->getState() == 0) {
    ui::UIObjectAcc root(GfMenuObject::getAttachedObject(0xc));
    if (root.isValid() && !root.isTerm()) {
      ui::UIObjectAcc main(root.duplicateChild("LAY_ene_main"));
      if (main.isValid()) {
        {
          ui::UIObjectAcc ene(main.searchChild("LAY_ene"));
          if (ene.isValid()) {
            GfMenuPosAdapter::create(ene.unknown10, param.unknown00, &param.unknown10)->setPosOffsMode(1);
            GfMenuGfObjAdapter *adapter = GfMenuGfObjAdapter::create(ene.unknown10, 2, param.unknown00, true);
            adapter->setDispFadeMode(0.25f);
            adapter->setDispSuspendMode(true);
            GfMenuGfObjAdapter *bgAdapter = GfMenuGfObjAdapter::create(ene.searchChild("IMG_ene_bg"), 5, param.unknown00, true);
            bgAdapter->setDispReverseMode(true);
            bgAdapter->setDispAlphaMode(true);
          }
        }
        {
          ui::UIObjectAcc bg(main.searchChild("IMG_ene_bg"));
          GfMenuGfObjAdapter::create(bg.unknown10, 0x20, param.unknown00, false);
        }
        {
          ui::UIObjectAcc gauge(main.searchChild("IMG_hpgauge"));
          if (gauge.isValid()) {
            GfMenuGfObjAdapter::create(gauge.unknown10, 0, param.unknown00, true);
            gauge.setExtType(1);
          }
        }
        {
          ui::UIObjectAcc scout(main.searchChild("IMG_scout"));
          if (scout.isValid()) {
            GfMenuGfObjAdapter::create(scout.unknown10, 0x21, param.unknown00, true);
          }
        }
        {
          ui::UIObjectAcc level(main.searchChild("TXT_ene_lvnum"));
          if (level.isValid()) {
            GfMenuObjUtil::createDockPlugin(main.searchChild("TXT_ene_lvtitle"), level.unknown10, 0, mm::Pnt<s16>(-2, 0), 0);
            GfMenuGfObjAdapter::create(main.searchChild("TXT_ene_lvnum"), 7, param.unknown00, true);
          }
        }
        {
          ui::UIObjectAcc info(main.searchChild("LAY_infoicon"));
          if (info.isValid()) {
            ui::UIObjectAcc ene(main.searchChild("LAY_ene"));
            ui::UIObjectDockPlugin *plugin = ui::UIObjectDockPlugin::create(info.unknown10, 0, -2, ene.unknown10);
            plugin->unknown24 = 2;
            mm::mtl::safeRelease(plugin);
          }
          ui::UIObjectAcc icon(main.searchChild("IMG_infoicon"));
          if (icon.isValid()) {
            GfMenuGfObjAdapter::create(icon.unknown10, 4, param.unknown00, true)->setDispFadeMode(0.25f);
          }
        }
        startOpen(root.unknown10, main.unknown10, 0, 0);
        GfMenuObject::startCallContext(context, 0xc, main.unknown10);
      }
    }
  }
}

void GfMenuObjTargetInfo::openSymbol(GfMenuCallContext *context, const OpenSymbolParam &param) {
  ui::UIObjectAcc root(GfMenuObject::getAttachedObject(0xe));
  if (root.isValid() && !root.isTerm()) {
    ui::UIObjectAcc main(root.duplicateChild("LAY_symbol_main"));
    if (main.isValid()) {
      {
        ui::UIObjectAcc acc(main.unknown10);
        if (acc.isValid()) {
          GfMenuPosAdapter::create(acc.unknown10, param.unknown00, &param.unknown10)->setPosOffsMode(1);
          GfMenuGfObjAdapter *adapter = GfMenuGfObjAdapter::create(acc.unknown10, 3, param.unknown00, true);
          adapter->setDispFadeMode(0.25f);
          adapter->setDispSuspendMode(true);
        }
      }
      {
        ui::UIObjectAcc info(main.searchChild("LAY_symbol_info"));
        if (info.isValid()) {
          GfMenuGfObjAdapter::create(info.unknown10, 2, param.unknown00, true)->setDispFadeMode(0.25f);
        }
        ui::UIObjectAcc base(main.searchChild("IMG_symbol_base"));
        if (base.isValid()) {
          GfMenuGfObjAdapter *adapter = GfMenuGfObjAdapter::create(base.unknown10, 2, param.unknown00, true);
          adapter->setDispReverseMode(true);
          adapter->setDispFadeMode(0.25f);
        }
        ui::UIObjectAcc active(main.searchChild("IMG_symbol_active"));
        if (active.isValid()) {
          GfMenuGfObjAdapter::create(active.unknown10, 6, param.unknown00, true)->setDispReverseMode(true);
          {
            ui::UIObjectAcc name(main.unknown10, "TXT_symbol_name");
            GfMenuObjUtil::createSyncPlugin(name.unknown10, active.unknown10, 0x20);
          }
          ui::UIObjectAcc access(main.searchChild("IMG_symbol_access"));
          if (access.isValid()) {
            GfMenuGfObjAdapter::create(access.unknown10, 6, param.unknown00, true);
            GfMenuObjUtil::createSyncPlugin(access.unknown10, active.unknown10, 1);
            ui::UIObjectAcc name(main.unknown10, "TXT_symbol_name_access");
            GfMenuObjUtil::createSyncPlugin(name.unknown10, access.unknown10, 0x20);
          }
        }
      }
      if (param.unknown30 != nullptr && param.unknown38 != 0) {
        ui::UIObjectAcc name(main.unknown10, "TXT_symbol_name");
        ui::UIObjectAcc nameAccess(main.unknown10, "TXT_symbol_name_access");
        name.setText(ui::UIStr(param.unknown30, param.unknown38));
        name.saveDefColor();
        nameAccess.setText(ui::UIStr(param.unknown30, param.unknown38));
        nameAccess.setMulColor(unknown001);
        nameAccess.setAddColor(unknown002);
      }
      if (param.unknown40 != nullptr && param.unknown48 != 0) {
        ui::UIObjectAcc pointName(main.unknown10, "TXT_symbol_point_name");
        ui::UIStr text(param.unknown40, param.unknown48);
        if (text.isValid()) {
          pointName.setText(text);
          pointName.setDisp(true);
        }
      }
      {
        ui::UIObjectAcc icon(main.searchChild("IMG_symbol_icon"));
        if (icon.isValid()) {
          icon.setImageIndex(param.unknown4c);
        }
      }
      {
        ui::UIObjectAcc eff(main.searchChild("IMG_symbol_eff"));
        if (eff.isValid()) {
          eff.startAnimationFromID(1, false);
        }
      }
      startOpen(root.unknown10, main.unknown10, 0, 0);
      GfMenuObject::startCallContext(context, 0xe, main.unknown10);
    }
  }
}
} // namespace gf
