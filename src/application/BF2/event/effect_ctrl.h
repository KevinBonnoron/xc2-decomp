#pragma once
#include <stddef.h>

#include "event/i_attach_actor.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace event {

enum ATTACH_TYPE : int;

class EffectCtrl {
public:
  static constexpr u32 HANDLE_COUNT = 64;

  EffectCtrl();
  virtual ~EffectCtrl() {}
  void create(const char *name, u32 attribute);
  void destroy();
  void update();
  void genelate();
  void dead();
  void kill();
  void setSpeed(f32 speed);
  void setSkip(f32 skip);
  void setPrio(int prio);
  void setPos(const mm::Vec3 &pos);
  const mm::Vec3 &getPos() const;
  void setRot(const mm::Vec3 &rot);
  const mm::Vec3 &getRot() const;
  void setScale(const mm::Vec3 &scale);
  const mm::Vec3 &getScale() const;
  void setColor(const mm::Col4 &color);
  const mm::Col4 &getColor() const;
  void setCaster(IAttachActor *caster);
  void setMount(IAttachActor *mount, const char *bone, const mm::Vec3 &offset, bool isRotate, ATTACH_TYPE type);
  size_t getEffCount() const;

private:
  void detach() {
    if (unknown1b0 != nullptr) {
      for (size_t i = 0; i < unknown10.size(); i++) {
        unknown1b0->setEffectCaster(false, unknown10[i]);
      }
    }
    if (unknown1c0 != nullptr) {
      for (size_t i = 0; i < unknown10.size(); i++) {
        unknown1c0->setEffectMount(false, unknown10[i], "", mm::Vec3::zero, false, static_cast<ATTACH_TYPE>(0));
      }
    }
  }

  void reset() {
    unknown08 = 0;
    m_pos = mm::Vec3(0.0f, 0.0f, 0.0f);
    m_rot = mm::Vec3(0.0f, 0.0f, 0.0f);
    m_scale = mm::Vec3(1.0f, 1.0f, 1.0f);
    m_color = mm::Col4(1.0f, 1.0f, 1.0f, 1.0f);
    m_speed = 0.0f;
    m_skip = 0.0f;
    m_prio = 0;
    unknown1b0 = nullptr;
    unknown1c0 = nullptr;
    unknown1c8 = "";
    unknown1f0 = mm::Vec3::zero;
    unknown200 = false;
    unknown204 = 0;
  }

  u32 unknown08;                                     // Inferred role: handle; original member name unknown.
  mm::mtl::FixedVector<u32, HANDLE_COUNT> unknown10; // Inferred role: handles; original member name unknown.
  mm::mtl::FixStr<64> unknown118;                    // Inferred role: name; original member name unknown.
  u32 unknown15c;                                    // Inferred role: attribute; original member name unknown.
  mm::Vec3 m_pos;
  mm::Vec3 m_rot;
  mm::Vec3 m_scale;
  mm::Col4 m_color;
  f32 m_speed;
  f32 m_skip;
  int m_prio;
  IAttachActor *unknown1b0; // Inferred role: caster; original member name unknown.
  u8 _1b8[0x1c0 - 0x1b8];
  IAttachActor *unknown1c0;       // Inferred role: mount; original member name unknown.
  mm::mtl::FixStr<32> unknown1c8; // Inferred role: mount name; original member name unknown.
  mm::Vec3 unknown1f0;            // Inferred role: mount offset; original member name unknown.
  bool unknown200;                // Inferred role: is mount rotate; original member name unknown.
  int unknown204;                 // Inferred role: attach type; original member name unknown.
};

static_assert(sizeof(EffectCtrl) == 0x210, "");

} // namespace event
