#include "event/object_chara.h"

#include <math.h>

#include "mm_math/mm_math.h"

#include "event/bou_rect.h"
#include "event/chara_manager.h"
#include "event/frame_manager.h"
#include "event/mani_manager.h"
#include "event/memory_manager.h"
#include "event/object_manager.h"
#include "event/object_util.h"
#include "mm_math/mm_mat44.h"
#include "mtl/alloc_handle.h"

namespace event {

mm::Vec3 ObjectChara::getPos() const { return m_charaObj->getPos(); }

mm::Vec3 ObjectChara::getRot() const { return m_charaObj->getRotTo(); }

void ObjectChara::resetTar() { m_charaObj->resetTar(); }

bool ObjectChara::OnBouRectSelect(const IBouCallback::SelectParam &param) {
  const BouRect *rect = param.rect;
  mm::Vec3 pos = m_charaObj->getPos();
  if (rect->isInside(pos)) {
    mm::mtl::Singleton<ManiManager>::getPtr()->addManipulate(this, static_cast<MANI_TYPE>(0));
    return true;
  }
  mm::mtl::Singleton<ManiManager>::getPtr()->removeManipulate(this);
  return false;
}

ObjectChara::ObjectChara(const char *name) : Object(OBJTYPE_UNKNOWN_2, name), unknown68(0), m_charaObj(nullptr) {}

ObjectChara::~ObjectChara() {
  if (m_charaObj != nullptr) {
    delete m_charaObj;
    m_charaObj = nullptr;
  }
}

void ObjectChara::createGfObj(gf::GF_OBJ_HANDLE *handle) {
  m_charaObj = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) CharaObj(getName());
  m_charaObj->createGfObj(handle);
  unknown68 |= FLAG_UNKNOWN_0;
}

void ObjectChara::createGfObj(CHARA_TYPE type, u32 id, u32 param3, u32 param4) {
  m_charaObj = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) CharaObj(getName());
  m_charaObj->createGfObj(type, id, param3, param4);
  unknown68 |= FLAG_UNKNOWN_0;
}

void ObjectChara::createModel(const char *model, u32 param2, u32 param3) {
  m_charaObj = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) CharaObj(getName());
  m_charaObj->createModel(model, param2, param3);
  unknown68 &= ~FLAG_UNKNOWN_0;
}

void ObjectChara::createGhost() {
  m_charaObj = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) CharaObj(getName());
  m_charaObj->createGhost();
  unknown68 |= FLAG_UNKNOWN_0;
}

void ObjectChara::clear() {
  if (m_charaObj != nullptr) {
    m_charaObj->clear();
  }
}

void ObjectChara::start() {
  if (m_charaObj != nullptr) {
    m_charaObj->start();
  }
}

void ObjectChara::end() {
  if (m_charaObj != nullptr) {
    m_charaObj->end();
  }
}

void ObjectChara::update() {
  const FrameInfo &info = mm::mtl::Singleton<FrameManager>::getPtr()->frameInfo();
  if (m_charaObj != nullptr) {
    m_charaObj->update(info);
  }
}

