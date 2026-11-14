#include "dr/dr_ibl_obj.h"

#include "dr/dr_ibl_coli_acc.h"
#include "dr/dr_man.h"
#include "grlib/cglib_texture.h"
#include "grlib/cglib_texture_buffer.h"
#include "ml/cache_draw.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_list.h" // IWYU pragma: keep
#include "mtl/alloc_handle.h"

namespace ml {

void (DrIBLObj::*DrIBLObj::s_pRenderColi[5])(const u8 *data) = {
    &DrIBLObj::render_box,
    &DrIBLObj::render_sphere,
    &DrIBLObj::render_cylinder,
    &DrIBLObj::render_notrot_box,
    &DrIBLObj::render_notrot_cylinder,
};

void DrIBLObj::initialize(DrMan *man) {
  if (unknown00->unknown00 != 0x4c424947) {
    return;
  }
  if (unknown00->unknown04 != 10000) {
    return;
  }
  unknown08 = reinterpret_cast<const unknown002 *>(reinterpret_cast<const u8 *>(unknown00) + unknown00->unknown0c);
  unknown10 = reinterpret_cast<const _IBLPrimHeader *>(reinterpret_cast<const u8 *>(unknown00) + unknown00->unknown14);
  unknown18 = reinterpret_cast<const _EnvColiListTreeData *>(reinterpret_cast<const u8 *>(unknown00) + unknown00->unknown1c);
  unknown40 = unknown00->unknown08;
  unknown48 = new (man->unknown10) grlib::CGLibTextureBuffer[unknown40];
  unknown50 = new (man->unknown10) grlib::CGLibTextureBuffer[unknown40];
  for (u32 i = 0; i < unknown40; i++) {
    const unknown002 *entry = &unknown08[i];
    grlib::CGLibTexture::createTextureImagePtrs(unknown48[i], reinterpret_cast<const u8 *>(unknown00) + entry->unknown10, entry->unknown14, true, nullptr, true);
    grlib::CGLibTexture::createTextureImagePtrs(unknown50[i], reinterpret_cast<const u8 *>(unknown00) + entry->unknown18, entry->unknown1c, false, nullptr, true);
  }
  unknown60 = new (man->unknown10) DrIBLColiAcc(unknown00, man->unknown10);
  unknown58 |= 1;
}

void DrIBLObj::update() {
  unknown38 = nullptr;
  if ((unknown58 & 3) == 1 && unknown5c != 0) {
    const _IBLPrimHeader *primitive;
    if (unknown60->testColi(unknown20, 2.0f, primitive)) {
      unknown38 = primitive;
    }
  }
}

DrIBLObj::DrIBLObj(const void *data)
    : unknown00(static_cast<const unknown001 *>(data)), unknown08(nullptr), unknown10(nullptr), unknown18(nullptr), unknown20(0.0f, 0.0f, 0.0f), unknown38(nullptr), unknown40(0), unknown48(nullptr),
      unknown50(nullptr), unknown58(0), unknown5c(1), unknown60(nullptr) {}

DrIBLObj::~DrIBLObj() {
  if (unknown60 != nullptr) {
    delete unknown60;
    unknown60 = nullptr;
  }
  for (u32 i = 0; i < unknown40; i++) {
    unknown48[i].release();
    unknown50[i].release();
  }
  if (unknown48 != nullptr) {
    delete[] unknown48;
    unknown48 = nullptr;
  }
  if (unknown50 != nullptr) {
    delete[] unknown50;
    unknown50 = nullptr;
  }
}

bool DrIBLObj::hasValidIBL() const { return unknown38 != nullptr; }

u32 DrIBLObj::getIBLNum() const {
  if (unknown00 != nullptr) {
    return unknown00->unknown08;
  }
  return 0;
}

int DrIBLObj::getPriority() const {
  if (unknown38 != nullptr) {
    return unknown38->unknown08;
  }
  return -1;
}

grlib::CGLibTextureBuffer *DrIBLObj::getAlbedoTexture() const {
  if (unknown38 != nullptr) {
    return &unknown48[unknown38->unknown06];
  }
  return nullptr;
}

grlib::CGLibTextureBuffer *DrIBLObj::getNormalTexture() const {
  if (unknown38 != nullptr) {
    return &unknown50[unknown38->unknown06];
  }
  return nullptr;
}

const char *DrIBLObj::getIBLName(u32 index) const {
  if (unknown08 != nullptr) {
    return reinterpret_cast<const char *>(unknown00) + unknown08[index].unknown0c;
  }
  return nullptr;
}

grlib::CGLibTextureBuffer *DrIBLObj::debug_getAlbedoTexture(u32 index) const {
  if ((unknown58 & 1) == 0) {
    return nullptr;
  }
  if (index < unknown40) {
    return unknown48 + index;
  }
  return nullptr;
}

grlib::CGLibTextureBuffer *DrIBLObj::debug_getNormalTexture(u32 index) const {
  if ((unknown58 & 1) == 0) {
    return nullptr;
  }
  if (index < unknown40) {
    return unknown50 + index;
  }
  return nullptr;
}

void DrIBLObj::debug_renderColli(bool isCurrent) {
  CacheDraw *cacheDraw = DebDraw::getCacheDraw();
  cacheDraw->setMatrix(mm::Mat44::identity);
  cacheDraw->setZComp(false);
  cacheDraw->setZWrite(false);
  const unknown001 *header = unknown00;
  for (int i = 0; i < header->unknown10; i++) {
    const _IBLPrimHeader *primitive = &unknown10[i];
    if (isCurrent && primitive == unknown38) {
      cacheDraw->setCol(mm::Col4(mm::Col3::red.r, mm::Col3::red.g, mm::Col3::red.b, 1.0f));
    } else {
      cacheDraw->setCol(mm::Col4(0.5f, 0.0f, 0.0f, 1.0f));
    }
    (this->*s_pRenderColi[primitive->unknown04])(reinterpret_cast<const u8 *>(unknown00) + primitive->unknown00);
  }
  if (unknown38 != nullptr) {
    const unknown002 *entries = unknown08;
    u32 index = unknown38->unknown06;
    cacheDraw->setCol(mm::Col4(mm::Col3::red.r, mm::Col3::red.g, mm::Col3::red.b, 1.0f));
    const unknown002 &entry = entries[index];
    mm::Vec3 position(entry.unknown00, entry.unknown04, entry.unknown08);
    cacheDraw->setMatrix(mm::Mat44::identity);
    cacheDraw->renderLine(position - mm::Vec3::unitX * 20.0f, position + mm::Vec3::unitX * 20.0f);
    cacheDraw->renderLine(position - mm::Vec3::unitY * 20.0f, position + mm::Vec3::unitY * 20.0f);
    cacheDraw->renderLine(position - mm::Vec3::unitZ * 20.0f, position + mm::Vec3::unitZ * 20.0f);
  }
  cacheDraw->setZComp(true);
}

void DrIBLObj::render_sphere(const u8 *data) {
  CacheDraw *cacheDraw = DebDraw::getCacheDraw();
  const unknown003 *sphere = reinterpret_cast<const unknown003 *>(data);
  cacheDraw->renderSphere(mm::Vec3(sphere->unknown00, sphere->unknown04, sphere->unknown08), sphere->unknown0c, 8);
}

} // namespace ml

template mm::mtl::FixedList<ml::DrIBLObj *, 32>::iterator mm::mtl::FixedList<ml::DrIBLObj *, 32>::erase(mm::mtl::FixedList<ml::DrIBLObj *, 32>::iterator);
