#include "dr/dr_mdo_texture_man.h"

#include "dr/dr_man.h"
#include "dr/dr_res_etc_tex_list.h"
#include "dr/dr_res_mdo_tex_list.h"
#include "mtl/alloc_handle.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

DrMdoTextureMan::DrMdoTextureMan(DrMan *drMan) : unknown00(drMan), unknown08(nullptr), unknown10(nullptr), unknown18(nullptr), unknown20(nullptr) {}

DrMdoTextureMan::~DrMdoTextureMan() {
  DrResMdoTexList *mdoList = unknown08;
  while (mdoList != nullptr) {
    DrResMdoTexList *next = mdoList->unknown08;
    delete mdoList;
    mdoList = next;
  }
  unknown08 = nullptr;
  unknown10 = nullptr;
  DrResEtcTexList *etcList = unknown18;
  while (etcList != nullptr) {
    DrResEtcTexList *next = etcList->unknown08;
    delete etcList;
    etcList = next;
  }
  unknown18 = nullptr;
  unknown20 = nullptr;
}

DrResMdoTexList *DrMdoTextureMan::createTextureObj(const u8 *data) {
  for (DrResMdoTexList *list = unknown08; list != nullptr; list = list->unknown08) {
    if (list->unknown10 == data) {
      list->unknown18++;
      return list;
    }
  }
  DrResMdoTexList *list = new (unknown00->unknown10) DrResMdoTexList(data);
  if (list != nullptr) {
    if (unknown10 == nullptr) {
      unknown08 = list;
      unknown10 = list;
      list->unknown00 = nullptr;
    } else {
      unknown10->unknown08 = list;
      list->unknown00 = unknown10;
      unknown10 = list;
    }
    list->unknown08 = nullptr;
  }
  return list;
}

DrResMdoTexList *DrMdoTextureMan::createTextureObj(const u8 *header, const u8 *data) {
  for (DrResMdoTexList *list = unknown08; list != nullptr; list = list->unknown08) {
    if (list->unknown10 == header) {
      list->unknown18++;
      return list;
    }
  }
  DrResMdoTexList *list = new (unknown00->unknown10) DrResMdoTexList(header, data);
  if (list != nullptr) {
    if (unknown10 == nullptr) {
      unknown08 = list;
      unknown10 = list;
      list->unknown00 = nullptr;
    } else {
      unknown10->unknown08 = list;
      list->unknown00 = unknown10;
      unknown10 = list;
    }
    list->unknown08 = nullptr;
  }
  return list;
}

void DrMdoTextureMan::releaseTextureObj(DrResMdoTexList *list) {
  list->unknown18--;
  if (list->unknown18 < 0) {
    list->unknown18 = 0;
  }
  if (list->unknown18 > 0) {
    return;
  }
  DrResMdoTexList *prev = list->unknown00;
  DrResMdoTexList *next = list->unknown08;
  if (prev == nullptr) {
    if (next != nullptr) {
      unknown08 = next;
      next->unknown00 = nullptr;
    } else {
      unknown08 = nullptr;
      unknown10 = nullptr;
    }
  } else if (next != nullptr) {
    prev->unknown08 = next;
    list->unknown08->unknown00 = list->unknown00;
  } else {
    unknown10 = prev;
    prev->unknown08 = nullptr;
  }
  list->unknown00 = nullptr;
  list->unknown08 = nullptr;
  delete list;
}

DrResEtcTexList *DrMdoTextureMan::createEtxTexture(const u8 *data) {
  DrResEtcTexList *list = new (unknown00->unknown10) DrResEtcTexList(data);
  if (unknown20 == nullptr) {
    unknown18 = list;
    unknown20 = list;
    list->unknown00 = nullptr;
  } else {
    unknown20->unknown08 = list;
    list->unknown00 = unknown20;
    unknown20 = list;
  }
  list->unknown08 = nullptr;
  return list;
}

grlib::CGLibTextureBuffer *DrMdoTextureMan::getTextureID(u32 id) {
  for (DrResEtcTexList *list = unknown18; list != nullptr; list = list->unknown08) {
    grlib::CGLibTextureBuffer *texture = list->getTextureID(id);
    if (texture != nullptr) {
      return texture;
    }
  }
  return nullptr;
}

grlib::CGLibTextureBuffer *DrMdoTextureMan::getTextureName(const char *name) {
  for (DrResEtcTexList *list = unknown18; list != nullptr; list = list->unknown08) {
    grlib::CGLibTextureBuffer *texture = list->getTextureName(name);
    if (texture != nullptr) {
      return texture;
    }
  }
  return nullptr;
}

} // namespace ml
