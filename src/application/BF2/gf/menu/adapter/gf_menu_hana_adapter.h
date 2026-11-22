#pragma once
#include <stddef.h>

#include "gf/game/gf_game_util_hana.h"
#include "gf/menu/adapter/gf_menu_adapter.h"
#include "gf/menu/gf_menu_reference.h"
#include "mm_mtl/delegate.h"
#include "types.h"

namespace ui {
class UIObjectPlugin;
} // namespace ui

namespace gf {

class GfMenuHanaAdapter : public GfMenuAdapter {
public:
  // Inferred role: type info; original type name unknown.
  struct unknown001 {
    bool (GfMenuHanaAdapter::*update)();
    PluginSetup setup;
  };

  class IConverter {
  public:
    virtual ~IConverter() {}
    virtual u32 getHanaId() = 0;
  };

  class ReferenceIndexConverter : public IConverter {
  public:
    ReferenceIndexConverter(u32 index) : index(index) {}
    u32 getHanaId() override { return GfMenuReference::getReferenceBladeID(index); }

    u32 index;
  };

  GfMenuHanaAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways);
  ~GfMenuHanaAdapter() override;
  static GfMenuHanaAdapter *create(u32 handle, u32 type, u32 blade, bool isUpdateAlways);
  bool update_ether();
  bool update_equipPower();
  bool update_maxPower();
  bool update_roleText();
  bool update_atrText();
  bool update_atrIcon();
  bool update_bustupIcon();
  bool update_equipIcon();
  bool update_rankPower();
  bool update_maxRankPower();
  bool update_partsExpandIcon();
  bool update_equipColor();
  static GfMenuHanaAdapter *createFromReferenceIndex(u32 handle, u32 type, u32 index, bool isUpdateAlways);
  static GfMenuHanaAdapter *createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways);
  void update(const fw::UpdateInfo &info) override;
  static bool isOpenCircuit(u32 blade, u32 circuit, RESULT_HANA &result);
  static u32 getEquipParts(u32 blade, u32 type);
  static bool isEquipParts(u32 blade, u32 type, u32 parts, RESULT_HANA &result);
  static bool chkEquipPartsGroup(u32 blade, u32 type, u32 parts);
  static bool isMakeParts(u32 type, u32 parts, RESULT_HANA &result);
  static bool isCrystalParts(u32 type, u32 parts, RESULT_HANA &result);
  static int getHanaCount();
  static u32 getSortTableId(u32 type);
  static u32 getMakeSortTableId(u32 type);

  mm::mtl::Delegate<bool()> unknown30; // Inferred role: updater; original member name unknown.
  IConverter *m_iConverter;            // Inferred role: converter; original member name unknown.
  u32 unknown58;                       // Inferred role: parts type; original member name unknown.
  u32 unknown5c;                       // Inferred role: blade; original member name unknown.
};

static_assert(offsetof(GfMenuHanaAdapter, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuHanaAdapter, m_iConverter) == 0x50, "");
static_assert(offsetof(GfMenuHanaAdapter, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuHanaAdapter, unknown5c) == 0x5c, "");
static_assert(sizeof(GfMenuHanaAdapter) == 0x60, "");

} // namespace gf
