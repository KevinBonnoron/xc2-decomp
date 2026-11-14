#include "dr/dr_res_mdo_seam_wrk_env.h"

#include <string.h>

#include "dr/dr_man.h"
#include "dr/dr_mdo_mat.h"
#include "grlib/cglib_uniform_array.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

DrResMdoSeamWrkEnv::DrResMdoSeamWrkEnv() : unknown28(nullptr), m_displayWrk(), m_displayWrkSize(), unknown58(nullptr), unknown60(nullptr), unknown6c(0), unknown70(0) {}

DrResMdoSeamWrkEnv::~DrResMdoSeamWrkEnv() { release(); }

void DrResMdoSeamWrkEnv::release() {
  if (unknown58 != nullptr) {
    mtl::MemManager::deallocate(unknown58, 0, false);
    unknown58 = nullptr;
  }
  if (m_displayWrk[0] != nullptr) {
    mtl::MemManager::deallocate(m_displayWrk[0], 0, false);
    m_displayWrk[0] = nullptr;
  }
  if (m_displayWrk[1] != nullptr) {
    mtl::MemManager::deallocate(m_displayWrk[1], 0, false);
    m_displayWrk[1] = nullptr;
  }
  if (unknown28 != nullptr) {
    mtl::MemManager::deallocate(unknown28, 0, false);
    unknown28 = nullptr;
  }
  m_displayWrkSize[0] = 0;
  m_displayWrkSize[1] = 0;
  unknown6c = 0;
  unknown60 = nullptr;
}

bool DrResMdoSeamWrkEnv::update(const mm::Vec3 &position, bool isOpen) {
  unknown6c &= ~0x10;
  if (unknown58 == nullptr) {
    return false;
  }
  if (isOpen) {
    return true;
  }
  if (unknown60->unknown24 & 2) {
    unknown6c |= 0x10;
  }
  return false;
}

void DrResMdoSeamWrkEnv::setupWork(MdoWrkMatRes *matRes, grlib::CGLibTriUniformArray *uniforms, mtl::ALLOC_HANDLE handle, const MdsSeamEnvMapHead *head, const MdsSeamEnvMapData *data) {
  unknown58 = matRes;
  unknown18 = head;
  unknown20 = data;
  unknown6c = 0;
  unknown70 = data->unknown38;
  m_displayWrk[0] = nullptr;
  m_displayWrk[1] = nullptr;
  m_displayWrkSize[0] = 0;
  m_displayWrkSize[1] = 0;
  matRes->unknowna0 = uniforms;
  u32 size = (matRes->unknown30 / 32 + 1) * 4;
  size += -size & 0x1f;
  unknown28 = mtl::MemManager::allocate(handle, size, 0x20, false, "no name", 0);
  unknown30 = static_cast<u32 *>(unknown28);
  memset(unknown30, 0, size);
}

void DrResMdoSeamWrkEnv::setDispState() { unknown6c |= 1 << DrMan::s_nDblNowIdx; }

u32 DrResMdoSeamWrkEnv::chkDispState() { return unknown6c & (1 << DrMan::s_nDblNowIdx); }

u8 *DrResMdoSeamWrkEnv::getDisplayWrk() { return m_displayWrk[DrMan::s_nDblNowIdx]; }

int DrResMdoSeamWrkEnv::getDisplayWrkSize() { return m_displayWrkSize[DrMan::s_nDblNowIdx]; }

void DrResMdoSeamWrkEnv::setDisplayWrk(u8 *work, int size) {
  int index = DrMan::s_nDblNowIdx;
  m_displayWrk[index] = work;
  m_displayWrkSize[index] = size;
}

void DrResMdoSeamWrkEnv::changeMemCall(const MdsSeamEnvMapHead *head) {
  unknown18 = head;
  unknown6c &= ~3u;
}

void DrResMdoSeamWrkEnv::setInfo(const mm::Vec3 &position, const mm::Vec3 &scale, bool isEnable, u32 flags) {
  unknown68 = flags;
  unknown74 = isEnable;
  unknown80 = position;
  unknown90 = scale;
}

} // namespace ml
