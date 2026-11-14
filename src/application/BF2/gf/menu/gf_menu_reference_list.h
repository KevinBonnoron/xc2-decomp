#pragma once
#include "gf/gf_allocator.h"
#include "mm_mtl/reference_object.h"

namespace gf {

// Reference-counted holder of a list shared by the menu objects (_ZN2gf19GfMenuReferenceListINS_14GfMenuItemListEE...).
// Layout seen in GfMenuObjItemList::initialize: vtable, reference count, then the list at 0x10 (object size 0x18).
template <typename T> class GfMenuReferenceList : public mm::mtl::ReferenceObject {
public:
  GfMenuReferenceList() : unknown10(nullptr) {}
  ~GfMenuReferenceList() override { mm::mtl::safeRelease(unknown10); }

  // Inferred helper: replaces the referenced list; original name unknown. GfMenuObjItemList::initialize (1.0.0: 0x710047afc0) and
  // GfMenuObjItemList::TypeListener::reciveEvent (0x710047b278) store the new list without releasing the previous one.
  void unknown001(T *list) {
    if (list != nullptr) {
      unknown10 = list;
      unknown10->addRef();
    } else {
      mm::mtl::safeRelease(unknown10);
    }
  }

  // Inferred helper: allocates an empty reference list; original name unknown.
  // __LINE__ must be 51 as in the original header: it is the line argument of operator new.
#line 51
  static GfMenuReferenceList *unknown002() { return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfMenuReferenceList(); }

  // Inferred role: referenced list; original member name unknown. A plain pointer: the game reads it without the IntrusivePtr assert
  // (GfMenuObjItemList::ListListener::reciveEvent, 0x710047b3c8) and stores it without releasing the previous value.
  T *unknown10;
};

} // namespace gf
