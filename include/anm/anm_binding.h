#pragma once
#include <stddef.h>

#include "anm/anm_array-inl.h"
#include "anm/anm_reference_object.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace anm {

class Animation;

class unknown002;

struct ExtraBinding {
  const unknown002 *unknown00; // Inferred role: p extra truck; original member name unknown.
  Array<s16> unknown08;        // Inferred role: truck index table; original member name unknown.
};

static_assert(offsetof(ExtraBinding, unknown08) == 0x08, "");
static_assert(sizeof(ExtraBinding) == 0x18, "");

class Binding : public ReferenceObject {
public:
  explicit Binding(mm::mtl::IAllocator *pAllocator);
  ~Binding() override;

  const Animation *m_pAnimation;
  Array<s16> m_indexTable;
  Array<ExtraBinding> unknown30; // Inferred role: extra bindings; original member name unknown.
};

static_assert(offsetof(Binding, m_pAnimation) == 0x18, "");
static_assert(offsetof(Binding, m_indexTable) == 0x20, "");
static_assert(offsetof(Binding, unknown30) == 0x30, "");

} // namespace anm
