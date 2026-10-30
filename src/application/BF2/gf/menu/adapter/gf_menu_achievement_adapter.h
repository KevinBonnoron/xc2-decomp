#pragma once
#include <stddef.h>

#include "gf/menu/adapter/gf_menu_adapter.h"
#include "gf/menu/gf_menu_reference.h"
#include "mm_mtl/delegate.h"
#include "types.h"

namespace ui {
class UIObjectPlugin;
} // namespace ui

namespace gf {

class GfMenuAchievementAdapter : public GfMenuAdapter {
public:
  // Inferred role: type info; original type name unknown.
  struct unknown001 {
    bool (GfMenuAchievementAdapter::*update)();
    PluginSetup setup;
  };

  class IConverter {
  public:
    virtual ~IConverter() {}
    virtual u32 getBladeId() = 0;
    virtual u32 getKizunaLine() = 0;
    virtual u32 getKizunaLevel() = 0;
  };

  class ReferenceBladeConverter : public IConverter {
  public:
    ReferenceBladeConverter(u32 bladeIndex, u32 line, u32 level) : bladeIndex(bladeIndex), line(line), level(level) {}
    u32 getBladeId() override { return GfMenuReference::getReferenceBladeID(bladeIndex); }
    u32 getKizunaLine() override { return line; }
    u32 getKizunaLevel() override { return level; }

    u32 bladeIndex;
    u32 line;
    u32 level;
  };

  class ReferenceBladeLineLevelConverter : public IConverter {
  public:
    ReferenceBladeLineLevelConverter(u32 bladeIndex, u32 lineIndex, u32 levelIndex) : bladeIndex(bladeIndex), lineIndex(lineIndex), levelIndex(levelIndex) {}
    u32 getBladeId() override { return GfMenuReference::getReferenceBladeID(bladeIndex); }
    u32 getKizunaLine() override { return GfMenuReference::getReferenceNumber(lineIndex); }
    u32 getKizunaLevel() override { return GfMenuReference::getReferenceNumber(levelIndex); }

    u32 bladeIndex;
    u32 lineIndex;
    u32 levelIndex;
  };

  GfMenuAchievementAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways);
  ~GfMenuAchievementAdapter() override;
  static GfMenuAchievementAdapter *create(u32 handle, u32 type, u32 blade, u16 line, u16 level, bool isUpdateAlways);
  bool update_AchievementReleaseFlagIcon();
  bool update_AchievementCategory();
  bool update_AchievementTitle();
  bool update_AchievementResult();
  bool update_AchievementIcon();
  bool update_AchievementVoiceCategory();
  bool update_AchievementVoiceAfter();
  bool update_AchievementDifficulty();
  bool update_AchievementQuest();
  bool update_AchievementSetCategory();
  bool update_AchievementSetAbilityLevel();
  bool update_AchievementTypeIcon();
  bool update_AchievementCategoryIcon();
  bool update_AchievementReleaseFlagColor();
  bool update_AchievementSkillName();
  bool update_LearnNum();
  bool update_LearnMax();
  bool update_QuestNum();
  bool update_QuestMax();
  bool update_IdeaText();
  bool update_IdeaIcon();
  bool update_QuestCaptionText();
  bool update_QuestResultText();
  bool update_KeyIcon();
  bool update_NetabareOkDisp();
  static GfMenuAchievementAdapter *createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways);
  static GfMenuAchievementAdapter *createFromReferenceBlade(u32 handle, u32 type, u32 bladeIndex, u16 line, u16 level, bool isUpdateAlways);
  static GfMenuAchievementAdapter *createFromReferenceBladeLineLevel(u32 handle, u32 type, u32 bladeIndex, u16 lineIndex, u16 levelIndex, bool isUpdateAlways);
  void update(const fw::UpdateInfo &info) override;
  bool update_AchievementReleaseFlagDisp();

  mm::mtl::Delegate<bool()> unknown30; // Inferred role: updater; original member name unknown.
  IConverter *unknown50;               // Inferred role: converter; original member name unknown.
  u32 unknown58;                       // Inferred role: disp complete; original member name unknown.
  u32 unknown5c;                       // Inferred role: blade; original member name unknown.
  u32 unknown60;                       // Inferred role: line; original member name unknown.
  u32 unknown64;                       // Inferred role: level; original member name unknown.
};

static_assert(offsetof(GfMenuAchievementAdapter, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuAchievementAdapter, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuAchievementAdapter, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuAchievementAdapter, unknown5c) == 0x5c, "");
static_assert(offsetof(GfMenuAchievementAdapter, unknown60) == 0x60, "");
static_assert(offsetof(GfMenuAchievementAdapter, unknown64) == 0x64, "");
static_assert(sizeof(GfMenuAchievementAdapter) == 0x68, "");

} // namespace gf
