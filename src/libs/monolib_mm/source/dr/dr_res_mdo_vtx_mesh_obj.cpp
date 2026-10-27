#include "dr/dr_res_mdo_vtx_mesh_obj.h"

#include "dr/dr_res_mdo_vertex.h"
#include "grlib/cglib_vtx_vertex.h"
#include "mtl/mem_manager.h"

namespace ml {

void DrResMdoVtxMeshObj::resourceInit(DrResMdoVertex *vertex) {
  DrResUniformVertex *uniformVertex = vertex->unknown70;
  unknown00 = uniformVertex->unknown00;
  unknown08 = uniformVertex->unknown08;
  unknown80 = unknown00->unknown08;
}

void DrResMdoVtxMeshObj::releaseWork() {
  unknown10.release();
  unknown38.release();
  if (unknown78 != nullptr) {
    mtl::MemManager::deallocate(unknown78, 0, false);
    unknown78 = nullptr;
  }
}

bool DrResMdoVtxMeshObj::isRender() const {
  if (!(unknown74 & 1)) {
    return false;
  }
  if (unknown8c == 0 && unknown94 == 0) {
    return false;
  }
  return true;
}

u32 DrResMdoVtxMeshObj::setup(const u8 *, u8 *) { return 0x140; }

u32 DrResMdoVtxMeshObj::calcWorkSize(const u8 *) { return 0x140; }

} // namespace ml
