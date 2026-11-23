#pragma once
#include <stddef.h>

#include "layer/layer_base.h"
#include "layer/layer_manager.h"
#include "layer/layer_obj.h"
#include "layer/layer_obj_layout.h"
#include "layer/layer_obj_manager.h"
#include "layer/layer_obj_sort_layout.h"
#include "layer/layer_obj_top_tex_obj.h"

namespace layer {
struct LayerRenderView;

class LayerObjTopLayout : public LayerObjLayout {
public:
  LayerObjTopLayout(const void *data);
  LayerObjTopLayout();
  ~LayerObjTopLayout() override;
  void workLayoutCreate(const void *data);
  void apply(LayerSortMan *sortMan, const LayerRenderView *view) override;
  void updateFast();
  void updateDispOffLayout(LayerResUpdateInfo &info, const LayerRenderView *view);
  void updateSpace(const LayerResUpdateInfo &info);
  void updateBeginLayout(LayerResUpdateInfo &info, const LayerRenderView *view);
  void updateEndLayout(const LayerRenderView *view, LayerResUpdateInfo &info);
  void applyBegin(LayerResUpdateInfo &info, const LayerRenderView *view) override;
  void applyEnd(LayerResUpdateInfo &info, const LayerRenderView *view) override;
  void setDrawList(LayerSortMan *sortMan, bool is3D) override;
  void finalRender();
  // Inferred helper: applies the children, hands the removed ones to the object manager, then applies the render target
  // texture; original name unknown.
  void unknown001(LayerResUpdateInfo &info, const LayerRenderView *view);

  LayerObjSortLayout m_layerObjSortLayout; // Inferred role: sort object; original member name unknown.
};

static_assert(offsetof(LayerObjTopLayout, m_layerObjSortLayout) == 0x400, "");
static_assert(sizeof(LayerObjTopLayout) == 0x420, "");

// Evidence: updateBeginLayout inlines this block, while apply and applyBegin call updateDispOffLayout, which holds the
// same block, out of line: clang 3.9 only gives the inline hint to a function declared with the inline keyword.
inline void LayerObjTopLayout::unknown001(LayerResUpdateInfo &info, const LayerRenderView *view) {
  LayerBase *node = unknown258.unknown00;
  while (node != nullptr) {
    LayerBase *next = node->unknown10;
    LayerObj *obj = static_cast<LayerObj *>(node);
    if (obj->getStateFlags(LayerManager::s_nDebIdx) & 0x1) {
      unknown258.unknown004(node);
      LayerManager::get()->m_layerObjManager->setDeleteList(obj);
    } else {
      obj->applyBegin(info, view);
    }
    node = next;
  }
  if (unknown2a0.unknown118.unknown00 & 0x4) {
    unknown2a0.unknown118.m_layerObjTopTexObj->applyBegin(info, view);
  }
}

} // namespace layer
