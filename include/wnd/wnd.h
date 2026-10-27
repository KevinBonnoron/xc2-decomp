#pragma once
#include <stddef.h>

#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

// Reconstructed from the symbols and call sites of the game executable (wnd:: namespace of the wind library).
// Only the members read by the framework are declared; the original member names are unknown.
namespace wnd {

struct Query;

struct Transform {
  mm::Vec3 unknown00; // Inferred role: position; original member name unknown.
  mm::Quat unknown10; // Inferred role: rotation; original member name unknown.
};

static_assert(sizeof(Transform) == 0x20, "");

class SphereShape {
public:
  explicit SphereShape(f32 radius);

  u8 _00[0x18];
};

static_assert(sizeof(SphereShape) == 0x18, "");

struct LocalWindCreateInfo {
  const Transform *unknown00; // Inferred role: transform; original member name unknown.
  SphereShape *unknown08;     // Inferred role: shape; original member name unknown.
  u32 unknown10;              // Role and original member name unknown.
  f32 unknown14;              // Role and original member name unknown.
  f32 unknown18;              // Role and original member name unknown.
  f32 unknown1c;              // Role and original member name unknown.
};

static_assert(sizeof(LocalWindCreateInfo) == 0x20, "");

class LocalWind {
public:
  explicit LocalWind(const LocalWindCreateInfo &info);

  u8 _00[0x88];
  f32 unknown88; // Inferred role: power; original member name unknown.
  u8 _8c[0xb0 - 0x8c];
};

static_assert(offsetof(LocalWind, unknown88) == 0x88, "");
static_assert(sizeof(LocalWind) == 0xb0, "");

class WindProbe : public mm::mtl::ReferenceObject {
public:
  u8 _0c[0x88 - 0x0c];
  u32 unknown88; // Inferred role: current power index; original member name unknown.
  u8 _8c[0xa0 - 0x8c];
  mm::Vec3 unknowna0[4]; // Inferred role: power per index; original member name and size unknown.
};

static_assert(offsetof(WindProbe, unknown88) == 0x88, "");
static_assert(offsetof(WindProbe, unknowna0) == 0xa0, "");

class GlobalWindManager {
public:
  bool setCurrentWind(int index);

  u8 _00[0x140];
  int unknown140; // Inferred role: current wind index; original member name unknown.
};

static_assert(offsetof(GlobalWindManager, unknown140) == 0x140, "");

class WindWorld : public mm::mtl::ReferenceObject {
public:
  void addProbe(WindProbe &probe);
  void removeProbe(WindProbe &probe);
  void addLocalWind(LocalWind &wind);
  void removeLocalWind(LocalWind &wind);
  void setDebugMode(bool enable, u32 mask);
  bool query(Query *query);
  void update(f32 deltaTime);

  u8 _0c[0x10 - 0x0c];
  GlobalWindManager unknown10; // Inferred role: global wind; original member name unknown.
};

static_assert(offsetof(WindWorld, unknown10) == 0x10, "");

} // namespace wnd
