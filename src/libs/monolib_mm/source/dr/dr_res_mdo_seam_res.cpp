#include "dr/dr_res_mdo_seam_res.h"

#include <new>

#include "dr/dr_man.h"
#include "dr/dr_res_chank_list.h" // IWYU pragma: keep
#include "dr/dr_res_mdo_vertex.h"
#include "grlib/cglib_texture.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

int DrResMdoSeamTexList::SEAMRES_TEXLIST_CNTMAX = 60;

DrResMdoSeamTexList::DrResMdoSeamTexList(int index)
    : unknown08(nullptr), unknown10(nullptr), m_drResMdoSeamMemObj(nullptr), unknown20(nullptr), unknown28(nullptr), m_buffer(nullptr), unknown38(index), unknown3a(0), unknown3b(false), unknown3c(0),
      unknown3e(0) {}

DrResMdoSeamTexList::~DrResMdoSeamTexList() {
  release();
  m_drResMdoSeamMemObj = nullptr;
}

void DrResMdoSeamTexList::release() {
  if (m_buffer != nullptr) {
    for (int i = 0; i < unknown3e; i++) {
      unknown20[i].release();
    }
    if (m_buffer != nullptr) {
      mtl::MemManager::deallocate(m_buffer, 0, false);
      m_buffer = nullptr;
    }
  }
  unknown28 = nullptr;
  unknown3e = 0;
}

bool DrResMdoSeamTexList::update(DrResMdoSeamParmRead *parmRead) {
  unknown3a++;
  if (unknown3a >= SEAMRES_TEXLIST_CNTMAX) {
    return true;
  }
  unknown3b = false;
  if (unknown28 != nullptr && (m_drResMdoSeamMemObj->unknown24 & 2)) {
    changeMemTextureList();
    unknown3b = true;
  }
  return false;
}

void DrResMdoSeamTexList::changeMemTextureList() {
  unknown28 = m_drResMdoSeamMemObj->m_buffer;
  if (unknown3e != 0) {
    const unknown134 *entry = reinterpret_cast<const unknown134 *>(unknown28 + reinterpret_cast<const unknown135 *>(unknown28)->unknown04);
    for (int i = 0; i < unknown3e; i++) {
      grlib::CGLibTexture::changeTextureImagePtrs(unknown20[i], unknown28 + entry->unknown08, entry->unknown04);
      entry++;
    }
  }
}

void DrResMdoSeamTexList::createTextureList(mtl::ALLOC_HANDLE handle) {
  release();
  const unknown135 *header = reinterpret_cast<const unknown135 *>(m_drResMdoSeamMemObj->m_buffer);
  unknown28 = m_drResMdoSeamMemObj->m_buffer;
  int size = header->unknown00 * 0x70;
  m_buffer = mtl::MemManager::allocate(handle, size, 0x40, false, "no name", 0);
  unknown20 = static_cast<grlib::CGLibTextureBuffer *>(m_buffer);
  unknown3e = header->unknown00;
  const unknown134 *entry = reinterpret_cast<const unknown134 *>(unknown28 + header->unknown04);
  for (int i = 0; i < unknown3e; i++, entry++) {
    new (&unknown20[i]) grlib::CGLibTextureBuffer();
    grlib::CGLibTexture::createTextureImagePtrs(unknown20[i], unknown28 + entry->unknown08, entry->unknown04, false, nullptr, false);
  }
}

void DrResMdoSeamTexList::setListCnt(int count) { SEAMRES_TEXLIST_CNTMAX = count; }

int DrResMdoSeamTexture::SEAMRES_NOM_CNTMAX = 120;
int DrResMdoSeamTexture::SEAMRES_HEIGHT_CNTMAX = 60;
int DrResMdoSeamVertex::SEAMRES_CNTMAX = 60;

DrResMdoSeamTexture::DrResMdoSeamTexture(int index)
    : unknown08(nullptr), unknown10(nullptr), unknown88(nullptr), unknown90(nullptr), unknown98(0), unknown9c(index), unknown9e(0), unknowna0(0), unknowna1(false), unknowna2(0), unknowna3(0) {}

