#pragma once
#include <stddef.h>

#include "ai/ai_state.h"
#include "mm/mm_std_base.h"
#include "mm_math/mm_math.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace ai {

class Hfsm {
public:
  typedef State *(*CreateFunc)(void *buffer);

  struct StateInfo {
    CreateFunc unknown00; // Inferred role: create; original member name unknown.
    int unknown08;        // Inferred role: parent; original member name unknown.
  };

  // __LINE__ must be 50 as in the original header: it is the line argument of the assert.
#line 49
  template <typename T> void registerState(u32 stateID, int parent) {
    MM_ASSERT(m_setup);
    m_stateInfos[stateID].unknown00 = &T::create;
    m_stateInfos[stateID].unknown08 = parent;
    unknown78 = (mm::max(sizeof(T), unknown78) + 15) & ~static_cast<size_t>(15);
  }

  void *unknown00; // Inferred role: p owner; original member name unknown.
  State *m_pState;
  mm::mtl::Vector<StateInfo> m_stateInfos;
  u8 _38[0x78 - 0x38];
  size_t unknown78; // Inferred role: state size; original member name unknown.
  bool m_setup;
};

static_assert(sizeof(Hfsm::StateInfo) == 0x10, "");
static_assert(offsetof(Hfsm, m_stateInfos) == 0x10, "");
static_assert(offsetof(Hfsm, unknown78) == 0x78, "");
static_assert(offsetof(Hfsm, m_setup) == 0x80, "");

} // namespace ai
