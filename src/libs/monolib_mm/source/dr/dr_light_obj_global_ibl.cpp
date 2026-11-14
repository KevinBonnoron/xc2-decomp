#include "dr/dr_light_obj_global_ibl.h"

#include "mm_math/mm_math.h"

#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_res_use_query_obj.h"
#include "grlib/cglib_ctl_vertex.h"

namespace ml {
class DrPixlOccQuery;

DrLightObjGlobalIBL::DrLightObjGlobalIBL()
    : unknown00(nullptr), unknown08(0), unknown10(0), unknown18(0), unknown48(0.0f), unknown50(mm::Vec3::zero), unknown60(mm::Vec3::zero), unknown70(0), unknown390(mm::Vec3::zero), unknown3b8(0),
      unknown3c0(0), unknown3c4(false) {
  unknown20.clear();
  for (int i = 0; i < SH_TERM_UNKNOWN_4; i++) {
    unknown410[i] = mm::Vec4::zero;
  }
}

DrLightObjGlobalIBL::~DrLightObjGlobalIBL() {
  for (u32 i = 0; i < unknown20.size(); i++) {
    MeshData &mesh = unknown20[i];
    mesh.unknown00.release();
    mesh.unknown28.release();
    if (mesh.unknown110 != nullptr) {
      delete mesh.unknown110;
      mesh.unknown110 = nullptr;
    }
  }
}

int DrLightObjGlobalIBL::getPriority() const { return m_priority; }

void DrLightObjGlobalIBL::bindVertex(u32 index) {
  unknown70 = index;
  grlib::CGLibCtlVertex::setVertex(unknown20[index].unknown00);
}

void DrLightObjGlobalIBL::drawVertex() { unknown20[unknown70].unknown28.drawIndex(); }

void DrLightObjGlobalIBL::beginOccQuery() {
  DrPixlOccQuery *occQuery = DrMan::getIns()->unknown78->unknown7f8;
  unknown20[unknown70].unknown110->begin(occQuery);
}

void DrLightObjGlobalIBL::endOccQuery() { unknown20[unknown70].unknown110->end(); }

f32 DrLightObjGlobalIBL::calcSimilarity(const DrLightObjGlobalIBL &other) const {
  f32 similarity = 0.0f;
  for (int i = 0; i < SH_TERM_UNKNOWN_4; i++) {
    similarity += mm::fabs(unknown410[i].x - other.unknown410[i].x);
    similarity += mm::fabs(unknown410[i].y - other.unknown410[i].y);
    similarity += mm::fabs(unknown410[i].z - other.unknown410[i].z);
    similarity += mm::fabs(unknown410[i].w - other.unknown410[i].w);
  }
  return similarity;
}

} // namespace ml

template void mm::mtl::Vector<ml::DrLightObjGlobalIBL *>::extend(size_t, size_t);
template void mm::mtl::Vector<ml::DrLightObjGlobalIBL *>::resize(size_t);
template void mm::mtl::Vector<ml::DrLightObjGlobalIBL::MeshData>::extend(size_t, size_t);
template void mm::mtl::Vector<ml::DrLightObjGlobalIBL::MeshData>::resize(size_t);
template void mm::mtl::Vector<ml::DrLightObjGlobalIBL::MeshData>::destroy();
