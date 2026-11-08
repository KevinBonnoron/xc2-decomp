#pragma once
#include <stddef.h>

#include "gf/menu/adapter/gf_menu_adapter.h"
#include "mm_mtl/delegate.h"
#include "types.h"

namespace ui {
class UIObjectPlugin;
} // namespace ui

namespace gf {

class DataParamAcc;
class GfMenuBladeList;
class GfMenuDriverList;
class GfMenuEnemyList;
class GfMenuIDList;
struct GF_OBJ_HANDLE;

class GfMenuCharDataAdapter : public GfMenuAdapter, public unknown140, public unknown135, public unknown136, public unknown137 {
public:
  class GfObjConverter;
  class PartyDriverConverter;
  class PartyBladeConverter;

  struct TypeInfo {
    bool (GfMenuCharDataAdapter::*update)(const DataParamAcc &acc);
    PluginSetup setup;
  };

  class IConverter {
  public:
    virtual void getCharData(u8 &type, u32 &id) = 0;
    virtual GfObjConverter *fromGfObj();
    virtual PartyDriverConverter *fromPartyDriver();
    virtual PartyBladeConverter *fromPartyBlade();
  };

  class GfObjConverter : public IConverter {
  public:
    GfObjConverter(GF_OBJ_HANDLE *handle) : unknown08(handle) {}
    void getCharData(u8 &type, u32 &id) override;
    GfObjConverter *fromGfObj() override;

    GF_OBJ_HANDLE *unknown08; // Inferred role: object handle; original member name unknown.
  };

  class PartyDriverConverter : public IConverter {
  public:
    PartyDriverConverter(u8 partyId) : unknown08(partyId) {}
    void getCharData(u8 &type, u32 &id) override;
    PartyDriverConverter *fromPartyDriver() override;

    u32 unknown08; // Inferred role: party id; original member name unknown.
  };

  class PartyBladeConverter : public IConverter {
  public:
    PartyBladeConverter(u8 partyId, int slot, bool isBackSlot, bool isVirtual) : unknown08(partyId), unknown0c(slot), unknown10(isBackSlot), unknown11(isVirtual) {}
    void getCharData(u8 &type, u32 &id) override;
    PartyBladeConverter *fromPartyBlade() override;

    u32 unknown08;  // Inferred role: party id, 0 for the chain attack party; original member name unknown.
    int unknown0c;  // Inferred role: blade slot; original member name unknown.
    bool unknown10; // Inferred role: back slot; original member name unknown.
    bool unknown11; // Inferred role: virtual parameters; original member name unknown.
  };

  class DriverListConverter : public IConverter {
  public:
    void getCharData(u8 &type, u32 &id) override;

    const GfMenuDriverList *unknown08; // Inferred role: driver list; original member name unknown.
    int unknown10;                     // Inferred role: list index, -1 for the selected one; original member name unknown.
  };

  class BladeListConverter : public IConverter {
  public:
    void getCharData(u8 &type, u32 &id) override;

    const GfMenuBladeList *unknown08; // Inferred role: blade list; original member name unknown.
    int unknown10;                    // Inferred role: list index, -1 for the selected one; original member name unknown.
  };

  class EnemyListConverter : public IConverter {
  public:
    void getCharData(u8 &type, u32 &id) override;

    const GfMenuEnemyList *unknown08; // Inferred role: enemy list; original member name unknown.
    int unknown10;                    // Inferred role: list index, -1 for the selected one; original member name unknown.
  };

  class EnBookListConverter : public IConverter {
  public:
    void getCharData(u8 &type, u32 &id) override;

    const GfMenuIDList *unknown08; // Inferred role: enemy book list; original member name unknown.
    int unknown10;                 // Inferred role: list index, -1 for the selected one; original member name unknown.
  };

  class ReferenceDriverConverter : public IConverter {
  public:
    ReferenceDriverConverter(u32 index) : unknown08(index) {}
    void getCharData(u8 &type, u32 &id) override;

    u32 unknown08; // Inferred role: reference index; original member name unknown.
  };

  class ReferenceBladeConverter : public IConverter {
  public:
    ReferenceBladeConverter(u32 index) : unknown08(index) {}
    void getCharData(u8 &type, u32 &id) override;

    u32 unknown08; // Inferred role: reference index; original member name unknown.
  };

  class BladeSetConverter : public IConverter {
  public:
    void getCharData(u8 &type, u32 &id) override;

    u32 unknown08; // Inferred role: driver; original member name unknown.
    int unknown0c; // Inferred role: blade slot; original member name unknown.
  };

  class ReferenceBladeSetConverter : public IConverter {
  public:
    void getCharData(u8 &type, u32 &id) override;

    u32 unknown08; // Inferred role: reference index of the driver; original member name unknown.
    int unknown0c; // Inferred role: blade slot; original member name unknown.
  };

  class ReferenceBladeOwnerDriverConverter : public IConverter {
  public:
    ReferenceBladeOwnerDriverConverter(u32 index) : unknown08(index) {}
    void getCharData(u8 &type, u32 &id) override;

