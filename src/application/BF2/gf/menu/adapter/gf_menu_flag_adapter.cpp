#include "gf/menu/adapter/gf_menu_flag_adapter.h"

#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_flag.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_object_plugin.h"

namespace gf {

static GfMenuFlagAdapter::TypeInfo TYPE_INFOS[] = {
    {&GfMenuFlagAdapter::update_FlagDisp, {GfMenuAdapter::PLUGIN_TYPE_DISP, 0, 0}},
    {&GfMenuFlagAdapter::update_FlagNum, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 1, 99}},
};

GfMenuFlagAdapter::GfMenuFlagAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways) : GfMenuAdapter(plugin, false, isUpdateAlways), flagBits(0), flagIndex(0), flagValue(0) {}

GfMenuFlagAdapter::~GfMenuFlagAdapter() {}

GfMenuFlagAdapter *GfMenuFlagAdapter::create(u32 handle, u32 type, u16 flagBits, u16 flagIndex, bool isUpdateAlways) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    TypeInfo &info = TYPE_INFOS[type];
    ui::UIObjectPlugin *plugin = createPlugin(handle, info.setup);
    if (plugin != nullptr) {
      // __LINE__ must be 58 as in the original source: it is the line argument of operator new.
#line 58
      GfMenuFlagAdapter *adapter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuFlagAdapter(plugin, isUpdateAlways);
      adapter->updater.bind(adapter, info.update);
      adapter->flagBits = flagBits;
      adapter->flagIndex = flagIndex;
      plugin->release();
      return adapter;
    }
  }
  return nullptr;
}

bool GfMenuFlagAdapter::update_FlagDisp() {
  u32 value;
  return getFlagValue(value) && value != 0;
}

bool GfMenuFlagAdapter::update_FlagNum() {
  u32 value;
  if (!getFlagValue(value)) {
    return false;
  }
  setNumber(value);
  return true;
}

void GfMenuFlagAdapter::update(const fw::UpdateInfo &info) {
  if (updater.isValid() && (flags & (FLAG_CHANGED | FLAG_UPDATE_ALWAYS)) != 0) {
    setDisp(updater());
    flags &= ~FLAG_CHANGED;
  }
}

bool GfMenuFlagAdapter::getFlagValue(u32 &value) {
  value = 0;
  switch (flagBits) {
  case 1:
    value = GfMenuFlag::get1(flagIndex);
    break;
  case 2:
    value = GfMenuFlag::get2(flagIndex);
    break;
  case 4:
    value = GfMenuFlag::get4(flagIndex);
    break;
  default:
    return false;
  }
  return true;
}

} // namespace gf
