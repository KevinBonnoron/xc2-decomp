#include "gf/menu/adapter/gf_menu_enhance_adapter.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_driver_arts.h"
#include "gf/data/gf_data_item.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/util/gf_item_util.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_object_plugin.h"
#include "ui/ui_str.h"

namespace gf {

static GfMenuEnhanceAdapter::TypeInfo TYPE_INFOS[] = {
    {&GfMenuEnhanceAdapter::update_Caption, {GfMenuAdapter::PLUGIN_TYPE_TEXT, 0, 0}},
};

GfMenuEnhanceAdapter::GfMenuEnhanceAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways) : GfMenuAdapter(plugin, false, isUpdateAlways), unknown50(nullptr), unknown58(0), _5c() {}

GfMenuEnhanceAdapter::~GfMenuEnhanceAdapter() {
  if (unknown50 != nullptr) {
    delete unknown50;
    unknown50 = nullptr;
  }
}

GfMenuEnhanceAdapter *GfMenuEnhanceAdapter::create(u32 handle, u32 type, u32 enhance, bool isUpdateAlways) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    TypeInfo &info = TYPE_INFOS[type];
    ui::UIObjectPlugin *plugin = createPlugin(handle, info.setup);
    if (plugin != nullptr) {
      // __LINE__ must be 211 as in the original source: it is the line argument of operator new.
#line 211
      GfMenuEnhanceAdapter *adapter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuEnhanceAdapter(plugin, isUpdateAlways);
      adapter->unknown30.bind(adapter, info.update);
      adapter->unknown58 = enhance;
      plugin->release();
      return adapter;
    }
  }
  return nullptr;
}

bool GfMenuEnhanceAdapter::update_Caption(u32 enhance) {
  ui::UIStr caption;
  bool result = false;
  if (getEnhanceCaption(enhance, caption)) {
    setText(caption);
    result = true;
  }
  return result;
}

GfMenuEnhanceAdapter *GfMenuEnhanceAdapter::createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways) {
  GfMenuEnhanceAdapter *adapter = create(handle, type, converter->getEnhanceID(), isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown50 = converter;
  }
  return adapter;
}

GfMenuEnhanceAdapter *GfMenuEnhanceAdapter::createFromReferenceItem(u32 handle, u32 type, mm::mtl::IntrusivePtr<IGfMenuReferenceItem> item, bool isUpdateAlways) {
  // __LINE__ must be 245 as in the original source: it is the line argument of operator new.
#line 245
  ReferenceItemConverter *converter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) ReferenceItemConverter(item);
  GfMenuEnhanceAdapter *adapter = create(handle, type, converter->getEnhanceID(), isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown50 = converter;
  }
  return adapter;
}

GfMenuEnhanceAdapter *GfMenuEnhanceAdapter::createFromArts(u32 handle, u32 type, u32 arts, u32 level, bool isUpdateAlways) {
  // __LINE__ must be 254 as in the original source: it is the line argument of operator new.
#line 254
  ArtsConverter *converter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) ArtsConverter(arts, level);
  GfMenuEnhanceAdapter *adapter = create(handle, type, GfDataDriverArts::getEnhance(arts, level), isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown50 = converter;
  }
  return adapter;
}

bool GfMenuEnhanceAdapter::getEnhanceCaption(u32 enhance, ui::UIStr &caption) {
  u8 *captionBdat = GfDataBdat::getFP(BDAT_BTL_ENHANCE_CAP);
  u8 *bdat = GfDataBdat::getFP(BDAT_BTL_ENHANCE);
  if (GfMenuBdat::isValidBdatID(bdat, enhance)) {
    u16 captionId = Bdat::getVal(bdat, "Caption", enhance).valueU16;
    if (GfMenuBdat::isValidBdatID(captionBdat, captionId)) {
      caption.copy(ui::UIStr(captionBdat, captionId));
      caption.unknown12 = enhance;
      return true;
    }
  }
  return false;
}

void GfMenuEnhanceAdapter::update(const fw::UpdateInfo &info) {
  if (unknown50 != nullptr) {
    u32 newEnhance = unknown50->getEnhanceID();
    if (unknown58 != newEnhance) {
      unknown58 = newEnhance;
      setChange();
    }
  }

  if (unknown30.isValid() && (unknown20 & (FLAG_CHANGED | FLAG_UPDATE_ALWAYS)) != 0) {
    if (unknown58 != 0) {
      setDisp(unknown30(unknown58));
    } else {
      setDisp(false);
    }
    unknown20 &= ~FLAG_CHANGED;
  }
}

u32 GfMenuEnhanceAdapter::ItemConverter::getEnhanceID() { return ItemConverter::getItemEnhance(info); }

u32 GfMenuEnhanceAdapter::ItemConverter::getItemEnhance(const MenuItemInfo &info) {
  u16 enhance = 0;
  if (info.unknown00 == ItemType::PC_EQUIP) {
    ItemProperty property;
    GfItemUtil::getProperty(property, info.unknown04, 0);
    enhance = property.unknown4a;
  } else if (info.unknown00 == ItemType::EQUIP_ORB) {
    ItemProperty property;
    GfItemUtil::getProperty(property, info.unknown04, 0);
    enhance = property.unknown4a;
  } else if (info.unknown00 == ItemType::FAVORITE) {
    ItemProperty property;
    GfItemUtil::getProperty(property, info.unknown04, 0);
    enhance = property.unknown50;
  }
  return enhance;
}

u32 GfMenuEnhanceAdapter::ItemListConverter::getEnhanceID() {
  GfMenuItemList *itemList = list;
  u32 index = listIndex == -1 ? itemList->getIndex(false) : itemList->getPageIndex(listIndex);
  return ItemConverter::getItemEnhance(itemList->getContents(index));
}

u32 GfMenuEnhanceAdapter::ReferenceItemConverter::getEnhanceID() {
  MenuItemInfo info;
  item->getItem(info);
  return ItemConverter::getItemEnhance(info);
}

u32 GfMenuEnhanceAdapter::ArtsConverter::getEnhanceID() { return GfDataDriverArts::getEnhance(arts, level); }

} // namespace gf
