#include "gf/menu/adapter/gf_menu_battle_adapter.h"

#include "battle/arts_data.h"
#include "battle/utility_battle.h"
#include "gf/data/gf_data_driver_arts.h"
#include "gf/game/gf_game_party.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_reference.h"
#include "mm_mtl/fixstr.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_object_plugin.h"
#include "ui/ui_str.h"

namespace gf {

constexpr f32 PERCENT = 100.0f;
constexpr f32 PARTY_GAUGE_MAX = 300.0f;
constexpr int PARTY_GAUGE_SEGMENT = 100;

static GfMenuBattleAdapter::TypeInfo TYPE_INFOS[] = {
    {&GfMenuBattleAdapter::update_ArtsSlotRecast, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 100}},
    {&GfMenuBattleAdapter::update_ArtsSlotIcon, {GfMenuAdapter::PLUGIN_TYPE_IMAGE, 0, 0}},
    {&GfMenuBattleAdapter::update_ArtsSlotIconElem, {GfMenuAdapter::PLUGIN_TYPE_COLOR, 0, 0}},
    {&GfMenuBattleAdapter::update_ArtsSlotIconType, {GfMenuAdapter::PLUGIN_TYPE_IMAGE, 0, 0}},
    {&GfMenuBattleAdapter::update_ArtsSlotIconEnhance, {GfMenuAdapter::PLUGIN_TYPE_IMAGE, 0, 0}},
    {&GfMenuBattleAdapter::update_ArtsSlotIconReaction, {GfMenuAdapter::PLUGIN_TYPE_IMAGE, 0, 0}},
    {&GfMenuBattleAdapter::update_ArtsSlotIconRange, {GfMenuAdapter::PLUGIN_TYPE_IMAGE, 0, 0}},
    {&GfMenuBattleAdapter::update_ArtsSlotName, {GfMenuAdapter::PLUGIN_TYPE_TEXT, 0, 0}},
    {&GfMenuBattleAdapter::update_ArtsSlotInfo, {GfMenuAdapter::PLUGIN_TYPE_TEXT, 0, 0}},
    {&GfMenuBattleAdapter::update_ArtsFightComboIcon, {GfMenuAdapter::PLUGIN_TYPE_IMAGE, 0, 0}},
    {&GfMenuBattleAdapter::update_ArtsSlotEnable, {GfMenuAdapter::PLUGIN_TYPE_DISP, 0, 0}},
    {&GfMenuBattleAdapter::update_ChainCount, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 99}},
    {&GfMenuBattleAdapter::update_PartyGauge, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 100}},
    {&GfMenuBattleAdapter::update_PartyGaugeAll, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 100}},
    {&GfMenuBattleAdapter::update_ChainAttackRecast, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 100}},
    {&GfMenuBattleAdapter::update_ChainAttackCount, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 99}},
    {&GfMenuBattleAdapter::update_ChainAttackDamageRatio, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 9999}},
    {&GfMenuBattleAdapter::update_ChainAttackExpBonus, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 999}},
    {&GfMenuBattleAdapter::update_ChainAttackTotalDamage, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 9999999}},
    {&GfMenuBattleAdapter::update_ChainAttackBurstCount, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 99}},
    {&GfMenuBattleAdapter::update_AwakeningRestTime, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 100}},
    {&GfMenuBattleAdapter::update_ElemComboEffTime, {GfMenuAdapter::PLUGIN_TYPE_NUMBER, 0, 100}},
    {&GfMenuBattleAdapter::update_ArtsRange, {GfMenuAdapter::PLUGIN_TYPE_DISP, 0, 0}},
    {&GfMenuBattleAdapter::update_ReverseIconCol, {GfMenuAdapter::PLUGIN_TYPE_COLOR, 0, 0}},
};

GfMenuBattleAdapter::GfMenuBattleAdapter(ui::UIObjectPlugin *plugin) : GfMenuAdapter(plugin, true, true), unknown30(0), unknown58(nullptr) {}

GfMenuBattleAdapter::~GfMenuBattleAdapter() {
  if (unknown58 != nullptr) {
    delete unknown58;
    unknown58 = nullptr;
  }
}

