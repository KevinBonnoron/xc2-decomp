#pragma once
#include "types.h"

namespace event {

enum CV_TYPE {
  CV_TYPE_UNKNOWN_0, // Inferred role: step; original name unknown.
  CV_TYPE_UNKNOWN_1, // Inferred role: linear; original name unknown.
  CV_TYPE_UNKNOWN_2, // Inferred role: ease in out; original name unknown.
  CV_TYPE_UNKNOWN_3, // Inferred role: ease in; original name unknown.
  CV_TYPE_UNKNOWN_4, // Inferred role: ease out; original name unknown.
  CV_TYPE_UNKNOWN_5, // Inferred role: ease in weak; original name unknown.
  CV_TYPE_UNKNOWN_6, // Inferred role: ease out weak; original name unknown.
};

class Curve {
public:
  static f32 getValue(CV_TYPE type, f32 rate);
};

} // namespace event
