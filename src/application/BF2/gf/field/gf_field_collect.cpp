#include "gf/field/gf_field_collect.h"
#include "mm_mtl/delegate.h" // IWYU pragma: keep

namespace gf {

void GfFieldCollect::seqEnd(float) {}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfFieldCollect>::~PtrSingleton();
template float mm::mtl::Delegate<float(float, float, float)>::staticFuncInvoker(const mm::mtl::Delegate<float(float, float, float)> *, float, float, float);
