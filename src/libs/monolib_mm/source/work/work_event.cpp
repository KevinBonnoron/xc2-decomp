#include "ml/work_event.h"
#include "mm_mtl/fixed_list.h" // IWYU pragma: keep

namespace ml {

void IWorkEvent::OnSystemPause(unsigned int reason) {}

} // namespace ml

template mm::mtl::FixedList<ml::IWorkEvent *, 32>::iterator mm::mtl::FixedList<ml::IWorkEvent *, 32>::erase(mm::mtl::FixedList<ml::IWorkEvent *, 32>::iterator);
