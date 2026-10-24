#pragma once
#include <stddef.h>

#include "gf/menu/adapter/gf_menu_adapter.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/list/gf_menu_field_skill_list.h"
#include "mm_mtl/delegate.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace ui {
class UIObjectPlugin;
} // namespace ui

namespace gf {

class GfMenuFieldSkillAdapter : public GfMenuAdapter {
public:
  struct TypeInfo {
    bool (GfMenuFieldSkillAdapter::*update)(const MenuFieldSkill &fieldSkill);
    PluginSetup setup;
  };

  class IConverter {
  public:
    virtual ~IConverter() {}
    virtual void getFieldSkill(MenuFieldSkill &fieldSkill) = 0;
  };

  class BladeConverter : public IConverter {
  public:
    BladeConverter(u32 blade, u32 slot) : blade(blade), slot(slot) {}
    void getFieldSkill(MenuFieldSkill &fieldSkill) override;

    u32 blade;
    u32 slot;
  };

  class ListConverter : public IConverter {
  public:
    ListConverter(GfMenuFieldSkillList *list, int listIndex) : list(list), listIndex(listIndex) { list->addRef(); }
    ~ListConverter() override { mm::mtl::safeRelease(list); }
    void getFieldSkill(MenuFieldSkill &fieldSkill) override;

    GfMenuFieldSkillList *list;
    int listIndex;
  };

  class ReferenceConverter : public IConverter {
  public:
    ReferenceConverter(mm::mtl::IntrusivePtr<GfMenuReferenceFs> reference) : reference(reference) {}
    ~ReferenceConverter() override { reference = nullptr; }
    void getFieldSkill(MenuFieldSkill &fieldSkill) override;

    mm::mtl::IntrusivePtr<GfMenuReferenceFs> reference;
  };

  GfMenuFieldSkillAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways);
  ~GfMenuFieldSkillAdapter() override;
  static GfMenuFieldSkillAdapter *create(u32 handle, u32 type, const MenuFieldSkill &fieldSkill);
  bool update_Name(const MenuFieldSkill &fieldSkill);
  bool update_Lv(const MenuFieldSkill &fieldSkill);
  static GfMenuFieldSkillAdapter *createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways);
  static GfMenuFieldSkillAdapter *createFromBlade(u32 handle, u32 type, u32 blade, u32 option);
  static GfMenuFieldSkillAdapter *createFromList(u32 handle, u32 type, GfMenuFieldSkillList *list, int listIndex);
  static GfMenuFieldSkillAdapter *createFromReference(u32 handle, u32 type, mm::mtl::IntrusivePtr<GfMenuReferenceFs> reference);
  void update(const fw::UpdateInfo &info) override;

  mm::mtl::Delegate<bool(const MenuFieldSkill &)> unknown30; // Inferred role: updater; original member name unknown.
  IConverter *unknown50;                                     // Inferred role: converter; original member name unknown.
  MenuFieldSkill unknown58;                                  // Inferred role: field skill; original member name unknown.
};

static_assert(offsetof(GfMenuFieldSkillAdapter, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuFieldSkillAdapter, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuFieldSkillAdapter, unknown58) == 0x58, "");
static_assert(sizeof(GfMenuFieldSkillAdapter) == 0x60, "");

} // namespace gf
