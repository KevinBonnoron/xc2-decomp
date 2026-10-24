#include "dr/dr_res_mdo_tex_list.h"

#include "dr/dr_calc_stm_list_obj.h"
#include "dr/dr_man.h"
#include "grlib/cglib_texture.h"
#include "grlib/cglib_texture_buffer.h"
#include "mtl/mem_manager.h"

namespace ml {

DrResMdoTexList::DrResMdoTexList(const u8 *texData)
    : unknown00(nullptr), unknown08(nullptr), unknown10(texData), unknown18(1), unknown20(nullptr), unknown58(nullptr), m_buffer(nullptr), unknown68(0), unknown6c(0), _70(), unknown80(texData),
      unknown88(texData), _90(), _98() {
  createTexInfoList();
  createTexList(unknown80, unknown88);
}

DrResMdoTexList::DrResMdoTexList(const u8 *texHeader, DrCalcStmListObj *stmList, const u8 *texData, const MdsTexHeader *stmHeader)
    : unknown00(nullptr), unknown08(nullptr), unknown10(texHeader), unknown18(1), unknown20(nullptr), unknown58(stmList), m_buffer(nullptr), unknown68(0), unknown6c(0), _70(), unknown80(texHeader),
      unknown88(texData), _90(), _98() {
  createStmTexInfoList(stmList, reinterpret_cast<const u8 *>(stmHeader), true);
  createTexList(unknown80, unknown88);
}

DrResMdoTexList::DrResMdoTexList(const u8 *texHeader, DrCalcStmListObj *stmList, const u8 *texData, const u16 *stmTexIdx)
    : unknown00(nullptr), unknown08(nullptr), unknown10(texHeader), unknown18(1), unknown20(nullptr), unknown58(stmList), m_buffer(nullptr), unknown68(0), unknown6c(0), _70(), unknown80(texHeader),
      unknown88(texData), _90(), _98() {
  createStmTexInfoList(stmList, reinterpret_cast<const u8 *>(stmTexIdx), false);
  createTexList(unknown80, unknown88);
}

DrResMdoTexList::DrResMdoTexList(const u8 *texHeader, const u8 *texData)
    : unknown00(nullptr), unknown08(nullptr), unknown10(texHeader), unknown18(1), unknown20(nullptr), unknown58(nullptr), m_buffer(nullptr), unknown68(0), unknown6c(0), _70(), unknown80(texHeader),
      unknown88(texData), _90(), _98() {
  createTexInfoList();
  createTexList(unknown80, unknown88);
}

DrResMdoTexList::~DrResMdoTexList() { release(); }

void DrResMdoTexList::release() {
  if (unknown68 != 0) {
    for (int i = 0; i < unknown68; i++) {
      unknown20[i].~CGLibTextureBuffer();
    }
    unknown20 = nullptr;
    unknown68 = 0;
  }
  if (m_buffer != nullptr) {
    mtl::MemManager::deallocate(m_buffer, 0, false);
    m_buffer = nullptr;
  }
  unknown28.release();
  unknown6c = 0;
}

void DrResMdoTexList::update() {
  texStmUpdate();
  unknown6c &= ~0x30000;
}

void DrResMdoTexList::callStmRead(int mode) {
  if (mode != 0) {
    unknown6c |= 0x10000;
    if (mode == 2) {
      unknown6c |= 0x20000;
    }
  }
}

grlib::CGLibTextureBuffer *DrResMdoTexList::getTexObj(u32 index) { return &unknown20[index]; }

grlib::CGLibTextureBuffer *DrResMdoTexList::getStmTexObj(u32 index) {
  u32 stmIdx = unknown78[index];
  if (stmIdx != 0) {
    return unknown58->getTexObj(stmIdx - 1);
  }
  return &unknown20[index];
}

const char *DrResMdoTexList::getTexName(u32 index) {
  const MdsTexHeader *header = reinterpret_cast<const MdsTexHeader *>(unknown80);
  const MdsTexInfo *infos = reinterpret_cast<const MdsTexInfo *>(unknown80 + header->infoOffset);
  return reinterpret_cast<const char *>(unknown80 + infos[index].unknown0c);
}

bool DrResMdoTexList::isTexMiddelStmCheck() const {
  if (!(unknown6c & 0x8000)) {
    return false;
  }
  return !unknown58->isResSafe();
}

int DrResMdoTexList::calcTextureMax(const u8 *texHeader) { return reinterpret_cast<const MdsTexHeader *>(texHeader)->texNum; }

DrResMdoTexSimple::DrResMdoTexSimple(const void *texData, int size, bool isMiddle) : unknown00(nullptr), unknown08(nullptr), unknown80(texData), m_size(size), unknown8c(isMiddle ? 2 : 0) {}

DrResMdoTexSimple::~DrResMdoTexSimple() { releaseTex(); }

void DrResMdoTexSimple::releaseTex() {
  unknown10.release();
  unknown8c &= ~0xd;
}

void DrResMdoTexSimple::release() { unknown8c |= 4 << DrMan::s_nDblStockIdx; }

void DrResMdoTexSimple::createTex() {
  grlib::CGLibTexture::createTextureImagePtrs(unknown10, unknown80, m_size, false, nullptr, false);
  unknown8c |= 1;
}

} // namespace ml
