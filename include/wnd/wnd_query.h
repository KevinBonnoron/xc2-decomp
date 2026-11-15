#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_queue.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace wnd {

class AreaBlock;
class AreaWind;
class LocalWind;
class WindProbe;

// Query passed to WindWorld::query and BroadPhazeInterface::query. Original header name unknown. The class names
// and m_rtti come from the game symbols; getRTTI is vtable slot 0 (BroadPhazeOctree::query, 0x71009879d0).
struct Query {
  virtual const mm::mtl::RTTI *getRTTI() const;

  static mm::mtl::RTTI m_rtti;
};

// Filled by BroadPhazeOctree::query.
struct AreaQuery : Query {
  static mm::mtl::RTTI m_rtti;

  AreaBlock *unknown08; // Inferred role: root area of the octree; original member name unknown.
};

static_assert(offsetof(AreaQuery, unknown08) == 0x08, "");

// The next three are filled by WindWorld::query (0x710098aa18). The game loads each object before the "!full()"
// assert of push (0x710098aaac): the const conversion makes the argument a temporary.
struct AreaWindQuery : Query {
  static mm::mtl::RTTI m_rtti;

  mm::mtl::FixedQueue<const AreaWind *, 4096> unknown08; // Inferred role: area winds of the world; original member name unknown.
};

struct LocalWindQuery : Query {
  static mm::mtl::RTTI m_rtti;

  mm::mtl::FixedQueue<const LocalWind *, 4096> unknown08; // Inferred role: local winds of the world; original member name unknown.
};

struct ProbeQuery : Query {
  static mm::mtl::RTTI m_rtti;

  mm::mtl::FixedQueue<const WindProbe *, 4096> unknown08; // Inferred role: probes of the world; original member name unknown.
};

static_assert(offsetof(ProbeQuery, unknown08) == 0x08, "");
static_assert(sizeof(ProbeQuery) == 0x8018, "");

} // namespace wnd
