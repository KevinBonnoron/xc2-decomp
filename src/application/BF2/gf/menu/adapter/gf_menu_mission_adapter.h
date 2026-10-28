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

class GfMenuMissionAdapter : public GfMenuAdapter {
public:
  class IConverter {
  public:
    virtual ~IConverter() {}
    virtual u32 getMissionId() = 0;
  };

  GfMenuMissionAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways);
  ~GfMenuMissionAdapter() override;
  bool update_MissionName();
  bool update_MissionCategoryIcon();
  bool update_MissionRewardIdeaPoint();
  bool update_MissionFieldSkill();
  bool update_MissionCondIcon();
  bool update_MissionCondParam();
  bool update_MissionCondBladeMax();
  bool update_MissionTeamIcon();
  bool update_MissionStateIcon();
  bool update_MissionNewDisp();
  bool update_MissionCondParamIcon();
  bool update_MissionProgressDisp();
  bool update_MissionFieldSkillColor();
  bool update_MemberFieldSkillLv();
  bool update_MemberFieldSkillColor();
  bool update_MissionTimeOriginal();
  bool update_MissionTimeAdjust();
  bool update_MissionFieldSkillDisp();
  bool update_MissionFieldSkillBladeMax();
  void update(const fw::UpdateInfo &info) override;

  mm::mtl::Delegate<bool()> unknown30; // Inferred role: updater; original member name unknown.
  IConverter *unknown50;               // Inferred role: converter; original member name unknown.
  u32 unknown58;                       // Inferred role: mission; original member name unknown.
  int unknown5c;                       // Inferred role: mission status; original member name unknown.
  u32 unknown60;                       // Role and original member name unknown.
  int unknown64;                       // Role and original member name unknown.
  GfMenuBladeList *unknown68;          // Inferred role: blade list; original member name unknown.
  int unknown70;                       // Inferred role: task; original member name unknown.
};

static_assert(offsetof(GfMenuMissionAdapter, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuMissionAdapter, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuMissionAdapter, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuMissionAdapter, unknown5c) == 0x5c, "");
static_assert(offsetof(GfMenuMissionAdapter, unknown60) == 0x60, "");
static_assert(offsetof(GfMenuMissionAdapter, unknown68) == 0x68, "");
static_assert(offsetof(GfMenuMissionAdapter, unknown70) == 0x70, "");
static_assert(sizeof(GfMenuMissionAdapter) == 0x78, "");

} // namespace gf
