#pragma once
#include <stddef.h>

#include "fw/fw_camera.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace gmk {

class GmkCamera {
public:
  struct CreateInfo {
    CreateInfo() : unknown104(0), unknown105(true), unknown106(false), unknown107(false), unknown110(mm::Vec3::zero), unknown120(0.0f) {}

    bool validateTransform(gf::GF_OBJ_HANDLE *handle);
    bool validateTransform(u16 lodId);

    mm::mtl::FixStr<256> unknown00;  // Inferred role: camera name; original member name unknown.
    u8 unknown104;                   // Inferred role: party display mode; original member name unknown.
    bool unknown105;                 // Inferred role: auto; original member name unknown.
    bool unknown106;                 // Inferred role: play from play factory; original member name unknown.
    bool unknown107;                 // Inferred role: has transform; original member name unknown.
    alignas(16) mm::Vec3 unknown110; // Inferred role: position; original member name unknown.
    f32 unknown120;                  // Inferred role: rotation; original member name unknown.
  };

  GmkCamera(const CreateInfo *info);
  virtual ~GmkCamera() { dispose(); }
  void create(const CreateInfo &info);
  bool isLoaded() const;
  bool isEnd() const;
  void dispose();
  void seqWaitToLoaded(f32 deltaTime);
  void update(f32 deltaTime);
  void play();
  void seqWaitToPlay(f32 deltaTime);
  void applyInvisibleParty();
  static void setDispOfParty(bool isDisp, bool isExceptMover);
  void seqWaitToEnd(f32 deltaTime);

  CreateInfo unknown10;                         // Inferred role: create info; original member name unknown.
  mm::mtl::IntrusivePtr<fw::Camera> unknown140; // Inferred role: gimmick camera; original member name unknown.
  void (GmkCamera::*unknown148)(f32);           // Inferred role: sequence; original member name unknown.
};

static_assert(sizeof(GmkCamera::CreateInfo) == 0x130, "");
static_assert(offsetof(GmkCamera::CreateInfo, unknown104) == 0x104, "");
static_assert(offsetof(GmkCamera::CreateInfo, unknown107) == 0x107, "");
static_assert(offsetof(GmkCamera::CreateInfo, unknown110) == 0x110, "");
static_assert(offsetof(GmkCamera::CreateInfo, unknown120) == 0x120, "");
static_assert(offsetof(GmkCamera, unknown10) == 0x10, "");
static_assert(offsetof(GmkCamera, unknown140) == 0x140, "");
static_assert(offsetof(GmkCamera, unknown148) == 0x148, "");
static_assert(sizeof(GmkCamera) == 0x160, "");

} // namespace gmk