GfMenuBattleAdapter *GfMenuBattleAdapter::create(u32 handle, u32 type) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    TypeInfo &info = TYPE_INFOS[type];
    ui::UIObjectPlugin *plugin = createPlugin(handle, info.setup);
    if (plugin != nullptr) {
      // __LINE__ must be 130 as in the original source: it is the line argument of operator new.
#line 130
      GfMenuBattleAdapter *adapter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuBattleAdapter(plugin);
      adapter->unknown38.bind(adapter, info.update);
      plugin->release();
      return adapter;
    }
  }
  return nullptr;
}

bool GfMenuBattleAdapter::update_ArtsSlotRecast() {
  const GfMenuReference::ArtsPaletteInfo &info = GfMenuReference::getArtsPaletteInfo(unknown30);
  setNumber(info.unknown04 * PERCENT);
  return info.unknown04 > 0.0f;
}

bool GfMenuBattleAdapter::update_ArtsSlotIcon() {
  u16 artsId = GfMenuReference::getArtsPaletteInfo(unknown30).unknown00;
  if (artsId != 0) {
    setNumber(GfMenuBdat::getIconImageIndex(GfMenuBdat::getIconIDFromArtsID(artsId)));
  }
  return artsId != 0;
}

bool GfMenuBattleAdapter::update_ArtsSlotIconElem() {
  u16 artsId = GfMenuReference::getArtsPaletteInfo(unknown30).unknown00;
  if (artsId != 0) {
    mm::mtl::FixStr<32> color;
    color.format("elemental%02d", GfMenuReference::getArtsPaletteElementType(unknown30));
    setMulColor(color.c_str());
  }
  return artsId != 0;
}

bool GfMenuBattleAdapter::update_ArtsSlotIconType() {
  u16 artsId = GfMenuReference::getArtsPaletteInfo(unknown30).unknown00;
  if (artsId != 0) {
    setNumber(GfMenuReference::getArtsPaletteIconInfo(unknown30).unknown00);
  }
  return artsId != 0;
}

bool GfMenuBattleAdapter::update_ArtsSlotIconEnhance() {
  u16 artsId = GfMenuReference::getArtsPaletteInfo(unknown30).unknown00;
  if (artsId != 0) {
    setNumber(GfMenuReference::getArtsPaletteIconInfo(unknown30).unknown04);
  }
  return artsId != 0;
}

bool GfMenuBattleAdapter::update_ArtsSlotIconReaction() {
  u16 artsId = GfMenuReference::getArtsPaletteInfo(unknown30).unknown00;
  if (artsId != 0) {
    setNumber(GfMenuReference::getArtsPaletteIconInfo(unknown30).unknown08);
  }
  return artsId != 0;
}

bool GfMenuBattleAdapter::update_ArtsSlotIconRange() {
  u16 artsId = GfMenuReference::getArtsPaletteInfo(unknown30).unknown00;
  if (artsId != 0) {
    setNumber(GfMenuReference::getArtsPaletteIconInfo(unknown30).unknown10);
  }
  return artsId != 0;
}

bool GfMenuBattleAdapter::update_ArtsSlotName() {
  const GfMenuReference::ArtsPaletteInfo &info = GfMenuReference::getArtsPaletteInfo(unknown30);
  u16 artsId = info.unknown00;
  if (artsId != 0) {
    setText(ui::UIStr(GfDataDriverArts::getNameFP(), GfDataDriverArts::getNameID(info.unknown00)));
  }
  return artsId != 0;
}

bool GfMenuBattleAdapter::update_ArtsSlotInfo() {
  const GfMenuReference::ArtsPaletteInfo &info = GfMenuReference::getArtsPaletteInfo(unknown30);
  u16 artsId = info.unknown00;
  if (artsId != 0) {
    setText(ui::UIStr(GfDataDriverArts::getCaptionFP(), GfDataDriverArts::getCaptionID(info.unknown00)));
  }
  return artsId != 0;
}

bool GfMenuBattleAdapter::update_ArtsFightComboIcon() {
  const GfMenuReference::ArtsPaletteInfo &info = GfMenuReference::getArtsPaletteInfo(unknown30);
  btl::ARTS_DATA data;
  if (info.unknown00 == 0) {
    return false;
  }
  btl::Utility::GetArtsData(btl::ARTS_DATA::DATA_TYPE_DRIVER, info.unknown00, data);
  if (data.unknown0c_0 == 0) {
    return false;
  }
  setNumber(data.unknown0c_0 - 1);
  return true;
}

