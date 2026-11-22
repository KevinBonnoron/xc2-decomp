#include "dr/dr_res_mdo_tex_list.h"

#include <string.h>

#include <new>

#include "dr/dr_calc_stm_list_obj.h"
#include "dr/dr_man.h"
#include "grlib/cglib_texture.h"
#include "grlib/cglib_texture_buffer.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

void DrResMdoTexList::createTexInfoList() {
  release();
  unknown70 = 0;
  unknown68 = reinterpret_cast<const MdsTexHeader *>(unknown80)->texNum;
  u32 size = reinterpret_cast<const MdsTexHeader *>(unknown80)->texNum * 0x70;
  m_buffer = mtl::MemManager::allocate(DrMan::get()->unknown14, size, 0x10, false, "no name", 0);
  m_texObj = static_cast<grlib::CGLibTextureBuffer *>(m_buffer);
  for (int i = 0; i < unknown68; i++) {
    new (&m_texObj[i]) grlib::CGLibTextureBuffer();
  }
}

void DrResMdoTexList::createTexList(const u8 *texHeader, const u8 *texData) {
  unknown6c |= 1;
  const MdsTexHeader *header = reinterpret_cast<const MdsTexHeader *>(texHeader);
  const unknown092 *infos = reinterpret_cast<const unknown092 *>(texHeader + header->infoOffset);
  if (!(unknown6c & 0x20)) {
    unknown6c |= 0x20;
    u32 size = infos[unknown68 - 1].unknown08 - infos[0].unknown08 + infos[unknown68 - 1].unknown04;
    size += -size & 0xfff;
    m_cGLibVtlMemPool.setupBuffer(const_cast<u8 *>(texData) + infos[0].unknown08, size);
  }
  u32 firstOffset = infos[0].unknown08;
  for (int i = 0; i < unknown68; i++) {
    grlib::CGLibTexture::createTextureImagePtrs(m_texObj[i], infos[i].unknown04, m_cGLibVtlMemPool, infos[i].unknown08 - firstOffset, false, nullptr, true);
  }
}

void DrResMdoTexList::createStmTexInfoList(DrCalcStmListObj *stmList, const u8 *stmHeader, bool isCreate) {
  release();
  unknown70 = 0;
  u32 texNum = reinterpret_cast<const MdsTexHeader *>(unknown80)->texNum;
  unknown68 = texNum;
  u32 texSize = reinterpret_cast<const MdsTexHeader *>(unknown80)->texNum * 0x70;
  size_t texOffset = texSize;
  u32 size = texSize + texNum * 2;
  if (texNum & 1) {
    size += 2;
  }
  m_buffer = mtl::MemManager::allocate(DrMan::get()->unknown14, size, 0x10, false, "no name", 0);
  m_texObj = static_cast<grlib::CGLibTextureBuffer *>(m_buffer);
  for (int i = 0; i < unknown68; i++) {
    new (&m_texObj[i]) grlib::CGLibTextureBuffer();
  }
  unknown6c |= 0x8000;
  unknown78 = reinterpret_cast<u16 *>(static_cast<u8 *>(m_buffer) + texOffset);
  m_drCalcStmListObj = stmList;
  if (isCreate) {
    const MdsTexHeader *stm = reinterpret_cast<const MdsTexHeader *>(stmHeader);
    const unknown092 *stmInfos = reinterpret_cast<const unknown092 *>(stmHeader + stm->infoOffset);
    const MdsTexHeader *header = reinterpret_cast<const MdsTexHeader *>(unknown80);
    for (int i = 0; i < unknown68; i++) {
      const unknown092 *infos = reinterpret_cast<const unknown092 *>(unknown80 + header->infoOffset);
      const char *name = reinterpret_cast<const char *>(unknown80 + infos[i].unknown0c);
      unknown78[i] = 0;
      for (int j = 0; j < stm->texNum; j++) {
        if (strcmp(name, reinterpret_cast<const char *>(stmHeader + stmInfos[j].unknown0c)) == 0) {
          unknown78[i] = j + 1;
          break;
        }
      }
    }
  } else {
    const u16 *stmTexIdx = reinterpret_cast<const u16 *>(stmHeader);
    for (int i = 0; i < unknown68; i++) {
      unknown78[i] = 0;
    }
    for (int i = 0; i < m_drCalcStmListObj->unknowna4; i++) {
      unknown78[stmTexIdx[i]] = i + 1;
    }
  }
}

