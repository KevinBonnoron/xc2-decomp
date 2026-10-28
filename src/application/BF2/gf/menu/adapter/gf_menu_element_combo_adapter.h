#pragma once
#include <stddef.h>

#include "gf/menu/adapter/gf_menu_adapter.h"
#include "mm_mtl/delegate.h"
#include "types.h"

namespace ui {
class UIObjectPlugin;
} // namespace ui

namespace gf {

class GfObjPropertyEnemy;

class GfMenuElementComboAdapter : public GfMenuAdapter {
public:
  class IConverter {
  public:
    virtual ~IConverter() {}
    virtual u32 getElementComboRouteNo() = 0;
    virtual u32 getElementComboId() = 0;
  };

  class ReferenceRouteConverter : public IConverter {
  public:
    ReferenceRouteConverter(u32 routeNo) : routeNo(routeNo) {}
    ~ReferenceRouteConverter() override {}
    u32 getElementComboRouteNo() override;
    u32 getElementComboId() override;

    u32 routeNo;
  };

  class TargetEnemyConverter : public IConverter {
  public:
    ~TargetEnemyConverter() override {}
    u32 getElementComboRouteNo() override;
    u32 getElementComboId() override;
  };

  GfMenuElementComboAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways);
  ~GfMenuElementComboAdapter() override;
  bool update_ComboRouteColor();
  bool update_ComboRouteIcon();
  bool update_ComboRouteEffectName();
  bool update_ComboRouteEffect();
  bool update_ComboRouteAttrPtn();
  bool update_ComboRouteCurrentDisp();
  static GfObjPropertyEnemy *getTargetProperty();
  static u32 getTargetElementComboId();
  static u32 getTargetElementComboLv();
  void update(const fw::UpdateInfo &info) override;

  mm::mtl::Delegate<bool()> unknown30; // Inferred role: updater; original member name unknown.
  u32 unknown50;                       // Inferred role: element combo; original member name unknown.
  int unknown54;                       // Inferred role: element combo route number; original member name unknown.
  IConverter *unknown58;               // Inferred role: converter; original member name unknown.
};

static_assert(offsetof(GfMenuElementComboAdapter, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuElementComboAdapter, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuElementComboAdapter, unknown54) == 0x54, "");
static_assert(offsetof(GfMenuElementComboAdapter, unknown58) == 0x58, "");
static_assert(sizeof(GfMenuElementComboAdapter) == 0x60, "");

} // namespace gf
