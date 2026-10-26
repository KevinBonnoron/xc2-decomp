#include "dr/dr_mdo_zsort.h"

namespace ml {

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
