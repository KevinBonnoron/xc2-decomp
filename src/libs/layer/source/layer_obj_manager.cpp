#include "layer/layer_obj_manager.h"

#include "dr/dr_draw_work_info.h"
#include "layer/layer_manager.h"
#include "layer/layer_obj.h"
#include "layer/layer_obj_top_def.h"
#include "layer/layer_obj_top_filter.h"
#include "layer/layer_obj_top_font.h"
#include "layer/layer_obj_top_layout.h"
#include "layer/layer_obj_top_mask_obj.h"
#include "layer/layer_obj_top_mem_obj.h"
#include "layer/layer_obj_top_poly_obj.h"
#include "layer/layer_obj_top_tex_obj.h"
#include "layer/layer_sort_man.h"
#include "ml/critical_section.h"
#include "mtl/alloc_handle.h"

namespace layer {

namespace {

struct unknown001 {
  u32 unknown00; // Inferred role: magic; original member name unknown.
  u32 unknown04; // Inferred role: version; original member name unknown.
};

} // namespace

LayerBase *LayerObjManager::createStaticTexObj(const grlib::CGLibTextureBuffer &texture) { return new (LayerManager::get()->unknown28) LayerObjTopTexObj(&texture); }

ml::CriticalSection &LayerObjManager::getCriticalSection() {
  static ml::CriticalSection sect;
  return sect;
}

LayerBase *LayerObjManager::createStaticMaskObj(const void *data) {
  const unknown001 *header = static_cast<const unknown001 *>(data);
  if (header->unknown00 == 0x4448414c && header->unknown04 == 0x2711) {
    return new (LayerManager::get()->unknown28) LayerObjTopMaskObj(data);
  }
  return nullptr;
}

LayerBase *LayerObjManager::createStaticObj(const void *data) {
  const unknown001 *header = static_cast<const unknown001 *>(data);
  if (header->unknown00 == 0x4448414c && header->unknown04 == 0x2711) {
    return new (LayerManager::get()->unknown28) LayerObjTopDef(data);
  }
  if (header->unknown00 == 0x5350414c && header->unknown04 == 0x2711) {
    return new (LayerManager::get()->unknown28) LayerObjTopLayout(data);
  }
  return nullptr;
}

LayerBase *LayerObjManager::createObj(const void *data) {
  ml::CS lock(getCriticalSection());
  LayerBase *object = createStaticObj(data);
  unknown30[LayerManager::s_nStkIdx].unknown002(object);
  return object;
}

LayerBase *LayerObjManager::createMaskObj(const void *data) {
  ml::CS lock(getCriticalSection());
  LayerBase *object = createStaticMaskObj(data);
  unknown30[LayerManager::s_nStkIdx].unknown002(object);
  return object;
}

LayerBase *LayerObjManager::createLayoutObj() {
  ml::CS lock(getCriticalSection());
  LayerBase *object = createStaticLayoutObj();
  unknown30[LayerManager::s_nStkIdx].unknown002(object);
  return object;
}

LayerBase *LayerObjManager::createStaticLayoutObj() { return new (LayerManager::get()->unknown28) LayerObjTopLayout(); }

LayerBase *LayerObjManager::createFontObj() {
  ml::CS lock(getCriticalSection());
  LayerBase *object = createStaticFontObj();
  unknown30[LayerManager::s_nStkIdx].unknown002(object);
  return object;
}

LayerBase *LayerObjManager::createStaticFontObj() { return new (LayerManager::get()->unknown28) LayerObjTopFont(); }

LayerBase *LayerObjManager::createTexObj(const grlib::CGLibTextureBuffer &texture) {
  ml::CS lock(getCriticalSection());
  LayerBase *object = createStaticTexObj(texture);
  unknown30[LayerManager::s_nStkIdx].unknown002(object);
  return object;
}

LayerBase *LayerObjManager::createMemObj(u32 width, u32 height, LayerMemType type) {
  ml::CS lock(getCriticalSection());
  LayerBase *object = createStaticMemObj(width, height, type);
  unknown30[LayerManager::s_nStkIdx].unknown002(object);
  return object;
}

LayerBase *LayerObjManager::createStaticMemObj(u32 width, u32 height, LayerMemType type) { return new (LayerManager::get()->unknown28) LayerObjTopMemObj(width, height, type); }

LayerBase *LayerObjManager::createPolyObj(u32 width, u32 height, u16 vertexNum, u16 indexNum, LayerPrimitiveType type) {
  ml::CS lock(getCriticalSection());
  LayerBase *object = createStaticPolyObj(width, height, vertexNum, indexNum, type);
  unknown30[LayerManager::s_nStkIdx].unknown002(object);
  return object;
}

LayerBase *LayerObjManager::createStaticPolyObj(u32 width, u32 height, u16 vertexNum, u16 indexNum, LayerPrimitiveType type) {
  return new (LayerManager::get()->unknown28) LayerObjTopPolyObj(width, height, vertexNum, indexNum, type);
}

LayerBase *LayerObjManager::createFilterObj() {
  ml::CS lock(getCriticalSection());
  LayerBase *object = createStaticFilterObj();
  unknown30[LayerManager::s_nStkIdx].unknown002(object);
  return object;
}

LayerBase *LayerObjManager::createStaticFilterObj() { return new (LayerManager::get()->unknown28) LayerObjTopFilter(); }

void LayerObjManager::alphaRender(const ml::IDrDrawWorkInfo *info) {
  unknown00 = info;
  m_layerSortMan->alphaRender();
}

void LayerObjManager::lastRender(const ml::IDrDrawWorkInfo *info) {
  unknown00 = info;
  m_layerSortMan->lastRender();
}

void LayerObjManager::finalRender(const ml::IDrDrawWorkInfo *info) {
  unknown00 = info;
  m_layerSortMan->finalRender();
}

void LayerObjManager::end() {}

void LayerObjManager::setDeleteList(LayerObj *object) { unknown60.unknown002(object); }

void LayerObjManager::begin() {
  unknown60.unknown003();
  LayerBase *node = unknown30[LayerManager::s_nDebIdx].unknown00;
  while (node != nullptr) {
    LayerBase *next = node->unknown10;
    unknown30[LayerManager::s_nDebIdx].unknown004(node);
    static_cast<LayerObj *>(node)->resourceInit();
    unknown18.unknown002(node);
    node = next;
  }
  unknown30[LayerManager::s_nDebIdx].unknown10 = 0;
  unknown30[LayerManager::s_nDebIdx].unknown00 = nullptr;
  unknown30[LayerManager::s_nDebIdx].unknown08 = nullptr;

  node = unknown18.unknown00;
  while (node != nullptr) {
    LayerBase *next = node->unknown10;
    if (static_cast<LayerObj *>(node)->getStateFlags(LayerManager::s_nDebIdx) & 1) {
      unknown18.unknown004(node);
      unknown60.unknown002(node);
    }
    node = next;
  }
}

void LayerObjManager::apply(const ml::IDrDrawWorkInfo *info) {
  unknown00 = info;
  m_layerRenderView.unknown10 = 0;
  m_layerRenderView.m_layerResViewPortInfo = nullptr;
  m_layerSortMan->begin(info->unknownb0);
  LayerBase *node = unknown18.unknown00;
  while (node != nullptr) {
    LayerBase *next = node->unknown10;
    static_cast<LayerObj *>(node)->apply(m_layerSortMan, &m_layerRenderView);
    node = next;
  }
  m_layerSortMan->end();
}

void LayerObjManager::allRelease() {
  unknown18.unknown003();
  unknown30[0].unknown003();
  unknown30[1].unknown003();
  unknown60.unknown003();
}

LayerObjManager::LayerObjManager(LayerManager *manager) {
  m_layerManager = manager;
  m_layerSortMan = nullptr;
  unknown18.unknown10 = 0;
  unknown60.unknown10 = 0;
  unknown18.unknown00 = nullptr;
  unknown18.unknown08 = nullptr;
  unknown60.unknown00 = nullptr;
  unknown60.unknown08 = nullptr;
  m_layerSortMan = new (manager->unknown28) LayerSortMan(m_layerManager, 0x200, 0x100);
}

LayerObjManager::~LayerObjManager() {
  allRelease();
  if (m_layerSortMan != nullptr) {
    delete m_layerSortMan;
    m_layerSortMan = nullptr;
  }
}

} // namespace layer
