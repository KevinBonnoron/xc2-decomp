#include "ml/work_background.h"
#include "mm_mtl/fixed_list.h" // IWYU pragma: keep

namespace ml {

void IWorkBackground::bkgHomeMenu(bool isEnter) {}

void IWorkBackground::bkgHomeMenuDenied() {}

} // namespace ml

template mm::mtl::FixedList<ml::IWorkBackground *, 32>::iterator mm::mtl::FixedList<ml::IWorkBackground *, 32>::erase(mm::mtl::FixedList<ml::IWorkBackground *, 32>::iterator);
