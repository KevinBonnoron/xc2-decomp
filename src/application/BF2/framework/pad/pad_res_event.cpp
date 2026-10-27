#include "framework/pad/pad_res_event.h"

#include "mm_mtl/intrusive_ptr.h" // IWYU pragma: keep
#include "mm_mtl/vector.h"        // IWYU pragma: keep
#include <string.h>

namespace fw {

const ResAction *findAction(const PadResEvent *event, const char *name) {
  for (u32 i = 0; i < event->unknown20; i++) {
    if (strcmp(event->unknown18[i].unknown00, name) == 0) {
      return &event->unknown18[i];
    }
  }

  return nullptr;
}

} // namespace fw

template void mm::mtl::Vector<mm::mtl::IntrusivePtr<fw::PadResEvent const>>::expand(size_t, size_t);
template void mm::mtl::Vector<mm::mtl::IntrusivePtr<fw::PadResEvent const>>::push_back(mm::mtl::IntrusivePtr<fw::PadResEvent const> const &);
