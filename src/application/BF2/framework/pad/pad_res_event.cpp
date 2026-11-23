#include "framework/pad/pad_res_event.h"

#include "mm_mtl/intrusive_ptr.h" // IWYU pragma: keep
#include "mm_mtl/vector.h"        // IWYU pragma: keep

template void mm::mtl::Vector<mm::mtl::IntrusivePtr<fw::PadResEvent const>>::expand(size_t, size_t);
template void mm::mtl::Vector<mm::mtl::IntrusivePtr<fw::PadResEvent const>>::push_back(mm::mtl::IntrusivePtr<fw::PadResEvent const> const &);

template void mm::mtl::Vector<mm::mtl::IntrusivePtr<fw::PadResEvent const>>::extend(size_t, size_t, const mm::mtl::IntrusivePtr<fw::PadResEvent const> &);
template void mm::mtl::Vector<mm::mtl::IntrusivePtr<fw::PadResEvent const>>::resize(size_t, const mm::mtl::IntrusivePtr<fw::PadResEvent const> &);
