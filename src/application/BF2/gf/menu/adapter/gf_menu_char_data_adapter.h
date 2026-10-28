#pragma once
#include <stddef.h>

#include "gf/menu/adapter/gf_menu_adapter.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace gf {

class DataParamAcc;
class GfMenuBladeList;

class GfMenuCharDataAdapter : public GfMenuAdapter {
public:
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
  u32 getBL_FieldSkillIndex(const DataParamAcc &acc);
  u32 getBL_SkillIndex(const DataParamAcc &acc);

  // Inferred role: the four receiver interfaces (0x30 to 0x50) and members not reconstructed yet; original member names unknown.
  u8 _30[0x79 - 0x30];
  u8 unknown79; // Inferred role: virtual parameters; original member name unknown.
  u8 _7a[0x80 - 0x7a];
  u32 unknown80; // Inferred role: slot index; original member name unknown.
  u8 _84[0x88 - 0x84];
  mm::mtl::IntrusivePtr<GfMenuBladeList> unknown88; // Inferred role: blade list; original member name unknown.
};

static_assert(offsetof(GfMenuCharDataAdapter, unknown79) == 0x79, "");
static_assert(offsetof(GfMenuCharDataAdapter, unknown80) == 0x80, "");
static_assert(offsetof(GfMenuCharDataAdapter, unknown88) == 0x88, "");
static_assert(sizeof(GfMenuCharDataAdapter) == 0x90, "");

} // namespace gf
