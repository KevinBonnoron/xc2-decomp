#include "gf/menu/adapter/gf_menu_shop_adapter.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_item.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/gf_menu_item_util.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/util/gf_item_util.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_object_plugin.h"
#include "ui/ui_str.h"

namespace gf {

static GfMenuShopAdapter::TypeInfo TYPE_INFOS[] = {
    {&GfMenuShopAdapter::update_Name, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuShopAdapter::update_CategoryName, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuShopAdapter::update_Icon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuShopAdapter::update_CategoryIcon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuShopAdapter::update_Owner, {GfMenuAdapter::unknown004_3, 0, 0}},
};

GfMenuShopAdapter::GfMenuShopAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways) : GfMenuAdapter(plugin, false, isUpdateAlways), unknown50(nullptr), unknown58(0), unknown5c(0) {}

GfMenuShopAdapter::~GfMenuShopAdapter() {
  if (unknown50 != nullptr) {
    delete unknown50;
    unknown50 = nullptr;
  }
}

GfMenuShopAdapter *GfMenuShopAdapter::create(u32 handle, u32 type, u32 shop, bool isUpdateAlways) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    TypeInfo &info = TYPE_INFOS[type];
    ui::UIObjectPlugin *plugin = createPlugin(handle, info.setup);
    if (plugin != nullptr) {
      // __LINE__ must be 123 as in the original source: it is the line argument of operator new.
#line 123
      GfMenuShopAdapter *adapter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfMenuShopAdapter(plugin, isUpdateAlways);
      adapter->unknown30.bind(adapter, info.update);
      adapter->unknown58 = shop;
      plugin->release();
      return adapter;
    }
  }
  return nullptr;
}

bool GfMenuShopAdapter::update_Name(u32 shop) {
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_SHOP_LIST);
  if (bdat != nullptr) {
    u16 name = Bdat::getVal(bdat, "Name", shop).valueU16;
    if (name != 0) {
      setText(ui::UIStr(GfDataBdat::getFP(BDAT_FLD_SHOPNAME), name));
      return true;
    }
  }
  return false;
}

bool GfMenuShopAdapter::update_CategoryName(u32 shop) {
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_SHOP_LIST);
  if (bdat != nullptr) {
    u16 icon = Bdat::getVal(bdat, "ShopIcon", shop).valueU16;
    if (icon != 0) {
      u8 *categoryBdat = GfDataBdat::getFP(BDAT_MNU_SHOP_CATEGORY_NAME);
      if (categoryBdat != nullptr) {
        int top = Bdat::getIdTop(categoryBdat);
        u16 name = 0;
        for (int i = 0; i < Bdat::getIdCount(categoryBdat); i++) {
          if (Bdat::getVal(categoryBdat, "icon_id", top + i).valueU16 == icon) {
            name = Bdat::getVal(categoryBdat, "name", top + i).valueU16;
          }
        }
        if (name != 0) {
          setText(ui::UIStr(GfDataBdat::getFP(BDAT_MENU_SHOP_CATEGORY), name));
          return true;
        }
      }
    }
  }
  return false;
}

bool GfMenuShopAdapter::update_Icon(u32 shop) {
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_SHOP_LIST);
  if (bdat != nullptr) {
    u16 shopType = Bdat::getVal(bdat, "ShopType", shop).valueU16;
    if (shopType != 1 && shopType != 2) {
      u16 icon = Bdat::getVal(bdat, "ShopIcon", shop).valueU16;
      if (icon == 0) {
        return false;
      }
      ItemType::Type itemType;
      u32 param;
      if (GfMenuItemUtil::convShopIcon(icon, itemType, param)) {
        u32 number;
        if (GfMenuItemUtil::getIconNumber(itemType, param, number, false)) {
          setNumber(number);
          return true;
        }
        return false;
      }
    }
  }
  return false;
}

