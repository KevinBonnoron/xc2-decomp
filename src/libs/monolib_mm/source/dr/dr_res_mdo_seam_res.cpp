#include "dr/dr_res_mdo_seam_res.h"

#include "dr/dr_res_mdo_vertex.h"
#include "grlib/cglib_texture.h"
#include "mtl/mem_manager.h"

namespace ml {

int DrResMdoSeamTexList::SEAMRES_TEXLIST_CNTMAX = 60;

DrResMdoSeamTexList::DrResMdoSeamTexList(int index)
    : m_next(nullptr), _10(), m_memObj(nullptr), m_textures(nullptr), m_header(nullptr), m_buffer(nullptr), m_index(index), m_cnt(0), m_isChangeMem(false), m_errIdx(0), m_texNum(0) {}

DrResMdoSeamTexList::~DrResMdoSeamTexList() {
  release();
  m_memObj = nullptr;
}

void DrResMdoSeamTexList::release() {
  if (m_buffer != nullptr) {
    for (int i = 0; i < m_texNum; i++) {
      m_textures[i].release();
    }
    if (m_buffer != nullptr) {
      mtl::MemManager::deallocate(m_buffer, 0, false);
      m_buffer = nullptr;
    }
  }
  m_header = nullptr;
  m_texNum = 0;
}

void DrResMdoSeamTexList::setListCnt(int count) { SEAMRES_TEXLIST_CNTMAX = count; }

int DrResMdoSeamTexture::SEAMRES_NOM_CNTMAX = 120;
int DrResMdoSeamTexture::SEAMRES_HEIGHT_CNTMAX = 60;
int DrResMdoSeamVertex::SEAMRES_CNTMAX = 60;

DrResMdoSeamTexture::DrResMdoSeamTexture(int index)
    : m_next(nullptr), _10(), m_memObj(nullptr), m_heightMemObj(nullptr), m_heightOffset(0), m_index(index), m_seamIdx(0), m_nomCnt(0), m_isChangeMem(false), m_heightCnt(0), m_heightState(0) {}

DrResMdoSeamTexture::~DrResMdoSeamTexture() {
  m_texture.release();
  m_heightState = 0;
  m_memObj = nullptr;
  m_heightMemObj = nullptr;
}

void DrResMdoSeamTexture::release() {
  m_texture.release();
  m_heightMemObj = nullptr;
  m_heightState = 0;
}

bool DrResMdoSeamTexture::update() {
  m_isChangeMem = false;
  m_nomCnt++;
  if (m_nomCnt >= SEAMRES_NOM_CNTMAX) {
    return true;
  }
  if (m_memObj->m_flags & 2) {
    m_isChangeMem = true;
  }
  return false;
}

bool DrResMdoSeamTexture::updateHeight() {
  m_heightCnt++;
  return m_heightCnt >= SEAMRES_HEIGHT_CNTMAX;
}

void DrResMdoSeamTexture::createTexture(int size) {
  m_heightMemObj = nullptr;
  grlib::CGLibTexture::createTextureImagePtrs(m_texture, m_memObj->m_buffer, size, false, nullptr, false);
  m_nomCnt = 0;
  m_heightCnt = 0;
  m_heightState = 0;
}

void DrResMdoSeamTexture::createHeightMoveTexture(int offset, u32 size) {
  grlib::CGLibTexture::changeTextureImagePtrs(m_texture, m_heightMemObj->m_buffer + offset, size);
  m_nomCnt = 0;
  m_heightCnt = 0;
  m_heightOffset = offset;
}

void DrResMdoSeamTexture::createHeightTexture(int size, int heightSize) { grlib::CGLibTexture::createMixTextureImagePtrs(m_texture, m_memObj->m_buffer, size, heightSize, false, nullptr, false); }

void DrResMdoSeamTexture::resetTexture(int size) {
  m_heightState = 0;
  m_heightMemObj = nullptr;
  grlib::CGLibTexture::createTextureImagePtrs(m_texture, m_memObj->m_buffer, size, false, nullptr, false);
}

void DrResMdoSeamTexture::changeMemTexture(int size) { grlib::CGLibTexture::changeTextureImagePtrs(m_texture, m_memObj->m_buffer, size); }

void DrResMdoSeamTexture::changeMemTexture(int size, int heightSize) { grlib::CGLibTexture::changeMixTextureImagePtrs(m_texture, m_memObj->m_buffer, size, heightSize); }

DrResMdoSeamVertex::DrResMdoSeamVertex(int index) : m_next(nullptr), _10(), m_memObj(nullptr), m_vertex(nullptr), m_index(index), m_cnt(0), _2c(), m_isChangeMem(false) {}

bool DrResMdoSeamVertex::update() {
  m_isChangeMem = false;
  m_cnt++;
  if (m_cnt >= SEAMRES_CNTMAX) {
    return true;
  }
  if (m_memObj->m_flags & 2) {
    m_isChangeMem = true;
  }
  return false;
}

void DrResMdoSeamVertex::changeMemVertex() {
  if (m_vertex != nullptr) {
    m_vertex->changeMemVertex(m_memObj->m_buffer);
  }
}

} // namespace ml
