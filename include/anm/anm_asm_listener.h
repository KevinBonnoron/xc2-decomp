#pragma once
#include <stddef.h>

#include "types.h"

namespace anm {

struct AsmAnnotetion {
  const char *unknown00; // Inferred role: name; original member name unknown.
  s32 unknown08;         // Inferred role: kind; original member name unknown.
  u8 _0c[0x10 - 0x0c];
  const char *unknown10; // Inferred role: parameter; original member name unknown.
};

struct AsmKeyframeAnnotation {
  f32 unknown00; // Inferred role: frame; original member name unknown.
  u8 _04[0x8 - 0x4];
  AsmAnnotetion unknown08; // Inferred role: annotation; original member name unknown.
};

static_assert(offsetof(AsmKeyframeAnnotation, unknown08) == 0x8, "");
static_assert(sizeof(AsmKeyframeAnnotation) == 0x20, "");

class AsmListener {
public:
  enum CallBackType {
    CALLBACK_ENTER,
    CALLBACK_LEAVE,
    CALLBACK_FRAME,
  };

  virtual void callback(CallBackType type, const AsmAnnotetion &annotation) = 0;
};

} // namespace anm
