#include "framework/anim/anim_control_updater.h"

#include "anm/anm_asm_control.h"
#include "anm/anm_blender.h"
#include "anm/anm_control.h"
#include "fw/fw_update_info.h"

namespace fw {

AnimControlUpdater::AnimControlUpdater() : unknown18(nullptr) {}

AnimControlUpdater::~AnimControlUpdater() { unbind(); }

void AnimControlUpdater::unbind() {
  if (unknown18 != nullptr) {
    unknown18->release();
    unknown18 = nullptr;
  }
}

void AnimControlUpdater::bind(anm::Control *control) {
  unbind();
  this->unknown18 = control;
  control->addRef();
}

void AnimControlUpdater::update(const UpdateInfo &info) { unknown18->update(info.unknown04); }

AnimBlenderUpdater::AnimBlenderUpdater() : unknown18(nullptr) {}

AnimBlenderUpdater::~AnimBlenderUpdater() { unbind(); }

void AnimBlenderUpdater::unbind() {
  if (unknown18 != nullptr) {
    unknown18->release();
    unknown18 = nullptr;
  }
}

void AnimBlenderUpdater::bind(anm::Blender *blender) {
  unbind();
  this->unknown18 = blender;
  blender->addRef();
}

void AnimBlenderUpdater::update(const UpdateInfo &info) { unknown18->update(info.unknown04); }

AnimAsmUpdater::AnimAsmUpdater() : unknown18(nullptr) {}

AnimAsmUpdater::~AnimAsmUpdater() { unbind(); }

void AnimAsmUpdater::unbind() {
  if (unknown18 != nullptr) {
    unknown18->release();
    unknown18 = nullptr;
  }
}

void AnimAsmUpdater::bind(anm::ASMControl *asmControl) {
  unbind();
  this->unknown18 = asmControl;
  asmControl->addRef();
}

void AnimAsmUpdater::update(const UpdateInfo &info) { unknown18->updateFrame(info.unknown04); }

} // namespace fw
