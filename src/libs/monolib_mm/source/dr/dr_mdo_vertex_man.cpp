#include "dr/dr_mdo_vertex_man.h"

#include "dr/dr_calc_stm_list_obj.h"
#include "dr/dr_man.h"
#include "dr/dr_res_list.h"
#include "dr/dr_res_mdo_vertex.h"
#include "grlib/cglib_vtx_instans.h"
#include "mtl/alloc_handle.h"

namespace ml {

s32 DrMdoVertexMan::s_nInstansBuffSize = 0x600000;

DrMdoVertexMan::DrMdoVertexMan() : unknown00(nullptr), unknown08(nullptr), unknown10(nullptr) {
  unknown10 = new (DrMan::getIns()->unknown0c) grlib::CGLibVtxInstans();
  unknown10->createInstansBuffer(s_nInstansBuffSize);
}

DrMdoVertexMan::~DrMdoVertexMan() {
  DrResMdoVertex *vertex = unknown00;
  while (vertex != nullptr) {
    DrResMdoVertex *next = vertex->unknown08;
    delete vertex;
    vertex = next;
  }
  grlib::CGLibVtxInstans *instans = unknown10;
  unknown00 = nullptr;
  unknown08 = nullptr;
  if (instans != nullptr) {
    delete instans;
    unknown10 = nullptr;
  }
}

DrResMdoVertex *DrMdoVertexMan::createVertexObj(const u8 *resource) {
  for (DrResMdoVertex *vertex = unknown00; vertex != nullptr; vertex = vertex->unknown08) {
    if (vertex->unknown10 == resource) {
      vertex->unknown18++;
      return vertex;
    }
  }
  DrResMdoVertex *vertex = new (DrMan::getIns()->unknown10) DrResMdoVertex(resource);
  if (vertex != nullptr) {
    if (unknown08 == nullptr) {
      unknown00 = vertex;
      unknown08 = vertex;
      vertex->unknown00 = nullptr;
    } else {
      unknown08->unknown08 = vertex;
      vertex->unknown00 = unknown08;
      unknown08 = vertex;
    }
    vertex->unknown08 = nullptr;
  }
  return vertex;
}

DrResMdoVertex *DrMdoVertexMan::createVertexObj(DrCalcStmListObj *list) {
  for (DrResMdoVertex *vertex = unknown00; vertex != nullptr; vertex = vertex->unknown08) {
    if (reinterpret_cast<const DrCalcStmListObj *>(vertex->unknown10) == list) {
      vertex->unknown18++;
      return vertex;
    }
  }
  DrCalcStmRes *res = list->getResVertexObj();
  DrResMdoVertex *vertex = new (DrMan::getIns()->unknown10) DrResMdoVertex(res->unknown00);
  vertex->unknown78 = list;
  if (vertex != nullptr) {
    if (unknown08 == nullptr) {
      unknown00 = vertex;
      unknown08 = vertex;
      vertex->unknown00 = nullptr;
    } else {
      unknown08->unknown08 = vertex;
      vertex->unknown00 = unknown08;
      unknown08 = vertex;
    }
    vertex->unknown08 = nullptr;
  }
  return vertex;
}

void DrMdoVertexMan::releaseVertexObj(DrResMdoVertex *vertex) {
  int count = vertex->unknown18 - 1;
  if (vertex->unknown18 < 1) {
    count = 0;
  }
  vertex->unknown18 = count;
  if (count > 0) {
    return;
  }
  unknown001(unknown00, unknown08, vertex);
  delete vertex;
}

void DrMdoVertexMan::update() {
  for (DrResMdoVertex *vertex = unknown00; vertex != nullptr; vertex = vertex->unknown08) {
    vertex->update();
  }
}

void DrMdoVertexMan::begin() { unknown10->beginInstansBuff(); }

void DrMdoVertexMan::end() { unknown10->updateInstansBuff(); }

} // namespace ml
