#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

// Reconstructed from the symbols and call sites of the game executable (wnd:: namespace of the wind library).
// Only the members read by the framework are declared; the original member names are unknown.
namespace wnd {

struct Query;
class LocalWind;

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

  u8 _0c[0x10 - 0x0c];
  GlobalWindManager unknown10; // Inferred role: global wind; original member name unknown.
};

static_assert(offsetof(WindWorld, unknown10) == 0x10, "");

} // namespace wnd
