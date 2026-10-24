#include "gf/menu/adapter/gf_menu_reference_adapter.h"

#include "gf/gf_allocator.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_object_plugin.h"

namespace gf {

GfMenuReferenceAdapter::GfMenuReferenceAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways)
    : GfMenuAdapter(plugin, false, isUpdateAlways), unknown38(0), unknown3c(0), unknown40(0), unknown44(0) {}

GfMenuReferenceAdapter::~GfMenuReferenceAdapter() { unknown30 = nullptr; }

GfMenuReferenceAdapter *GfMenuReferenceAdapter::create(u32 handle, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> reference, bool isUpdateAlways) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    PluginSetup setup;
    setup.unknown00 = PLUGIN_TYPE_NUMBER;
    setup.unknown04 = reference->unknown10;
    setup.unknown08 = reference->unknown14;
    ui::UIObjectPlugin *plugin = createPlugin(handle, setup);
    if (plugin != nullptr) {
      // __LINE__ must be 52 as in the original source: it is the line argument of operator new.
#line 52
      GfMenuReferenceAdapter *adapter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuReferenceAdapter(plugin, isUpdateAlways);
      if (adapter != nullptr) {
        adapter->unknown30 = reference;
        plugin->release();
        return adapter;
      }
      plugin->release();
    }
  }
  return nullptr;
}

void GfMenuReferenceAdapter::update(const fw::UpdateInfo &info) {
  bool isChanged = (unknown20 & (FLAG_CHANGED | FLAG_UPDATE_ALWAYS)) != 0;
  if (!isChanged) {
    isChanged = unknown38 != unknown30->unknown0c;
    isChanged |= unknown3c != unknown30->unknown14;
    isChanged |= unknown40 != unknown30->unknown10;
  }
  if (isChanged) {
    int number = unknown30->unknown0c + unknown44;
    setNumberMax(unknown30->unknown14);
    setNumberMin(unknown30->unknown10);
    setNumber(number);
    unknown38 = number;
    unknown3c = unknown30->unknown14;
    unknown40 = unknown30->unknown10;
    setDisp(number >= unknown30->unknown10 && number <= unknown30->unknown14);
    unknown20 &= ~FLAG_CHANGED;
  }
}

} // namespace gf
