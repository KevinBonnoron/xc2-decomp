#include "dr/dr_res_mdo_seam_wrk_base_vertex.h"

#include "dr/dr_res_mdo_seam_res.h"
#include "dr/dr_res_mdo_vertex.h"

namespace ml {

DrResMdoSeamWrkBaseVertex::DrResMdoSeamWrkBaseVertex() : unknown00(nullptr), unknown08(nullptr) {}

void DrResMdoSeamWrkBaseVertex::release() {
  DrResMdoVertex *vertex = unknown08;
  if (vertex != nullptr) {
    vertex->vertexRelease();
    ::operator delete(vertex);
    unknown08 = nullptr;
  }
  unknown00 = nullptr;
}

void DrResMdoSeamWrkBaseVertex::changeMemVertex() { unknown08->changeMemVertex(unknown00->m_buffer); }

} // namespace ml
