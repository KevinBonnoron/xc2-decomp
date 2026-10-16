#include "framework/anim/anim_control_updater.h"

#include "anm/anm_asm_control.h"
#include "anm/anm_blender.h"
#include "anm/anm_control.h"
#include "fw/fw_update_info.h"

namespace fw {

AnimControlUpdater::AnimControlUpdater() : control(nullptr) {}

AnimControlUpdater::~AnimControlUpdater() { unbind(); }

void AnimControlUpdater::unbind() {
  if (control != nullptr) {
    control->release();
    control = nullptr;
  }
}

void AnimControlUpdater::bind(anm::Control *control) {
  unbind();
  this->control = control;
  control->addRef();
}

void AnimControlUpdater::update(const UpdateInfo &info) { control->update(info.deltaTime); }

AnimBlenderUpdater::AnimBlenderUpdater() : blender(nullptr) {}

AnimBlenderUpdater::~AnimBlenderUpdater() { unbind(); }

void AnimBlenderUpdater::unbind() {
  if (blender != nullptr) {
    blender->release();
    blender = nullptr;
  }
}

void AnimBlenderUpdater::bind(anm::Blender *blender) {
  unbind();
  this->blender = blender;
  blender->addRef();
}

void AnimBlenderUpdater::update(const UpdateInfo &info) { blender->update(info.deltaTime); }

AnimAsmUpdater::AnimAsmUpdater() : asmControl(nullptr) {}

AnimAsmUpdater::~AnimAsmUpdater() { unbind(); }

void AnimAsmUpdater::unbind() {
  if (asmControl != nullptr) {
    asmControl->release();
    asmControl = nullptr;
  }
}

void AnimAsmUpdater::bind(anm::ASMControl *asmControl) {
  unbind();
  this->asmControl = asmControl;
  asmControl->addRef();
}

void AnimAsmUpdater::update(const UpdateInfo &info) { asmControl->updateFrame(info.deltaTime); }

} // namespace fw