// 0x71001107d0, 524 instructions. The actor/box block of the first branch is written out as in OnBouRender and OnManiRender (ruling 8, measured at OnBouRender).
void ObjectChara::render(const mm::Col4 &color) {
  if (mm::mtl::Singleton<ObjectManager>::getPtr()->isDisp()) {
    if ((unknown68 & FLAG_UNKNOWN_0) != 0) {
      ObjectUtil::drawActor(getPos(), m_charaObj->getRotTo().y, m_charaObj->getEyeOffset(), color, m_charaObj->isTar() ? &m_charaObj->getTar() : nullptr);
    } else {
      ObjectUtil::drawObject(getPos(), getRot(), color);
    }
  }
  if (mm::mtl::Singleton<CharaManager>::getPtr()->isCharaDisp()) {
    ObjectUtil::drawChara(getName(), getPos(), getRot(), m_charaObj->isTar() ? m_tarAxis.getOrigName() : nullptr, m_charaObj->getEyeOffset(), m_charaObj->getHandle());
    if ((unknown68 & FLAG_UNKNOWN_0) != 0) {
      ObjectUtil::drawState(getPos(), m_charaObj->getEyeOffset(), m_charaObj->getHandle());
    }
    if (m_charaObj != nullptr) {
      m_charaObj->renderAction();
    }
    if (m_charaObj != nullptr) {
      m_charaObj->renderMotion();
    }
  }
  if (mm::mtl::Singleton<CharaManager>::getPtr()->isFacialDisp()) {
    if (m_charaObj != nullptr) {
      m_charaObj->renderHead();
    }
    if (m_charaObj != nullptr) {
      m_charaObj->renderFacial();
    }
    if (m_charaObj != nullptr) {
      m_charaObj->renderWink();
    }
    if (m_charaObj != nullptr) {
      m_charaObj->renderLens();
    }
    if (m_charaObj != nullptr) {
      m_charaObj->renderTalk();
    }
    if (m_charaObj != nullptr) {
      m_charaObj->renderWeight();
    }
    if (m_charaObj != nullptr) {
      m_charaObj->renderIK();
    }
  }
  if (mm::mtl::Singleton<CharaManager>::getPtr()->isBoneDisp()) {
    if (m_charaObj != nullptr) {
      m_charaObj->renderBone();
    }
  }
}

void ObjectChara::setTar(const TarAxis &axis, f32 frame, EVT_tarcvtype cv, EVT_aimtype aim, f32 weight, f32 speed) {
  m_tarAxis = axis;
  m_charaObj->setTar(axis, frame, cv, aim, weight, speed);
}

bool ObjectChara::isTar() const { return m_charaObj->isTar(); }

void ObjectChara::tail() {
  const FrameInfo &info = mm::mtl::Singleton<FrameManager>::getPtr()->frameInfo();
  if (m_charaObj != nullptr) {
    m_charaObj->tail(info);
  }
}

bool ObjectChara::isLoading() const { return !m_charaObj->isReady(); }

// The game (0x710011114c) ends with a tail call to CharaObj::mount (b at 0x710011127c), as linerPosAxis does. Without
// CharaObj::walkPos defined earlier in this unit (chara_obj.cpp) the tail call is lost (78 instructions instead of 77):
// LLVM only infers nocapture on the position argument, and so can mark the call tail, from a definition.
void ObjectChara::walkPosAxis(const PosAxis &axis, EVT_poscvtype cv, bool isRun) {
  m_posAxis = axis;
  m_charaObj->walkPos(mm::mtl::Singleton<DataManager>::getPtr()->axis2pos(axis.getAxis(), axis.getPos().x, axis.getPos().y, axis.getPos().z), cv, isRun);
  m_charaObj->mount(nullptr, "", mm::Vec3::zero, mm::Vec3::zero);
}

void ObjectChara::linerPosAxis(const PosAxis &axis, bool isWalk, f32 frame, CV_TYPE cv) {
  m_posAxis = axis;
  m_charaObj->linerPos(mm::mtl::Singleton<DataManager>::getPtr()->axis2pos(axis.getAxis(), axis.getPos().x, axis.getPos().y, axis.getPos().z), isWalk, frame, cv);
  m_charaObj->mount(nullptr, "", mm::Vec3::zero, mm::Vec3::zero);
}

void ObjectChara::turnRotAxis(const RotAxis &axis, EVT_rotcvtype cv, f32 frame) {
  m_rotAxis = axis;
  const mm::Vec3 &pos = m_charaObj->getPosTo();
  m_charaObj->turnRot(mm::mtl::Singleton<DataManager>::getPtr()->axis2rot(axis.getAxis(), axis.getRot().x, axis.getRot().y, axis.getRot().z, pos), cv, frame);
  m_charaObj->mount(nullptr, "", mm::Vec3::zero, mm::Vec3::zero);
}

void ObjectChara::linerRotAxis(const RotAxis &axis, f32 frame, CV_TYPE cv) {
  m_rotAxis = axis;
  const mm::Vec3 &pos = m_charaObj->getPosTo();
  m_charaObj->linerRot(mm::mtl::Singleton<DataManager>::getPtr()->axis2rot(axis.getAxis(), axis.getRot().x, axis.getRot().y, axis.getRot().z, pos), frame, cv);
  m_charaObj->mount(nullptr, "", mm::Vec3::zero, mm::Vec3::zero);
}

