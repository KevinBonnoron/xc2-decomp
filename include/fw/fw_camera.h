#pragma once
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace fw {

struct UpdateInfo;

class Camera : public mm::mtl::ReferenceObject {
public:
  virtual const mm::mtl::RTTI *getRTTI() const;
};

class CameraTarget : public mm::mtl::ReferenceObject {
public:
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual void update(const UpdateInfo &info) = 0;
  virtual void requestResetCamera();
};

class CameraLayer {
public:
  void push(mm::mtl::IntrusivePtr<Camera> &camera, f32 time);
  void pop(mm::mtl::IntrusivePtr<Camera> &camera, f32 time);
};

class CameraManager : public mm::mtl::PtrSingleton<CameraManager> {
public:
  u8 _08[0x20 - 0x08];
  CameraLayer layer;
  u8 _21[0x360 - 0x21];
  mm::mtl::IntrusivePtr<CameraTarget> target;
};

static_assert(offsetof(CameraManager, layer) == 0x20, "");
static_assert(offsetof(CameraManager, target) == 0x360, "");

} // namespace fw
