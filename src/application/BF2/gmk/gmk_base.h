#pragma once
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_setup.h"
#include "gmk/gmk_manager.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/rtti.h"
#include "types.h"
#include <stddef.h>

namespace gf {
struct GF_OBJ_HANDLE;
}

namespace gmk {

class IGmkList;

struct GmkInfo {
  u16 id;
  u16 unknown02; // Role and original member name unknown.
};

struct Xform {
  mm::Vec3 unknown00; // Inferred role: position; original member name unknown.
  mm::Vec3 unknown10; // Inferred role: rotation; original member name unknown.
  mm::Vec3 unknown20; // Inferred role: scale; original member name unknown.
  u8 _30[0x40 - 0x30];
};

static_assert(sizeof(Xform) == 0x40, "");

struct GobInfo {
  const char *unknown00; // Inferred role: name; original member name unknown.
  u32 unknown08;         // Inferred role: xform index; original member name unknown.
  ShapeType unknown0c;   // Inferred role: shape type; original member name unknown.
};

static_assert(sizeof(GobInfo) == 0x10, "");

// Inferred helper: matrix of a debug drawing, the identity moved to a position; original name unknown.
inline void unknown001(mm::Mat44 &matrix, const mm::Vec3 &position) {
  for (int row = 0; row < 3; row++) {
    for (int column = 0; column < 4; column++) {
      matrix.rows[row][column] = row == column ? 1.0f : 0.0f;
    }
  }
  matrix.rows[3][0] = position.x;
  matrix.rows[3][1] = position.y;
  matrix.rows[3][2] = position.z;
  matrix.rows[3][3] = 1.0f;
}

// Inferred helper: sets or clears the target attribute of a game object; original name unknown.
inline void unknown002(gf::GF_OBJ_HANDLE *handle, bool isTargetable) {
  gf::GfObjAcc acc(handle);
  if (acc.isValid()) {
    gf::GfObjSetupGimmick *setup = mm::mtl::dynamicCast<gf::GfObjSetupGimmick>(gf::GfObjManager::getObjInfo(handle)->unknown30);
    if (isTargetable) {
      setup->unknown6c |= gf::OBJ_ATTRIBUTE_TARGET_MASK;
    } else {
      setup->unknown6c &= ~gf::OBJ_ATTRIBUTE_TARGET_MASK;
    }
  }
  gf::GfObj *obj = acc.getObj();
  if (obj != nullptr) {
    if (isTargetable) {
      obj->unknown110 |= gf::OBJ_ATTRIBUTE_TARGET_MASK;
    } else {
      obj->unknown110 &= ~gf::OBJ_ATTRIBUTE_TARGET_MASK;
    }
  }
}

// Inferred helper: places a game object setup at the position and rotation of a transform; original name unknown.
inline void unknown003(gf::GfObjSetup *setup, const Xform *xform) {
  setup->unknown20 = xform->unknown00;
  setup->unknown30 = xform->unknown10;
}

class AGmkBase {
public:
  struct CreateBaseInfo {
    IGmkList *unknown00;      // Inferred role: list; original member name unknown.
    const Xform *unknown08;   // Inferred role: xform; original member name unknown.
    const GobInfo *unknown10; // Inferred role: gob info; original member name unknown.
  };

  struct CreateInfo {
    CreateInfo() : unknown00(0), unknown08(nullptr), unknown10(nullptr), unknown18(-1) {}

    u32 unknown00;            // Inferred role: version; original member name unknown.
    void *unknown08;          // Inferred role: data; original member name unknown.
    const GmkInfo *unknown10; // Inferred role: info; original member name unknown.
    int unknown18;            // Inferred role: bdat index; original member name unknown.
  };

  AGmkBase();
  virtual ~AGmkBase() { disposeBase(); }
  virtual GmkType getGmkType() const = 0;
  virtual bool isValid() const { return unknown08.unknown00 != nullptr && unknown20.unknown08 != nullptr && unknown20.unknown10 != nullptr; }

  virtual void create(const CreateInfo &info) {
    dispose();
    unknown20 = info;
  }

  virtual void dispose() {
    unknown20.unknown00 = 0;
    unknown20.unknown08 = nullptr;
    unknown20.unknown10 = nullptr;
  }

  virtual void update(f32 deltaTime);
  virtual void debugDraw() const;
  virtual void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle);
  virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) {}
  virtual void debugUpdateMmf() {}

  void disposeBase() {
    unknown08.unknown00 = nullptr;
    unknown08.unknown08 = nullptr;
    unknown08.unknown10 = nullptr;
  }
  u8 *getBindedBdatFp() const;

  // Inferred helper: wraps the bdat of the list; original name unknown.
  CBdatWrapper unknown004() const {
    CBdatWrapper bdat = {getBindedBdatFp()};
    return bdat;
  }
  bool canCreateGameEntity() const;
  f32 getYSnapRayLength() const;
  void createBase(const CreateBaseInfo &info);
  void bindToGameObj(gf::GF_OBJ_HANDLE *handle) const;
  void unbindToGameObj(gf::GF_OBJ_HANDLE *handle) const;
  int findBdatRowIndex() const;
  bool getPositionInShape(mm::Vec3 &position, bool isRandom) const;
  bool getYSnapPosInShape(mm::Vec3 &position) const;
  bool getPositionAppliedYSnap(mm::Vec3 &result, const mm::Vec3 &position, bool isXformY) const;

  CreateBaseInfo unknown08; // Inferred role: base info; original member name unknown.
  CreateInfo unknown20;     // Inferred role: create info; original member name unknown.
  alignas(8) u8 _40[0x48 - 0x40];
};

static_assert(offsetof(AGmkBase, unknown08) == 0x08, "");
static_assert(offsetof(AGmkBase, unknown20) == 0x20, "");
static_assert(sizeof(AGmkBase) == 0x48, "");

} // namespace gmk