mm::Vec3 ObjectChara::getTar() const { return m_charaObj->getTar(); }

f32 ObjectChara::getEyeOffset() const { return m_charaObj->getEyeOffset(); }

mm::Mat44 ObjectChara::getMat() {
  mm::Mat44 mat;
  mat.setRotXYZ(getRot());
  mat.setTrans(getPos());
  return mat;
}

mm::Mat44 ObjectChara::getEyeMat() {
  mm::Mat44 mat;
  mat.setRotXYZ(getRot());
  mat.setTrans(getEyePos());
  return mat;
}

// 0x7100112014, 393 instructions. `relative` places the product before the call that copies `original` into the parameter (the game computes the
// 16 values first and keeps them across the call: eight in d8-d15, eight spilled); written straight into param.unknown40 the call comes before the
// product (392 instructions). The position is read through the member getPos(): through m_charaObj->getPos() the three loads are consecutive and
// Reassociate puts the sum of the translation row in the other operand order.
// Ruling 8: the same body is written out in OnManiStartTar (0x7100112c8c) and in ObjectEffect::OnManiStartPos (0x71001179ec), 393 instructions each. A file-local static template holding the body
// (axis and position as parameters, the position by const reference or by value) gives 397 instructions against 393 for OnManiStartPos and OnManiStartTar.
bool ObjectChara::OnManiStartPos(IManiCallback::StartParam &param) {
  mm::Mat44 original = m_posAxis.calcOrigMat();
  mm::Mat44 inverse;
  inverse.unknown014(original);
  mm::Mat44 current;
  current.unknown007(getPos());
  mm::Mat44 relative = current * inverse;
  param.unknown00 = original;
  param.unknown40 = relative;
  return true;
}

void ObjectChara::OnManiSetPos(IManiCallback::SetParam &param) {
  mm::Vec3 pos = param.matrix.unknown004();
  PosAxis axis = m_posAxis;
  pos = DataManager::unknown001(axis.calcOrigMatInv(), pos.x, pos.y, pos.z);
  axis.set(axis.getAxis(), pos);
  setPosAxis(axis);
}

void ObjectChara::OnManiSetRot(IManiCallback::SetParam &param) {
  mm::Vec3 euler = mm::matrixToEuler(param.matrix);
  RotAxis axis = m_rotAxis;
  mm::Vec3 pos = m_charaObj->getPos();
  f32 ofs = mm::mtl::Singleton<DataManager>::getPtr()->getRotOfsY(axis.getAxis(), pos);
  axis.set(axis.getAxis(), 0.0f, euler.y - ofs, 0.0f);
  setRotAxis(axis);
}

bool ObjectChara::OnManiStartRot(IManiCallback::StartParam &param) {
  mm::Vec3 pos = m_charaObj->getPos();
  f32 ofs = mm::mtl::Singleton<DataManager>::getPtr()->getRotOfsY(m_rotAxis.getAxis(), pos);
  mm::Mat44 start;
  start.setRotY(ofs);
  start.setTrans(m_charaObj->getPos());
  mm::Mat44 rot;
  rot.setRotY(m_charaObj->getRotTo().y - ofs);
  param.unknown00 = start;
  param.unknown40 = rot;
  return true;
}

// 0x7100112c8c, 393 instructions: the same body as OnManiStartPos on the target axis and the target position (CharaObj+0x5b0, getTar()); ruling 8, see OnManiStartPos for the helper form measured.
bool ObjectChara::OnManiStartTar(IManiCallback::StartParam &param) {
  mm::Mat44 original = m_tarAxis.calcOrigMat();
  mm::Mat44 inverse;
  inverse.unknown014(original);
  mm::Mat44 current;
  current.unknown007(getTar());
  mm::Mat44 relative = current * inverse;
  param.unknown00 = original;
  param.unknown40 = relative;
  return true;
}

