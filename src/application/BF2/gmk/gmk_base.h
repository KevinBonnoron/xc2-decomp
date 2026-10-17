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
};

struct Xform {
  mm::Vec3 position;
  mm::Vec3 rotation;
  mm::Vec3 scale;
  u8 _30[0x40 - 0x30];
};

static_assert(sizeof(Xform) == 0x40, "");

struct GobInfo {
  const char *name;
  u32 xformIndex;
  ShapeType shapeType;
};

static_assert(sizeof(GobInfo) == 0x10, "");

class AGmkBase {
public:
  struct CreateBaseInfo {
    IGmkList *list;
    const Xform *xform;
    const GobInfo *gobInfo;
  };

  struct CreateInfo {
    CreateInfo() : version(0), data(nullptr), info(nullptr), bdatIndex(-1) {}

    u32 version;
    const void *data;
    const GmkInfo *info;
    int bdatIndex;
  };

  AGmkBase();
  virtual ~AGmkBase() { disposeBase(); }
  virtual GmkType getGmkType() const = 0;
  virtual bool isValid() const { return baseInfo.list != nullptr && createInfo.data != nullptr && createInfo.info != nullptr; }

  virtual void create(const CreateInfo &info) {
    dispose();
    createInfo = info;
  }

  virtual void dispose() {
    createInfo.version = 0;
    createInfo.data = nullptr;
    createInfo.info = nullptr;
  }

  virtual void update(f32 deltaTime);
  virtual void debugDraw() const;
  virtual void onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle);
  virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) {}
  virtual void debugUpdateMmf() {}

  void disposeBase();
  u8 *getBindedBdatFp() const;
  bool canCreateGameEntity() const;
  f32 getYSnapRayLength() const;
  void createBase(const CreateBaseInfo &info);
  void bindToGameObj(gf::GF_OBJ_HANDLE *handle) const;
  void unbindToGameObj(gf::GF_OBJ_HANDLE *handle) const;
  int findBdatRowIndex() const;

  CreateBaseInfo baseInfo;
  CreateInfo createInfo;
  alignas(8) u8 _40[0x48 - 0x40];
};

static_assert(offsetof(AGmkBase, baseInfo) == 0x08, "");
static_assert(offsetof(AGmkBase, createInfo) == 0x20, "");
static_assert(sizeof(AGmkBase) == 0x48, "");

} // namespace gmk
