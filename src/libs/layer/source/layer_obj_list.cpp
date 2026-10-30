#include "layer/layer_obj_list.h"

#include "layer/layer_manager.h"
#include "layer/layer_obj.h"
#include "types.h"

namespace layer {

LayerObjList::LayerObjList() {
  unknown258.unknown00 = nullptr;
  unknown258.unknown08 = nullptr;
  unknown258.unknown10 = 0;
  for (s32 i = 0; i < 2; i++) {
    unknown270[i].unknown00 = nullptr;
    unknown270[i].unknown08 = nullptr;
    unknown270[i].unknown10 = 0;
  }
}

void LayerObjList::workListRelease() {
  unknown258.unknown003();
  unknown270[0].unknown003();
  unknown270[1].unknown003();
}

void LayerObjList::addListInfo() {
  LayerBase *node = unknown270[LayerManager::s_nDebIdx].unknown00;
  while (node != nullptr) {
    LayerBase *next = node->unknown10;
    unknown270[LayerManager::s_nDebIdx].unknown004(node);
    static_cast<LayerObj *>(node)->resourceInit();
    unknown258.unknown002(node);
    node = next;
  }
  unknown270[LayerManager::s_nDebIdx].unknown10 = 0;
  unknown270[LayerManager::s_nDebIdx].unknown00 = nullptr;
  unknown270[LayerManager::s_nDebIdx].unknown08 = nullptr;
}

} // namespace layer
