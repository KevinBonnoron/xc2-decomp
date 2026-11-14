#include "dr/irrvol.h"

#include <stddef.h>
#include <string.h>

#include "bin/bin_binary_resolver.h"
#include "dr/dr_irr_vol_allocator.h"
#include "dr/dr_irr_vol_cascade.h"
#include "dr/dr_irr_vol_res_man.h"
#include "dr/dr_irr_vol_sector.h"
#include "dr/dr_man.h"
#include "grlib/cglib_acc_util_texture.h"
#include "ml/cache_draw.h"
#include "ml/dev_file_th.h"
#include "mm_math/mm_aabb.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_math/mm_vec4.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/list.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {
class FileHandleTh;

namespace irrvol {

void convertSHMatrix(mm::Mat44 &matrix, const f32 *coefficients) {
  matrix.rows[0][0] = coefficients[8] * 0.429043f;
  matrix.rows[0][1] = coefficients[4] * 0.429043f;
  matrix.rows[0][2] = coefficients[7] * 0.429043f;
  matrix.rows[0][3] = coefficients[3] * 0.511664f;
  matrix.rows[1][0] = coefficients[4] * 0.429043f;
  matrix.rows[1][1] = coefficients[8] * -0.429043f;
  matrix.rows[1][2] = coefficients[5] * 0.429043f;
  matrix.rows[1][3] = coefficients[1] * 0.511664f;
  matrix.rows[2][0] = coefficients[7] * 0.429043f;
  matrix.rows[2][1] = coefficients[5] * 0.429043f;
  matrix.rows[2][2] = coefficients[6] * 0.743125f;
  matrix.rows[2][3] = coefficients[2] * 0.511664f;
  matrix.rows[3][0] = coefficients[3] * 0.511664f;
  matrix.rows[3][1] = coefficients[1] * 0.511664f;
  matrix.rows[3][2] = coefficients[2] * 0.511664f;
  matrix.rows[3][3] = coefficients[0] * 0.886227f + coefficients[6] * -0.247708f;
}

f32 calcIrradiance(const mm::Mat44 &matrix, const mm::Vec4 &normal) {
  mm::Vec4 result;
  result.x = normal.x * matrix.rows[0][0] + normal.y * matrix.rows[1][0] + normal.z * matrix.rows[2][0] + normal.w * matrix.rows[3][0];
  result.y = normal.x * matrix.rows[0][1] + normal.y * matrix.rows[1][1] + normal.z * matrix.rows[2][1] + normal.w * matrix.rows[3][1];
  result.z = normal.x * matrix.rows[0][2] + normal.y * matrix.rows[1][2] + normal.z * matrix.rows[2][2] + normal.w * matrix.rows[3][2];
  result.w = normal.x * matrix.rows[0][3] + normal.y * matrix.rows[1][3] + normal.z * matrix.rows[2][3] + normal.w * matrix.rows[3][3];
  return normal.x * result.x + normal.y * result.y + normal.z * result.z + normal.w * result.w;
}

void lerpSH(const f32 *from, const f32 *to, f32 ratio, f32 *result) {
  f32 inverse = 1.0f - ratio;
  for (int i = 0; i < 9; i++) {
    result[i] = inverse * from[i] + to[i] * ratio;
  }
}

float frac(float value) { return value - static_cast<int>(value); }

MemHandlebaseAllocator::MemHandlebaseAllocator() {}

MemHandlebaseAllocator::MemHandlebaseAllocator(mtl::ALLOC_HANDLE handle) : unknown08(handle) {}

void MemHandlebaseAllocator::setMemHandle(mtl::ALLOC_HANDLE handle) { unknown08 = handle; }

mtl::ALLOC_HANDLE MemHandlebaseAllocator::getMemHandle() const { return unknown08; }

void *MemHandlebaseAllocator::allocate(size_t size, size_t alignment) { return mtl::MemManager::allocate(unknown08, size, alignment, false, "no name", 0); }

void MemHandlebaseAllocator::deallocate(void *pointer) {
  if (pointer != nullptr) {
    mtl::MemManager::deallocate(pointer, 0, false);
  }
}

DrIrrVolSector::DrIrrVolSector(const SSectorInfo *sectorInfo, const SCascadeInfo *cascadeInfo) : unknown00(sectorInfo), unknown08(cascadeInfo->unknown20) {}

DrIrrVolSector::~DrIrrVolSector() {}

const SLightProbe *DrIrrVolSector::getProbe(int index) const { return unknown00->unknown40 + index; }

DrIrrVolCascade::DrIrrVolCascade(const SGlobalInfo *globalInfo, u32 index, const char *name)
    : unknown00(globalInfo), unknown08(&globalInfo->unknown28[index]), unknown10(index), unknown18(nullptr), unknown5e0(0), unknown890(nullptr) {
  mm::Vec3 size = unknown08->unknown00.max - unknown08->unknown00.min;
  unknown548 = static_cast<u32>(size.x / unknown08->unknown24 + 0.5f);
  unknown54c = static_cast<u32>(size.z / unknown08->unknown24 + 0.5f);
  memset(unknown20, 0, sizeof(unknown20));
  memset(unknown2a8, 0, sizeof(unknown2a8));
  unknown18 = new (DrMan::get()->unknown0c) DrIrrVolResMan(DrMan::get()->unknown14, unknown10, unknown548 * unknown54c, name);
}

DrIrrVolCascade::~DrIrrVolCascade() {
  for (int i = 0; i < 81; i++) {
    if (unknown20[i] != nullptr) {
      delete unknown20[i];
      unknown20[i] = nullptr;
    }
  }
  memset(unknown2a8, 0, sizeof(unknown2a8));
  if (unknown18 != nullptr) {
    delete unknown18;
    unknown18 = nullptr;
  }
}

void DrIrrVolCascade::createSector(void *buffer, u32 index) {}

// Inferred role: directions the irradiance of a global probe is evaluated for; original name unknown.
static const mm::Vec4 unknown003[4] = {
    mm::Vec4(-0.408248f, 0.5773503f, -0.707107f, 1.0f),
    mm::Vec4(-0.408248f, 0.5773503f, 0.707107f, 1.0f),
    mm::Vec4(0.816497f, 0.5773503f, 0.0f, 1.0f),
    mm::Vec4(0.0f, -1.0f, 0.0f, 1.0f),
};

void DrIrrVolCascade::updateIrrVolByGlobalProbe(u32 x, u32 y, u32 z, u32 index, const SHTerms &terms, grlib::CGLibAcc3DTexture &texture) {
  mm::Mat44 matrix;
  convertSHMatrix(matrix, terms.unknown00[index]);
  f32 irradiance[4];
  for (int i = 0; i < 4; i++) {
    irradiance[i] = calcIrradiance(matrix, unknown003[i]);
  }
  texture.setFloat(irradiance[0], irradiance[1], irradiance[2], irradiance[3], x, y, z);
}

// Inferred role: rounds a file buffer size up to 16 bytes; original name unknown.
template <typename T> static inline T unknown002(T size) { return size % 0x10 != 0 ? size + 0x10 - size % 0x10 : size; }

void DrIrrVolResObj::release() { unknown00->releaseSector(this); }

DrIrrVolResObj *DrIrrVolResMan::loadSector(u32 index) {
  if (unknown18 == nullptr) {
    return nullptr;
  }
  for (mm::mtl::List<DrIrrVolResObj *>::iterator it = unknown38.begin(); it != unknown38.end(); ++it) {
    if ((*it)->unknown24 == index) {
      return *it;
    }
  }
  for (mm::mtl::List<DrIrrVolResObj *>::iterator it = unknown78.begin(); it != unknown78.end(); ++it) {
    DrIrrVolResObj *resObj = *it;
    if (resObj->unknown24 == index) {
      unknown38.push_back(resObj);
      unknown78.erase(it);
      return resObj;
    }
  }
  mm::mtl::FixStr<128> path;
  path.format("%s_c%02d.bin", unknownc0.c_str(), unknownb8);
  u32 size = unknown18->unknown10[index];
  DevFileParamTh param;
  u32 bufferSize = unknown002(size);
  param.unknown00 = path.c_str();
  param.unknown40 = mtl::MemManager::allocate(unknown20, bufferSize, 0x40, false, "no name", 0);
  param.unknown48 = bufferSize;
  param.unknown50 = size;
  param.unknown4c = unknown18->unknown18[index];
  param.unknown60 = this;
  param.unknown68 = 1;
  FileHandleTh *handle = DevFileTh::readFile(param);
  if (handle == nullptr) {
    return nullptr;
  }
  DrIrrVolResObj *resObj = new (unknown20) DrIrrVolResObj(index, this, handle);
  unknown38.push_back(resObj);
  return resObj;
}

void DrIrrVolResMan::update() {
  if (unknown18 != nullptr || unknown08 != nullptr) {
    return;
  }
  mm::mtl::FixStr<128> path;
  path.format("%s_c%02d.bin", unknownc0.c_str(), unknownb8);
  u32 size = unknown002(sizeof(unknown001) + unknownbc * sizeof(u32) * 2);
  if (unknown10 == nullptr) {
    unknown10 = mtl::MemManager::allocate(unknown20, size, 0x40, false, "no name", 0);
  }
  DevFileParamTh param;
  param.unknown00 = path.c_str();
  param.unknown40 = unknown10;
  param.unknown48 = size;
  param.unknown4c = 0;
  param.unknown50 = size;
  param.unknown60 = this;
  param.unknown68 = 1;
  unknown08 = DevFileTh::readFile(param);
}

void DrIrrVolCascade::drawDebugInfo(DebDraw *debDraw) {
  debDraw->setMatrix(mm::Mat44::identity);
  debDraw->setZComp(true);
  debDraw->setZWrite(false);
  debDraw->setCol(mm::Col3::gray, 1.0f);
  for (int i = 0; i < 81; i++) {
    if (unknown20[i] != nullptr) {
      const mm::Aabb &bounds = unknown20[i]->unknown00->unknown00;
      debDraw->renderCube(bounds.min, bounds.max);
    }
  }
  unknown18->drawDebugInfo(debDraw);
}

void DrIrrVolResMan::drawDebugInfo(DebDraw *debDraw) {
  debDraw->setCol(mm::Col3::black, 1.0f);
  for (mm::mtl::List<DrIrrVolResObj *>::iterator it = unknown78.begin(); it != unknown78.end(); ++it) {
    if ((*it)->unknown20 > 0) {
      const mm::Aabb &bounds = (*it)->unknown18->unknown00;
      debDraw->renderCube(bounds.min, bounds.max);
    }
  }
}

DrIrrVolResObj::DrIrrVolResObj(int index, DrIrrVolResMan *manager, FileHandleTh *handle)
    : unknown00(manager), unknown08(handle), unknown10(nullptr), unknown18(nullptr), unknown20(0), unknown24(index) {}

DrIrrVolResObj::~DrIrrVolResObj() {
  if (unknown08 != nullptr) {
    DevFileTh::cancel(unknown08, false);
  }
  if (unknown10 != nullptr) {
    mtl::MemManager::deallocate(unknown10, 0, false);
    unknown10 = nullptr;
  }
}

void DrIrrVolResMan::releaseSector(DrIrrVolResObj *resObj) {
  unknown38.erase(mm::mtl::find(unknown38.begin(), unknown38.end(), resObj));
  if (unknown78.unknown002()) {
    delete *unknown78.begin();
    unknown78.erase(unknown78.begin());
  }
  unknown78.push_back(resObj);
}

void DrIrrVolResObj::onLoaded(EventFileTh *event) {
  unknown10 = event->unknown28;
  unknown18 = static_cast<const SSectorInfo *>(bin::BinaryResolver::resolve(unknown10));
  unknown20 = 1;
}

DrIrrVolResMan::~DrIrrVolResMan() { destroy(); }

void DrIrrVolResMan::destroy() {
  for (mm::mtl::List<DrIrrVolResObj *>::iterator it = unknown38.begin(); it != unknown38.end(); ++it) {
    delete *it;
  }
  unknown38.unknown001();
  for (mm::mtl::List<DrIrrVolResObj *>::iterator it = unknown78.begin(); it != unknown78.end(); ++it) {
    delete *it;
  }
  unknown78.unknown001();
  if (unknown10 != nullptr) {
    mtl::MemManager::deallocate(unknown10, 0, false);
    unknown10 = nullptr;
  }
}

void DrIrrVolResMan::setupHeader(EventFileTh *event) {
  const u32 *fileType = static_cast<const u32 *>(unknown10);
  if (fileType[0] == 0x43415453 && fileType[1] == 0) {
    unknown001 *header = static_cast<unknown001 *>(unknown10);
    header->unknown10 = reinterpret_cast<u32 *>(reinterpret_cast<u64>(header->unknown10) + reinterpret_cast<u64>(header));
    header->unknown18 = reinterpret_cast<u32 *>(reinterpret_cast<u64>(header->unknown18) + reinterpret_cast<u64>(header));
    unknown18 = header;
  }
}

} // namespace irrvol
} // namespace ml

// clang-format off
#include "dr_irr_vol_man.cpp"
// clang-format on
