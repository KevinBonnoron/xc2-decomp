#pragma once
#include <stddef.h>

#include "gf/menu/adapter/gf_menu_adapter.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "mm_mtl/delegate.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace ui {
class UIObjectPlugin;
} // namespace ui

namespace gf {

class GfMenuBattleAdapter : public GfMenuAdapter {
public:
  struct TypeInfo {
    bool (GfMenuBattleAdapter::*update)();
    PluginSetup setup;
  };

  class ReferenceIndexConverter {
  public:
    ReferenceIndexConverter(mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number) : number(number) {}
    virtual ~ReferenceIndexConverter() { number = nullptr; }
    virtual void getIndex(int &index);

    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number;
  };

  GfMenuBattleAdapter(ui::UIObjectPlugin *plugin);
  ~GfMenuBattleAdapter() override;
  static GfMenuBattleAdapter *create(u32 handle, u32 type);
  bool update_ArtsSlotRecast();
  bool update_ArtsSlotIcon();
  bool update_ArtsSlotIconElem();
  bool update_ArtsSlotIconType();
  bool update_ArtsSlotIconEnhance();
  bool update_ArtsSlotIconReaction();
  bool update_ArtsSlotIconRange();
  bool update_ArtsSlotName();
  bool update_ArtsSlotInfo();
  bool update_ArtsFightComboIcon();
  bool update_ArtsSlotEnable();
  bool update_ChainCount();
  bool update_PartyGauge();
  bool update_PartyGaugeAll();
  bool update_ChainAttackRecast();
  bool update_ChainAttackCount();
  bool update_ChainAttackDamageRatio();
  bool update_ChainAttackExpBonus();
  bool update_ChainAttackTotalDamage();
  bool update_ChainAttackBurstCount();
  bool update_AwakeningRestTime();
  bool update_ElemComboEffTime();
  bool update_ArtsRange();
  bool update_ReverseIconCol();
  static GfMenuBattleAdapter *createFromReferenceIndex(u32 handle, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number, u32 type);
  void update(const fw::UpdateInfo &info) override;

  int index;
  mm::mtl::Delegate<bool()> updater;
  ReferenceIndexConverter *converter;
};

static_assert(offsetof(GfMenuBattleAdapter, index) == 0x30, "");
static_assert(offsetof(GfMenuBattleAdapter, updater) == 0x38, "");
static_assert(offsetof(GfMenuBattleAdapter, converter) == 0x58, "");
static_assert(sizeof(GfMenuBattleAdapter) == 0x60, "");

} // namespace gf
