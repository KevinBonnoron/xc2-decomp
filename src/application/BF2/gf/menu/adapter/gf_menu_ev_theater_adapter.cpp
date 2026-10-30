#include "gf/menu/adapter/gf_menu_ev_theater_adapter.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/gf_allocator.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_object_plugin.h"
#include "ui/ui_str.h"

namespace gf {

static GfMenuEvTherterAdapter::TypeInfo TYPE_INFOS[] = {
    {&GfMenuEvTherterAdapter::update_Title, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuEvTherterAdapter::update_Thumb, {GfMenuAdapter::unknown004_0, 0, 0}},
};

GfMenuEvTherterAdapter::GfMenuEvTherterAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways) : GfMenuAdapter(plugin, false, isUpdateAlways), unknown50(0), unknown58(nullptr) {}

GfMenuEvTherterAdapter::~GfMenuEvTherterAdapter() {
  if (unknown58 != nullptr) {
    delete unknown58;
    unknown58 = nullptr;
  }
}

GfMenuEvTherterAdapter *GfMenuEvTherterAdapter::create(u32 handle, u32 type, u32 evTheater, bool isUpdateAlways) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    TypeInfo &info = TYPE_INFOS[type];
    ui::UIObjectPlugin *plugin = createPlugin(handle, info.setup);
    if (plugin != nullptr) {
      // __LINE__ must be 138 as in the original source: it is the line argument of operator new.
#line 138
      GfMenuEvTherterAdapter *adapter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuEvTherterAdapter(plugin, isUpdateAlways);
      adapter->unknown30.bind(adapter, info.update);
      adapter->unknown50 = evTheater;
      plugin->release();
      return adapter;
    }
  }
  return nullptr;
}

bool GfMenuEvTherterAdapter::update_Title(u32 evTheater) {
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_EVENT_THEATER);
  if (bdat == nullptr) {
    return false;
  }
  u16 title = Bdat::getVal(bdat, "title", evTheater).valueU16;
  setText(ui::UIStr(GfDataBdat::getFP(BDAT_MENU_EV_THEATER_MS), title));
  return true;
}

bool GfMenuEvTherterAdapter::update_Thumb(u32 evTheater) {
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_EVENT_THEATER);
  if (bdat != nullptr) {
    u16 thumbnail = Bdat::getVal(bdat, "thumbnail", evTheater).valueU16;
    if (thumbnail != 0) {
      setNumber(thumbnail);
      return true;
    }
  }
  return false;
}

GfMenuEvTherterAdapter *GfMenuEvTherterAdapter::createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways) {
  GfMenuEvTherterAdapter *adapter = create(handle, type, converter->getEvTheaterID(), isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown58 = converter;
  }
  return adapter;
}

GfMenuEvTherterAdapter *GfMenuEvTherterAdapter::createFromReference(u32 handle, u32 type, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number, bool isUpdateAlways) {
  // __LINE__ must be 163 as in the original source: it is the line argument of operator new.
#line 163
  ReferenceConverter *converter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) ReferenceConverter(number);
  GfMenuEvTherterAdapter *adapter = create(handle, type, converter->getEvTheaterID(), isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown58 = converter;
  }
  return adapter;
}

void GfMenuEvTherterAdapter::update(const fw::UpdateInfo &info) {
  if (unknown58 != nullptr) {
    u32 newEvTheater = unknown58->getEvTheaterID();
    if (unknown50 != newEvTheater) {
      unknown50 = newEvTheater;
      setChange();
    }
  }

  if (unknown30.isValid() && (unknown20 & (FLAG_CHANGED | FLAG_UPDATE_ALWAYS)) != 0) {
    if (unknown50 != 0) {
      setDisp(unknown30(unknown50));
    } else {
      setDisp(false);
    }
    unknown20 &= ~FLAG_CHANGED;
  }
}

u32 GfMenuEvTherterAdapter::ReferenceConverter::getEvTheaterID() {
  if (number.get() != nullptr) {
    return number->unknown0c;
  }
  return 0;
}

} // namespace gf
