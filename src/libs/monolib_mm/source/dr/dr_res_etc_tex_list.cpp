#include "dr/dr_res_etc_tex_list.h"

#include <new>
#include <string.h>

#include "dr/dr_man.h"
#include "grlib/cglib_texture.h"
#include "grlib/cglib_texture_buffer.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

DrResEtcTexList::DrResEtcTexList(const void *data) {
  unknown30 = 0;
  unknown28 = nullptr;
  unknown20 = 0;
  unknown00 = nullptr;
  unknown08 = nullptr;
  unknown10 = nullptr;
  createTexture(data);
}

DrResEtcTexList::~DrResEtcTexList() { releaseTexture(); }

void DrResEtcTexList::createTexture(const void *data) {
  releaseTexture();
  unknown18 = static_cast<const unknown001 *>(data);
  s32 count = unknown18->unknown08;
  u32 tableOffset = unknown18->unknown0c;
  unknown20 = count;
  u32 size = count * 0x70;
  unknown28 = mtl::MemManager::allocate(DrMan::getIns()->unknown14, size, 8, false, "no name", 0);
  unknown10 = static_cast<grlib::CGLibTextureBuffer *>(unknown28);
  const unknown002 *entry = reinterpret_cast<const unknown002 *>(static_cast<const u8 *>(data) + tableOffset);
  for (int i = 0; i < unknown20; i++, entry++) {
    new (&unknown10[i]) grlib::CGLibTextureBuffer();
    grlib::CGLibTexture::createTextureImagePtrs(unknown10[i], reinterpret_cast<const u8 *>(unknown18) + entry->unknown04, entry->unknown00, false, nullptr, false);
  }
}

void DrResEtcTexList::releaseTexture() {
  if (unknown28 == nullptr) {
    return;
  }
  for (int i = 0; i < unknown20; i++) {
    unknown10[i].~CGLibTextureBuffer();
  }
  if (unknown28 != nullptr) {
    mtl::MemManager::deallocate(unknown28, 0, false);
    unknown28 = nullptr;
  }
  unknown10 = nullptr;
  unknown20 = 0;
}

void DrResEtcTexList::release() { unknown30 |= 1; }

grlib::CGLibTextureBuffer *DrResEtcTexList::getTextureID(u32 id) {
  if ((unknown30 & 1) != 0) {
    return nullptr;
  }
  if (unknown20 > 0) {
    const unknown002 *entry = reinterpret_cast<const unknown002 *>(reinterpret_cast<const u8 *>(unknown18) + unknown18->unknown0c);
    for (int i = 0; i < unknown20; i++, entry++) {
      if (entry->unknown0c == id) {
        return &unknown10[i];
      }
    }
  }
  return nullptr;
}

grlib::CGLibTextureBuffer *DrResEtcTexList::getTextureName(const char *name) {
  if ((unknown30 & 1) == 0 && unknown20 > 0) {
    const u8 *resource = reinterpret_cast<const u8 *>(unknown18);
    const unknown002 *entry = reinterpret_cast<const unknown002 *>(resource + unknown18->unknown0c);
    for (int i = 0; i < unknown20; i++, entry++) {
      if (strcmp(name, reinterpret_cast<const char *>(resource + entry->unknown08)) == 0) {
        return &unknown10[i];
      }
    }
  }
  return nullptr;
}

} // namespace ml
