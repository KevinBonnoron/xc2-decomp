#include "gf/menu/adapter/gf_menu_exc_task_adapter.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/list/gf_menu_id_list.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_object_plugin.h"
#include "ui/ui_str.h"

namespace gf {

static GfMenuExcTaskAdapter::TypeInfo TYPE_INFOS[] = {
    {&GfMenuExcTaskAdapter::update_Name, {GfMenuAdapter::unknown004_2, 0, 0}},
};

GfMenuExcTaskAdapter::GfMenuExcTaskAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways) : GfMenuAdapter(plugin, false, isUpdateAlways), unknown30(0), unknown58(nullptr) {}

GfMenuExcTaskAdapter::~GfMenuExcTaskAdapter() {
  if (unknown58 != nullptr) {
    delete unknown58;
    unknown58 = nullptr;
  }
}

GfMenuExcTaskAdapter *GfMenuExcTaskAdapter::create(u32 handle, u32 type, u32 taskId, bool isUpdateAlways) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    TypeInfo &info = TYPE_INFOS[type];
    ui::UIObjectPlugin *plugin = createPlugin(handle, info.setup);
    if (plugin != nullptr) {
      // __LINE__ must be 113 as in the original source: it is the line argument of operator new.
#line 113
      GfMenuExcTaskAdapter *adapter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuExcTaskAdapter(plugin, isUpdateAlways);
      adapter->unknown38.bind(adapter, info.update);
      adapter->unknown30 = taskId;
      plugin->release();
      return adapter;
    }
  }
  return nullptr;
}

bool GfMenuExcTaskAdapter::update_Name(u32 taskId) {
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_SHOP_CHANGE_TASK);
  if (!GfMenuBdat::isValidBdatID(bdat, taskId)) {
    return false;
  }
  u16 nameId = Bdat::getVal(bdat, "Name", taskId).valueU16;
  setText(ui::UIStr(GfDataBdat::getFP(BDAT_FLD_SHOPCHANGE), nameId));
  return true;
}

GfMenuExcTaskAdapter *GfMenuExcTaskAdapter::createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways) {
  u32 taskId = 0;
  converter->getTaskID(taskId);
  GfMenuExcTaskAdapter *adapter = create(handle, type, taskId, isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown58 = converter;
  }
  return adapter;
}

GfMenuExcTaskAdapter *GfMenuExcTaskAdapter::createFromList(u32 handle, u32 type, GfMenuIDList *list, int listIndex, bool isUpdateAlways) {
  // __LINE__ must be 144 as in the original source: it is the line argument of operator new.
#line 144
  ListConverter *converter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) ListConverter(list, listIndex);
  return createFromCoverter(handle, type, converter, isUpdateAlways);
}

void GfMenuExcTaskAdapter::update(const fw::UpdateInfo &info) {
  if (unknown58 != nullptr) {
    u32 newTaskId = 0;
    unknown58->getTaskID(newTaskId);
    if (unknown30 != newTaskId) {
      unknown30 = newTaskId;
      setChange();
    }
  }

  if (unknown38.isValid() && (unknown20 & (FLAG_CHANGED | FLAG_UPDATE_ALWAYS)) != 0) {
    if (unknown30 != 0) {
      setDisp(unknown38(unknown30));
    } else {
      setDisp(false);
    }
    unknown20 &= ~FLAG_CHANGED;
  }
}

void GfMenuExcTaskAdapter::ListConverter::getTaskID(u32 &taskId) {
  if (listIndex == -1) {
    taskId = list->getContents(list->getIndex(false)).unknown00;
  } else if (static_cast<u32>(listIndex) < list->getSize()) {
    taskId = list->getContents(list->getPageIndex(listIndex)).unknown00;
  }
}

void GfMenuExcTaskAdapter::ListConverter::fromList() {}

} // namespace gf
