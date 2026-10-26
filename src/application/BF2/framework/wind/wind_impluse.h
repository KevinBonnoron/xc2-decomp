#pragma once
#include <stddef.h>

#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/reference_object.h"

namespace wnd {
class LocalWind;
} // namespace wnd

namespace fw {

class WindImpluse : public mm::mtl::ReferenceObject, public mm::mtl::IntrusiveListNode<WindImpluse> {
public:
  wnd::LocalWind *unknown20; // Inferred role: local wind; original member name unknown.
};

static_assert(offsetof(WindImpluse, unknown20) == 0x20, "");

} // namespace fw
