#pragma once
#include <stddef.h>

#include "gf/game/quest/gf_quest_id.h"
#include "gf/gf_allocator.h"
#include "mm_mtl/reference_object.h"

namespace gf {

class GfMenuReferenceQuest : public mm::mtl::ReferenceObject {
public:
  virtual void getQuest(QuestID &quest) const;

  QuestID unknown0c; // Inferred role: quest; original member name unknown.
};

static_assert(offsetof(GfMenuReferenceQuest, unknown0c) == 0x0c, "");

// Inferred helper: allocates a quest reference; original name unknown.
// __LINE__ must be 57 as in the original header: it is the line argument of operator new.
#line 57
inline GfMenuReferenceQuest *unknown161() { return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfMenuReferenceQuest; }

} // namespace gf
