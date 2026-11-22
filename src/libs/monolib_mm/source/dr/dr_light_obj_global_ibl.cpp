#include "dr/dr_light_obj_global_ibl.h"

#include <math.h>

#include "dr/dr_calc_clip_work_view_plane.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_res_use_query_obj.h"
#include "grlib/cglib_ctl_vertex.h"
#include "mm_math/mm_math.h"

namespace ml {
class DrPixlOccQuery;

DrLightObjGlobalIBL::DrLightObjGlobalIBL()
    : m_drGlobalIBLPack(nullptr), m_version(0), unknown10(0), unknown18(0), unknown48(0.0f), unknown50(mm::Vec3::zero), unknown60(mm::Vec3::zero), unknown70(0), unknown390(mm::Vec3::zero),
      unknown3b8(0), unknown3c0(0), unknown3c4(false) {
  unknown20.clear();
  for (int i = 0; i < SH_TERM_UNKNOWN_4; i++) {
    unknown410[i] = mm::Vec4::zero;
  }
}

DrLightObjGlobalIBL::~DrLightObjGlobalIBL() {
  for (u32 i = 0; i < unknown20.size(); i++) {
    MeshData &mesh = unknown20[i];
    mesh.m_cGLibVtxVertex.release();
    mesh.m_cGLibVtxIndex.release();
    if (mesh.m_drResUseQueryObj != nullptr) {
      delete mesh.m_drResUseQueryObj;
      mesh.m_drResUseQueryObj = nullptr;
    }
  }
}

int DrLightObjGlobalIBL::getPriority() const { return m_priority; }

void DrLightObjGlobalIBL::bindVertex(u32 index) {
  unknown70 = index;
  grlib::CGLibCtlVertex::setVertex(unknown20[index].m_cGLibVtxVertex);
}

void DrLightObjGlobalIBL::drawVertex() { unknown20[unknown70].m_cGLibVtxIndex.drawIndex(); }

void DrLightObjGlobalIBL::beginOccQuery() {
  DrPixlOccQuery *occQuery = DrMan::getIns()->m_drPixlMan->m_drPixlOccQuery;
  unknown20[unknown70].m_drResUseQueryObj->begin(occQuery);
}

void DrLightObjGlobalIBL::endOccQuery() { unknown20[unknown70].m_drResUseQueryObj->end(); }

void DrLightObjGlobalIBL::update() {
  unknown3c0 = 0;
  for (u32 i = 0; i < unknown20.size(); i++) {
    unknown20[i].m_drResUseQueryObj->update();
    unknown3c0 += unknown20[i].m_drResUseQueryObj->m_pixel;
  }
  DrCalcViewWork *view = DrMan::getIns()->m_drCalcMan->m_drCalcViewWork;
  mm::Vec3 center((unknown50.x + unknown60.x) * 0.5f, (unknown50.y + unknown60.y) * 0.5f, (unknown50.z + unknown60.z) * 0.5f);
  bool isVisible = false;
  if (view->m_drCalcClipWorkViewPlane.clipTest(center, unknown48)) {
    for (MeshData &mesh : unknown20) {
      bool isClipped = view->m_drCalcClipWorkViewPlane.clipTest(mesh.unknown100, mesh.unknownd0);
      mesh.unknown118 = isClipped;
      isVisible = isVisible || isClipped;
      // The game computes the three differences before it squares them (0x71007da36c to 0x71007da390).
      mm::Vec3 difference = view->unknown400 - mesh.unknown100;
      f32 distance = sqrtf(difference.x * difference.x + difference.y * difference.y + difference.z * difference.z);
      f32 sine = sinf(view->unknown4c4 * 0.5f);
      f32 aspect = sine * view->unknown4c0;
      f32 margin = sqrtf(aspect * aspect + 1.0f + sine * sine);
      // The game multiplies by the view distance (fmul at 0x71007da408) before it loads the radius of the mesh (ldr at 0x71007da40c).
      f32 reach = margin * view->unknown4c8;
      mesh.unknown119 = mesh.unknown118 && distance <= mesh.unknownd0 + reach + 0.01f;
    }
  }
  unknown3c4 = isVisible;
  for (MeshData &mesh : unknown20) {
    mm::Vec3 offset = mesh.unknown100 - view->unknown400;
    mesh.unknown140.w = offset.x * view->unknown410.x + offset.y * view->unknown410.y + offset.z * view->unknown410.z + mesh.unknownd0 + 0.01f;
  }
}

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
