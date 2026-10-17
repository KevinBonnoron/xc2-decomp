#include "gf/menu/adapter/gf_menu_pos_adapter.h"

#include "gf/game/gf_game_party.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/object/gf_obj_handle.h"
#include "ui/ui_object_plugin.h"

namespace gf {

GfMenuPosAdapter::GfMenuPosAdapter(ui::UIObjectPlugin *plugin)
    : GfMenuAdapter(plugin, false, true), objHandle(INVALID_HANDLE), isWorld(false), isFixedPoint(false), isDiffOffset(false), screenOffset(0, 0),
      converter(nullptr) {}

GfMenuPosAdapter::~GfMenuPosAdapter() {
  if (converter != nullptr) {
    delete converter;
    converter = nullptr;
  }
}

GfMenuPosAdapter *GfMenuPosAdapter::create(u32 handle, GF_OBJ_HANDLE *objHandle, const MenuOffset *menuOffset) {
  PluginSetup setup;
  setup.type = PLUGIN_TYPE_POS;
  ui::UIObjectPlugin *plugin = createPlugin(handle, setup);
  if (plugin == nullptr) {
    return nullptr;
  }
  // __LINE__ must be 103 as in the original source: it is the line argument of operator new.
#line 103
  GfMenuPosAdapter *adapter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuPosAdapter(plugin);
  if (adapter != nullptr) {
    adapter->setup(objHandle, menuOffset);
    adapter->worldPos = adapter->offset;
  }
  plugin->release();
  return adapter;
}

void GfMenuPosAdapter::setup(GF_OBJ_HANDLE *objHandle, const MenuOffset *menuOffset) {
  this->objHandle = objHandle;
  offset = mm::Vec3(0.0f, 0.0f, 0.0f);
  boneName = "";
  if (menuOffset != nullptr) {
    offset.x = menuOffset->x;
    offset.y = menuOffset->y;
    offset.z = menuOffset->z;
    worldPos.x = menuOffset->x;
    worldPos.y = menuOffset->y;
    worldPos.z = menuOffset->z;
    if (menuOffset->boneName != nullptr && menuOffset->boneName[0] != '\0') {
      boneName = menuOffset->boneName;
    }
  }
}

GfMenuPosAdapter *GfMenuPosAdapter::createDiffOffset(u32 handle, GF_OBJ_HANDLE *objHandle, const MenuOffset *menuOffset, u16 limitX, u16 limitY) {
  PluginSetup setup;
  setup.type = PLUGIN_TYPE_OFFSET;
  ui::UIObjectPlugin *plugin = createPlugin(handle, setup);
  if (plugin == nullptr) {
    return nullptr;
  }
  // __LINE__ must be 131 as in the original source: it is the line argument of operator new.
#line 131
  GfMenuPosAdapter *adapter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuPosAdapter(plugin);
  if (adapter != nullptr) {
    adapter->setup(objHandle, menuOffset);
    adapter->worldPos = adapter->offset;
    adapter->isDiffOffset = true;
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
  adapter->converter = converter;
  return adapter;
}

GfMenuPosAdapter *GfMenuPosAdapter::createWorld(u32 handle, GF_OBJ_HANDLE *objHandle, const MenuOffset *menuOffset) {
  PluginSetup setup;
  setup.type = PLUGIN_TYPE_WORLD_POS;
  ui::UIObjectPlugin *plugin = createPlugin(handle, setup);
  if (plugin == nullptr) {
    return nullptr;
  }
  // __LINE__ must be 175 as in the original source: it is the line argument of operator new.
#line 175
  GfMenuPosAdapter *adapter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuPosAdapter(plugin);
  if (adapter != nullptr) {
    adapter->setup(objHandle, menuOffset);
    adapter->worldPos = adapter->offset;
    adapter->isWorld = true;
  }
  plugin->release();
  return adapter;
}

GfMenuPosAdapter *GfMenuPosAdapter::createFixedPoint(u32 handle, const mm::Vec3 &pos, bool isWorld) {
  PluginSetup setup;
  setup.type = isWorld ? PLUGIN_TYPE_WORLD_POS : PLUGIN_TYPE_POS;
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
    adapter->isWorld = isWorld;
    adapter->isFixedPoint = true;
  }
  plugin->release();
  return adapter;
}

void GfMenuPosAdapter::changeReference(GF_OBJ_HANDLE *objHandle, const MenuOffset *menuOffset) { setup(objHandle, menuOffset); }

void GfMenuPosAdapter::changeFixedPoint(const mm::Vec3 &pos) { worldPos = pos; }

GF_OBJ_HANDLE *GfMenuPosAdapter::PartyDriverConverter::getGfObjHandle() { return GfGameParty::getHandleDriver(partyIndex); }

} // namespace gf
