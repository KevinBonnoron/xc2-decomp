#pragma once
#include <stddef.h>

#include "framework/anim/anim_manager.h"

namespace anm {
class ASMControl;
class Blender;
class Control;
} // namespace anm

namespace fw {

class AnimControlUpdater : public AnimControlUpdaterInterface {
public:
  AnimControlUpdater();
  ~AnimControlUpdater() override;
  void unbind();
  void bind(anm::Control *control);
  void update(const UpdateInfo &info) override;

  anm::Control *control;
};

static_assert(offsetof(AnimControlUpdater, control) == 0x18, "");

class AnimBlenderUpdater : public AnimControlUpdaterInterface {
public:
  AnimBlenderUpdater();
  ~AnimBlenderUpdater() override;
  void unbind();
  void bind(anm::Blender *blender);
  void update(const UpdateInfo &info) override;

  anm::Blender *blender;
};

static_assert(offsetof(AnimBlenderUpdater, blender) == 0x18, "");

class AnimAsmUpdater : public AnimControlUpdaterInterface {
public:
  AnimAsmUpdater();
  ~AnimAsmUpdater() override;
  void unbind();
  void bind(anm::ASMControl *asmControl);
  void update(const UpdateInfo &info) override;

  anm::ASMControl *asmControl;
};

static_assert(offsetof(AnimAsmUpdater, asmControl) == 0x18, "");

} // namespace fw
