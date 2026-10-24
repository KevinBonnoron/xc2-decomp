#include "gf/menu/adapter/gf_menu_reference_adapter.h"

#include "gf/gf_allocator.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_object_plugin.h"

namespace gf {

GfMenuReferenceAdapter::GfMenuReferenceAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways) : GfMenuAdapter(plugin, false, isUpdateAlways), lastNumber(0), lastMax(0), lastMin(0), offset(0) {}

GfMenuReferenceAdapter::~GfMenuReferenceAdapter() { reference = nullptr; }

GfMenuReferenceAdapter *GfMenuReferenceAdapter::create(u32 handle, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> reference, bool isUpdateAlways) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    PluginSetup setup;
    setup.type = PLUGIN_TYPE_NUMBER;
    setup.param = reference->min;
    setup.max = reference->max;
    ui::UIObjectPlugin *plugin = createPlugin(handle, setup);
    if (plugin != nullptr) {
      // __LINE__ must be 52 as in the original source: it is the line argument of operator new.
#line 52
      GfMenuReferenceAdapter *adapter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuReferenceAdapter(plugin, isUpdateAlways);
      if (adapter != nullptr) {
        adapter->reference = reference;
        plugin->release();
        return adapter;
      }
      plugin->release();
    }
  }
  return nullptr;
}

void GfMenuReferenceAdapter::update(const fw::UpdateInfo &info) {
  bool isChanged = (flags & (FLAG_CHANGED | FLAG_UPDATE_ALWAYS)) != 0;
  if (!isChanged) {
    isChanged = lastNumber != reference->number;
    isChanged |= lastMax != reference->max;
    isChanged |= lastMin != reference->min;
  }
  if (isChanged) {
    int number = reference->number + offset;
    setNumberMax(reference->max);
    setNumberMin(reference->min);
    setNumber(number);
    lastNumber = number;
    lastMax = reference->max;
    lastMin = reference->min;
    setDisp(number >= reference->min && number <= reference->max);
    flags &= ~FLAG_CHANGED;
  }
}

} // namespace gf
