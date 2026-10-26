#pragma once
#include <stddef.h>

#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace wnd {
class LocalWind;
} // namespace wnd

namespace fw {

struct UpdateInfo;

class WindImpluse : public mm::mtl::ReferenceObject, public mm::mtl::IntrusiveListNode<WindImpluse> {
public:
  ~WindImpluse() override;
  bool update(const UpdateInfo &info);

  wnd::LocalWind *unknown20; // Inferred role: local wind; original member name unknown.
  f32 unknown28;             // Inferred role: elapsed time; original member name unknown.
  f32 unknown2c;             // Inferred role: duration; original member name unknown.
  f32 unknown30;             // Inferred role: power; original member name unknown.
};

static_assert(offsetof(WindImpluse, unknown20) == 0x20, "");
static_assert(offsetof(WindImpluse, unknown28) == 0x28, "");
static_assert(offsetof(WindImpluse, unknown2c) == 0x2c, "");
static_assert(offsetof(WindImpluse, unknown30) == 0x30, "");

} // namespace fw