void DrResMdoTexList::resetTexutre() {
  _90 = 0;
  createTexList(unknown80, unknown88);
}

DrResMdoTexList::DrResMdoTexList(const u8 *texData)
    : unknown00(nullptr), unknown08(nullptr), unknown10(texData), unknown18(1), m_texObj(nullptr), m_drCalcStmListObj(nullptr), m_buffer(nullptr), unknown68(0), unknown6c(0), unknown70(0),
      unknown80(texData), unknown88(texData), _90(), _98() {
  createTexInfoList();
  createTexList(unknown80, unknown88);
}

DrResMdoTexList::DrResMdoTexList(const u8 *texHeader, DrCalcStmListObj *stmList, const u8 *texData, const MdsTexHeader *stmHeader)
    : unknown00(nullptr), unknown08(nullptr), unknown10(texHeader), unknown18(1), m_texObj(nullptr), m_drCalcStmListObj(stmList), m_buffer(nullptr), unknown68(0), unknown6c(0), unknown70(0),
      unknown80(texHeader), unknown88(texData), _90(), _98() {
  createStmTexInfoList(stmList, reinterpret_cast<const u8 *>(stmHeader), true);
  createTexList(unknown80, unknown88);
}

DrResMdoTexList::DrResMdoTexList(const u8 *texHeader, DrCalcStmListObj *stmList, const u8 *texData, const u16 *stmTexIdx)
    : unknown00(nullptr), unknown08(nullptr), unknown10(texHeader), unknown18(1), m_texObj(nullptr), m_drCalcStmListObj(stmList), m_buffer(nullptr), unknown68(0), unknown6c(0), unknown70(0),
      unknown80(texHeader), unknown88(texData), _90(), _98() {
  createStmTexInfoList(stmList, reinterpret_cast<const u8 *>(stmTexIdx), false);
  createTexList(unknown80, unknown88);
}

DrResMdoTexList::DrResMdoTexList(const u8 *texHeader, const u8 *texData)
    : unknown00(nullptr), unknown08(nullptr), unknown10(texHeader), unknown18(1), m_texObj(nullptr), m_drCalcStmListObj(nullptr), m_buffer(nullptr), unknown68(0), unknown6c(0), unknown70(0),
      unknown80(texHeader), unknown88(texData), _90(), _98() {
  createTexInfoList();
  createTexList(unknown80, unknown88);
}

DrResMdoTexList::~DrResMdoTexList() { release(); }

void DrResMdoTexList::release() {
  if (unknown68 != 0) {
    for (int i = 0; i < unknown68; i++) {
      m_texObj[i].~CGLibTextureBuffer();
    }
    m_texObj = nullptr;
    unknown68 = 0;
  }
  if (m_buffer != nullptr) {
    mtl::MemManager::deallocate(m_buffer, 0, false);
    m_buffer = nullptr;
  }
  m_cGLibVtlMemPool.release();
  unknown6c = 0;
}

void DrResMdoTexList::update() {
  texStmUpdate();
  unknown6c &= ~0x30000;
}

void DrResMdoTexList::texStmUpdate() {
  if (unknown6c & 0x8000) {
    if (!(unknown6c & 0x10000)) {
      m_drCalcStmListObj->setUseMode(DrCalcStmListObj::DR_TEX_USE_MODE_UNKNOWN_0);
    } else if (!(unknown6c & 0x20000)) {
      m_drCalcStmListObj->setUseMode(DrCalcStmListObj::DR_TEX_USE_MODE_UNKNOWN_1);
    } else {
      m_drCalcStmListObj->setUseMode(DrCalcStmListObj::DR_TEX_USE_MODE_UNKNOWN_2);
    }
    if (m_drCalcStmListObj->isResSub() && (m_drCalcStmListObj->unknown80 & 0x400)) {
      unknown035 *lowTex = m_drCalcStmListObj->getResLowTexObj();
      if (lowTex->unknown10 & 1) {
        changeCallTexMemTexList(unknown80, lowTex->unknown00);
      }
    }
    if (m_drCalcStmListObj->isResTex()) {
      unknown70 = 2;
    } else {
      unknown70 = 1;
    }
  }
}