DrResMdoSeamTexture::~DrResMdoSeamTexture() {
  m_cGLibTextureBuffer.release();
  unknowna3 = 0;
  unknown88 = nullptr;
  unknown90 = nullptr;
}

void DrResMdoSeamTexture::release() {
  m_cGLibTextureBuffer.release();
  unknown90 = nullptr;
  unknowna3 = 0;
}

bool DrResMdoSeamTexture::update() {
  unknowna1 = false;
  unknowna0++;
  if (unknowna0 >= SEAMRES_NOM_CNTMAX) {
    return true;
  }
  if (unknown88->unknown24 & 2) {
    unknowna1 = true;
  }
  return false;
}

bool DrResMdoSeamTexture::updateHeight() {
  unknowna2++;
  return unknowna2 >= SEAMRES_HEIGHT_CNTMAX;
}

void DrResMdoSeamTexture::createTexture(int size) {
  unknown90 = nullptr;
  grlib::CGLibTexture::createTextureImagePtrs(m_cGLibTextureBuffer, unknown88->m_buffer, size, false, nullptr, false);
  unknowna0 = 0;
  unknowna2 = 0;
  unknowna3 = 0;
}

void DrResMdoSeamTexture::createHeightMoveTexture(int offset, u32 size) {
  grlib::CGLibTexture::changeTextureImagePtrs(m_cGLibTextureBuffer, unknown90->m_buffer + offset, size);
  unknowna0 = 0;
  unknowna2 = 0;
  unknown98 = offset;
}

void DrResMdoSeamTexture::createHeightTexture(int size, int heightSize) {
  grlib::CGLibTexture::createMixTextureImagePtrs(m_cGLibTextureBuffer, unknown88->m_buffer, size, heightSize, false, nullptr, false);
}

void DrResMdoSeamTexture::resetTexture(int size) {
  unknowna3 = 0;
  unknown90 = nullptr;
  grlib::CGLibTexture::createTextureImagePtrs(m_cGLibTextureBuffer, unknown88->m_buffer, size, false, nullptr, false);
}

void DrResMdoSeamTexture::changeMemTexture(int size) { grlib::CGLibTexture::changeTextureImagePtrs(m_cGLibTextureBuffer, unknown88->m_buffer, size); }

void DrResMdoSeamTexture::changeMemTexture(int size, int heightSize) { grlib::CGLibTexture::changeMixTextureImagePtrs(m_cGLibTextureBuffer, unknown88->m_buffer, size, heightSize); }

DrResMdoSeamVertex::DrResMdoSeamVertex(int index)
    : unknown08(nullptr), unknown10(nullptr), m_drResMdoSeamMemObj(nullptr), m_drResMdoVertex(nullptr), unknown28(index), unknown2a(0), unknown2c(0), unknown2e(false) {}

DrResMdoSeamVertex::~DrResMdoSeamVertex() { release(); }

void DrResMdoSeamVertex::release() {
  DrResMdoVertex *vertex = m_drResMdoVertex;
  if (vertex != nullptr) {
    vertex->vertexRelease();
    ::operator delete(vertex);
    m_drResMdoVertex = nullptr;
  }
}

bool DrResMdoSeamVertex::update() {
  unknown2e = false;
  unknown2a++;
  if (unknown2a >= SEAMRES_CNTMAX) {
    return true;
  }
  if (m_drResMdoSeamMemObj->unknown24 & 2) {
    unknown2e = true;
  }
  return false;
}

void DrResMdoSeamVertex::createVertex() {
  release();
  m_drResMdoVertex = new (DrMan::getIns()->unknown10) DrResMdoVertex(m_drResMdoSeamMemObj->m_buffer);
  unknown2a = 0;
  unknown2e = false;
}

void DrResMdoSeamVertex::changeMemVertex() {
  if (m_drResMdoVertex != nullptr) {
    m_drResMdoVertex->changeMemVertex(m_drResMdoSeamMemObj->m_buffer);
  }
}

} // namespace ml

template void ml::DrResChankList<ml::DrResMdoSeamMemObj>::changeList(ml::DrResMdoSeamMemObj *first, ml::DrResMdoSeamMemObj *second);
