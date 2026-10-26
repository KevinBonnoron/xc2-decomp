#pragma once
#include <stddef.h>

#include "framework/coli/coli_object.h"
#include "fw/fw_coli_check.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace gmk {

class AGmkBase;
class GmkPhantom;

class GmkDmgPhantomTargetInfo {
public:
  u32 getTargetType() const;
  bool isTargetPlayer() const;

  gf::GF_OBJ_HANDLE *unknown00; // Inferred role: target handle; original member name unknown.
  int unknown08;                // Inferred role: remaining time; original member name unknown.
  f32 unknown0c;                // Role and original member name unknown.
};

static_assert(sizeof(GmkDmgPhantomTargetInfo) == 0x10, "");
static_assert(offsetof(GmkDmgPhantomTargetInfo, unknown08) == 0x8, "");
static_assert(offsetof(GmkDmgPhantomTargetInfo, unknown0c) == 0xc, "");

class GmkDoorPhantomTargetInfo {
public:
  u32 getTargetType() const;

  gf::GF_OBJ_HANDLE *unknown00; // Inferred role: target handle; original member name unknown.
};

static_assert(sizeof(GmkDoorPhantomTargetInfo) == 0x8, "");

typedef mm::mtl::FixedArray<fw::TColiCheckResult<256>, 3> GmkPhantomCheckResults;

class IGmkPhantomEventListener {
public:
  struct OnEnterInfo {
    GmkPhantom *phantom;
    const fw::TColiCheckResult<256> *result;
    int hitIndex;
  };

  struct OnLeaveInfo {
    GmkPhantom *phantom;
  };

  virtual void onEnterPhantom(const OnEnterInfo &info) = 0;
  virtual void onLeavePhantom(const OnLeaveInfo &info) = 0;
};

class GmkPhantom : public fw::ColiUserData, public mm::mtl::IntrusiveListNode<GmkPhantom> {
public:
  enum ShapeType {
    SHAPE_TYPE_NONE = 0,
    SHAPE_TYPE_SPHERE = 1,
    SHAPE_TYPE_CAPSULE = 2,
    SHAPE_TYPE_BOX = 3,
  };

  struct CreateInfo {
    CreateInfo() : unknown00(SHAPE_TYPE_NONE), unknown10(0.0f, 0.0f, 0.0f), unknown20(0.0f, 0.0f, 0.0f), unknown40(nullptr), unknown48(false) { unknown30[0] = unknown30[1] = unknown30[2] = 0.0f; }

    ShapeType unknown00;                 // Inferred role: shape type; original member name unknown.
    mm::Vec3 unknown10;                  // Inferred role: position; original member name unknown.
    mm::Vec3 unknown20;                  // Inferred role: rotation; original member name unknown.
    f32 unknown30[3];                    // Inferred role: size; original member name unknown.
    IGmkPhantomEventListener *unknown40; // Inferred role: listener; original member name unknown.
    bool unknown48;                      // Inferred role: check party; original member name unknown.
  };

  static mm::mtl::RTTI m_rtti;

  explicit GmkPhantom(const CreateInfo *info);
  void create(const CreateInfo &info);
  ~GmkPhantom() override;
  void dispose();
  void create(const AGmkBase &gmk, IGmkPhantomEventListener *listener, bool isCheckParty);
  void update(const GmkPhantomCheckResults &results);
  const mm::mtl::RTTI *getRTTI() const override { return &m_rtti; }

  CreateInfo unknown20;      // Inferred role: create info; original member name unknown.
  const char *unknown70;     // Inferred role: name; original member name unknown.
  fw::ColiObject *unknown78; // Inferred role: phantom; original member name unknown.
  bool unknown80;            // Inferred role: hit; original member name unknown.
  bool unknown81;            // Inferred role: entered; original member name unknown.
  bool unknown82;            // Inferred role: left; original member name unknown.
  bool unknown83;            // Inferred role: inside; original member name unknown.
};

static_assert(sizeof(GmkPhantom::CreateInfo) == 0x50, "");
static_assert(offsetof(GmkPhantom, unknown20) == 0x20, "");
static_assert(offsetof(GmkPhantom, unknown70) == 0x70, "");
static_assert(offsetof(GmkPhantom, unknown78) == 0x78, "");
static_assert(offsetof(GmkPhantom, unknown80) == 0x80, "");
static_assert(offsetof(GmkPhantom, unknown83) == 0x83, "");
static_assert(sizeof(GmkPhantom) == 0x90, "");

class GmkPhantomManager : public mm::mtl::PtrSingleton<GmkPhantomManager> {
public:
  void update(f32 deltaTime);
  void addGmkPhantom(GmkPhantom *phantom);
  void removeGmkPhantom(GmkPhantom *phantom);
  GmkPhantomManager();
  ~GmkPhantomManager() override;

  mm::mtl::IntrusiveList<GmkPhantom> unknown08; // Inferred role: phantoms; original member name unknown.
  GmkPhantomCheckResults unknown20;             // Inferred role: results; original member name unknown.
};

static_assert(offsetof(GmkPhantomManager, unknown08) == 0x08, "");
static_assert(offsetof(GmkPhantomManager, unknown20) == 0x20, "");

} // namespace gmk
