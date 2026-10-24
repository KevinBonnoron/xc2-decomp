#include "scn/scn_debug.h"

#include "ml/attr_transform.h"
#include "ml/cache_draw.h"
#include "ml/ml_mem.h"
#include "ml/threadval.h"
#include "mm_math/mm_vec3.h"

namespace ml {
class EventView;

ScnDebug::ScnDebug(Scn *scn, mtl::ALLOC_HANDLE mem) : unknown10(scn), m_manipulator(nullptr), _20(-1), _28(nullptr), _30(true) { m_manipulator = new (mem) ScnDebugManipu(scn); }

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
  CS cs(unknown08);
  if (unknown38 == nullptr) {
    return false;
  }
  return unknown38->unknown18 != 0;
}

void ScnDebug::setManipuCalcRotationZXY() { m_manipulator->setCalcRotationZXY(); }

ScnDebugManipu *ScnDebug::getManipulator() { return m_manipulator; }

void ScnDebugManipu::setCalcRotationZXY() {
  CS cs(unknown08);
  if (unknown38 != nullptr) {
    unknown38->unknownb0.m_back->unknown00.unknown130 |= AttrTransform::FLAG_ROTATION_ZXY;
  }
}

void ScnDebug::setManipuAxisLock(SCNAXIS axis) { m_manipulator->setAxisLock(axis); }

void ScnDebugManipu::setAxisLock(SCNAXIS axis) {
  CS cs(unknown08);
  if (unknown38 != nullptr) {
    unknown38->unknown14 = axis;
  }
}

SCNAXIS ScnDebug::getManipuAxisLock() const { return m_manipulator->getAxisLock(); }

SCNAXIS ScnDebugManipu::getAxisLock() const {
  CS cs(unknown08);
  if (unknown38 == nullptr) {
    return SCNAXIS();
  }
  return unknown38->unknown14;
}

SCNMANIPU ScnDebug::getManipuType() const { return m_manipulator->getType(); }

SCNMANIPU ScnDebugManipu::getType() const {
  CS cs(unknown08);
  if (unknown38 == nullptr) {
    return SCNMANIPU_NONE;
  }
  return unknown38->unknown10;
}

void ScnDebug::setManipulatorTrans(const mm::Mat44 *matrix, const mm::Vec3 *scale) { m_manipulator->createTrans(matrix, scale); }

void ScnDebug::setManipulatorTrans2D(const mm::Mat44 *matrix, const mm::Vec3 *scale) { m_manipulator->createTrans2D(matrix, scale); }

void ScnDebug::setManipulatorRot(const mm::Mat44 *matrix, const mm::Vec3 *scale) { m_manipulator->createRot(matrix, scale); }

void ScnDebug::setManipulatorScale(const mm::Mat44 *matrix, const mm::Vec3 *scale) { m_manipulator->createScale(matrix, scale); }

void ScnDebug::setManipulatorScale2D(const mm::Mat44 *matrix, const mm::Vec3 *scale) { m_manipulator->createScale2D(matrix, scale); }

void ScnDebug::setManipulatorRadius(f32 radius) { m_manipulator->setRadius(radius); }

void ScnDebugManipu::setRadius(f32 radius) {
  CS cs(unknown08);
  if (unknown38 != nullptr) {
    unknown38->setRadius(radius);
  }
}

void ScnDebug::setManipulatorDisp(bool isDisp) { m_manipulator->setDisp(isDisp); }

void ScnDebugManipu::setDisp(bool isDisp) {
  CS cs(unknown08);
  unknown40 = isDisp;
  if (unknown38 != nullptr) {
    unknown38->unknown20 = isDisp;
  }
}

void ScnDebug::clrManipulator() { m_manipulator->clear(); }

void ScnDebugManipu::clear() {
  CS cs(unknown08);
  if (unknown38 != nullptr) {
    delete unknown38;
    unknown38 = nullptr;
  }
}

const AttrTransform *ScnDebug::getManipuTrans(bool isBack) const {
  if (m_manipulator->getTrans(isBack) == nullptr) {
    return nullptr;
  }
  return m_manipulator->getTrans(isBack);
}

const AttrTransform *ScnDebugManipu::getTrans(bool isBack) const {
  CS cs(unknown08);
  if (unknown38 == nullptr) {
    return nullptr;
  }
  return &(isBack ? unknown38->unknownb0.m_back : unknown38->unknownb0.m_front)->unknown00;
}

void ScnDebug::setManipuTrans(const mm::Vec3 *position, const mm::Vec3 *rotation, const mm::Vec3 *scale) {
  if (m_manipulator->getTrans(true) != nullptr) {
    m_manipulator->setTrans(position, rotation, scale);
  }
}

void ScnDebugManipu::setTrans(const mm::Vec3 *position, const mm::Vec3 *rotation, const mm::Vec3 *scale) {
  CS cs(unknown08);
  if (unknown38 != nullptr) {
    if (position != nullptr) {
      unknown38->unknownb0.m_back->unknown00.unknown00 = *position;
    }
    if (rotation != nullptr) {
      unknown38->unknownb0.m_back->unknown00.unknownf0 = *rotation;
    }
    if (scale != nullptr) {
      unknown38->unknownb0.m_back->unknown00.unknown20 = *scale;
    }
    unknown38->unknownb0.m_back->unknown00.update();
  }
}

void ScnDebug::setManipuTrans(const AttrTransform &transform) {
  if (m_manipulator->getTrans(true) != nullptr) {
    m_manipulator->setTrans(transform);
  }
}

void ScnDebugManipu::setTrans(const AttrTransform &transform) {
  CS cs(unknown08);
  if (unknown38 != nullptr) {
    unknown38->unknownb0.m_back->unknown00 = transform;
    unknown38->unknownb0.m_back->unknown00.update();
  }
}

void ScnDebug::update() {}

void ScnDebugManipu::render(DebDraw *debDraw) {
  CS cs(unknown08);
  if (unknown40 && unknown38 != nullptr) {
    unknown38->render(debDraw);
  }
}

void ScnDebug::cbRenderAfter(Scn *scn, SCNPRIO_CB priority) { render(DebDraw::get(-1)); }

ScnDebugManipu::ScnDebugManipu(Scn *scn) : unknown30(scn), unknown38(nullptr), unknown40(true) {}

ScnDebugManipu::~ScnDebugManipu() { clear(); }

bool ScnDebugManipu::getGblMat(mm::Mat44 &matrix, bool isBack) {
  CS cs(unknown08);
  if (unknown38 != nullptr) {
    unknown38->getGblMat(matrix, isBack);
    return true;
  }
  return false;
}

bool ScnDebugManipu::OnMouseButtonDown(EventView *event) {
  CS cs(unknown08);
  if (unknown38 == nullptr) {
    return false;
  }
  return unknown38->checkMouseButtonDown(event);
}

bool ScnDebugManipu::OnMouseButtonUp(EventView *event) {
  CS cs(unknown08);
  if (unknown38 == nullptr) {
    return false;
  }
  return unknown38->checkMouseButtonUp(event);
}

bool ScnDebugManipu::OnMouseMove(EventView *event) {
  CS cs(unknown08);
  if (unknown38 == nullptr) {
    return false;
  }
  return unknown38->checkMouseMove(event);
}

void ScnDebugManipu::update() {
  CS cs(unknown08);
  if (unknown38 != nullptr) {
    unknown38->update();
  }
}

} // namespace ml
