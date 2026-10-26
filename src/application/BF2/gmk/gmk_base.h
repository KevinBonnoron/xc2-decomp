#pragma once
#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_manager.h"
#include "mm_math/mm_vec3.h"
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
    const void *unknown08;    // Inferred role: data; original member name unknown.
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
  bool canCreateGameEntity() const;
  f32 getYSnapRayLength() const;
  void createBase(const CreateBaseInfo &info);
  void bindToGameObj(gf::GF_OBJ_HANDLE *handle) const;
  void unbindToGameObj(gf::GF_OBJ_HANDLE *handle) const;
  int findBdatRowIndex() const;

  CreateBaseInfo unknown08; // Inferred role: base info; original member name unknown.
  CreateInfo unknown20;     // Inferred role: create info; original member name unknown.
  alignas(8) u8 _40[0x48 - 0x40];
};

static_assert(offsetof(AGmkBase, unknown08) == 0x08, "");
static_assert(offsetof(AGmkBase, unknown20) == 0x20, "");
static_assert(sizeof(AGmkBase) == 0x48, "");

} // namespace gmk
