#include "dr/dr_mdo_tex_simple_man.h"

#include "dr/dr_man.h"
#include "dr/dr_res_mdo_tex_list.h"
#include "ml/critical_section.h"
#include "mtl/alloc_handle.h"

namespace ml {

DrMdoTexSimpleMan::DrMdoTexSimpleMan(DrMan *drMan) : unknown00(drMan), unknown08(), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr) {}

DrMdoTexSimpleMan::~DrMdoTexSimpleMan() {
  for (int i = 0; i < 2; i++) {
    DrResMdoTexSimple *tex = unknown08[i][0];
    while (tex != nullptr) {
      DrResMdoTexSimple *next = tex->unknown08;
      delete tex;
      tex = next;
    }
    unknown08[i][0] = nullptr;
    unknown08[i][1] = nullptr;
  }
  DrResMdoTexSimple *tex = unknown38;
  while (tex != nullptr) {
    DrResMdoTexSimple *next = tex->unknown08;
    delete tex;
    tex = next;
  }
  unknown38 = nullptr;
  unknown40 = nullptr;
  tex = unknown28;
  while (tex != nullptr) {
    DrResMdoTexSimple *next = tex->unknown08;
    delete tex;
    tex = next;
  }
  unknown28 = nullptr;
  unknown30 = nullptr;
}

DrResMdoTexSimple *DrMdoTexSimpleMan::createTextureObj(const void *data, int size, bool isMiddle) {
  CS lock(DrMan::getCriticalSection());
  DrResMdoTexSimple *tex = new (unknown00->unknown10) DrResMdoTexSimple(data, size, isMiddle);
  DrResMdoTexSimple **list = unknown08[DrMan::s_nDblStockIdx];
  if (list[1] == nullptr) {
    list[0] = tex;
    list[1] = tex;
    tex->unknown00 = nullptr;
  } else {
    list[1]->unknown08 = tex;
    tex->unknown00 = list[1];
    list[1] = tex;
  }
  tex->unknown08 = nullptr;
  return tex;
}

} // namespace ml
