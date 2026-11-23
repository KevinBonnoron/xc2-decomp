#pragma once
#include <stddef.h>

#include "layer/layer_obj_draw.h"
#include "layer/layer_obj_sort_def.h"

namespace layer {

struct LayerArgMdlRenInf;
struct LayerRenderView;

class LayerObjTopDef : public LayerObjDraw {
public:
  LayerObjTopDef(const char *name);
  LayerObjTopDef(const void *data);
  ~LayerObjTopDef() override;
  void workIconCreate();
  void resourceInit() override;
  void apply(LayerSortMan *sortMan, const LayerRenderView *view) override;
  void updateFast();
  void updateParams(LayerArgMdlRenInf &info, const LayerRenderView *view);
  void applyBegin(LayerResUpdateInfo &info, const LayerRenderView *view) override;
  void applyEnd(LayerResUpdateInfo &info, const LayerRenderView *view) override;
  void setDrawList(LayerSortMan *sortMan, bool is3D) override;
  void updateResCheck();
  void alphaRender();
  void lastRender();
  void finalRender();

  LayerObjSortDef m_layerObjSortDef; // Inferred role: sort object; original member name unknown.
};

static_assert(offsetof(LayerObjTopDef, m_layerObjSortDef) == 0x308, "");

} // namespace layer
