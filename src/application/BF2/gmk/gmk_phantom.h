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

namespace gmk {

class AGmkBase;
class GmkPhantom;

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
    CreateInfo() : shapeType(SHAPE_TYPE_NONE), position(0.0f, 0.0f, 0.0f), rotation(0.0f, 0.0f, 0.0f), listener(nullptr), isCheckParty(false) {
      size[0] = size[1] = size[2] = 0.0f;
    }

    ShapeType shapeType;
    mm::Vec3 position;
    mm::Vec3 rotation;
    f32 size[3];
    IGmkPhantomEventListener *listener;
    bool isCheckParty;
  };

  static mm::mtl::RTTI m_rtti;

  explicit GmkPhantom(const CreateInfo *info);
  void create(const CreateInfo &info);
  ~GmkPhantom() override;
  void dispose();
  void create(const AGmkBase &gmk, IGmkPhantomEventListener *listener, bool isCheckParty);
  void update(const GmkPhantomCheckResults &results);
  const mm::mtl::RTTI *getRTTI() const override { return &m_rtti; }

  CreateInfo createInfo;
  const char *name;
  fw::ColiObject *phantom;
  bool isHit;
  bool isEntered;
  bool isLeft;
  bool isInside;
};

static_assert(sizeof(GmkPhantom::CreateInfo) == 0x50, "");
static_assert(offsetof(GmkPhantom, createInfo) == 0x20, "");
static_assert(offsetof(GmkPhantom, name) == 0x70, "");
static_assert(offsetof(GmkPhantom, phantom) == 0x78, "");
static_assert(offsetof(GmkPhantom, isHit) == 0x80, "");
static_assert(offsetof(GmkPhantom, isInside) == 0x83, "");
static_assert(sizeof(GmkPhantom) == 0x90, "");

class GmkPhantomManager : public mm::mtl::PtrSingleton<GmkPhantomManager> {
public:
  void update(f32 deltaTime);
  void addGmkPhantom(GmkPhantom *phantom);
  void removeGmkPhantom(GmkPhantom *phantom);
  GmkPhantomManager();
  ~GmkPhantomManager() override;

  mm::mtl::IntrusiveList<GmkPhantom> phantoms;
  GmkPhantomCheckResults results;
};

static_assert(offsetof(GmkPhantomManager, phantoms) == 0x08, "");
static_assert(offsetof(GmkPhantomManager, results) == 0x20, "");

} // namespace gmk