bool GfMenuBattleAdapter::update_ChainCount() {
  setNumber(GfMenuReference::getChainNum());
  return true;
}

bool GfMenuBattleAdapter::update_PartyGauge() {
  int gauge = GfGameParty::getPartyGauge() - unknown30 * PARTY_GAUGE_SEGMENT;
  setNumber(gauge < 0 ? 0 : (gauge > PARTY_GAUGE_SEGMENT ? PARTY_GAUGE_SEGMENT : gauge));
  return true;
}

bool GfMenuBattleAdapter::update_PartyGaugeAll() {
  u16 gauge = GfGameParty::getPartyGauge();
  if (gauge == 0) {
    setNumber(0);
    return false;
  }
  setNumber(gauge / PARTY_GAUGE_MAX * PERCENT);
  return true;
}

bool GfMenuBattleAdapter::update_ChainAttackRecast() {
  setNumber(GfMenuReference::getChainAttackActionRecast() * PERCENT);
  return true;
}

bool GfMenuBattleAdapter::update_ChainAttackCount() {
  setNumber(GfMenuReference::getChainAttackActionCount());
  return true;
}

bool GfMenuBattleAdapter::update_ChainAttackDamageRatio() {
  setNumber(GfMenuReference::getChainAttackDamageRatio() * PERCENT);
  return true;
}

bool GfMenuBattleAdapter::update_ChainAttackExpBonus() {
  setNumber(GfMenuReference::getChainAttackExpRatio() * PERCENT);
  return true;
}

bool GfMenuBattleAdapter::update_ChainAttackTotalDamage() {
  setNumber(GfMenuReference::getChainAttackTotalDamage());
  return true;
}

bool GfMenuBattleAdapter::update_ChainAttackBurstCount() {
  setNumber(GfMenuReference::getChainAttackBurstCount());
  return true;
}

bool GfMenuBattleAdapter::update_AwakeningRestTime() {
  setNumber(GfMenuReference::getAwakeningRestTimeRatio() * PERCENT);
  return true;
}

bool GfMenuBattleAdapter::update_ElemComboEffTime() {
  if (GfMenuReference::getElementComboParty(unknown30) == 0) {
    return false;
  }
  setNumber(GfMenuReference::getElementComboPartyTimeLeft(unknown30) * PERCENT);
  return true;
}

bool GfMenuBattleAdapter::update_ArtsRange() { return GfMenuReference::isWeaponJustRange(); }

bool GfMenuBattleAdapter::update_ReverseIconCol() {
  if (!GfMenuReference::isReversePaletteBtnState(unknown30, 0)) {
    return false;
  }
  if (GfMenuReference::isReversePaletteBtnState(unknown30, 1)) {
    setColor("white");
  } else {
    setColor("gray");
  }
  return true;
}

GfMenuBattleAdapter *GfMenuBattleAdapter::createFromReferenceIndex(u32 handle, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number, u32 type) {
  // __LINE__ must be 146 as in the original source: it is the line argument of operator new.
#line 146
  ReferenceIndexConverter *converter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) ReferenceIndexConverter(number);
  GfMenuBattleAdapter *adapter = create(handle, type);
  adapter->unknown58 = converter;
  return adapter;
}

void GfMenuBattleAdapter::update(const fw::UpdateInfo &info) {
  if (unknown58 != nullptr) {
    int newIndex = 0;
    unknown58->getIndex(newIndex);
    if (unknown30 != newIndex) {
      unknown30 = newIndex;
      setChange();
    }
  }

  if (unknown38.isValid() && (unknown20 & (FLAG_CHANGED | FLAG_UPDATE_ALWAYS)) != 0) {
    if (GfMenuManager::isBattleState(0) || GfMenuManager::isBattleState(1)) {
      if (unknown30 >= 0) {
        setDisp(unknown38());
      } else {
        setDisp(false);
      }
      unknown20 &= ~FLAG_CHANGED;
    }
  }
}

void GfMenuBattleAdapter::ReferenceIndexConverter::getIndex(int &index) {
  if (number.get() != nullptr) {
    index = number->unknown0c;
  }
}

} // namespace gf
