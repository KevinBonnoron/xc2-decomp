#include "dr/dr_res_mdo_seam_res.h"

#include "dr/dr_res_mdo_vertex.h"
#include "grlib/cglib_texture.h"
#include "mtl/mem_manager.h"

namespace ml {

int DrResMdoSeamTexList::SEAMRES_TEXLIST_CNTMAX = 60;

DrResMdoSeamTexList::DrResMdoSeamTexList(int index)
    : unknown08(nullptr), _10(), unknown18(nullptr), unknown20(nullptr), unknown28(nullptr), m_buffer(nullptr), unknown38(index), unknown3a(0), unknown3b(false), unknown3c(0), unknown3e(0) {}

DrResMdoSeamTexList::~DrResMdoSeamTexList() {
  release();
  unknown18 = nullptr;
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

void DrResMdoSeamTexList::setListCnt(int count) { SEAMRES_TEXLIST_CNTMAX = count; }

int DrResMdoSeamTexture::SEAMRES_NOM_CNTMAX = 120;
int DrResMdoSeamTexture::SEAMRES_HEIGHT_CNTMAX = 60;
int DrResMdoSeamVertex::SEAMRES_CNTMAX = 60;

DrResMdoSeamTexture::DrResMdoSeamTexture(int index)
    : unknown08(nullptr), _10(), unknown88(nullptr), unknown90(nullptr), unknown98(0), unknown9c(index), unknown9e(0), unknowna0(0), unknowna1(false), unknowna2(0), unknowna3(0) {}

DrResMdoSeamTexture::~DrResMdoSeamTexture() {
  unknown18.release();
  unknowna3 = 0;
  unknown88 = nullptr;
  unknown90 = nullptr;
}

void DrResMdoSeamTexture::release() {
  unknown18.release();
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
  grlib::CGLibTexture::createTextureImagePtrs(unknown18, unknown88->m_buffer, size, false, nullptr, false);
  unknowna0 = 0;
  unknowna2 = 0;
  unknowna3 = 0;
}

void DrResMdoSeamTexture::createHeightMoveTexture(int offset, u32 size) {
  grlib::CGLibTexture::changeTextureImagePtrs(unknown18, unknown90->m_buffer + offset, size);
  unknowna0 = 0;
  unknowna2 = 0;
  unknown98 = offset;
}

void DrResMdoSeamTexture::createHeightTexture(int size, int heightSize) { grlib::CGLibTexture::createMixTextureImagePtrs(unknown18, unknown88->m_buffer, size, heightSize, false, nullptr, false); }

void DrResMdoSeamTexture::resetTexture(int size) {
  unknowna3 = 0;
  unknown90 = nullptr;
  grlib::CGLibTexture::createTextureImagePtrs(unknown18, unknown88->m_buffer, size, false, nullptr, false);
}

void DrResMdoSeamTexture::changeMemTexture(int size) { grlib::CGLibTexture::changeTextureImagePtrs(unknown18, unknown88->m_buffer, size); }

void DrResMdoSeamTexture::changeMemTexture(int size, int heightSize) { grlib::CGLibTexture::changeMixTextureImagePtrs(unknown18, unknown88->m_buffer, size, heightSize); }

DrResMdoSeamVertex::DrResMdoSeamVertex(int index) : unknown08(nullptr), _10(), unknown18(nullptr), unknown20(nullptr), unknown28(index), unknown2a(0), _2c(), unknown2e(false) {}

bool DrResMdoSeamVertex::update() {
  unknown2e = false;
  unknown2a++;
  if (unknown2a >= SEAMRES_CNTMAX) {
    return true;
  }
  if (unknown18->unknown24 & 2) {
    unknown2e = true;
  }
  return false;
}

void DrResMdoSeamVertex::changeMemVertex() {
  if (unknown20 != nullptr) {
    unknown20->changeMemVertex(unknown18->m_buffer);
  }
}

} // namespace ml