// Measured forms (1.0.0: 0x71001132cc, 239 instructions): TarAxis::calcOrigMatInv is defined in this unit, so LLVM infers readonly and nocapture on its this and forwards the local axis from registers
// (a declaration only gives 238 instructions). DataManager::unknown002 takes the matrix by value: the game keeps the inverse of each branch in its own stack slot (0x80, 0x40, 0), while a const
// reference parameter or a named local matrix lets the compiler share one slot (200 instructions). The angle branch copies the axis, then writes y and x of the local axis through a non-const
// getTar(): the game stores the copied axis index and z before the calls and the two angles afterwards one field at a time (building a Vec3 and calling set() gives 240 instructions). Each branch ends
// with its own setTar (the game stores m_tarAxis and loads m_charaObj per branch).
void ObjectChara::OnManiSetTar(IManiCallback::SetParam &param) {
  TarAxis axis;
  u32 type = m_tarAxis.getAxis();
  if (type < TarAxis::AXIS_UNKNOWN_4) {
    mm::Vec3 pos = param.matrix.unknown004();
    axis = m_tarAxis;
    pos = DataManager::unknown002(axis.calcOrigMatInv(), pos.x, pos.y, pos.z);
    axis.set(axis.getAxis(), pos);
    setTar(axis, -1.0f, static_cast<EVT_tarcvtype>(0), static_cast<EVT_aimtype>(0), -1.0f, -1.0f);
  } else if (type < TarAxis::AXIS_UNKNOWN_6) {
    mm::Vec3 pos = param.matrix.unknown004();
    axis = m_tarAxis;
    pos = pos - getEyePos();
    mm::Mat44 mat = m_tarAxis.calcOrigMatInv();
    f32 x = mat.rows[0][0] * pos.x + mat.rows[1][0] * pos.y + mat.rows[2][0] * pos.z;
    f32 y = mat.rows[0][1] * pos.x + mat.rows[1][1] * pos.y + mat.rows[2][1] * pos.z;
    f32 z = mat.rows[0][2] * pos.x + mat.rows[1][2] * pos.y + mat.rows[2][2] * pos.z;
    axis.getTar().y = -atan2f(x, -z);
    axis.getTar().x = atan2f(y, sqrtf(x * x + z * z));
    setTar(axis, -1.0f, static_cast<EVT_tarcvtype>(0), static_cast<EVT_aimtype>(0), -1.0f, -1.0f);
  } else if (type < mm::mtl::Singleton<ObjectManager>::getPtr()->getCharaCount() + TarAxis::AXIS_UNKNOWN_6) {
    mm::Vec3 pos = param.matrix.unknown004();
    axis = m_tarAxis;
    pos = DataManager::unknown002(axis.calcOrigMatInv(), pos.x, pos.y, pos.z);
    axis.set(axis.getAxis(), pos);
    setTar(axis, -1.0f, static_cast<EVT_tarcvtype>(0), static_cast<EVT_aimtype>(0), -1.0f, -1.0f);
  }
}

// Ruling 8: the game writes the actor/box block out in OnBouRender (0x7100111cf4), OnManiRender (0x7100113690), 200 instructions each, and in render (0x71001107d0, 524 instructions). The helper
// form (a private member holding the block, also defined `inline`) is not inlined: OnBouRender and OnManiRender are then 1 instruction (a tail call) against 200 and render has 338 against 524.
void ObjectChara::OnBouRender(const IBouCallback::RenderParam &param) {
  if ((unknown68 & FLAG_UNKNOWN_0) != 0) {
    ObjectUtil::drawActor(getPos(), m_charaObj->getRotTo().y, m_charaObj->getEyeOffset(), param.color, m_charaObj->isTar() ? &m_charaObj->getTar() : nullptr);
  } else {
    ObjectUtil::drawObject(getPos(), getRot(), param.color);
  }
}

void ObjectChara::OnManiRender(IManiCallback::RenderParam &param) {
  if ((unknown68 & FLAG_UNKNOWN_0) != 0) {
    ObjectUtil::drawActor(getPos(), m_charaObj->getRotTo().y, m_charaObj->getEyeOffset(), param.unknown00, m_charaObj->isTar() ? &m_charaObj->getTar() : nullptr);
  } else {
    ObjectUtil::drawObject(getPos(), getRot(), param.unknown00);
  }
}

} // namespace event
