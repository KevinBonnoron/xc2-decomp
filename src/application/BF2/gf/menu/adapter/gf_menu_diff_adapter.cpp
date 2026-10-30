#include "gf/menu/adapter/gf_menu_diff_adapter.h"

#include "gf/gf_allocator.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_object_plugin.h"

namespace gf {

static GfMenuDiffAdapter::TypeInfo TYPE_INFOS[] = {
    {&GfMenuDiffAdapter::update_Icon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuDiffAdapter::update_MulCol, {GfMenuAdapter::unknown004_8, 0, 0}},
    {&GfMenuDiffAdapter::update_Sub, {GfMenuAdapter::unknown004_0, -9999, 9999}},
    {&GfMenuDiffAdapter::update_DispSameOn, {GfMenuAdapter::unknown004_3, 0, 0}},
    {&GfMenuDiffAdapter::update_DispSameOff, {GfMenuAdapter::unknown004_3, 0, 0}},
};

GfMenuDiffAdapter::GfMenuDiffAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways) : GfMenuAdapter(plugin, false, isUpdateAlways) {}

GfMenuDiffAdapter::~GfMenuDiffAdapter() {}

GfMenuAdapter *GfMenuDiffAdapter::create(u32 handle, GfMenuAdapter *adapter, GfMenuAdapter *other, u32 type, bool isUpdateAlways) {
  ui::UIObjectAcc acc(handle);
  GfMenuAdapter *result = nullptr;
  if (acc.isValid() && adapter != nullptr && other != nullptr) {
    TypeInfo &info = TYPE_INFOS[type];
    ui::UIObjectPlugin *plugin = createPlugin(handle, info.setup);
    if (plugin != nullptr) {
      // __LINE__ must be 54 as in the original source: it is the line argument of operator new.
#line 54
      GfMenuDiffAdapter *diffAdapter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuDiffAdapter(plugin, isUpdateAlways);
      diffAdapter->unknown30.bind(diffAdapter, info.update);
      diffAdapter->unknown50 = adapter;
      diffAdapter->unknown58 = other;
      plugin->release();
      result = diffAdapter;
    }
  }
  return result;
}

bool GfMenuDiffAdapter::update_Icon(int result) {
  switch (result) {
  case unknown005_0:
    return false;
  case unknown005_1:
    setNumber(0);
    break;
  case unknown005_2:
    setNumber(1);
    break;
  }
  return true;
}

bool GfMenuDiffAdapter::update_MulCol(int result) {
  switch (result) {
  case unknown005_0:
    setMulColor("select");
    break;
  case unknown005_1:
    setMulColor("diff_high");
    break;
  case unknown005_2:
    setMulColor("diff_low");
    break;
  }
  return true;
}

bool GfMenuDiffAdapter::update_Sub(int result) {
  setNumber(unknown50->getNumber() - unknown58->getNumber());
  return true;
}

bool GfMenuDiffAdapter::update_DispSameOn(int result) { return result == unknown005_0; }

bool GfMenuDiffAdapter::update_DispSameOff(int result) { return result != unknown005_0; }

void GfMenuDiffAdapter::update(const fw::UpdateInfo &info) {
  if (unknown30.isValid() && (unknown20 & (FLAG_CHANGED | FLAG_UPDATE_ALWAYS)) != 0) {
    setDisp(unknown30(compare(unknown50, unknown58)));
    unknown20 &= ~FLAG_CHANGED;
  }
}

} // namespace gf
