#include "event/object_light.h"

#include "event/data_manager.h"
#include "event/frame_manager.h"
#include "event/light_manager.h"
#include "event/light_obj.h"
#include "event/memory_manager.h"
#include "ml/dev_graph.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {

ObjectLight::ObjectLight(const char *name, u32 id) : Object(OBJTYPE_UNKNOWN_5, name) {
  m_lightObj = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) LightObj(id);
}

ObjectLight::~ObjectLight() {
  if (m_lightObj != nullptr) {
    delete m_lightObj;
    m_lightObj = nullptr;
  }
}

void ObjectLight::render(const mm::Col4 &color) {
  if (!mm::mtl::Singleton<LightManager>::getPtr()->isLightDisp()) {
    return;
  }
  int x = ml::DevGraph::getRootWidth() - 250;
  LightObj *light = m_lightObj;
  light->render(x, light->unknown18 * 80 + 300);
}

void ObjectLight::update() {
  const FrameInfo &info = mm::mtl::Singleton<FrameManager>::getPtr()->frameInfo();
  m_lightObj->update(info);
}

void ObjectLight::play(const char *name, f32 frame) { m_lightObj->play(name, frame); }

void ObjectLight::setPosAxis(const PosAxis &axis) {
  m_posAxis.set(axis.getAxis(), axis.getPos());
  m_lightObj->setPos(mm::mtl::Singleton<DataManager>::getPtr()->axis2pos(axis.getAxis(), axis.getPos().x, axis.getPos().y, axis.getPos().z));
}

void ObjectLight::setRotAxis(const RotAxis &axis) {
  m_rotAxis.set(axis.getAxis(), axis.getRot());
  LightObj *light = m_lightObj;
  const mm::Vec3 &pos = light->getPos();
  light->setRot(mm::mtl::Singleton<DataManager>::getPtr()->axis2rot(axis.getAxis(), axis.getRot().x, axis.getRot().y, axis.getRot().z, pos));
}

} // namespace event
