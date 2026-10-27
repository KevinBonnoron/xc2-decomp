#pragma once
#include <stddef.h>

#include "grlib/cglib_texture_buffer.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace ptlib {
namespace material {

enum eMaterialType {
  eMaterialType_UNKNOWN_0,
  eMaterialType_UNKNOWN_1,
  eMaterialType_UNKNOWN_2,
};

class MaterialBase {
public:
  MaterialBase() : unknown08(-1), unknown0c(0), unknown14(1.0f), unknown18(nullptr), unknown20(nullptr), unknown28(0), unknown38(0), unknown3c(false) {}
  virtual ~MaterialBase() {}

  int unknown08;   // Inferred role: key; original member name unknown.
  u32 unknown0c;   // Inferred role: hash; original member name unknown.
  int unknown10;   // Inferred role: type; original member name unknown.
  f32 unknown14;   // Original member name unknown.
  void *unknown18; // Inferred role: owner; original member name unknown.
  void *unknown20; // Inferred role: data; original member name unknown.
  u32 unknown28;   // Inferred role: data size; original member name unknown.
  void *unknown30; // Original member name unknown.
  int unknown38;   // Inferred role: reference count; original member name unknown.
  bool unknown3c;  // Original member name unknown.
  bool unknown3d;  // Inferred role: is 3d texture; original member name unknown.
};

class MaterialTexture : public MaterialBase {
public:
  MaterialTexture() {
    unknown10 = 0;
    unknown3d = false;
  }
  ~MaterialTexture() override {}

  grlib::CGLibTextureBuffer unknown40; // Inferred role: texture; original member name unknown.
};

class MaterialManager {
public:
  MaterialManager() : unknown8010(0), unknown8014(1), unknown8018(-1) {}

  static void init();
  static void term();
  static MaterialManager *get();
  static MaterialManager *&getPtr();
  static bool isValid();
  void initSub();
  void termSub(bool isAll);
  void allClear(bool isAll);
  MaterialBase *getMaterial(eMaterialType type, void *data, u32 size, u8 *owner);
  MaterialBase *createTexture(void *data, u32 size, bool isResident, int format);
  void addActiveMaterial(MaterialBase *material);
  MaterialBase *getFreeMaterial();
  u32 getMaterialNum();
  MaterialBase *getMaterialByIdx(u32 index);
  MaterialBase *getMaterialByHash(const u32 &hash);
  MaterialBase *getMaterialByKey(const int &key, void *owner);
  void destroyMateriaByHash(const u32 &hash);
  void destroyMateriaByKey(const int &key, void *owner);
  void destroyMateriaByKey(void *material, void *owner);

  mm::mtl::FixedVector<MaterialBase *, 2048> unknown0000; // Inferred role: free materials; original member name unknown.
  mm::mtl::FixedVector<MaterialBase *, 2048> unknown4008; // Inferred role: active materials; original member name unknown.
  u32 unknown8010;                                        // Inferred role: hash counter; original member name unknown.
  u32 unknown8014;                                        // Original member name unknown.
  int unknown8018;                                        // Original member name unknown.
  u8 _801c[0x8020 - 0x801c];
  MaterialTexture *unknown8020; // Inferred role: material pool; original member name unknown.
};

static_assert(offsetof(MaterialManager, unknown4008) == 0x4008, "");
static_assert(offsetof(MaterialManager, unknown8010) == 0x8010, "");
static_assert(offsetof(MaterialManager, unknown8018) == 0x8018, "");
static_assert(offsetof(MaterialManager, unknown8020) == 0x8020, "");
static_assert(sizeof(MaterialManager) == 0x8028, "");
static_assert(offsetof(MaterialBase, unknown08) == 0x08, "");
static_assert(offsetof(MaterialBase, unknown38) == 0x38, "");
static_assert(offsetof(MaterialBase, unknown3d) == 0x3d, "");
static_assert(offsetof(MaterialTexture, unknown40) == 0x40, "");
static_assert(sizeof(MaterialTexture) == 0xb0, "");

} // namespace material
} // namespace ptlib
