#include "gf/menu/adapter/gf_menu_pos_adapter.h"

#include "gf/game/gf_game_party.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/object/gf_obj_handle.h"
#include "ui/ui_object_plugin.h"

namespace gf {

GfMenuPosAdapter::GfMenuPosAdapter(ui::UIObjectPlugin *plugin)
    : GfMenuAdapter(plugin, false, true), unknown30(INVALID_HANDLE), unknown80(false), unknown81(false), unknown82(false), unknown84(0, 0), unknown88(nullptr) {}

GfMenuPosAdapter::~GfMenuPosAdapter() {
  if (unknown88 != nullptr) {
    delete unknown88;
    unknown88 = nullptr;
  }
}

GfMenuPosAdapter *GfMenuPosAdapter::create(u32 handle, GF_OBJ_HANDLE *objHandle, const MenuOffset *menuOffset) {
  PluginSetup setup;
  setup.unknown00 = unknown004_4;
  ui::UIObjectPlugin *plugin = createPlugin(handle, setup);
  if (plugin == nullptr) {
    return nullptr;
  }
  // __LINE__ must be 103 as in the original source: it is the line argument of operator new.
#line 103
  GfMenuPosAdapter *adapter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuPosAdapter(plugin);
  if (adapter != nullptr) {
    adapter->setup(objHandle, menuOffset);
    adapter->unknown70 = adapter->unknown40;
  }
  plugin->release();
  return adapter;
}

void GfMenuPosAdapter::setup(GF_OBJ_HANDLE *objHandle, const MenuOffset *menuOffset) {
  this->unknown30 = objHandle;
  unknown40 = mm::Vec3(0.0f, 0.0f, 0.0f);
  unknown50 = "";
  if (menuOffset != nullptr) {
    unknown40.x = menuOffset->unknown00;
    unknown40.y = menuOffset->unknown04;
    unknown40.z = menuOffset->unknown08;
    unknown70.x = menuOffset->unknown00;
    unknown70.y = menuOffset->unknown04;
    unknown70.z = menuOffset->unknown08;
    if (menuOffset->unknown10 != nullptr && menuOffset->unknown10[0] != '\0') {
      unknown50 = menuOffset->unknown10;
    }
  }
}

GfMenuPosAdapter *GfMenuPosAdapter::createDiffOffset(u32 handle, GF_OBJ_HANDLE *objHandle, const MenuOffset *menuOffset, u16 limitX, u16 limitY) {
  PluginSetup setup;
  setup.unknown00 = unknown004_6;
  ui::UIObjectPlugin *plugin = createPlugin(handle, setup);
  if (plugin == nullptr) {
    return nullptr;
  }
  // __LINE__ must be 131 as in the original source: it is the line argument of operator new.
#line 131
  GfMenuPosAdapter *adapter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuPosAdapter(plugin);
  if (adapter != nullptr) {
    adapter->setup(objHandle, menuOffset);
    adapter->unknown70 = adapter->unknown40;
    adapter->unknown82 = true;
    adapter->setOffsetLimit(limitX, limitY);
  }
  plugin->release();
  return adapter;
}

GfMenuPosAdapter *GfMenuPosAdapter::createFromPartyDriver(u32 handle, u8 partyIndex, const MenuOffset *menuOffset) {
  // __LINE__ must be 153 as in the original source: it is the line argument of operator new.
#line 153
  PartyDriverConverter *converter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) PartyDriverConverter(partyIndex);
  GfMenuPosAdapter *adapter = create(handle, converter->getGfObjHandle(), menuOffset);
  adapter->unknown88 = converter;
  return adapter;
}

GfMenuPosAdapter *GfMenuPosAdapter::createWorld(u32 handle, GF_OBJ_HANDLE *objHandle, const MenuOffset *menuOffset) {
  PluginSetup setup;
  setup.unknown00 = unknown004_5;
  ui::UIObjectPlugin *plugin = createPlugin(handle, setup);
  if (plugin == nullptr) {
    return nullptr;
  }
  // __LINE__ must be 175 as in the original source: it is the line argument of operator new.
#line 175
  GfMenuPosAdapter *adapter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuPosAdapter(plugin);
  if (adapter != nullptr) {
    adapter->setup(objHandle, menuOffset);
    adapter->unknown70 = adapter->unknown40;
    adapter->unknown80 = true;
  }
  plugin->release();
  return adapter;
}

GfMenuPosAdapter *GfMenuPosAdapter::createFixedPoint(u32 handle, const mm::Vec3 &pos, bool isWorld) {
  PluginSetup setup;
  setup.unknown00 = isWorld ? unknown004_5 : unknown004_4;
  ui::UIObjectPlugin *plugin = createPlugin(handle, setup);
  if (plugin == nullptr) {
    return nullptr;
  }
  // __LINE__ must be 210 as in the original source: it is the line argument of operator new.
#line 210
  GfMenuPosAdapter *adapter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuPosAdapter(plugin);
  if (adapter != nullptr) {
    adapter->setup(INVALID_HANDLE, nullptr);
    adapter->changeFixedPoint(pos);
    adapter->unknown80 = isWorld;
    adapter->unknown81 = true;
  }
  plugin->release();
  return adapter;
}

void GfMenuPosAdapter::changeReference(GF_OBJ_HANDLE *objHandle, const MenuOffset *menuOffset) { setup(objHandle, menuOffset); }

void GfMenuPosAdapter::changeFixedPoint(const mm::Vec3 &pos) { unknown70 = pos; }

GF_OBJ_HANDLE *GfMenuPosAdapter::PartyDriverConverter::getGfObjHandle() { return GfGameParty::getHandleDriver(partyIndex); }

} // namespace gf
