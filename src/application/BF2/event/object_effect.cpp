#include "event/object_effect.h"

#include "event/bou_rect.h"
#include "event/data_manager.h"
#include "event/effect_obj.h"
#include "event/mani_manager.h"
#include "event/memory_manager.h"
#include "event/object_util.h"
#include "mm_math/mm_math.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {

// The body of resetAttach written out: the call (inline in the header, in this same unit, like in play) gives 133 instructions against the game's 134, a prologue that differs from the first
// instruction (the game keeps one more register).
ObjectEffect::ObjectEffect(const char *name) : Object(OBJTYPE_UNKNOWN_4, name) {
  m_effectObj = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) EffectObj(name);
  unknownb0 = nullptr;
  unknownc0 = nullptr;
  unknownc8 = "";
  unknownf0 = mm::Vec3::zero;
  unknown100 = false;
  unknown104 = static_cast<ATTACH_TYPE>(0);
  unknown110 = mm::Mat44::identity;
  unknown150.clear();
}

void ObjectEffect::OnBouRender(const IBouCallback::RenderParam &param) { ObjectUtil::drawObject(getPos(), getRot(), param.color); }

void ObjectEffect::OnManiRender(IManiCallback::RenderParam &param) { ObjectUtil::drawObject(getPos(), getRot(), param.unknown00); }

ObjectEffect::~ObjectEffect() {
  if (m_effectObj != nullptr) {
    delete m_effectObj;
    m_effectObj = nullptr;
  }
}

void ObjectEffect::start() {}

void ObjectEffect::end() {
  if (m_effectObj != nullptr) {
    m_effectObj->end();
  }
}

mm::Vec3 ObjectEffect::getPos() const { return m_effectObj->getPos(); }

mm::Vec3 ObjectEffect::getRot() const { return m_effectObj->getRot(); }

void ObjectEffect::tail() { m_effectObj->tail(); }

bool ObjectEffect::OnBouRectSelect(const IBouCallback::SelectParam &param) {
  const BouRect *rect = param.rect;
  mm::Vec3 pos = m_effectObj->getPos();
  if (rect->isInside(pos)) {
    mm::mtl::Singleton<ManiManager>::getPtr()->addManipulate(this, static_cast<MANI_TYPE>(0));
    return true;
  }
  mm::mtl::Singleton<ManiManager>::getPtr()->removeManipulate(this);
  return false;
}

// 0x71001179ec, 393 instructions: the same body as ObjectChara::OnManiStartPos (object_chara.cpp); ruling 8, the helper form measured there (397 instructions against 393) does not match.
bool ObjectEffect::OnManiStartPos(IManiCallback::StartParam &param) {
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

void ObjectEffect::OnManiSetPos(IManiCallback::SetParam &param) {
  mm::Vec3 pos = param.matrix.unknown004();
  PosAxis axis = m_posAxis;
  pos = DataManager::unknown001(axis.calcOrigMatInv(), pos.x, pos.y, pos.z);
  axis.set(axis.getAxis(), pos);
  setPosAxis(axis);
}

void ObjectEffect::setPosAxis(const PosAxis &axis) {
  m_posAxis = axis;
  m_effectObj->setPos(mm::mtl::Singleton<DataManager>::getPtr()->axis2pos(axis.getAxis(), axis.getPos().x, axis.getPos().y, axis.getPos().z));
}

void ObjectEffect::OnManiSetRot(IManiCallback::SetParam &param) {
  mm::Vec3 euler = mm::matrixToEuler(param.matrix);
  RotAxis axis = m_rotAxis;
  mm::Vec3 pos = getPos();
  f32 ofs = mm::mtl::Singleton<DataManager>::getPtr()->getRotOfsY(axis.getAxis(), pos);
  axis.set(axis.getAxis(), euler.x, euler.y - ofs, euler.z);
  setRotAxis(axis);
}

void ObjectEffect::setRotAxis(const RotAxis &axis) {
  m_rotAxis = axis;
  const mm::Vec3 &pos = m_effectObj->getPos();
  m_effectObj->setRot(mm::mtl::Singleton<DataManager>::getPtr()->axis2rot(axis.getAxis(), axis.getRot().x, axis.getRot().y, axis.getRot().z, pos));
}

void ObjectEffect::play(const char *name, f32 life, f32 speed, f32 skip, int prio, int offscrId) {
  m_effectObj->play(name, life, speed, skip, prio, offscrId);
  resetAttach();
}

void ObjectEffect::stop() { m_effectObj->stop(); }

void ObjectEffect::linerPosAxis(const PosAxis &axis, f32 frame, CV_TYPE cv) {
  m_posAxis = axis;
  m_effectObj->moveTo(mm::mtl::Singleton<DataManager>::getPtr()->axis2pos(axis.getAxis(), axis.getPos().x, axis.getPos().y, axis.getPos().z), frame, cv);
}

void ObjectEffect::linerRotAxis(const RotAxis &axis, f32 frame, CV_TYPE cv) {
  m_rotAxis = axis;
  const mm::Vec3 &pos = m_effectObj->getPos();
  m_effectObj->turnTo(mm::mtl::Singleton<DataManager>::getPtr()->axis2rot(axis.getAxis(), axis.getRot().x, axis.getRot().y, axis.getRot().z, pos), frame, cv);
}

void ObjectEffect::setScale(const mm::Vec3 &scale) { m_effectObj->setScale(scale); }

mm::Vec3 ObjectEffect::getScale() const { return m_effectObj->getScale(); }

void ObjectEffect::setColor(const mm::Col4 &color) { m_effectObj->setColor(color); }

void ObjectEffect::linerColor(const mm::Col4 &color, f32 frame, CV_TYPE cv) { m_effectObj->colorTo(color, frame, cv); }

mm::Col4 ObjectEffect::getColor() const { return m_effectObj->getColor(); }

void ObjectEffect::setCaster(IAttachActor *caster) {
  m_effectObj->setCaster(caster);
  this->unknownb0 = caster;
  unknownc0 = nullptr;
}

void ObjectEffect::setMount(IAttachActor *mount, const char *bone, const mm::Vec3 &offset, bool isRotate, ATTACH_TYPE type) {
  m_effectObj->setMount(mount, bone, offset, isRotate, type);
  unknownb0 = nullptr;
  this->unknownc0 = mount;
  unknownc8 = bone;
  unknownf0 = offset;
  unknown100 = isRotate;
  unknown104 = type;
}

size_t ObjectEffect::getEffCount() const { return m_effectObj->getEffCount(); }

} // namespace event
