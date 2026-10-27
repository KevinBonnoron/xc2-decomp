#include "dr/dr_res_mdo_seam_wrk_base.h"

#include <string.h>

#include "dr/dr_mdo_mat.h"
#include "dr/dr_res_mdo_seam_wrk_base_vertex.h"
#include "dr/dr_res_mdo_vertex.h"

namespace ml {

void DrResMdoSeamWrkBase::beginBaseMapRenderList() {
  unknown94 = 0;
  unknown170 = 0;
  unknown8c = 0;
  unknown90 = 0;
  memset(unknown110, 0, unknown174);
}

void DrResMdoSeamWrkBase::callShadowCacheBaseUpdate(u64 mask) {
  for (int i = 0; i < 0x24; i++) {
    if ((1ull << i) & mask) {
      memset(unknownf0[i], 0, unknownf8);
    }
  }
  unknown98 &= ~mask;
}

void DrResMdoSeamWrkBase::beginRender() {
  unknown178 = -1;
  unknown68->unknownc8 = nullptr;
}

void DrResMdoSeamWrkBase::endRender() { unknown68->unknownc8 = nullptr; }

void DrResMdoSeamWrkBase::selectVertex(int index) {
  if (unknown178 != index) {
    unknown68->unknownc8 = unknown78[index].unknown08;
    unknown68->unknownc8->unknown4e = -1;
    unknown178 = index;
  }
}

} // namespace ml
