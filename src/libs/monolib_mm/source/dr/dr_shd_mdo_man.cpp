#include "dr/dr_shd_mdo_man.h"

#include "dr/dr_res_list.h"

#include "dr/dr_calc_stm_list_obj.h"
#include "dr/dr_shd_mdo_dec_res.h"
#include "dr/dr_shd_mdo_dec_shd_obj.h"
#include "grlib/cglib_shd_list.h"
#include "grlib/cglib_vtl_mem_pool.h"
#include "types.h"

namespace ml {
struct MdsMatTechnique;

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

void DrShdMdoDecShdObj::update() {
  if (unknown20 == nullptr) {
    return;
  }
  unknown035 *res = unknown20->getResShaderObj();
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
