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

class GfMenuItemList;

class GfMenuWeaponAdapter : public GfMenuAdapter {
public:
  struct TypeInfo {
    bool (GfMenuWeaponAdapter::*update)(u32 weapon);
    PluginSetup setup;
  };

  class IConverter {
  public:
    virtual ~IConverter() {}
    virtual u32 getWeaponID() = 0;
  };

  class BladeConverter : public IConverter {
  public:
    BladeConverter(u32 blade) : unknown08(blade) {}
    u32 getWeaponID() override;

    u32 unknown08; // Inferred role: blade; original member name unknown.
  };

  class ReferenceBladeConverter : public IConverter {
  public:
    ReferenceBladeConverter(u32 index) : unknown08(index) {}
    u32 getWeaponID() override;

    u32 unknown08; // Inferred role: reference blade index; original member name unknown.
  };

  class BladeWithChipListConverter : public IConverter {
  public:
    BladeWithChipListConverter(u32 blade, GfMenuItemList *list, u32 index) : unknown08(blade), unknown10(list), unknown18(index) {}
    u32 getWeaponID() override;

    u32 unknown08;             // Inferred role: blade; original member name unknown.
    GfMenuItemList *unknown10; // Inferred role: chip list; original member name unknown.
    u32 unknown18;             // Inferred role: chip list index; original member name unknown.
  };

  struct ReferenceChip {
    u32 unknown00;                                          // Inferred role: reference blade index; original member name unknown.
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown08; // Inferred role: reference chip item; original member name unknown.
  };

  class ReferenceChipConverter : public IConverter {
  public:
    ReferenceChipConverter(const ReferenceChip &chip) : unknown08(chip.unknown00), unknown10(chip.unknown08) {}
    u32 getWeaponID() override;

    u32 unknown08;                                          // Inferred role: reference blade index; original member name unknown.
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown10; // Inferred role: reference chip item; original member name unknown.
  };

  GfMenuWeaponAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways);
  ~GfMenuWeaponAdapter() override;
  static GfMenuWeaponAdapter *create(u32 handle, u32 type, u32 weapon, bool isUpdateAlways);
  bool update_Name(u32 weapon);
  bool update_Atk(u32 weapon);
  bool update_Guard(u32 weapon);
  bool update_Critical(u32 weapon);
  bool update_Balance(u32 weapon);
  bool update_TypeName(u32 weapon);
  bool update_Caption(u32 weapon);
  bool update_Image(u32 weapon);
  static GfMenuWeaponAdapter *createFromBlade(u32 handle, u32 type, u32 blade, bool isUpdateAlways);
  static GfMenuWeaponAdapter *createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways);
  static GfMenuWeaponAdapter *createFromReferenceBlade(u32 handle, u32 type, u32 index, bool isUpdateAlways);
  static GfMenuWeaponAdapter *createFromBladeWithChipList(u32 handle, u32 type, u32 blade, GfMenuItemList *list, u32 index, bool isUpdateAlways);
  static GfMenuWeaponAdapter *createFromReferenceChip(u32 handle, u32 type, const ReferenceChip &chip, bool isUpdateAlways);
  void update(const fw::UpdateInfo &info) override;

  mm::mtl::Delegate<bool(u32)> unknown30; // Inferred role: updater; original member name unknown.
  IConverter *unknown50;                  // Inferred role: converter; original member name unknown.
  u32 unknown58;                          // Inferred role: weapon; original member name unknown.
  u32 unknown5c;                          // Role and original member name unknown.
};

static_assert(offsetof(GfMenuWeaponAdapter, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuWeaponAdapter, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuWeaponAdapter, unknown58) == 0x58, "");
static_assert(sizeof(GfMenuWeaponAdapter) == 0x60, "");

} // namespace gf
