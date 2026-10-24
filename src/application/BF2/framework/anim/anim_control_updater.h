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

  anm::Control *unknown18; // Inferred role: control; original member name unknown.
};

static_assert(offsetof(AnimControlUpdater, unknown18) == 0x18, "");

class AnimBlenderUpdater : public AnimControlUpdaterInterface {
public:
  AnimBlenderUpdater();
  ~AnimBlenderUpdater() override;
  void unbind();
  void bind(anm::Blender *blender);
  void update(const UpdateInfo &info) override;

  anm::Blender *unknown18; // Inferred role: blender; original member name unknown.
};

static_assert(offsetof(AnimBlenderUpdater, unknown18) == 0x18, "");

class AnimAsmUpdater : public AnimControlUpdaterInterface {
public:
  AnimAsmUpdater();
  ~AnimAsmUpdater() override;
  void unbind();
  void bind(anm::ASMControl *asmControl);
  void update(const UpdateInfo &info) override;

  anm::ASMControl *unknown18; // Inferred role: asm control; original member name unknown.
};

static_assert(offsetof(AnimAsmUpdater, unknown18) == 0x18, "");

} // namespace fw
