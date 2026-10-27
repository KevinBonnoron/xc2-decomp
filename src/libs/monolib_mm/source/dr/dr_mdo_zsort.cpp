#include "dr/dr_mdo_zsort.h"

#include <string.h>

#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "mtl/mem_manager.h"

namespace ml {

DrMdoZSortMan::~DrMdoZSortMan() {
  if (unknown20 != nullptr) {
    mtl::MemManager::deallocate(unknown20, 0, false);
    unknown20 = nullptr;
  }
}

void DrMdoZSortMan::beginViewWorld() {
  const mm::Vec3 &viewPos = unknown00->unknown580->unknown10->unknown400;
  memset(unknown18, 0, 64);
  unknown40 = viewPos;
  unknown28 = nullptr;
  unknown30 = nullptr;
  unknown38 = nullptr;
}

void DrMdoZSortMan::stockObj(DrMdoZSortObj *object, int index) {
  u32 bits = unknown18[index >> 5];
  u32 mask = 1 << (index & 31);
  if ((bits & mask) == 0) {
    unknown18[index >> 5] = bits | mask;
    object->setParent(nullptr);
    unknown08[index] = object;
  } else {
    object->setParent(unknown10[index]);
    unknown10[index]->setNext(object);
  }
  object->setNext(nullptr);
  unknown10[index] = object;
}

void DrMdoZSortMan::setViewCloud(DrMdoZSortObj *object) { stockObj(object, 510); }

void DrMdoZSortMan::setViewCloudBack(DrMdoZSortObj *object) { stockObj(object, 511); }

void DrMdoZSortMan::setViewLast(DrMdoZSortObj *object) { stockObj(object, 505); }

void DrMdoZSortMan::setViewSeamLast(DrMdoZSortObj *object) {
  if (unknown38 != nullptr) {
    stockObj(object, 511);
  } else {
    unknown38 = object;
  }
}

void DrMdoZSortMan::setViewWorldPos(DrMdoZSortObj *object, const mm::Vec3 &position) {
  f32 ratio = unknown001(position);
  if (ratio >= 1.0f) {
    stockObj(object, 505);
  } else if (ratio <= 0.001f) {
    stockObj(object, 4);
  } else {
    ratio = powf(ratio, unknown54);
    int index = static_cast<int>(ratio * 502.0f) + 4;
    if (index > 505) {
      index = 505;
    } else if (index < 4) {
      index = 4;
    }
    stockObj(object, index);
  }
}

void DrMdoZSortMan::setViewWorldPosLastAlpha(DrMdoZSortObj *object, const mm::Vec3 &position) {
  f32 ratio = unknown001(position);
  if (ratio >= 1.0f) {
    stockObj(object, 3);
  } else if (ratio <= 0.001f) {
    stockObj(object, 0);
  } else {
    ratio = powf(ratio, unknown54);
    int index = static_cast<int>(ratio * 4.0f);
    if (index > 3) {
      index = 3;
    } else if (index < 0) {
      index = 0;
    }
    stockObj(object, index);
  }
}

void DrMdoZSortMan::setViewWorldPosFastAlpha(DrMdoZSortObj *object, const mm::Vec3 &position) {
  f32 ratio = unknown001(position);
  if (ratio >= 1.0f) {
    stockObj(object, 509);
  } else if (ratio <= 0.001f) {
    stockObj(object, 506);
  } else {
    ratio = powf(ratio, unknown54);
    int index = static_cast<int>(ratio * 4.0f) + 506;
    if (index > 508) {
      index = 509;
    } else if (index < 506) {
      index = 506;
    }
    stockObj(object, index);
  }
}

void DrMdoZSortMan::endViewWorld() {
  for (int i = 0; i < 512; i++) {
    if ((unknown18[i >> 5] & (1 << (i & 31))) != 0) {
      if (unknown28 == nullptr) {
        unknown28 = unknown08[i];
      } else {
        unknown30->setNext(unknown08[i]);
        unknown08[i]->setParent(unknown30);
      }
      unknown30 = unknown10[i];
    }
  }
}

void DrMdoZSortObj::setNext(DrMdoZSortObj *next) { m_next = next; }

void DrMdoZSortObj::setParent(DrMdoZSortObj *parent) {
  if (this != parent) {
    m_parent = parent;
  }
}

DrMdoZSortObj *DrMdoZSortObj::getNext() { return m_next; }

DrMdoZSortObj *DrMdoZSortObj::getParent() { return m_parent; }

DrMdoZSortObj::DrMdoZSortObj(void *owner) : m_next(nullptr), m_parent(nullptr), unknown18(owner) {}

void DrMdoZSortMan::viewSetupRender() {
  if (unknown38 != nullptr) {
    unknown38->SetupRender();
  }
  for (DrMdoZSortObj *object = unknown28; object != nullptr; object = object->m_next) {
    object->SetupRender();
  }
}

void DrMdoZSortMan::viewZPrepassRender() {
  if (unknown38 != nullptr) {
    unknown38->ZPrepassRender();
  }
  for (DrMdoZSortObj *object = unknown28; object != nullptr; object = object->m_next) {
    object->ZPrepassRender();
  }
}

void DrMdoZSortMan::viewThicknessRenderFirst() {
  if (unknown38 != nullptr) {
    unknown38->ThicknessRenderFirst();
  }
  for (DrMdoZSortObj *object = unknown28; object != nullptr; object = object->m_next) {
    object->ThicknessRenderFirst();
  }
}

void DrMdoZSortMan::viewThicknessRenderSecond() {
  if (unknown38 != nullptr) {
    unknown38->ThicknessRenderSecond();
  }
  for (DrMdoZSortObj *object = unknown28; object != nullptr; object = object->m_next) {
    object->ThicknessRenderSecond();
  }
}

void DrMdoZSortMan::viewLightPrePassRender() {
  if (unknown38 != nullptr) {
    unknown38->lightPrePassRender();
  }
  for (DrMdoZSortObj *object = unknown30; object != nullptr; object = object->m_parent) {
    object->lightPrePassRender();
  }
}

void DrMdoZSortMan::viewAlphaRender() {
  if (unknown38 != nullptr) {
    unknown38->alphaRender();
  }
  for (DrMdoZSortObj *object = unknown30; object != nullptr; object = object->m_parent) {
    object->alphaRender();
  }
}

void DrMdoZSortMan::viewSpAlphaRender() {
  if (unknown38 != nullptr) {
    unknown38->spAlphaRender();
  }
  for (DrMdoZSortObj *object = unknown30; object != nullptr; object = object->m_parent) {
    object->spAlphaRender();
  }
}

void DrMdoZSortMan::viewRefractionRender() {
  if (unknown38 != nullptr) {
    unknown38->refractionRender();
  }
  for (DrMdoZSortObj *object = unknown30; object != nullptr; object = object->m_parent) {
    object->refractionRender();
  }
}

void DrMdoZSortMan::viewRender() {
  for (DrMdoZSortObj *object = unknown28; object != nullptr; object = object->m_next) {
    object->render();
  }
  if (unknown38 != nullptr) {
    unknown38->render();
  }
}

void DrMdoZSortMan::viewGBuffRender() {
  for (DrMdoZSortObj *object = unknown28; object != nullptr; object = object->m_next) {
    object->GBuffRender();
  }
  if (unknown38 != nullptr) {
    unknown38->GBuffRender();
  }
}

} // namespace ml
