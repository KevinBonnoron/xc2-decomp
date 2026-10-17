#include "dr/dr_res_mdo_tex_list.h"

#include "dr/dr_calc_stm_list_obj.h"
#include "dr/dr_man.h"
#include "grlib/cglib_texture.h"
#include "grlib/cglib_texture_buffer.h"
#include "mtl/mem_manager.h"

namespace ml {

DrResMdoTexList::DrResMdoTexList(const u8 *texData)
    : m_prev(nullptr), m_next(nullptr), m_resourceKey(texData), m_refCount(1), m_textures(nullptr), m_stmList(nullptr), m_buffer(nullptr),
      m_texMax(0), m_flags(0), _70(), m_texHeader(texData), m_texData(texData), _90(), _98() {
  createTexInfoList();
  createTexList(m_texHeader, m_texData);
}

DrResMdoTexList::DrResMdoTexList(const u8 *texHeader, DrCalcStmListObj *stmList, const u8 *texData, const MdsTexHeader *stmHeader)
    : m_prev(nullptr), m_next(nullptr), m_resourceKey(texHeader), m_refCount(1), m_textures(nullptr), m_stmList(stmList), m_buffer(nullptr),
      m_texMax(0), m_flags(0), _70(), m_texHeader(texHeader), m_texData(texData), _90(), _98() {
  createStmTexInfoList(stmList, reinterpret_cast<const u8 *>(stmHeader), true);
  createTexList(m_texHeader, m_texData);
}

DrResMdoTexList::DrResMdoTexList(const u8 *texHeader, DrCalcStmListObj *stmList, const u8 *texData, const u16 *stmTexIdx)
    : m_prev(nullptr), m_next(nullptr), m_resourceKey(texHeader), m_refCount(1), m_textures(nullptr), m_stmList(stmList), m_buffer(nullptr),
      m_texMax(0), m_flags(0), _70(), m_texHeader(texHeader), m_texData(texData), _90(), _98() {
  createStmTexInfoList(stmList, reinterpret_cast<const u8 *>(stmTexIdx), false);
  createTexList(m_texHeader, m_texData);
}

DrResMdoTexList::DrResMdoTexList(const u8 *texHeader, const u8 *texData)
    : m_prev(nullptr), m_next(nullptr), m_resourceKey(texHeader), m_refCount(1), m_textures(nullptr), m_stmList(nullptr), m_buffer(nullptr),
      m_texMax(0), m_flags(0), _70(), m_texHeader(texHeader), m_texData(texData), _90(), _98() {
  createTexInfoList();
  createTexList(m_texHeader, m_texData);
}

DrResMdoTexList::~DrResMdoTexList() { release(); }

void DrResMdoTexList::release() {
  if (m_texMax != 0) {
    for (int i = 0; i < m_texMax; i++) {
      m_textures[i].~CGLibTextureBuffer();
    }
    m_textures = nullptr;
    m_texMax = 0;
  }
  if (m_buffer != nullptr) {
    mtl::MemManager::deallocate(m_buffer, 0, false);
    m_buffer = nullptr;
  }
  m_memPool.release();
  m_flags = 0;
}

void DrResMdoTexList::update() {
  texStmUpdate();
  m_flags &= ~0x30000;
}

void DrResMdoTexList::callStmRead(int mode) {
  if (mode != 0) {
    m_flags |= 0x10000;
    if (mode == 2) {
      m_flags |= 0x20000;
    }
  }
}

grlib::CGLibTextureBuffer *DrResMdoTexList::getTexObj(u32 index) { return &m_textures[index]; }

grlib::CGLibTextureBuffer *DrResMdoTexList::getStmTexObj(u32 index) {
  u32 stmIdx = m_stmTexIdx[index];
  if (stmIdx != 0) {
    return m_stmList->getTexObj(stmIdx - 1);
  }
  return &m_textures[index];
}

const char *DrResMdoTexList::getTexName(u32 index) {
  const MdsTexHeader *header = reinterpret_cast<const MdsTexHeader *>(m_texHeader);
  const MdsTexInfo *infos = reinterpret_cast<const MdsTexInfo *>(m_texHeader + header->infoOffset);
  return reinterpret_cast<const char *>(m_texHeader + infos[index].nameOffset);
}

bool DrResMdoTexList::isTexMiddelStmCheck() const {
  if (!(m_flags & 0x8000)) {
    return false;
  }
  return !m_stmList->isResSafe();
}

int DrResMdoTexList::calcTextureMax(const u8 *texHeader) { return reinterpret_cast<const MdsTexHeader *>(texHeader)->texNum; }

DrResMdoTexSimple::DrResMdoTexSimple(const void *texData, int size, bool isMiddle)
    : m_prev(nullptr), m_next(nullptr), m_texData(texData), m_size(size), m_flags(isMiddle ? 2 : 0) {}

DrResMdoTexSimple::~DrResMdoTexSimple() { releaseTex(); }

void DrResMdoTexSimple::releaseTex() {
  m_texture.release();
  m_flags &= ~0xd;
}

void DrResMdoTexSimple::release() { m_flags |= 4 << DrMan::s_nDblStockIdx; }

void DrResMdoTexSimple::createTex() {
  grlib::CGLibTexture::createTextureImagePtrs(m_texture, m_texData, m_size, false, nullptr, false);
  m_flags |= 1;
}

} // namespace ml
