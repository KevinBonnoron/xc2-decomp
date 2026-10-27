#include "ssd/ssd_array.h"
#include "ssd/ssd_array_impl.h" // IWYU pragma: keep
#include "ssd/ssd_behavior.h"   // IWYU pragma: keep
#include "ssd/ssd_delegate.h"   // IWYU pragma: keep

namespace ssd {

template class Array<Delegate::Handle *>;

template List<Delegate::Handle>::Node::~Node();

} // namespace ssd
