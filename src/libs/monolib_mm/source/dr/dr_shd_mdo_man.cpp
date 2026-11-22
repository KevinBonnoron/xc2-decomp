#include "dr/dr_shd_mdo_man.h"

#include "dr/dr_calc_stm_list_obj.h"
#include "dr/dr_man.h"
#include "dr/dr_mdo_mat.h"
#include "dr/dr_res_list.h"
#include "dr/dr_shd_man.h"
#include "dr/dr_shd_mdo_dec_res.h"
#include "dr/dr_shd_mdo_dec_shd_obj.h"
#include "grlib/cglib_shd_list.h"
#include "grlib/cglib_vtl_mem_pool.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace ml {
class DrShdFetchMan;
struct MdsMatVertexInfo;

DrShdMdoMan::DrShdMdoMan() : unknown00(nullptr), unknown08(nullptr) {}

DrShdMdoMan::~DrShdMdoMan() {
  DrShdMdoDecShdObj *obj = unknown00;
  while (obj != nullptr) {
    DrShdMdoDecShdObj *next = obj->unknown08;
    delete obj;
    obj = next;
  }
  unknown00 = nullptr;
  unknown08 = nullptr;
}

void DrShdMdoMan::update() {
  for (DrShdMdoDecShdObj *obj = unknown00; obj != nullptr; obj = obj->unknown08) {
    obj->update();
  }
}

DrShdMdoDecShdObj *DrShdMdoMan::createShaderObj(const u8 *data, const u8 *vertexData, const MdsMatTechnique *technique) {
  DrShdMdoDecShdObj *found = unknown003(unknown00, data);
  if (found != nullptr) {
    return found;
  }
  DrShdMdoDecShdObj *obj = new (DrMan::getIns()->unknown10) DrShdMdoDecShdObj(data, vertexData, technique);
  if (obj != nullptr) {
    unknown101(unknown00, unknown08, obj);
  }
  return obj;
}

DrShdMdoDecShdObj *DrShdMdoMan::createShaderObj(DrCalcStmListObj *list, const u8 *vertexData, const MdsMatTechnique *technique) {
  DrShdMdoDecShdObj *found = unknown003(unknown00, list);
  if (found != nullptr) {
    return found;
  }
  unknown035 *res = list->getResShaderObj();
  DrShdMdoDecShdObj *obj = new (DrMan::getIns()->unknown10) DrShdMdoDecShdObj(res->unknown00, vertexData, technique);
  // The game stores the list before the null test of the new object (0x71008a08b0, 0x71008a08cc, then cbz at 0x71008a08d0), as DrMdoVertexMan::createVertexObj does.
  obj->m_drCalcStmListObj = list;
  if (obj != nullptr) {
    unknown101(unknown00, unknown08, obj);
  }
  return obj;
}

void DrShdMdoMan::releaseShaderObj(DrShdMdoDecShdObj *obj) {
  obj->unknown18--;
  if (obj->unknown18 < 0) {
    obj->unknown18 = 0;
  }
  if (obj->unknown18 > 0) {
    return;
  }
  unknown001(unknown00, unknown08, obj);
  delete obj;
}

DrShdMdoDecShdObj::~DrShdMdoDecShdObj() { unknown28.release(); }

DrShdMdoDecShdObj::DrShdMdoDecShdObj(const u8 *data, const u8 *vertexData, const MdsMatTechnique *technique)
    : unknown00(nullptr), unknown08(nullptr), unknown10(data), unknown18(1), m_drCalcStmListObj(nullptr) {
  unknown28.createPacShader(data, 0, true);
  // The game calls DrMan::getIns() once, before the test of the loop (0x71008a0af4), and keeps the fetch man in x22 across the calls (0x71008a0b04, 0x71008a0b08); written in the call,
  // getIns is called again in each iteration.
  DrShdFetchMan *fetchMan = DrMan::getIns()->m_drShdMan->m_drShdFetchMan;
  for (s32 i = 0; i < unknown28.unknown50; i++) {
    unknown102(unknown28, i)->setVertexParam(fetchMan, technique[i].unknown04, static_cast<const MdsMatVertexInfo *>(static_cast<const void *>(vertexData + technique[i].unknown00)));
  }
}

void DrShdMdoDecShdObj::update() {
  if (m_drCalcStmListObj == nullptr) {
    return;
  }
  unknown035 *res = m_drCalcStmListObj->getResShaderObj();
  if (res->unknown10 & 1) {
    changeMemShader(res->unknown00, nullptr, nullptr);
  }
}

void DrShdMdoDecShdObj::changeMemShader(const u8 *data, const u8 *vertexData, const MdsMatTechnique *technique) {
  typedef grlib::CGLibShdListBase<DrShdMdoDecRes>::unknown001 Header;
  typedef grlib::CGLibShdListBase<DrShdMdoDecRes>::unknown002 Entry;
  const Header *header = reinterpret_cast<const Header *>(data);
  unknown28.unknown08 = data;
  u32 codeSize = header->unknown24;
  u32 size = (-codeSize & 0xfff) + codeSize;
  // CGLibVtlMemPool::setupBuffer takes a non-const pointer (_ZN5grlib15CGLibVtlMemPool11setupBufferEPvj).
  unknown28.unknown10.setupBuffer(const_cast<u8 *>(data) + header->unknown20, size);
  const u8 *base = static_cast<const u8 *>(unknown28.unknown08);
  const Entry *table = reinterpret_cast<const Entry *>(base + header->unknown08);
  const u8 *control = base + header->unknown28;
  const u8 *shaders = base + header->unknown18;
  for (s32 i = 0; i < unknown28.unknown50; i++) {
    unknown28.unknown40[i].changeMemPoolSetMem(shaders + table[i].unknown00, control, &unknown28.unknown10);
  }
}

} // namespace ml
