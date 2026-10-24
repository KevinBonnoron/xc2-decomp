#pragma once
#include <stddef.h>

#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace wnd {
class WindProbe;
} // namespace wnd

namespace fw {

class ReferenceFrame;

class WindProbe : public mm::mtl::ReferenceObject, public mm::mtl::IntrusiveListNode<WindProbe> {
public:
  WindProbe(u32 group, f32 radius, mm::mtl::IntrusivePtr<ReferenceFrame> frame, bool isFollowFrame);
  ~WindProbe() override;
  void update();

  wnd::WindProbe *unknown20;                       // Inferred role: probe; original member name unknown.
  mm::mtl::IntrusivePtr<ReferenceFrame> unknown28; // Inferred role: frame; original member name unknown.
  f32 unknown30;                                   // Inferred role: radius; original member name unknown.
  bool unknown34;                                  // Inferred role: follow frame; original member name unknown.
};

static_assert(offsetof(WindProbe, unknown20) == 0x20, "");
static_assert(offsetof(WindProbe, unknown28) == 0x28, "");
static_assert(offsetof(WindProbe, unknown30) == 0x30, "");
static_assert(offsetof(WindProbe, unknown34) == 0x34, "");
static_assert(sizeof(WindProbe) == 0x38, "");

} // namespace fw
