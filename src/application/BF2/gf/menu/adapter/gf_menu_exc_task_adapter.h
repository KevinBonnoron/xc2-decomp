#pragma once
#include <stddef.h>

#include "gf/menu/adapter/gf_menu_adapter.h"
#include "gf/menu/gf_menu_id_list.h"
#include "mm_mtl/delegate.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace ui {
class UIObjectPlugin;
} // namespace ui

namespace gf {

class GfMenuExcTaskAdapter : public GfMenuAdapter {
public:
  struct TypeInfo {
    bool (GfMenuExcTaskAdapter::*update)(u32 taskId);
    PluginSetup setup;
  };

  class IConverter {
  public:
    virtual ~IConverter() {}
    virtual void getTaskID(u32 &taskId) = 0;
    virtual void fromList() = 0;
  };

  class ListConverter : public IConverter {
  public:
    ListConverter(GfMenuIDList *list, int listIndex) : list(list), listIndex(listIndex) { list->addRef(); }
    ~ListConverter() override { mm::mtl::safeRelease(list); }
    void getTaskID(u32 &taskId) override;
    void fromList() override;

    GfMenuIDList *list;
    int listIndex;
  };

  GfMenuExcTaskAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways);
  ~GfMenuExcTaskAdapter() override;
  static GfMenuExcTaskAdapter *create(u32 handle, u32 type, u32 taskId, bool isUpdateAlways);
  bool update_Name(u32 taskId);
  static GfMenuExcTaskAdapter *createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways);
  static GfMenuExcTaskAdapter *createFromList(u32 handle, u32 type, GfMenuIDList *list, int listIndex, bool isUpdateAlways);
  void update(const fw::UpdateInfo &info) override;

  u32 taskId;
  mm::mtl::Delegate<bool(u32)> updater;
  IConverter *converter;
};

static_assert(offsetof(GfMenuExcTaskAdapter, taskId) == 0x30, "");
static_assert(offsetof(GfMenuExcTaskAdapter, updater) == 0x38, "");
static_assert(offsetof(GfMenuExcTaskAdapter, converter) == 0x58, "");
static_assert(sizeof(GfMenuExcTaskAdapter) == 0x60, "");

} // namespace gf
