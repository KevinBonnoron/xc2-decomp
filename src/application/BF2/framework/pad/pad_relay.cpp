#include "fw/fw_pad.h"
#include "mm_mtl/delegate.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/map.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

PadRelay::PadRelay() : unknown00(-1), unknown04(-1) {}

PadRelay::~PadRelay() {}

void PadRelay::bind(int padNo, int type, mm::mtl::IAllocator *allocator) {
  unknown00 = padNo;
  unknown04 = type;
  unknown08.setAllocator(allocator);
  unknown20.setAllocator(allocator);
}

void PadRelay::unbind() {
  unknown20.clear();
  unknown08.clear();
  unknown20.setAllocator(nullptr);
  unknown08.setAllocator(nullptr);
  unknown00 = -1;
  unknown04 = -1;
}

} // namespace fw
