#include "layer/layer_obj_sort_def.h"
#include "layer/layer_obj_sort_filter.h"
#include "layer/layer_obj_sort_font.h"
#include "layer/layer_obj_sort_layout.h"
#include "layer/layer_obj_sort_mem_obj.h"
#include "layer/layer_obj_sort_poly_obj.h"
#include "layer/layer_obj_sort_tex_obj.h"
#include "layer/layer_obj_top_def.h"
#include "layer/layer_obj_top_filter.h"
#include "layer/layer_obj_top_font.h"
#include "layer/layer_obj_top_layout.h"
#include "layer/layer_obj_top_mem_obj.h"
#include "layer/layer_obj_top_poly_obj.h"
#include "layer/layer_obj_top_tex_obj.h"

namespace layer {

void LayerObjSortLayout::finalRender() { static_cast<LayerObjTopLayout *>(unknown10)->finalRender(); }

void LayerObjSortMemObj::finalRender() { static_cast<LayerObjTopMemObj *>(unknown10)->finalRender(); }

void LayerObjSortDef::finalRender() { static_cast<LayerObjTopDef *>(unknown10)->finalRender(); }

void LayerObjSortFont::finalRender() { static_cast<LayerObjTopFont *>(unknown10)->finalRender(); }

void LayerObjSortTexObj::finalRender() { static_cast<LayerObjTopTexObj *>(unknown10)->finalRender(); }

void LayerObjSortPolyObj::finalRender() { static_cast<LayerObjTopPolyObj *>(unknown10)->finalRender(); }

void LayerObjSortFilter::finalRender() { static_cast<LayerObjTopFilter *>(unknown10)->finalRender(); }

} // namespace layer
