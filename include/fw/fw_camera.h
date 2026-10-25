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

class CameraPlugin : public mm::mtl::ReferenceObject, public mm::mtl::IntrusiveListNode<CameraPlugin> {};

class Camera : public mm::mtl::ReferenceObject, public mm::mtl::IntrusiveListNode<Camera> {
public:
  static mm::mtl::RTTI m_rtti;

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

  CameraLayer *unknown20; // Inferred role: layer; original member name unknown.
  CAMERA_PRIO unknown28;  // Inferred role: prio; original member name unknown.
  f32 m_fov;
  f32 unknown30;       // Inferred role: near clip; original member name unknown.
  f32 unknown34;       // Inferred role: far clip; original member name unknown.
  mm::Vec3 unknown40;  // Inferred role: position; original member name unknown.
  mm::Vec3 unknown50;  // Inferred role: target; original member name unknown.
  mm::Mat44 unknown60; // Inferred role: view matrix; original member name unknown.
  bool unknowna0;      // Inferred role: active; original member name unknown.
  f32 unknowna4;       // Inferred role: roll; original member name unknown.
};

static_assert(offsetof(Camera, unknown20) == 0x20, "");
static_assert(offsetof(Camera, unknown40) == 0x40, "");
static_assert(offsetof(Camera, unknown60) == 0x60, "");
static_assert(offsetof(Camera, unknowna0) == 0xa0, "");
static_assert(offsetof(Camera, unknowna4) == 0xa4, "");

class CameraTarget : public mm::mtl::ReferenceObject {
public:
  static mm::mtl::RTTI m_rtti;

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
  void pushPlugin(mm::mtl::IntrusivePtr<CameraPlugin> &plugin);
  void popPlugin(mm::mtl::IntrusivePtr<CameraPlugin> &plugin);
  mm::Vec3 getCameraPosition() const;

  mm::mtl::IntrusiveList<Camera> unknown08;       // Inferred role: cameras; original member name unknown.
  mm::mtl::IntrusiveList<CameraPlugin> unknown20; // Inferred role: plugins; original member name unknown.
  ml::ScnObjCam *unknown38;                       // Inferred role: scn camera; original member name unknown.
  mm::Mat44 unknown40;                            // Inferred role: matrix; original member name unknown.
  mm::Mat44 unknown80;                            // Inferred role: previous matrix; original member name unknown.
  f32 unknownc0;                                  // Inferred role: blend time; original member name unknown.
  f32 unknownc4;                                  // Inferred role: blend rate; original member name unknown.
  bool unknownc8;                                 // Inferred role: blending; original member name unknown.
};

static_assert(offsetof(CameraLayer, unknown38) == 0x38, "");
static_assert(offsetof(CameraLayer, unknownc0) == 0xc0, "");
static_assert(sizeof(CameraLayer) == 0xd0, "");

class CameraManager : public mm::mtl::PtrSingleton<CameraManager> {
public:
  static constexpr u32 LAYER_COUNT = 4;

  u8 _08[0x20 - 0x08];
  CameraLayer unknown20[LAYER_COUNT];             // Inferred role: layers; original member name unknown.
  mm::mtl::IntrusivePtr<CameraTarget> unknown360; // Inferred role: target; original member name unknown.
};

static_assert(offsetof(CameraManager, unknown20) == 0x20, "");
static_assert(offsetof(CameraManager, unknown360) == 0x360, "");

} // namespace fw
