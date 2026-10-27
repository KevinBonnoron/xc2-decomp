#include "layer/layer_obj_sort_def.h"
#include "layer/layer_obj_sort_filter.h"
#include "layer/layer_obj_sort_font.h"
#include "layer/layer_obj_sort_poly_obj.h"
#include "layer/layer_obj_sort_tex_obj.h"
#include "layer/layer_obj_top_def.h"
#include "layer/layer_obj_top_filter.h"
#include "layer/layer_obj_top_font.h"
#include "layer/layer_obj_top_poly_obj.h"
#include "layer/layer_obj_top_tex_obj.h"

namespace layer {

void LayerObjSortDef::finalRender() { unknown10->finalRender(); }

void LayerObjSortFont::finalRender() { unknown10->finalRender(); }

void LayerObjSortTexObj::finalRender() { unknown10->finalRender(); }

void LayerObjSortPolyObj::finalRender() { unknown10->finalRender(); }

void LayerObjSortFilter::finalRender() { unknown10->finalRender(); }

} // namespace layer