void DrResMdoTexList::callStmRead(int mode) {
  if (mode != 0) {
    unknown6c |= 0x10000;
    if (mode == 2) {
      unknown6c |= 0x20000;
    }
  }
}

void DrResMdoTexList::changeCallTexMemTexList(const u8 *texHeader, const u8 *texData) {
  unknown80 = texHeader;
  unknown88 = texData;
  const MdsTexHeader *header = reinterpret_cast<const MdsTexHeader *>(texHeader);
  const unknown092 *infos = reinterpret_cast<const unknown092 *>(texHeader + header->infoOffset);
  u32 firstOffset = infos[0].unknown08;
  unknown6c |= 0x20;
  u32 size = infos[unknown68 - 1].unknown08 - infos[0].unknown08 + infos[unknown68 - 1].unknown04;
  size += -size & 0xfff;
  m_cGLibVtlMemPool.setupBuffer(const_cast<u8 *>(texData) + infos[0].unknown08, size);
  // The entries are walked with a pointer: of the loop forms tried (index, locals, while, unsigned counter) it is the one that gives the game's
  // order of the counters once this function is inlined into texStmUpdate (0x710088dae4) and changeMemTexList (0x710088ddb8) as well as
  // standing alone (0x710088dc54).
  const unknown092 *info = infos;
  for (int i = 0; i < unknown68; i++, info++) {
    grlib::CGLibTexture::changeTextureImagePtrs(m_texObj[i], info->unknown04, m_cGLibVtlMemPool, info->unknown08 - firstOffset);
  }
}

void DrResMdoTexList::changeMemTexList(const u8 *texData) { changeCallTexMemTexList(texData, texData); }

grlib::CGLibTextureBuffer *DrResMdoTexList::getTexObj(u32 index) { return &m_texObj[index]; }

grlib::CGLibTextureBuffer *DrResMdoTexList::getStmTexObj(u32 index) {
  u32 stmIdx = unknown78[index];
  if (stmIdx != 0) {
    return m_drCalcStmListObj->getTexObj(stmIdx - 1);
  }
  return &m_texObj[index];
}

const char *DrResMdoTexList::getTexName(u32 index) {
  const MdsTexHeader *header = reinterpret_cast<const MdsTexHeader *>(unknown80);
  const unknown092 *infos = reinterpret_cast<const unknown092 *>(unknown80 + header->infoOffset);
  return reinterpret_cast<const char *>(unknown80 + infos[index].unknown0c);
}

bool DrResMdoTexList::isTexMiddelStmCheck() const {
  if (!(unknown6c & 0x8000)) {
    return false;
  }
  return !m_drCalcStmListObj->isResSafe();
}

int DrResMdoTexList::calcTextureMax(const u8 *texHeader) { return reinterpret_cast<const MdsTexHeader *>(texHeader)->texNum; }

DrResMdoTexSimple::DrResMdoTexSimple(const void *texData, int size, bool isMiddle) : unknown00(nullptr), unknown08(nullptr), unknown80(texData), m_size(size), unknown8c(isMiddle ? 2 : 0) {}

DrResMdoTexSimple::~DrResMdoTexSimple() { releaseTex(); }

void DrResMdoTexSimple::releaseTex() {
  m_cGLibTextureBuffer.release();
  unknown8c &= ~0xd;
}

void DrResMdoTexSimple::release() { unknown8c |= 4 << DrMan::s_nDblStockIdx; }

void DrResMdoTexSimple::createTex() {
  grlib::CGLibTexture::createTextureImagePtrs(m_cGLibTextureBuffer, unknown80, m_size, false, nullptr, false);
  unknown8c |= 1;
}

} // namespace ml
