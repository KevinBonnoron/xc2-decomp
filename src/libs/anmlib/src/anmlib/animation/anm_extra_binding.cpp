#include <new>

#include "anm/anm_binding.h"
#include "anm/anm_cubic_extra_truck.h"
#include "anm/anm_extra_truck.h"
#include "anm/anm_uncompress_extra_truck.h"

namespace anm {
struct SerialiseArg;

ExtraBinding::ExtraBinding(const SerialiseArg &arg) : unknown08(arg) {
  if (unknown00 != nullptr) {
    switch (unknown00->unknown10) {
    case 0:
      new (unknown00) UncompressExtraTruck(arg);
      break;
    case 1:
      new (unknown00) CubicExtraTruck(arg);
      break;
    }
  }
}

} // namespace anm
