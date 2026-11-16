#pragma once
#include <stddef.h>

#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace wnd {

class WindObject;
class WindProbe;
struct HitCache;
struct UpdateInfo;

// Settings of the collision dispatcher; the game reads member 0.
struct CollisionInfo {
  f32 unknown00; // Role unknown; stored as 0.001f by fw::WindManager::buildWorld and passed as the float argument of the agent callback; original member name unknown.
};

static_assert(sizeof(CollisionInfo) == 0x04, "");

class Dispatcher;

class SphereSphereAgent {
public:
  static void registerAgent(Dispatcher &dispatcher);
  static bool processCollision(const WindObject &wind0, const WindObject &wind1, f32 radius, HitCache *cache);
};

class SphereBoxAgent {
public:
  static void registerAgent(Dispatcher &dispatcher);
  static bool processCollision(const WindObject &wind0, const WindObject &wind1, f32 radius, HitCache *cache);
};

class Dispatcher : public mm::mtl::ReferenceObject {
public:
  explicit Dispatcher(const CollisionInfo &info);

  void dispatchAll(mm::mtl::IntrusiveList<WindProbe> &probes, const UpdateInfo &info);

  // Inferred role: collision tests indexed by the probe shape type, then the wind shape type (dispatchAll at
  // 0x7100988490 reads Dispatcher + 0x10 + probe type * 0x10 + wind type * 8); original member name unknown.
  bool (*unknown10[2][2])(const WindObject &, const WindObject &, f32, HitCache *);
  CollisionInfo unknown30; // Inferred role: settings; original member name unknown.
  u8 _34[0x38 - 0x34];
};

static_assert(offsetof(Dispatcher, unknown10) == 0x10, "");
static_assert(offsetof(Dispatcher, unknown30) == 0x30, "");
// The game allocates a Dispatcher with size 0x38 at 0x71001af57c.
static_assert(sizeof(Dispatcher) == 0x38, "");

} // namespace wnd
