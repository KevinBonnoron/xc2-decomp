#pragma once
#include <stddef.h>

#include "anm/anm_reference_object.h"

namespace anm {

class Animation;

class Binding : public ReferenceObject {
public:
  ~Binding() override;

  const Animation *m_pAnimation;
};

static_assert(offsetof(Binding, m_pAnimation) == 0x18, "");

} // namespace anm
