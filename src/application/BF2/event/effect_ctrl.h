#pragma once
#include "mm_math/mm_col4.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"
#include <stddef.h>

namespace event {

class IAttachActor;
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
  void reset() {
    handle = 0;
    mPos = mm::Vec3(0.0f, 0.0f, 0.0f);
    mRot = mm::Vec3(0.0f, 0.0f, 0.0f);
    mScale = mm::Vec3(1.0f, 1.0f, 1.0f);
    mColor = mm::Col4(1.0f, 1.0f, 1.0f, 1.0f);
    mSpeed = 0.0f;
    mSkip = 0.0f;
    mPrio = 0;
    mCaster = nullptr;
    mMount = nullptr;
    mMountName = "";
    mMountOffset = mm::Vec3::zero;
    mIsMountRotate = false;
    mAttachType = 0;
  }

  u32 handle;
  mm::mtl::FixedVector<u32, HANDLE_COUNT> mHandles;
  mm::mtl::FixStr<64> mName;
  u32 mAttribute;
  mm::Vec3 mPos;
  mm::Vec3 mRot;
  mm::Vec3 mScale;
  mm::Col4 mColor;
  f32 mSpeed;
  f32 mSkip;
  int mPrio;
  IAttachActor *mCaster;
  u8 _1b8[0x1c0 - 0x1b8];
  IAttachActor *mMount;
  mm::mtl::FixStr<32> mMountName;
  mm::Vec3 mMountOffset;
  bool mIsMountRotate;
  int mAttachType;
};

static_assert(sizeof(EffectCtrl) == 0x210, "");

} // namespace event
