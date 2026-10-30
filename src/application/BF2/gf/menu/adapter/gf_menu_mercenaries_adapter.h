#pragma once
#include <stddef.h>

#include "gf/menu/adapter/gf_menu_adapter.h"
#include "mm_mtl/delegate.h"
#include "types.h"

namespace ui {
class UIObjectPlugin;
} // namespace ui

namespace gf {

class GfMenuBladeList;
class GfMenuFieldSkillList;

class GfMenuMercenariesAdapter : public GfMenuAdapter {
public:
  struct TypeInfo {
    bool (GfMenuMercenariesAdapter::*update)();
    PluginSetup setup;
  };

  class IConverter {
  public:
    virtual ~IConverter() {}
    virtual u32 getTeamId() = 0;
  };

  class ReferenceTeamConverter : public IConverter {
  public:
    ~ReferenceTeamConverter() override {}
    u32 getTeamId() override;
  };

  class ReferenceBladeConverter : public IConverter {
  public:
    ReferenceBladeConverter(u32 index) : index(index) {}
    ~ReferenceBladeConverter() override {}
    u32 getTeamId() override;

    u32 index;
  };

  GfMenuMercenariesAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways);
  ~GfMenuMercenariesAdapter() override;
  static GfMenuMercenariesAdapter *create(u32 handle, u32 type, u32 teamId, bool isUpdateAlways);
  bool update_TeamName();
  bool update_TeamBlFace();
  bool update_TeamIcon();
  bool update_TeamStat();
  bool update_TeamStatColor();
  bool update_TeamWait();
  bool update_TeamMisInfo();
  bool update_TeamMisZone();
  bool update_TeamMisZoneIcon();
  bool update_TeamMisName();
  bool update_TeamMisTime();
  bool update_TeamMisComplete();
  bool update_TeamStrength();
  bool update_TeamMale();
  bool update_TeamFemale();
  bool update_TeamAnimal();
  bool update_TeamStrengthDiffIcon();
  bool update_TeamFieldSkillDiffIcon();
  bool update_TeamNameRes();
  bool update_TeamIconRes();
  bool update_TeamIconResFace();
  bool update_TeamDispNum1();
  static GfMenuMercenariesAdapter *createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways);
  static GfMenuMercenariesAdapter *createFromReferenceTeam(u32 handle, u32 type, bool isUpdateAlways);
  static GfMenuMercenariesAdapter *createFromReferenceTeamBladeList(u32 handle, u32 type, GfMenuBladeList *list, bool isUpdateAlways);
  static GfMenuMercenariesAdapter *createFromReferenceTeamFieldSkillList(u32 handle, u32 type, GfMenuFieldSkillList *list, u32 index, bool isUpdateAlways);
  static GfMenuMercenariesAdapter *createFromBladeList(u32 handle, u32 type, GfMenuBladeList *list, u32 index, bool isUpdateAlways);
  static GfMenuMercenariesAdapter *createFromReferenceBlade(u32 handle, u32 type, u32 index, bool isUpdateAlways);
  void update(const fw::UpdateInfo &info) override;
  bool isOrder(u32 teamId);

  mm::mtl::Delegate<bool()> unknown30; // Inferred role: updater; original member name unknown.
  IConverter *unknown50;               // Inferred role: converter; original member name unknown.
  u16 unknown58;                       // Inferred role: team id; original member name unknown.
  u16 unknown5a;                       // Inferred role: team mission; original member name unknown.
  u8 _5c[0x60 - 0x5c];
  GfMenuBladeList *unknown60;      // Inferred role: blade list; original member name unknown.
  GfMenuFieldSkillList *unknown68; // Inferred role: field skill list; original member name unknown.
  u32 unknown70;                   // Inferred role: list index; original member name unknown.
};

static_assert(offsetof(GfMenuMercenariesAdapter, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuMercenariesAdapter, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuMercenariesAdapter, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuMercenariesAdapter, unknown5a) == 0x5a, "");
static_assert(offsetof(GfMenuMercenariesAdapter, unknown60) == 0x60, "");
static_assert(offsetof(GfMenuMercenariesAdapter, unknown68) == 0x68, "");
static_assert(offsetof(GfMenuMercenariesAdapter, unknown70) == 0x70, "");
static_assert(sizeof(GfMenuMercenariesAdapter) == 0x78, "");

} // namespace gf
