#include "gf/menu/adapter/gf_menu_hana_parts_adapter.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/game/gf_game_util_hana.h"
#include "gf/gf_allocator.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_object_plugin.h"
#include "ui/ui_str.h"

namespace gf {

static GfMenuHanaPartsAdapter::TypeInfo TYPE_INFOS[] = {
    {&GfMenuHanaPartsAdapter::update_partsText, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuHanaPartsAdapter::update_partsIcon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuHanaPartsAdapter::update_needEther, {GfMenuAdapter::unknown004_0, 0, 999999999}},
};

GfMenuHanaPartsAdapter::GfMenuHanaPartsAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways) : GfMenuAdapter(plugin, false, isUpdateAlways), unknown50(nullptr), unknown58(0) {}

GfMenuHanaPartsAdapter::~GfMenuHanaPartsAdapter() {
  if (unknown50 != nullptr) {
    delete unknown50;
    unknown50 = nullptr;
  }
}

GfMenuHanaPartsAdapter *GfMenuHanaPartsAdapter::create(u32 handle, u32 type, u32 partsId, bool isUpdateAlways) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    TypeInfo &info = TYPE_INFOS[type];
    ui::UIObjectPlugin *plugin = createPlugin(handle, info.setup);
    if (plugin != nullptr) {
      // __LINE__ must be 148 as in the original source: it is the line argument of operator new.
#line 148
      GfMenuHanaPartsAdapter *adapter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuHanaPartsAdapter(plugin, isUpdateAlways);
      adapter->unknown30.bind(adapter, info.update);
      adapter->unknown5c = partsId;
      plugin->release();
      return adapter;
    }
  }
  return nullptr;
}

bool GfMenuHanaPartsAdapter::update_needEther() {
  if (unknown5c == 0) {
    return false;
  }
  u32 blade = unknown58;
  u32 ether;
  switch (unknown5c) {
  case 9:
  case 10:
  case 11:
  case 16:
  case 17:
  case 18: {
    int offset = -9;
    if (unknown5c > 15) {
      offset = -16;
    }
    u32 circuit = offset + unknown5c;
    ether = 0;
    if (GfGameUtilHana::isOpenArtsCircuit(blade, circuit) == unknown003_10) {
      ether = GfGameUtilHana::getEtherForOpenArtsCircuit(blade, circuit);
    }
    break;
  }
  case 12:
  case 13:
  case 14:
  case 19:
  case 20:
  case 21: {
    int offset = -12;
    if (unknown5c > 18) {
      offset = -19;
    }
    u32 circuit = offset + unknown5c;
    ether = 0;
    if (GfGameUtilHana::isOpenCondenserCircuit(blade, circuit) == unknown003_10) {
      ether = GfGameUtilHana::getEtherForOpenCondenserCircuit(blade, circuit);
    }
    break;
  }
  case 15: {
    u32 rank = GfGameUtilHana::getPowerRank(blade) + 1;
    ether = 0;
    if (GfGameUtilHana::isExecPowerRankup(blade, rank) != unknown003_6) {
      ether = GfGameUtilHana::getNeedEtherForExecPowerRankup(blade, rank);
    }
    break;
  }
  default:
    return false;
  }
  setNumber(ether);
  return true;
}

bool GfMenuHanaPartsAdapter::update_partsText() {
  if (unknown5c != 0) {
    u8 *msBdat = GfDataBdat::getFP(BDAT_MENU_MS);
    u8 *bdat = GfDataBdat::getFP(BDAT_MNU_HANA_SET);
    u16 nameId = Bdat::getVal(bdat, "name", unknown5c).valueU16;
    if (nameId != 0) {
      setText(ui::UIStr(msBdat, nameId));
      return true;
    }
  }
  return false;
}

bool GfMenuHanaPartsAdapter::update_partsIcon() {
  if (unknown5c != 0) {
    u8 *bdat = GfDataBdat::getFP(BDAT_MNU_HANA_SET);
    u16 icon = Bdat::getVal(bdat, "icon", unknown5c).valueU16;
    if (icon != 0) {
      setNumber(icon);
      return true;
    }
  }
  return false;
}

GfMenuHanaPartsAdapter *GfMenuHanaPartsAdapter::createFromList(u32 handle, u32 type, GfMenuIDList *list, int listIndex, bool isUpdateAlways) {
  // __LINE__ must be 164 as in the original source: it is the line argument of operator new.
#line 164
  ListConverter *converter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) ListConverter(list, listIndex);
  return createFromCoverter(handle, type, converter, isUpdateAlways);
}

GfMenuHanaPartsAdapter *GfMenuHanaPartsAdapter::createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways) {
  GfMenuHanaPartsAdapter *adapter = create(handle, type, converter->getPartsId(), isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown50 = converter;
  }
  return adapter;
}

GfMenuHanaPartsAdapter *GfMenuHanaPartsAdapter::createFromReference(u32 handle, u32 type, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number, bool isUpdateAlways) {
  // __LINE__ must be 172 as in the original source: it is the line argument of operator new.
#line 172
  ReferenceNumberConverter *converter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) ReferenceNumberConverter(number);
  return createFromCoverter(handle, type, converter, isUpdateAlways);
}

u32 GfMenuHanaPartsAdapter::ListConverter::getPartsId() {
  int index = listIndex;
  if (index == -1) {
    return list->getContents(list->getIndex(false)).unknown00;
  }
  int size = list->getSize();
  if (index < size) {
    return list->getContents(list->getPageIndex(listIndex)).unknown00;
  }
  return 0;
}

u32 GfMenuHanaPartsAdapter::ReferenceNumberConverter::getPartsId() { return number->unknown0c; }

void GfMenuHanaPartsAdapter::update(const fw::UpdateInfo &info) {
  if (unknown50 != nullptr) {
    u32 newPartsId = unknown50->getPartsId();
    if (unknown5c != newPartsId) {
      unknown5c = newPartsId;
      setChange();
    }
  }

  if (unknown30.isValid() && (unknown20 & (FLAG_CHANGED | FLAG_UPDATE_ALWAYS)) != 0) {
    setDisp(unknown30());
    unknown20 &= ~FLAG_CHANGED;
  }
}

} // namespace gf
