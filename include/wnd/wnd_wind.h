#pragma once
#include <stddef.h>

#include "types.h"
#include "wnd/wnd_node.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace wnd {

// Inferred: one oscillating component of a ResConpoundWind; ConpoundWind::calcWind (0x71009896ac) reads five of them
// with a 0x10 stride. Original name unknown.
struct unknown004 {
  f32 unknown00; // Inferred role: maximum power; original member name unknown.
  f32 unknown04; // Inferred role: minimum power; original member name unknown.
  f32 unknown08; // Inferred role: period; original member name unknown.
  f32 unknown0c; // Inferred role: phase; original member name unknown.
};

static_assert(sizeof(unknown004) == 0x10, "");

// Layout evidence: ConpoundWind::calcWind (0x71009896ac) reads five components at 0x0 to 0x4c; the full size is unknown.
struct ResConpoundWind {
  unknown004 unknown00[5]; // Inferred role: components along -z, +z, +x, -x and -y; original member name unknown.
};

class WindBlender : public WindNode {
public:
  WindBlender();
  void update(const UpdateInfo &info) override;
  void setNode(const WindNode *node);
  void changeNode(const WindNode *node, f32 time);

  const WindNode *unknownd0; // Inferred role: node; original member name unknown.
  const WindNode *unknownd8; // Inferred role: previous node, blended out; original member name unknown.
  f32 unknowne0;             // Inferred role: blend ratio; original member name unknown.
  f32 unknowne4;             // Inferred role: blend time; original member name unknown.
};

static_assert(offsetof(WindBlender, unknownd0) == 0xd0, "");
static_assert(offsetof(WindBlender, unknownd8) == 0xd8, "");
static_assert(offsetof(WindBlender, unknowne0) == 0xe0, "");
static_assert(offsetof(WindBlender, unknowne4) == 0xe4, "");
static_assert(sizeof(WindBlender) == 0xf0, "");

class ConpoundWind : public WindNode {
public:
  ConpoundWind();
  void update(const UpdateInfo &info) override;
  void calcWind(f32 time, u32 index, mm::Vec3 *wind);

  const ResConpoundWind *unknownd0; // Inferred role: wind resource, written by GlobalWindManager::setup; original member name unknown.
  f32 unknownd8[12][5];             // Inferred role: component powers per probe index, written by calcWind; original member name unknown.
  u8 _1c8[0x1d0 - 0x1c8];
};

static_assert(offsetof(ConpoundWind, unknownd0) == 0xd0, "");
static_assert(offsetof(ConpoundWind, unknownd8) == 0xd8, "");
static_assert(sizeof(ConpoundWind) == 0x1d0, "");

class GlobalWind : public WindBlender {
public:
  GlobalWind() : unknowne8(nullptr), unknownf0(nullptr) {}
  void update(const UpdateInfo &info) override;

  WindNode *unknowne8; // Inferred role: current node; original member name unknown.
  WindNode *unknownf0; // Inferred role: debug node; original member name unknown.
  u8 _f8[0x100 - 0xf8];
};

static_assert(offsetof(GlobalWind, unknowne8) == 0xe8, "");
static_assert(offsetof(GlobalWind, unknownf0) == 0xf0, "");
static_assert(sizeof(GlobalWind) == 0x100, "");

} // namespace wnd
