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

  wnd::WindProbe *probe;
  mm::mtl::IntrusivePtr<ReferenceFrame> frame;
  f32 radius;
  bool isFollowFrame;
};

static_assert(offsetof(WindProbe, probe) == 0x20, "");
static_assert(offsetof(WindProbe, frame) == 0x28, "");
static_assert(offsetof(WindProbe, radius) == 0x30, "");
static_assert(offsetof(WindProbe, isFollowFrame) == 0x34, "");
static_assert(sizeof(WindProbe) == 0x38, "");

} // namespace fw
