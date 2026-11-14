#include "framework/render/light_object.h"

#include "dr/dr_creator.h"
#include "dr/dr_environment_obj.h"
#include "framework/framework.h"
#include "framework/layer_list.h"
#include "framework/render/light_manager.h"
#include "mm_mtl/fixed_array.h"
#include "mtl/alloc_handle.h"

namespace fw {

LightObject *LightObject::create(const LightSetup &setup) {
  LightObject *light = new (Framework::getMemHandle()) LightObject();
  if (light != nullptr) {
    light->addRef();
    light->unknown28 = setup.unknown0c;
    ml::DrCreator creator;
    light->m_interface = creator.createLgt(setup.unknown00, setup.unknown08);
    mm::mtl::IntrusiveList<LightObject> &lights = LightManager::get()->unknown18[light->unknown28].unknown00;
    mm::mtl::IntrusiveList<LightObject>::iterator it = unknown001(lights.begin(), lights.end(), light);
    if (lights.end() == it) {
      lights.push_back(light);
    }
  }
  return light;
}

void LightObject::setup() {}

LightObject::LightObject() : m_interface(nullptr), unknown28(0) {}

LightObject::~LightObject() {
  if (m_interface != nullptr) {
    m_interface->release();
    m_interface = nullptr;
  }

  LightManager::get()->unknown18[unknown28].unknown00.erase(this);
}

void LightObject::update() {}

ml::DrEnvironmentObj *LightObject::getInterface() { return m_interface; }

} // namespace fw
