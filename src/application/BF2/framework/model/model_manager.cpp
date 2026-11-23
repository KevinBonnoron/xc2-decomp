#include "framework/model/model_manager.h"

#include "fw/fw_model_object.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/intrusive_list.h"
#include "types.h"

namespace fw {

void ModelManager::update(const UpdateInfo &info, u32 layers) {
  for (u32 layer = 0; layer < LAYER_UNKNOWN_32; layer++) {
    if ((layers & 1 << layer) != 0) {
      mm::mtl::IntrusiveList<unknown083> &list = unknown18[layer].unknown00;
      mm::mtl::for_each(list.begin(), list.end(), [](unknown083 &object) { object.update(); });
    }
  }
}

} // namespace fw