    u32 unknown08; // Inferred role: reference index of the blade; original member name unknown.
  };

  GfMenuCharDataAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways);
  ~GfMenuCharDataAdapter() override;
  void setSlotList(GfMenuBladeList *list);
  static GfMenuCharDataAdapter *create(u32 handle, u32 type, u8 objType, u32 id, bool isUpdateAlways);
  static GfMenuCharDataAdapter *createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways);
  static GfMenuCharDataAdapter *createFromGfObj(u32 handle, u32 type, GF_OBJ_HANDLE *objHandle, bool isUpdateAlways);
  static GfMenuCharDataAdapter *createFromPartyDriver(u32 handle, u32 type, u8 partyId, bool isUpdateAlways);
  static GfMenuCharDataAdapter *createFromPartyBlade(u32 handle, u32 type, u8 partyId, int slot, bool isUpdateAlways, bool isBackSlot, bool isVirtual);
  static GfMenuCharDataAdapter *createFromDriverList(u32 handle, u32 type, const GfMenuDriverList *list, int index, bool isUpdateAlways);
  static GfMenuCharDataAdapter *createFromBladeList(u32 handle, u32 type, const GfMenuBladeList *list, int index, bool isUpdateAlways);
  static GfMenuCharDataAdapter *createFromReferenceDriver(u32 handle, u32 type, u32 index, bool isUpdateAlways);
  static GfMenuCharDataAdapter *createFromReferenceBlade(u32 handle, u32 type, u32 index, bool isUpdateAlways);
  static GfMenuCharDataAdapter *createFromReferenceBladeOwnerDriver(u32 handle, u32 type, u32 index, bool isUpdateAlways);
  bool update_Name(const DataParamAcc &acc);
  bool update_BL_RoleIcon(const DataParamAcc &acc);
  bool update_HpMax(const DataParamAcc &acc);
  bool update_Lv(const DataParamAcc &acc);
  bool update_PhysDef(const DataParamAcc &acc);
  bool update_EtherDef(const DataParamAcc &acc);
  bool update_Guard(const DataParamAcc &acc);
  bool update_AutoAtkDmg(const DataParamAcc &acc);
  bool update_Critical(const DataParamAcc &acc);
  bool update_Strength(const DataParamAcc &acc);
  bool update_EtherPow(const DataParamAcc &acc);
  bool update_Dex(const DataParamAcc &acc);
  bool update_Agl(const DataParamAcc &acc);
  bool update_Luck(const DataParamAcc &acc);
  bool update_DR_ExpNext(const DataParamAcc &acc);
  bool update_DR_ExpBonus(const DataParamAcc &acc);
  bool update_DR_LevelUpEnable(const DataParamAcc &acc);
  bool update_DR_Wp(const DataParamAcc &acc);
  bool update_DR_Sp(const DataParamAcc &acc);
  bool update_DR_Bustup(const DataParamAcc &acc);
  bool update_DR_BustupPlate(const DataParamAcc &acc);
  bool update_DR_BladeEnable(const DataParamAcc &acc);
  bool update_DR_KizunaRingOpen(const DataParamAcc &acc);
  bool update_DR_KizunaRingMax(const DataParamAcc &acc);
  bool update_DR_IdeaPoint(const DataParamAcc &acc);
  bool update_DR_ClassBuffVal(const DataParamAcc &acc);
  bool update_DR_ClassBuffLv(const DataParamAcc &acc);
  bool update_BL_WeaponIcon(const DataParamAcc &acc);
  bool update_BL_AttrIcon(const DataParamAcc &acc);
  bool update_BL_RareIcon(const DataParamAcc &acc);
  bool update_BL_Bustup(const DataParamAcc &acc);
  bool update_BL_Power(const DataParamAcc &acc);
  bool update_BL_Attr(const DataParamAcc &acc);
  bool update_BL_AttrCol(const DataParamAcc &acc);
  bool update_BL_Enable(const DataParamAcc &acc);
  bool update_BL_IdeaPoint(const DataParamAcc &acc);
  bool update_BL_IdeaLv(const DataParamAcc &acc);
  bool update_BL_RecastLv(const DataParamAcc &acc);
  bool update_BL_BtlSkillIcon(const DataParamAcc &acc);
  bool update_BL_BtlSkillLv(const DataParamAcc &acc);
  bool update_BL_Selectable(const DataParamAcc &acc);
  bool update_BL_Releasable(const DataParamAcc &acc);
  bool update_BL_AffinityIcon(const DataParamAcc &acc);
  bool update_BL_KizunaRingOpen(const DataParamAcc &acc);
  bool update_BL_KizunaRingMax(const DataParamAcc &acc);
  bool update_BL_OrbSlotEnable(const DataParamAcc &acc);
  bool update_BL_InMercenry(const DataParamAcc &acc);
  bool update_BL_Rank(const DataParamAcc &acc);
  bool update_BL_Rarity(const DataParamAcc &acc);
  bool update_EN_BookID(const DataParamAcc &acc);
  bool update_EN_RewardExp(const DataParamAcc &acc);
  bool update_EN_RewardGold(const DataParamAcc &acc);
  bool update_AttrName(const DataParamAcc &acc);
  bool update_EN_Genus(const DataParamAcc &acc);
  bool update_FaceIcon(const DataParamAcc &acc);
  bool update_DR_SetBladeFace(const DataParamAcc &acc);
  bool update_DR_IdeaLv(const DataParamAcc &acc);
  bool update_DR_ExpNextVirtual(const DataParamAcc &acc);
  bool update_BL_SpecialName(const DataParamAcc &acc);
  bool update_BL_SpecialDesc(const DataParamAcc &acc);
  bool update_BL_FieldSkillName(const DataParamAcc &acc);
  bool update_BL_FieldSkillDesc(const DataParamAcc &acc);
  bool update_BL_SkillName(const DataParamAcc &acc);
  bool update_BL_weaponTypeName(const DataParamAcc &acc);
  bool update_BL_CorrectiveTypeName(const DataParamAcc &acc);
  bool update_BL_TeamName(const DataParamAcc &acc);
  bool update_DR_Exp(const DataParamAcc &acc);
  bool update_DR_BtlFace(const DataParamAcc &acc);
  bool update_DR_ClassName(const DataParamAcc &acc);
  bool update_BL_FieldSkillLv(const DataParamAcc &acc);
  bool update_BL_SkillLv(const DataParamAcc &acc);
  bool update_BL_AttrCol2(const DataParamAcc &acc);
  bool update_BL_RoleName(const DataParamAcc &acc);
  bool update_BL_Selectable2(const DataParamAcc &acc);
  bool update_BL_CorrectiveValue(const DataParamAcc &acc);
  bool update_BL_ArtsName(const DataParamAcc &acc);
  bool update_BL_ArtsDesc(const DataParamAcc &acc);
  bool update_BL_GenderIcon(const DataParamAcc &acc);
  bool update_BL_DR_Face(const DataParamAcc &acc);
  bool update_DR_ExpProgress(const DataParamAcc &acc);
  bool update_DR_ExpProgressBonus(const DataParamAcc &acc);
  bool update_DR_ClassBuffName(const DataParamAcc &acc);
  bool update_BL_DR_Name(const DataParamAcc &acc);
  bool update_BL_AffinityText(const DataParamAcc &acc);
  bool update_BL_CVName(const DataParamAcc &acc);
  bool update_BL_IlustName(const DataParamAcc &acc);
  bool update_EN_Family(const DataParamAcc &acc);
  bool update_BL_GenderText(const DataParamAcc &acc);
  bool update_BL_SkillDesc(const DataParamAcc &acc);
  bool update_HobbyIcon(const DataParamAcc &acc);
  bool update_HobbyName(const DataParamAcc &acc);
  bool update_FavoriteItemIcon(const DataParamAcc &acc);
  bool update_FavoriteItemName(const DataParamAcc &acc);
  bool update_BL_ChangeBtnIcon(const DataParamAcc &acc);
  bool update_BL_WpnImage(const DataParamAcc &acc);
  u32 getBL_FieldSkillIndex(const DataParamAcc &acc);
  u32 getBL_SkillIndex(const DataParamAcc &acc);
  void update(const fw::UpdateInfo &info) override;
  void changeCharData(u8 type, u32 id) override;
  void changeGfObj(GF_OBJ_HANDLE *handle) override;
  void changePartyDriver(u8 partyId) override;
  void changePartyBlade(u8 partyId, u8 slot) override;

  mm::mtl::Delegate<bool(const DataParamAcc &)> unknown50; // Inferred role: updater; original member name unknown.
  IConverter *unknown70;                                   // Inferred role: converter; original member name unknown.
  u8 unknown78;                                            // Inferred role: object type; original member name unknown.
  u8 unknown79;                                            // Inferred role: virtual parameters; original member name unknown.
  u32 unknown7c;                                           // Inferred role: object id; original member name unknown.
  u32 unknown80;                                           // Inferred role: slot index; original member name unknown.
  GfMenuBladeList *unknown88;                              // Inferred role: blade list, reference counted by hand; original member name unknown.
};

static_assert(offsetof(GfMenuCharDataAdapter, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuCharDataAdapter, unknown70) == 0x70, "");
static_assert(offsetof(GfMenuCharDataAdapter, unknown78) == 0x78, "");
static_assert(offsetof(GfMenuCharDataAdapter, unknown79) == 0x79, "");
static_assert(offsetof(GfMenuCharDataAdapter, unknown7c) == 0x7c, "");
static_assert(offsetof(GfMenuCharDataAdapter, unknown80) == 0x80, "");
static_assert(offsetof(GfMenuCharDataAdapter, unknown88) == 0x88, "");
static_assert(sizeof(GfMenuCharDataAdapter) == 0x90, "");
static_assert(offsetof(GfMenuCharDataAdapter::PartyBladeConverter, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuCharDataAdapter::PartyBladeConverter, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuCharDataAdapter::PartyBladeConverter, unknown11) == 0x11, "");
static_assert(sizeof(GfMenuCharDataAdapter::PartyBladeConverter) == 0x18, "");

} // namespace gf
