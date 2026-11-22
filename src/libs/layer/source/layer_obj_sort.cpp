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

void LayerObjSortLayout::finalRender() { static_cast<LayerObjTopLayout *>(m_layerObj)->finalRender(); }

void LayerObjSortMemObj::finalRender() { static_cast<LayerObjTopMemObj *>(m_layerObj)->finalRender(); }

void LayerObjSortDef::finalRender() { static_cast<LayerObjTopDef *>(m_layerObj)->finalRender(); }

void LayerObjSortFont::finalRender() { static_cast<LayerObjTopFont *>(m_layerObj)->finalRender(); }

void LayerObjSortTexObj::finalRender() { static_cast<LayerObjTopTexObj *>(m_layerObj)->finalRender(); }

void LayerObjSortPolyObj::finalRender() { static_cast<LayerObjTopPolyObj *>(m_layerObj)->finalRender(); }

void LayerObjSortFilter::finalRender() { static_cast<LayerObjTopFilter *>(m_layerObj)->finalRender(); }

} // namespace layer
