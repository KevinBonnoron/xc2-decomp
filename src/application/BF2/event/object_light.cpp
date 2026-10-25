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

ObjectLight::ObjectLight(const char *name, u32 id) : Object(OBJTYPE_LIGHT, name) { unknown68 = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) LightObj(id); }

ObjectLight::~ObjectLight() {
  if (unknown68 != nullptr) {
    delete unknown68;
    unknown68 = nullptr;
  }
}

void ObjectLight::render(const mm::Col4 &color) {
  if (!mm::mtl::Singleton<LightManager>::getPtr()->isLightDisp()) {
    return;
  }
  int x = ml::DevGraph::getRootWidth() - 250;
  LightObj *light = unknown68;
  light->render(x, light->unknown18 * 80 + 300);
}

void ObjectLight::update() {
  const FrameInfo &info = mm::mtl::Singleton<FrameManager>::getPtr()->frameInfo();
  unknown68->update(info);
}

void ObjectLight::play(const char *name, f32 frame) { unknown68->play(name, frame); }

void ObjectLight::setPosAxis(const PosAxis &axis) {
  unknown70.set(axis.getAxis(), axis.getPos());
  unknown68->setPos(mm::mtl::Singleton<DataManager>::getPtr()->axis2pos(axis.getAxis(), axis.getPos().x, axis.getPos().y, axis.getPos().z));
}

void ObjectLight::setRotAxis(const RotAxis &axis) {
  unknown90.set(axis.getAxis(), axis.getRot());
  LightObj *light = unknown68;
  const mm::Vec3 &pos = light->getPos();
  light->setRot(mm::mtl::Singleton<DataManager>::getPtr()->axis2rot(axis.getAxis(), axis.getRot().x, axis.getRot().y, axis.getRot().z, pos));
}

} // namespace event
