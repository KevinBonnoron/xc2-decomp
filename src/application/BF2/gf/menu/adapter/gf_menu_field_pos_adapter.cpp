#include "gf/menu/adapter/gf_menu_field_pos_adapter.h"

#include "gf/gf_allocator.h"
#include "gf/util/gf_util.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/rtti.h"
#include "ui/plugin/ui_object_pos_plugin.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_util.h"

namespace gf {

constexpr s16 HIDDEN_POS = 10000;

GfMenuFieldPosAdapter::GfMenuFieldPosAdapter(ui::UIObjectPlugin *plugin)
    : GfMenuAdapter(plugin, false, true), isOutOfScreen(false), handle(0), isFirstUpdate(true) {}

GfMenuFieldPosAdapter::~GfMenuFieldPosAdapter() {
  // A body that is not empty keeps the vtable pointer store that the game does.
  ;
}

GfMenuFieldPosAdapter *GfMenuFieldPosAdapter::create(u32 handle, const mm::Vec3 &pos) {
  ui::UIObjectPosPlugin *plugin = ui::UIObjectPosPlugin::create(handle, 0, 0);
  if (plugin != nullptr) {
    // __LINE__ must be 51 as in the original source: it is the line argument of operator new.
#line 51
    GfMenuFieldPosAdapter *adapter = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuFieldPosAdapter(plugin);
    if (adapter != nullptr) {
      adapter->pos = pos;
      adapter->handle = handle;
      adapter->isOutOfScreen = false;
      adapter->isFirstUpdate = true;
    }
    plugin->release();
    return adapter;
  }
  return nullptr;
}

void GfMenuFieldPosAdapter::update(const fw::UpdateInfo &info) {
  ui::UIObjectPosPlugin *posPlugin = static_cast<ui::UIObjectPosPlugin *>(plugin);
  if (posPlugin == nullptr || !posPlugin->getRTTI()->isKindOf(&ui::UIObjectPosPlugin::m_rtti)) {
    return;
  }
  mm::Vec3 screenPos;
  if (!util::getScreenPos(screenPos, pos)) {
    return;
  }
  if (!mm::isValidFloat(screenPos.x) || !mm::isValidFloat(screenPos.y)) {
    return;
  }
  mm::Pnt<s16> point(screenPos.x, screenPos.y);
  if (!isOutOfScreen) {
    ui::UIObjectAcc acc(handle);
    if (acc.isValid()) {
      if (isFirstUpdate) {
        point.x = HIDDEN_POS;
        point.y = HIDDEN_POS;
        isFirstUpdate = false;
      } else {
        mm::Rect<s16> rect;
        acc.getRect(rect, 2);
        rect.x = point.x - rect.width / 2;
        rect.y = point.y - rect.height / 2;
        if (ui::UIUtil::adjustScreen(rect)) {
          point.x = rect.x + rect.width / 2;
          point.y = rect.y + rect.height / 2;
        } else {
          isOutOfScreen = true;
        }
      }
    }
  }
  posPlugin->pos.x = point.x;
  posPlugin->pos.y = point.y;
}

} // namespace gf
