#include "scn/scn_debug.h"

#include "ml/attr_transform.h"
#include "ml/cache_draw.h"
#include "ml/ml_mem.h"
#include "ml/threadval.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "scn/scn_debug_manipu_rot.h"
#include "scn/scn_debug_manipu_scale.h"
#include "scn/scn_debug_manipu_scale_2d.h"
#include "scn/scn_debug_manipu_trans.h"
#include "scn/scn_debug_manipu_trans_2d.h"

namespace ml {
class EventView;

ScnDebug::ScnDebug(Scn *scn, mtl::ALLOC_HANDLE mem) : m_scn(scn), m_manipulator(nullptr), _20(-1), _28(nullptr), _30(true) { m_manipulator = new (mem) ScnDebugManipu(scn); }

ScnDebug::~ScnDebug() {
  if (m_manipulator != nullptr) {
    delete m_manipulator;
    m_manipulator = nullptr;
  }
}

mtl::ALLOC_HANDLE ScnDebug::getMem() const { return MlMem::getProductMem(); }

bool ScnDebug::isPickManipu() const {
  if (m_manipulator == nullptr) {
    return false;
  }
  return m_manipulator->isPick();
}

const ScnDebugManipu *ScnDebug::getManipulator() const { return m_manipulator; }

bool ScnDebugManipu::isPick() const {
  CS cs(m_criticalSection);
  if (m_scnDebugManipuObj == nullptr) {
    return false;
  }
  return m_scnDebugManipuObj->unknown18 != 0;
}

void ScnDebug::setManipuCalcRotationZXY() { m_manipulator->setCalcRotationZXY(); }

ScnDebugManipu *ScnDebug::getManipulator() { return m_manipulator; }

void ScnDebugManipu::setCalcRotationZXY() {
  CS cs(m_criticalSection);
  if (m_scnDebugManipuObj != nullptr) {
    m_scnDebugManipuObj->unknownb0.m_back->m_attrTransform.unknown130 |= AttrTransform::FLAG_UNKNOWN_3;
  }
}

void ScnDebug::setManipuAxisLock(SCNAXIS axis) { m_manipulator->setAxisLock(axis); }

void ScnDebugManipu::setAxisLock(SCNAXIS axis) {
  CS cs(m_criticalSection);
  if (m_scnDebugManipuObj != nullptr) {
    m_scnDebugManipuObj->unknown14 = axis;
  }
}

SCNAXIS ScnDebug::getManipuAxisLock() const { return m_manipulator->getAxisLock(); }

SCNAXIS ScnDebugManipu::getAxisLock() const {
  CS cs(m_criticalSection);
  if (m_scnDebugManipuObj == nullptr) {
    return SCNAXIS();
  }
  return m_scnDebugManipuObj->unknown14;
}

SCNMANIPU ScnDebug::getManipuType() const { return m_manipulator->getType(); }

SCNMANIPU ScnDebugManipu::getType() const {
  CS cs(m_criticalSection);
  if (m_scnDebugManipuObj == nullptr) {
    return SCNMANIPU_UNKNOWN_FFFFFFFF;
  }
  return m_scnDebugManipuObj->unknown10;
}

void ScnDebug::setManipulatorTrans(const mm::Mat44 *matrix, const mm::Vec3 *scale) { m_manipulator->createTrans(matrix, scale); }

void ScnDebugManipu::createTrans(const mm::Mat44 *matrix, const mm::Vec3 *scale) {
  CS cs(m_criticalSection);
  clear();
  m_scnDebugManipuObj = new (MlMem::getProductMem()) ScnDebugManipuTrans(m_scn, matrix, scale);
  setDisp(unknown40);
}

void ScnDebug::setManipulatorTrans2D(const mm::Mat44 *matrix, const mm::Vec3 *scale) { m_manipulator->createTrans2D(matrix, scale); }

void ScnDebugManipu::createTrans2D(const mm::Mat44 *matrix, const mm::Vec3 *scale) {
  CS cs(m_criticalSection);
  clear();
  m_scnDebugManipuObj = new (MlMem::getProductMem()) ScnDebugManipuTrans2D(m_scn, matrix, scale);
  setDisp(unknown40);
}

void ScnDebug::setManipulatorRot(const mm::Mat44 *matrix, const mm::Vec3 *scale) { m_manipulator->createRot(matrix, scale); }

void ScnDebugManipu::createRot(const mm::Mat44 *matrix, const mm::Vec3 *scale) {
  CS cs(m_criticalSection);
  clear();
  m_scnDebugManipuObj = new (MlMem::getProductMem()) ScnDebugManipuRot(m_scn, matrix, scale);
  setDisp(unknown40);
}

void ScnDebug::setManipulatorScale(const mm::Mat44 *matrix, const mm::Vec3 *scale) { m_manipulator->createScale(matrix, scale); }

void ScnDebugManipu::createScale(const mm::Mat44 *matrix, const mm::Vec3 *scale) {
  CS cs(m_criticalSection);
  clear();
  m_scnDebugManipuObj = new (MlMem::getProductMem()) ScnDebugManipuScale(m_scn, matrix, scale);
  setDisp(unknown40);
}

void ScnDebug::setManipulatorScale2D(const mm::Mat44 *matrix, const mm::Vec3 *scale) { m_manipulator->createScale2D(matrix, scale); }

void ScnDebugManipu::createScale2D(const mm::Mat44 *matrix, const mm::Vec3 *scale) {
  CS cs(m_criticalSection);
  clear();
  m_scnDebugManipuObj = new (MlMem::getProductMem()) ScnDebugManipuScale2D(m_scn, matrix, scale);
  setDisp(unknown40);
}

void ScnDebug::setManipulatorRadius(f32 radius) { m_manipulator->setRadius(radius); }

void ScnDebugManipu::setRadius(f32 radius) {
  CS cs(m_criticalSection);
  if (m_scnDebugManipuObj != nullptr) {
    m_scnDebugManipuObj->setRadius(radius);
  }
}

void ScnDebug::setManipulatorDisp(bool isDisp) { m_manipulator->setDisp(isDisp); }

void ScnDebugManipu::setDisp(bool isDisp) {
  CS cs(m_criticalSection);
  unknown40 = isDisp;
  if (m_scnDebugManipuObj != nullptr) {
    m_scnDebugManipuObj->unknown20 = isDisp;
  }
}

void ScnDebug::clrManipulator() { m_manipulator->clear(); }

void ScnDebugManipu::clear() {
  CS cs(m_criticalSection);
  if (m_scnDebugManipuObj != nullptr) {
    delete m_scnDebugManipuObj;
    m_scnDebugManipuObj = nullptr;
  }
}

const AttrTransform *ScnDebug::getManipuTrans(bool isBack) const {
  if (m_manipulator->getTrans(isBack) == nullptr) {
    return nullptr;
  }
  return m_manipulator->getTrans(isBack);
}

const AttrTransform *ScnDebugManipu::getTrans(bool isBack) const {
  CS cs(m_criticalSection);
  if (m_scnDebugManipuObj == nullptr) {
    return nullptr;
  }
  return &(isBack ? m_scnDebugManipuObj->unknownb0.m_back : m_scnDebugManipuObj->unknownb0.m_front)->m_attrTransform;
}

void ScnDebug::setManipuTrans(const mm::Vec3 *position, const mm::Vec3 *rotation, const mm::Vec3 *scale) {
  if (m_manipulator->getTrans(true) != nullptr) {
    m_manipulator->setTrans(position, rotation, scale);
  }
}

void ScnDebugManipu::setTrans(const mm::Vec3 *position, const mm::Vec3 *rotation, const mm::Vec3 *scale) {
  CS cs(m_criticalSection);
  if (m_scnDebugManipuObj != nullptr) {
    if (position != nullptr) {
      m_scnDebugManipuObj->unknownb0.m_back->m_attrTransform.unknown00 = *position;
    }
    if (rotation != nullptr) {
      m_scnDebugManipuObj->unknownb0.m_back->m_attrTransform.unknownf0 = *rotation;
    }
    if (scale != nullptr) {
      m_scnDebugManipuObj->unknownb0.m_back->m_attrTransform.unknown20 = *scale;
    }
    m_scnDebugManipuObj->unknownb0.m_back->m_attrTransform.update();
  }
}

void ScnDebug::setManipuTrans(const AttrTransform &transform) {
  if (m_manipulator->getTrans(true) != nullptr) {
    m_manipulator->setTrans(transform);
  }
}

void ScnDebugManipu::setTrans(const AttrTransform &transform) {
  CS cs(m_criticalSection);
  if (m_scnDebugManipuObj != nullptr) {
    m_scnDebugManipuObj->unknownb0.m_back->m_attrTransform = transform;
    m_scnDebugManipuObj->unknownb0.m_back->m_attrTransform.update();
  }
}

void ScnDebug::update() {}

void ScnDebugManipu::render(DebDraw *debDraw) {
  CS cs(m_criticalSection);
  if (unknown40 && m_scnDebugManipuObj != nullptr) {
    m_scnDebugManipuObj->render(debDraw);
  }
}

void ScnDebug::render(DebDraw *debDraw) {
  if (m_manipulator != nullptr) {
    m_manipulator->render(debDraw);
  }
}

void ScnDebug::cbRenderAfter(Scn *scn, SCNPRIO_CB priority) { render(DebDraw::get(-1)); }

ScnDebugManipu::ScnDebugManipu(Scn *scn) : m_scn(scn), m_scnDebugManipuObj(nullptr), unknown40(true) {}

ScnDebugManipu::~ScnDebugManipu() { clear(); }

bool ScnDebugManipu::getGblMat(mm::Mat44 &matrix, bool isBack) {
  CS cs(m_criticalSection);
  if (m_scnDebugManipuObj != nullptr) {
    m_scnDebugManipuObj->getGblMat(matrix, isBack);
    return true;
  }
  return false;
}

void ScnDebugManipuObj::getGblMat(mm::Mat44 &matrix, bool isBack) {
  RENDER_INFO *info = isBack ? unknownb0.m_back : unknownb0.m_front;
  matrix.unknown009(info->m_attrTransform.unknown70, unknown30);
}

bool ScnDebugManipu::OnMouseButtonDown(EventView *event) {
  CS cs(m_criticalSection);
  if (m_scnDebugManipuObj == nullptr) {
    return false;
  }
  return m_scnDebugManipuObj->checkMouseButtonDown(event);
}

bool ScnDebugManipu::OnMouseButtonUp(EventView *event) {
  CS cs(m_criticalSection);
  if (m_scnDebugManipuObj == nullptr) {
    return false;
  }
  return m_scnDebugManipuObj->checkMouseButtonUp(event);
}

bool ScnDebugManipu::OnMouseMove(EventView *event) {
  CS cs(m_criticalSection);
  if (m_scnDebugManipuObj == nullptr) {
    return false;
  }
  return m_scnDebugManipuObj->checkMouseMove(event);
}

void ScnDebugManipu::update() {
  CS cs(m_criticalSection);
  if (m_scnDebugManipuObj != nullptr) {
    m_scnDebugManipuObj->update();
  }
}

template class threadval<ScnDebugManipuObj::RENDER_INFO>;

} // namespace ml

// The game builds the manipulator objects in the same unit: the create functions of ScnDebugManipu inline their constructors.
// clang-format off
#include "scn_debug_manipu_rot.cpp"
#include "scn_debug_manipu_scale.cpp"
#include "scn_debug_manipu_scale_2d.cpp"
#include "scn_debug_manipu_trans.cpp"
#include "scn_debug_manipu_trans_2d.cpp"
// clang-format on
