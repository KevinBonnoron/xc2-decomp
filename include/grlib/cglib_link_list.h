#pragma once

namespace grlib {

// Layout evidence: CGLibBuffSamplerTbl::releaseObj 0x71007b0aa0 (first object at 0x0, last object at 0x8, both cleared
// after the walk) and the list updates of CGLibBuffSamplerTbl (0x71007b0af4 to 0x71007b0f9c). The linked type has its
// previous link at 0x0 (unknown00) and its next link at 0x8 (unknown08).
template <typename T> class CGLibLinkList {
public:
  // Inferred role: append an object at the end of the list; original name unknown.
  void unknown001(T *obj) {
    if (unknown08 == nullptr) {
      unknown00 = obj;
      unknown08 = obj;
      obj->unknown00 = nullptr;
    } else {
      unknown08->unknown08 = obj;
      obj->unknown00 = unknown08;
      unknown08 = obj;
    }
    obj->unknown08 = nullptr;
  }

  // Inferred role: unlink an object from the list; original name unknown.
  void unknown002(T *obj) {
    T *previous = obj->unknown00;
    T *next = obj->unknown08;
    if (previous != nullptr) {
      if (next != nullptr) {
        previous->unknown08 = next;
        obj->unknown08->unknown00 = obj->unknown00;
      } else {
        unknown08 = previous;
        previous->unknown08 = nullptr;
      }
    } else if (next != nullptr) {
      unknown00 = next;
      next->unknown00 = nullptr;
    } else {
      unknown00 = nullptr;
      unknown08 = nullptr;
    }
    obj->unknown00 = nullptr;
    obj->unknown08 = nullptr;
  }

  T *unknown00; // Inferred role: first object; original member name unknown.
  T *unknown08; // Inferred role: last object; original member name unknown.
};

} // namespace grlib
