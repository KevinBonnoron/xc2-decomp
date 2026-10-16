#pragma once
#include <stddef.h>

#include "mm_mtl/intrusive_list.h"
#include "types.h"

namespace ui {

class UIObjectParam : public mm::mtl::IntrusiveListNodeBase {
public:
  struct AdditionalParam {
    f32 alpha;
  };

  UIObjectParam(u32 handle);
  virtual ~UIObjectParam();
  virtual void apply(AdditionalParam &param) const = 0;

  u32 handle;
};

static_assert(offsetof(UIObjectParam, handle) == 0x18, "");

} // namespace ui
