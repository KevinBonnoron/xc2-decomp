#pragma once
#include <stddef.h>

#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace ml {
class Scn;
class ScnObjCam;
} // namespace ml

namespace fw {

struct UpdateInfo;

enum CAMERA_PRIO : int;

class CameraLayer;
class CameraPlugin;

class Camera : public mm::mtl::ReferenceObject, public mm::mtl::IntrusiveListNode<Camera> {
public:
  Camera(CAMERA_PRIO prio);
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual const char *getName() const;
  virtual void onPush();
  virtual void onPop();
  virtual void onActivate();
  virtual void onDeactivate();
  virtual void update(const UpdateInfo &info);
  virtual void updateViewMatrix();
  void setLookAt(const mm::Vec3 &position, const mm::Vec3 &target, f32 roll);

  CameraLayer *layer;
  CAMERA_PRIO prio;
  f32 fov;
  f32 nearClip;
  f32 farClip;
  mm::Vec3 position;
  mm::Vec3 target;
  mm::Mat44 viewMatrix;
  bool isActive;
  f32 roll;
};

static_assert(offsetof(Camera, layer) == 0x20, "");
static_assert(offsetof(Camera, position) == 0x40, "");
static_assert(offsetof(Camera, viewMatrix) == 0x60, "");
static_assert(offsetof(Camera, isActive) == 0xa0, "");
static_assert(offsetof(Camera, roll) == 0xa4, "");

class CameraTarget : public mm::mtl::ReferenceObject {
public:
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual void update(const UpdateInfo &info) = 0;
  virtual void requestResetCamera();
};

class CameraLayer {
public:
  CameraLayer();
  ~CameraLayer();
  void setup(ml::Scn *scn, u32 index);
  void onPopCamera(Camera &camera);
  virtual void update(const UpdateInfo &info);
  void push(mm::mtl::IntrusivePtr<Camera> &camera, f32 time);
  void onPushCamera(Camera &camera);
  void pop(mm::mtl::IntrusivePtr<Camera> &camera, f32 time);
  mm::Vec3 getCameraPosition() const;

  mm::mtl::IntrusiveList<Camera> cameras;
  mm::mtl::IntrusiveList<CameraPlugin> plugins;
  ml::ScnObjCam *scnCamera;
  mm::Mat44 matrix;
  mm::Mat44 previousMatrix;
  f32 blendTime;
  f32 blendRate;
  bool isBlending;
};

static_assert(offsetof(CameraLayer, scnCamera) == 0x38, "");
static_assert(offsetof(CameraLayer, blendTime) == 0xc0, "");
static_assert(sizeof(CameraLayer) == 0xd0, "");

class CameraManager : public mm::mtl::PtrSingleton<CameraManager> {
public:
  static constexpr u32 LAYER_COUNT = 4;

  u8 _08[0x20 - 0x08];
  CameraLayer layers[LAYER_COUNT];
  mm::mtl::IntrusivePtr<CameraTarget> target;
};

static_assert(offsetof(CameraManager, layers) == 0x20, "");
static_assert(offsetof(CameraManager, target) == 0x360, "");

} // namespace fw
