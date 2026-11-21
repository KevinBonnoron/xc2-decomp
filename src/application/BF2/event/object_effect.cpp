#include "event/object_effect.h"

#include "event/bou_rect.h"
#include "event/data_manager.h"
#include "event/effect_obj.h"
#include "event/mani_manager.h"
#include "event/memory_manager.h"
#include "fw/fw_debug.h"
#include "mm_math/mm_math.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {

// The body of resetAttach written out: the call (inline in the header, in this same unit, like in play) gives 133 instructions against the game's 134, a prologue that differs from the first
// instruction (the game keeps one more register).
ObjectEffect::ObjectEffect(const char *name) : Object(OBJTYPE_UNKNOWN_4, name) {
  unknown68 = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) EffectObj(name);
  unknownb0 = nullptr;
  unknownc0 = nullptr;
  unknownc8 = "";
  unknownf0 = mm::Vec3::zero;
  unknown100 = false;
  unknown104 = static_cast<ATTACH_TYPE>(0);
  unknown110 = mm::Mat44::identity;
  unknown150.clear();
}

// Inferred helper: draws the box of an effect object at its position and rotation; original name unknown. The game inlines it in OnBouRender, OnManiRender and render
// (0x71001178a0, 0x7100118988, 0x71001173f4): the rotation and the position are read before the six sinf and cosf calls of the matrix.
static void unknown001(const mm::Vec3 &rotation, const mm::Vec3 &pos, const mm::Col4 &color) {
  mm::Mat44 matrix;
  matrix.unknown015(rotation);
  matrix.setTrans(pos);
  mm::Vec3 size(0.25f, 0.25f, 0.25f);
  fw::debug::drawBoxLine(matrix, size, color);
}

void ObjectEffect::OnBouRender(const IBouCallback::RenderParam &param) { unknown001(getRot(), getPos(), param.color); }

void ObjectEffect::OnManiRender(IManiCallback::RenderParam &param) { unknown001(getRot(), getPos(), param.unknown00); }

ObjectEffect::~ObjectEffect() {
  if (unknown68 != nullptr) {
    delete unknown68;
    unknown68 = nullptr;
  }
}

void ObjectEffect::start() {}

void ObjectEffect::end() {
  if (unknown68 != nullptr) {
    unknown68->end();
  }
}

mm::Vec3 ObjectEffect::getPos() const { return unknown68->getPos(); }

mm::Vec3 ObjectEffect::getRot() const { return unknown68->getRot(); }

void ObjectEffect::tail() { unknown68->tail(); }

bool ObjectEffect::OnBouRectSelect(const IBouCallback::SelectParam &param) {
  const BouRect *rect = param.rect;
  mm::Vec3 pos = unknown68->getPos();
  if (rect->isInside(pos)) {
    mm::mtl::Singleton<ManiManager>::getPtr()->addManipulate(this, static_cast<MANI_TYPE>(0));
    return true;
  }
  mm::mtl::Singleton<ManiManager>::getPtr()->removeManipulate(this);
  return false;
}

void ObjectEffect::setPosAxis(const PosAxis &axis) {
  unknown70 = axis;
  unknown68->setPos(mm::mtl::Singleton<DataManager>::getPtr()->axis2pos(axis.getAxis(), axis.getPos().x, axis.getPos().y, axis.getPos().z));
}

void ObjectEffect::OnManiSetRot(IManiCallback::SetParam &param) {
  mm::Vec3 euler = mm::matrixToEuler(param.matrix);
  RotAxis axis = unknown90;
  mm::Vec3 pos = getPos();
  f32 ofs = mm::mtl::Singleton<DataManager>::getPtr()->getRotOfsY(axis.getAxis(), pos);
  axis.set(axis.getAxis(), euler.x, euler.y - ofs, euler.z);
  setRotAxis(axis);
}

void ObjectEffect::setRotAxis(const RotAxis &axis) {
  unknown90 = axis;
  const mm::Vec3 &pos = unknown68->getPos();
  unknown68->setRot(mm::mtl::Singleton<DataManager>::getPtr()->axis2rot(axis.getAxis(), axis.getRot().x, axis.getRot().y, axis.getRot().z, pos));
}

void ObjectEffect::play(const char *name, f32 life, f32 speed, f32 skip, int prio, int offscrId) {
  unknown68->play(name, life, speed, skip, prio, offscrId);
  resetAttach();
}

void ObjectEffect::stop() { unknown68->stop(); }

void ObjectEffect::linerPosAxis(const PosAxis &axis, f32 frame, CV_TYPE cv) {
  unknown70 = axis;
  unknown68->moveTo(mm::mtl::Singleton<DataManager>::getPtr()->axis2pos(axis.getAxis(), axis.getPos().x, axis.getPos().y, axis.getPos().z), frame, cv);
}

void ObjectEffect::linerRotAxis(const RotAxis &axis, f32 frame, CV_TYPE cv) {
  unknown90 = axis;
  const mm::Vec3 &pos = unknown68->getPos();
  unknown68->turnTo(mm::mtl::Singleton<DataManager>::getPtr()->axis2rot(axis.getAxis(), axis.getRot().x, axis.getRot().y, axis.getRot().z, pos), frame, cv);
}

void ObjectEffect::setScale(const mm::Vec3 &scale) { unknown68->setScale(scale); }

mm::Vec3 ObjectEffect::getScale() const { return unknown68->getScale(); }

void ObjectEffect::setColor(const mm::Col4 &color) { unknown68->setColor(color); }

void ObjectEffect::linerColor(const mm::Col4 &color, f32 frame, CV_TYPE cv) { unknown68->colorTo(color, frame, cv); }

mm::Col4 ObjectEffect::getColor() const { return unknown68->getColor(); }

void ObjectEffect::setCaster(IAttachActor *caster) {
  unknown68->setCaster(caster);
  this->unknownb0 = caster;
  unknownc0 = nullptr;
}

void ObjectEffect::setMount(IAttachActor *mount, const char *bone, const mm::Vec3 &offset, bool isRotate, ATTACH_TYPE type) {
  unknown68->setMount(mount, bone, offset, isRotate, type);
  unknownb0 = nullptr;
  this->unknownc0 = mount;
  unknownc8 = bone;
  unknownf0 = offset;
  unknown100 = isRotate;
  unknown104 = type;
}

size_t ObjectEffect::getEffCount() const { return unknown68->getEffCount(); }

} // namespace event
