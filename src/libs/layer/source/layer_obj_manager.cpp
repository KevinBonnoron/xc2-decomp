#include "layer/layer_obj_manager.h"

#include "layer/layer_manager.h"
#include "layer/layer_obj.h"
#include "layer/layer_sort_man.h"

namespace layer {

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
  delete unknown10;
  unknown10 = nullptr;
}

} // namespace layer
