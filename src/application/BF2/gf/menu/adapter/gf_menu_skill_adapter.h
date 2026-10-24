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

class GfMenuSkillAdapter : public GfMenuAdapter {
public:
  struct TypeInfo {
    bool (GfMenuSkillAdapter::*update)();
    PluginSetup setup;
  };

  class IConverter {
  public:
    virtual ~IConverter() {}
    virtual u32 getDriverId() = 0;
    virtual u32 getKizunaLine() = 0;
    virtual u32 getKizunaLevel() = 0;
    virtual u32 getRound() = 0;
  };

  class ReferenceDriverConverter : public IConverter {
  public:
    ReferenceDriverConverter(u32 driverIndex, u32 line, u32 level, u32 roundIndex) : driverIndex(driverIndex), line(line), level(level), roundIndex(roundIndex) {}
    u32 getDriverId() override { return GfMenuReference::getReferenceDriverID(driverIndex); }
    u32 getKizunaLine() override { return line; }
    u32 getKizunaLevel() override { return level; }
    u32 getRound() override { return GfMenuReference::getReferenceNumber(roundIndex); }

    u32 driverIndex;
    u32 line;
    u32 level;
    u32 roundIndex;
  };

  class ReferenceDriverLineLevelConverter : public IConverter {
  public:
    ReferenceDriverLineLevelConverter(u32 driverIndex, u32 lineIndex, u32 levelIndex, u32 roundIndex)
        : driverIndex(driverIndex), lineIndex(lineIndex), levelIndex(levelIndex), roundIndex(roundIndex) {}
    u32 getDriverId() override { return GfMenuReference::getReferenceDriverID(driverIndex); }
    u32 getKizunaLine() override { return GfMenuReference::getReferenceNumber(lineIndex); }
    u32 getKizunaLevel() override { return GfMenuReference::getReferenceNumber(levelIndex); }
    u32 getRound() override { return GfMenuReference::getReferenceNumber(roundIndex); }

    u32 driverIndex;
    u32 lineIndex;
    u32 levelIndex;
    u32 roundIndex;
  };

  GfMenuSkillAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways);
  ~GfMenuSkillAdapter() override;
  static GfMenuSkillAdapter *create(u32 handle, u32 type, u32 driver, u16 line, u16 level, u16 round, bool isUpdateAlways);
  bool update_SkillName();
  bool update_SkillCaption();
  bool update_SkillPoint();
  bool update_SkillReleaseFlagIcon();
  bool update_SkillReleaseFlagColor();
  bool update_SkillReleaseFlagColorIcon();
  bool update_SkillLearnDisp();
  bool update_SkillLevelLockIcon();
  bool update_SkillLearnNum();
  bool update_SkillLearnMax();
  bool update_SkillLevelUnlockNum();
  static GfMenuSkillAdapter *createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways);
  static GfMenuSkillAdapter *createFromReferenceDriver(u32 handle, u32 type, u32 driverIndex, u16 line, u16 level, u16 roundIndex, bool isUpdateAlways);
  static GfMenuSkillAdapter *createFromReferenceDriverLineLevel(u32 handle, u32 type, u32 driverIndex, u16 lineIndex, u16 levelIndex, u16 roundIndex, bool isUpdateAlways);
  void update(const fw::UpdateInfo &info) override;

  mm::mtl::Delegate<bool()> unknown30; // Inferred role: updater; original member name unknown.
  IConverter *unknown50;               // Inferred role: converter; original member name unknown.
  u8 _58[0x5c - 0x58];
  u32 unknown5c; // Inferred role: driver; original member name unknown.
  u32 unknown60; // Inferred role: line; original member name unknown.
  u32 unknown64; // Inferred role: level; original member name unknown.
  u32 unknown68; // Inferred role: round; original member name unknown.
};

static_assert(offsetof(GfMenuSkillAdapter, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuSkillAdapter, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuSkillAdapter, unknown5c) == 0x5c, "");
static_assert(offsetof(GfMenuSkillAdapter, unknown60) == 0x60, "");
static_assert(offsetof(GfMenuSkillAdapter, unknown64) == 0x64, "");
static_assert(offsetof(GfMenuSkillAdapter, unknown68) == 0x68, "");
static_assert(sizeof(GfMenuSkillAdapter) == 0x70, "");

} // namespace gf
