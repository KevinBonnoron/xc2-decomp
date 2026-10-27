#include "dr/dr_mdo_texture_man.h"

#include "dr/dr_res_etc_tex_list.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

DrMdoTextureMan::DrMdoTextureMan(DrMan *drMan) : unknown00(drMan), unknown08(nullptr), unknown10(nullptr), unknown18(nullptr), unknown20(nullptr) {}

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
