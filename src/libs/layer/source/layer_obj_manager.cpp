#include "layer/layer_obj_manager.h"

#include "layer/layer_manager.h"
#include "layer/layer_obj.h"
#include "layer/layer_obj_top_mask_obj.h"
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

void LayerObjManager::alphaRender(const ml::IDrDrawWorkInfo *info) {
  unknown00 = info;
  unknown10->alphaRender();
}

void LayerObjManager::lastRender(const ml::IDrDrawWorkInfo *info) {
  unknown00 = info;
  unknown10->lastRender();
}

void LayerObjManager::finalRender(const ml::IDrDrawWorkInfo *info) {
  unknown00 = info;
  unknown10->finalRender();
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

void LayerObjManager::allRelease() {
  unknown18.unknown003();
  unknown30[0].unknown003();
  unknown30[1].unknown003();
  unknown60.unknown003();
}

LayerObjManager::~LayerObjManager() {
  allRelease();
  if (unknown10 != nullptr) {
    delete unknown10;
    unknown10 = nullptr;
  }
}

} // namespace layer
