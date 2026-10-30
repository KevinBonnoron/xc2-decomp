#pragma once
#include "mm_mtl/reference_object.h"

namespace ai {

// Only the reference counted base is declared (reference count at 0x08 in Vector<IntrusivePtr<BehaviorNode>>::destroy): the
// node members are not decompiled yet.
class BehaviorNode : public mm::mtl::ReferenceObject {};

// Only the reference counted base is declared (reference count at 0x08 in Vector<IntrusivePtr<BehaviorNodeInfo>>::destroy):
// the members are not decompiled yet.
class BehaviorNodeInfo : public mm::mtl::ReferenceObject {};

} // namespace ai
