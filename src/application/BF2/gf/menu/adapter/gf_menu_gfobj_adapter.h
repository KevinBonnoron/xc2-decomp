#pragma once
#include <stddef.h>

#include "gf/menu/adapter/gf_menu_adapter.h"
#include "mm_mtl/delegate.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace ui {
class UIObjectPlugin;
} // namespace ui

namespace gf {

struct GF_OBJ_HANDLE;
class GfObjPropertyEnemy;

class IGfMenuReferenceGfObj : public mm::mtl::ReferenceObject {
public:
  // Inferred role: object handle of the reference (vtable slot 0x10); original name unknown.
  virtual GF_OBJ_HANDLE *unknown001() = 0;
};

class GfMenuGfObjAdapter : public GfMenuAdapter, public unknown135, public unknown136, public unknown137 {
public:
  class PartyDriverConverter;
  class PartyBladeConverter;

  class IConverter {
  public:
    virtual GF_OBJ_HANDLE *getGfObjHandle() = 0;
    virtual PartyDriverConverter *fromPartyDriver();
    virtual PartyBladeConverter *fromPartyBlade();
  };

  class PartyDriverConverter : public IConverter {
  public:
    PartyDriverConverter(u8 partyId) : unknown08(partyId) {}
    GF_OBJ_HANDLE *getGfObjHandle() override;
    PartyDriverConverter *fromPartyDriver() override;

    u32 unknown08; // Inferred role: party id; original member name unknown.
  };

  class PartyBladeConverter : public IConverter {
  public:
    PartyBladeConverter(u8 partyId, int slot, bool isVirtual) : unknown08(partyId), unknown0c(slot), unknown10(isVirtual) {}
    GF_OBJ_HANDLE *getGfObjHandle() override;
    PartyBladeConverter *fromPartyBlade() override;

    u32 unknown08;  // Inferred role: party id, 0 for the chain attack party; original member name unknown.
    int unknown0c;  // Inferred role: blade slot; original member name unknown.
    bool unknown10; // Inferred role: virtual parameters; original member name unknown.
  };

  class TargetEnemyConverter : public IConverter {
  public:
    GF_OBJ_HANDLE *getGfObjHandle() override;
  };

  class ReferenceConverter : public IConverter {
  public:
    ReferenceConverter(mm::mtl::IntrusivePtr<IGfMenuReferenceGfObj> reference) : unknown08(reference) {}
    GF_OBJ_HANDLE *getGfObjHandle() override;

    mm::mtl::IntrusivePtr<IGfMenuReferenceGfObj> unknown08; // Inferred role: reference; original member name unknown.
  };

  GfMenuGfObjAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways, bool isUpdateAfter);
  ~GfMenuGfObjAdapter() override;
  static GfMenuGfObjAdapter *create(u32 handle, u32 type, GF_OBJ_HANDLE *objHandle, bool isUpdateAlways);
  static GfMenuGfObjAdapter *createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways);
  static GfMenuGfObjAdapter *createFromPartyDriver(u32 handle, u32 type, u8 partyId, bool isUpdateAlways);
  static GfMenuGfObjAdapter *createFromPartyBlade(u32 handle, u32 type, u8 partyId, int slot, bool isUpdateAlways, bool isVirtual);
  static GfMenuGfObjAdapter *createFromTargetEnemy(u32 handle, u32 type, bool isUpdateAlways);
  static GfMenuGfObjAdapter *createFromReference(u32 handle, u32 type, mm::mtl::IntrusivePtr<IGfMenuReferenceGfObj> reference, bool isUpdateAlways);
  bool update_NowHp(GF_OBJ_HANDLE *handle);
  bool update_Battle(GF_OBJ_HANDLE *handle);
  bool update_InfoBody(GF_OBJ_HANDLE *handle);
  bool update_InfoDisp(GF_OBJ_HANDLE *handle);
  bool update_InfoIcon(GF_OBJ_HANDLE *handle);
  bool update_TargetDisp(GF_OBJ_HANDLE *handle);
  bool update_AccessDisp(GF_OBJ_HANDLE *handle);
  bool update_EN_Lv(GF_OBJ_HANDLE *handle);
  bool update_EN_ArtsName(GF_OBJ_HANDLE *handle);
  bool update_EN_ArtsID(GF_OBJ_HANDLE *handle);
  bool update_EN_ElemComboName(GF_OBJ_HANDLE *handle);
  bool update_EN_Aggressive(GF_OBJ_HANDLE *handle);
  bool update_EN_Link(GF_OBJ_HANDLE *handle);
  bool update_EN_Arts(GF_OBJ_HANDLE *handle);
  bool update_EN_FightComboIcon(GF_OBJ_HANDLE *handle);
  bool update_EN_FightComboName(GF_OBJ_HANDLE *handle);
  bool update_EN_FightComboTime(GF_OBJ_HANDLE *handle);
  bool update_EN_FightComboSuspend(GF_OBJ_HANDLE *handle);
  bool update_EN_ElemComboLv(GF_OBJ_HANDLE *handle);
  bool update_EN_ElemComboTime(GF_OBJ_HANDLE *handle);
  bool update_EN_ElemComboState(GF_OBJ_HANDLE *handle);
  bool update_EN_ElemComboAttrIcon(GF_OBJ_HANDLE *handle);
  bool update_EN_ElemComboAttrCol(GF_OBJ_HANDLE *handle);
  bool update_EN_ElemComboAttrPtn(GF_OBJ_HANDLE *handle);
  bool update_EN_ElemComboSuspend(GF_OBJ_HANDLE *handle);
  bool update_EN_WeakAttrIcon(GF_OBJ_HANDLE *handle);
  bool update_EN_WeakAttrColor(GF_OBJ_HANDLE *handle);
  bool update_EN_ResAttrOn(GF_OBJ_HANDLE *handle);
  bool update_EN_ResAttrTarget(GF_OBJ_HANDLE *handle);
  bool update_EN_ResAttrBurst(GF_OBJ_HANDLE *handle);
  bool update_EN_ResAttrHP(GF_OBJ_HANDLE *handle);
  bool update_EN_ElemEffID(GF_OBJ_HANDLE *handle);
  bool update_EN_TypeIcon(GF_OBJ_HANDLE *handle);
  bool update_EN_Scout(GF_OBJ_HANDLE *handle);
  bool update_BL_Kizuna(GF_OBJ_HANDLE *handle);
  bool update_BL_Special(GF_OBJ_HANDLE *handle);
  bool update_BL_SpecialLv(GF_OBJ_HANDLE *handle);
  bool update_BL_ChangeRecast(GF_OBJ_HANDLE *handle);
  bool update_BL_ChangeRecast2(GF_OBJ_HANDLE *handle);
  bool update_BL_DispComboReady(GF_OBJ_HANDLE *handle);
  bool update_BL_DispCurrent(GF_OBJ_HANDLE *handle);
  void update(const fw::UpdateInfo &info) override;
  void changeGfObj(GF_OBJ_HANDLE *handle) override;
  void changePartyDriver(u8 partyId) override;
  void changePartyBlade(u8 partyId, u8 slot) override;
  GfObjPropertyEnemy *getEnProperty(GF_OBJ_HANDLE *handle);

  GF_OBJ_HANDLE *unknown48;                           // Inferred role: object handle; original member name unknown.
  mm::mtl::Delegate<bool(GF_OBJ_HANDLE *)> unknown50; // Inferred role: updater; original member name unknown.
  u32 unknown70;                                      // Inferred role: index into the enemy attribute list; original member name unknown.
  IConverter *unknown78;                              // Inferred role: converter; original member name unknown.
};

static_assert(offsetof(GfMenuGfObjAdapter, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuGfObjAdapter, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuGfObjAdapter, unknown70) == 0x70, "");
static_assert(offsetof(GfMenuGfObjAdapter, unknown78) == 0x78, "");
static_assert(sizeof(GfMenuGfObjAdapter) == 0x80, "");
static_assert(offsetof(GfMenuGfObjAdapter::PartyBladeConverter, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuGfObjAdapter::PartyBladeConverter, unknown10) == 0x10, "");

} // namespace gf
