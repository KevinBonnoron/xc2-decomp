#include "gf/camera/script/gf_camera_script.h"

namespace gf {

ScriptCameraEntity::~ScriptCameraEntity() {}

void ScriptCameraEntity::onActivate() {}

const mm::mtl::RTTI *ScriptCameraEntity::getRTTI() const { return &m_rtti; }

const char *ScriptCameraEntity::getName() const { return "ScriptCameraEntity"; }

} // namespace gf
