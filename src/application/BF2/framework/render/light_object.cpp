#include "framework/render/light_object.h"

#include "dr/dr_environment_obj.h"
#include "framework/render/light_manager.h"
#include "mm_mtl/fixed_array.h"

namespace fw {
void LightObject::setup() {}

LightObject::LightObject() : unknown20(nullptr), unknown28(0) {}

LightObject::~LightObject() {
  if (unknown20 != nullptr) {
    unknown20->release();
    unknown20 = nullptr;
  }

  LightManager::get()->unknown18[unknown28].unknown00.erase(this);
}

void LightObject::update() {}

ml::DrEnvironmentObj *LightObject::getInterface() { return unknown20; }

} // namespace fw