bool GfMenuShopAdapter::update_CategoryIcon(u32 shop) {
  // Inferred role: icon number of each shop category; original name unknown.
  static const int unknown001[] = {0, 2, 3, 1};
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_SHOP_LIST);
  if (bdat != nullptr) {
    u16 icon = Bdat::getVal(bdat, "ShopIcon", shop).valueU16;
    u16 shopType = Bdat::getVal(bdat, "ShopType", shop).valueU16;
    u64 index = shopType;
    if (index < 4) {
      int number;
      if (index == 0) {
        if (icon != 0x1a4) {
          return false;
        }
        number = 5;
      } else if (shopType != 3) {
        number = unknown001[index];
        if (shopType == 1) {
          u8 *changeBdat = GfDataBdat::getFP(BDAT_MNU_SHOP_CHANGE);
          if (changeBdat == nullptr) {
            return false;
          }
          u16 tableId = Bdat::getVal(bdat, "TableID", shop).valueU16;
          if (tableId == 0) {
            return false;
          }
          if (Bdat::getVal(changeBdat, "LinkQuestTask", tableId).valueU16 != 0) {
            number = 4;
          } else {
            u16 shopIcon = Bdat::getVal(bdat, "ShopIcon", shop).valueU16;
            if (shopIcon == 0x1aa) {
              number = 6;
            } else if (shopIcon == 0x1ab) {
              number = 7;
            } else if (shopIcon == 0x1a4) {
              number = 5;
            }
          }
        }
      } else {
        return false;
      }
      setNumber(number);
      return true;
    }
  }
  return false;
}

bool GfMenuShopAdapter::update_Owner(u32 shop) {
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_SHOP_LIST);
  if (bdat != nullptr) {
    u8 *normalBdat = GfDataBdat::getFP(BDAT_MNU_SHOP_NORMAL);
    if (normalBdat != nullptr && Bdat::getVal(bdat, "ShopType", shop).valueS16 == 0) {
      u16 tableId = Bdat::getVal(bdat, "TableID", shop).valueU16;
      if (tableId != 0) {
        u16 privilegeItem = Bdat::getVal(normalBdat, "PrivilegeItem", tableId).valueU16;
        if (privilegeItem == 0) {
          return false;
        }
        return GfItemUtil::getItemBoxCount(privilegeItem) != 0;
      }
    }
  }
  return false;
}

GfMenuShopAdapter *GfMenuShopAdapter::createFromReference(u32 handle, u32 type, bool isUpdateAlways) {
  if (handle == 0) {
    return nullptr;
  }
  // __LINE__ must be 139 as in the original source: it is the line argument of operator new.
#line 139
  ReferenceConverter *converter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ReferenceConverter();
  GfMenuShopAdapter *adapter = create(handle, type, GfMenuReference::getReferenceShopID(), isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown50 = converter;
  }
  return adapter;
}

GfMenuShopAdapter *GfMenuShopAdapter::createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways) {
  if (handle == 0) {
    return nullptr;
  }
  GfMenuShopAdapter *adapter = create(handle, type, converter->getShopID(), isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown50 = converter;
  }
  return adapter;
}

GfMenuShopAdapter *GfMenuShopAdapter::createFromReference(u32 handle, u32 type, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number, bool isUpdateAlways) {
  if (handle == 0) {
    return nullptr;
  }
  // __LINE__ must be 148 as in the original source: it is the line argument of operator new.
#line 148
  ReferenceNumberConverter *converter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ReferenceNumberConverter(number);
  GfMenuShopAdapter *adapter = create(handle, type, converter->getShopID(), isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown50 = converter;
  }
  return adapter;
}

void GfMenuShopAdapter::update(const fw::UpdateInfo &info) {
  if (unknown50 != nullptr) {
    u32 newShop = unknown50->getShopID();
    if (unknown58 != newShop) {
      unknown58 = newShop;
      setChange();
    }
  }

  if (unknown30.isValid() && (unknown20 & (FLAG_UNKNOWN_0 | FLAG_UNKNOWN_1)) != 0) {
    u8 *bdat = nullptr;
    if (unknown58 != 0) {
      bdat = GfDataBdat::getFP(BDAT_MNU_SHOP_LIST);
    }
    if (bdat != nullptr && GfMenuBdat::isValidBdatID(bdat, unknown58)) {
      setDisp(unknown30(unknown58));
    } else {
      setDisp(false);
    }
    unknown20 &= ~FLAG_UNKNOWN_0;
  }
}

u32 GfMenuShopAdapter::ReferenceConverter::getShopID() { return GfMenuReference::getReferenceShopID(); }

u32 GfMenuShopAdapter::ReferenceNumberConverter::getShopID() { return number->unknown0c; }

} // namespace gf
