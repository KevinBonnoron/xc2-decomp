#include "scn/scn_debug.h"

#include "ml/attr_transform.h"
#include "ml/cache_draw.h"
#include "ml/ml_mem.h"
#include "ml/threadval.h"
#include "mm_math/mm_vec3.h"

namespace ml {
class EventView;

ScnDebug::ScnDebug(Scn *scn, mtl::ALLOC_HANDLE mem) : m_scn(scn), m_manipu(nullptr), _20(-1), _28(nullptr), _30(true) { m_manipu = new (mem) ScnDebugManipu(scn); }

ScnDebug::~ScnDebug() {
  if (m_manipu != nullptr) {
    delete m_manipu;
    m_manipu = nullptr;
  }
}

mtl::ALLOC_HANDLE ScnDebug::getMem() const { return MlMem::getProductMem(); }

bool ScnDebug::isPickManipu() const {
  if (m_manipu == nullptr) {
    return false;
  }
  return m_manipu->isPick();
}

const ScnDebugManipu *ScnDebug::getManipulator() const { return m_manipu; }

bool ScnDebugManipu::isPick() const {
  CS cs(m_cs);
  if (m_obj == nullptr) {
    return false;
  }
  return m_obj->m_pick != 0;
}

void ScnDebug::setManipuCalcRotationZXY() { m_manipu->setCalcRotationZXY(); }

ScnDebugManipu *ScnDebug::getManipulator() { return m_manipu; }

void ScnDebugManipu::setCalcRotationZXY() {
  CS cs(m_cs);
  if (m_obj != nullptr) {
    m_obj->m_renderInfo.m_back->transform.m_flags |= AttrTransform::FLAG_ROTATION_ZXY;
  }
}

void ScnDebug::setManipuAxisLock(SCNAXIS axis) { m_manipu->setAxisLock(axis); }

void ScnDebugManipu::setAxisLock(SCNAXIS axis) {
  CS cs(m_cs);
  if (m_obj != nullptr) {
    m_obj->m_axisLock = axis;
  }
}

SCNAXIS ScnDebug::getManipuAxisLock() const { return m_manipu->getAxisLock(); }

SCNAXIS ScnDebugManipu::getAxisLock() const {
  CS cs(m_cs);
  if (m_obj == nullptr) {
    return SCNAXIS();
  }
  return m_obj->m_axisLock;
}

SCNMANIPU ScnDebug::getManipuType() const { return m_manipu->getType(); }

SCNMANIPU ScnDebugManipu::getType() const {
  CS cs(m_cs);
  if (m_obj == nullptr) {
    return SCNMANIPU_NONE;
  }
  return m_obj->m_type;
}

void ScnDebug::setManipulatorTrans(const mm::Mat44 *matrix, const mm::Vec3 *scale) { m_manipu->createTrans(matrix, scale); }

void ScnDebug::setManipulatorTrans2D(const mm::Mat44 *matrix, const mm::Vec3 *scale) { m_manipu->createTrans2D(matrix, scale); }

void ScnDebug::setManipulatorRot(const mm::Mat44 *matrix, const mm::Vec3 *scale) { m_manipu->createRot(matrix, scale); }

void ScnDebug::setManipulatorScale(const mm::Mat44 *matrix, const mm::Vec3 *scale) { m_manipu->createScale(matrix, scale); }

void ScnDebug::setManipulatorScale2D(const mm::Mat44 *matrix, const mm::Vec3 *scale) { m_manipu->createScale2D(matrix, scale); }

void ScnDebug::setManipulatorRadius(f32 radius) { m_manipu->setRadius(radius); }

void ScnDebugManipu::setRadius(f32 radius) {
  CS cs(m_cs);
  if (m_obj != nullptr) {
    m_obj->setRadius(radius);
  }
}

void ScnDebug::setManipulatorDisp(bool isDisp) { m_manipu->setDisp(isDisp); }

void ScnDebugManipu::setDisp(bool isDisp) {
  CS cs(m_cs);
  m_isDisp = isDisp;
  if (m_obj != nullptr) {
    m_obj->m_isDisp = isDisp;
  }
}

void ScnDebug::clrManipulator() { m_manipu->clear(); }

void ScnDebugManipu::clear() {
  CS cs(m_cs);
  if (m_obj != nullptr) {
    delete m_obj;
    m_obj = nullptr;
  }
}

const AttrTransform *ScnDebug::getManipuTrans(bool isBack) const {
  if (m_manipu->getTrans(isBack) == nullptr) {
    return nullptr;
  }
  return m_manipu->getTrans(isBack);
}

const AttrTransform *ScnDebugManipu::getTrans(bool isBack) const {
  CS cs(m_cs);
  if (m_obj == nullptr) {
    return nullptr;
  }
  return &(isBack ? m_obj->m_renderInfo.m_back : m_obj->m_renderInfo.m_front)->transform;
}

void ScnDebug::setManipuTrans(const mm::Vec3 *position, const mm::Vec3 *rotation, const mm::Vec3 *scale) {
  if (m_manipu->getTrans(true) != nullptr) {
    m_manipu->setTrans(position, rotation, scale);
  }
}

void ScnDebugManipu::setTrans(const mm::Vec3 *position, const mm::Vec3 *rotation, const mm::Vec3 *scale) {
  CS cs(m_cs);
  if (m_obj != nullptr) {
    if (position != nullptr) {
      m_obj->m_renderInfo.m_back->transform.m_pos = *position;
    }
    if (rotation != nullptr) {
      m_obj->m_renderInfo.m_back->transform.m_rot = *rotation;
    }
    if (scale != nullptr) {
      m_obj->m_renderInfo.m_back->transform.m_scl = *scale;
    }
    m_obj->m_renderInfo.m_back->transform.update();
  }
}

void ScnDebug::setManipuTrans(const AttrTransform &transform) {
  if (m_manipu->getTrans(true) != nullptr) {
    m_manipu->setTrans(transform);
  }
}

void ScnDebugManipu::setTrans(const AttrTransform &transform) {
  CS cs(m_cs);
  if (m_obj != nullptr) {
    m_obj->m_renderInfo.m_back->transform = transform;
    m_obj->m_renderInfo.m_back->transform.update();
  }
}

void ScnDebug::update() {}

void ScnDebugManipu::render(DebDraw *debDraw) {
  CS cs(m_cs);
  if (m_isDisp && m_obj != nullptr) {
    m_obj->render(debDraw);
  }
}

void ScnDebug::cbRenderAfter(Scn *scn, SCNPRIO_CB priority) { render(DebDraw::get(-1)); }

ScnDebugManipu::ScnDebugManipu(Scn *scn) : m_scn(scn), m_obj(nullptr), m_isDisp(true) {}

ScnDebugManipu::~ScnDebugManipu() { clear(); }

bool ScnDebugManipu::getGblMat(mm::Mat44 &matrix, bool isBack) {
  CS cs(m_cs);
  if (m_obj != nullptr) {
    m_obj->getGblMat(matrix, isBack);
    return true;
  }
  return false;
}

bool ScnDebugManipu::OnMouseButtonDown(EventView *event) {
  CS cs(m_cs);
  if (m_obj == nullptr) {
    return false;
  }
  return m_obj->checkMouseButtonDown(event);
}

bool ScnDebugManipu::OnMouseButtonUp(EventView *event) {
  CS cs(m_cs);
  if (m_obj == nullptr) {
    return false;
  }
  return m_obj->checkMouseButtonUp(event);
}

bool ScnDebugManipu::OnMouseMove(EventView *event) {
  CS cs(m_cs);
  if (m_obj == nullptr) {
    return false;
  }
  return m_obj->checkMouseMove(event);
}

void ScnDebugManipu::update() {
  CS cs(m_cs);
  if (m_obj != nullptr) {
    m_obj->update();
  }
}

} // namespace ml
