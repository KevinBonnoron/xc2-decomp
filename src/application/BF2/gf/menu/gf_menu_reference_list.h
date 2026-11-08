#pragma once
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"

namespace gf {

// Reference-counted holder of a list shared by the menu objects (_ZN2gf19GfMenuReferenceListINS_14GfMenuItemListEE...).
// Layout seen in GfMenuObjItemList::initialize: vtable, reference count, then the list at 0x10 (object size 0x18).
template <typename T> class GfMenuReferenceList : public mm::mtl::ReferenceObject {
public:
  mm::mtl::IntrusivePtr<T> unknown10; // Inferred role: referenced list; original member name unknown.
};

} // namespace gf
