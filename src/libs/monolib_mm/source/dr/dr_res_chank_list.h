#pragma once

namespace ml {

// Doubly linked list of memory chunks, linked through T::unknown08 (previous) and T::unknown10 (next).
template <typename T> class DrResChankList {
public:
  // Inferred helper: unlinks an object from the list; original name unknown.
  void unknown001(T *obj) {
    if (obj->unknown08 == nullptr) {
      if (obj->unknown10 == nullptr) {
        unknown00 = nullptr;
        unknown08 = nullptr;
      } else {
        unknown00 = obj->unknown10;
        unknown00->unknown08 = nullptr;
      }
    } else if (obj->unknown10 == nullptr) {
      unknown08 = obj->unknown08;
      unknown08->unknown10 = nullptr;
    } else {
      obj->unknown08->unknown10 = obj->unknown10;
      obj->unknown10->unknown08 = obj->unknown08;
    }
    obj->unknown08 = nullptr;
    obj->unknown10 = nullptr;
  }

  // Inferred helper: links an object at the head of the list; original name unknown.
  void unknown002(T *obj) {
    if (unknown00 == nullptr) {
      unknown00 = obj;
      unknown08 = obj;
      obj->unknown10 = nullptr;
    } else {
      unknown00->unknown08 = obj;
      obj->unknown10 = unknown00;
      unknown00 = obj;
    }
    obj->unknown08 = nullptr;
  }

  // Inferred helper: links an object after another one; original name unknown.
  void unknown003(T *prev, T *obj) {
    T *next = prev->unknown10;
    prev->unknown10 = obj;
    obj->unknown08 = prev;
    if (next != nullptr) {
      obj->unknown10 = next;
      next->unknown08 = obj;
    } else {
      obj->unknown10 = nullptr;
      unknown08 = obj;
    }
  }

  // Inferred helper: links an object at the end of the list; original name unknown.
  void unknown004(T *obj) {
    if (unknown08 == nullptr) {
      unknown00 = obj;
      unknown08 = obj;
      obj->unknown08 = nullptr;
    } else {
      unknown08->unknown10 = obj;
      obj->unknown08 = unknown08;
      unknown08 = obj;
    }
    obj->unknown10 = nullptr;
  }

  // Inferred helper: deletes every object of the list and empties it; original name unknown.
  void unknown005() {
    for (T *obj = unknown00; obj != nullptr;) {
      T *next = obj->unknown10;
      delete obj;
      obj = next;
    }
    unknown00 = nullptr;
    unknown08 = nullptr;
  }

  void changeList(T *first, T *second);

  T *unknown00; // Inferred role: first object; original member name unknown.
  T *unknown08; // Inferred role: last object; original member name unknown.
};

template <typename T> void DrResChankList<T>::changeList(T *first, T *second) {
  T *firstPrev = first->unknown08;
  T *secondPrev = second->unknown08;
  if (firstPrev == second) {
    T *firstNext = first->unknown10;
    if (secondPrev == nullptr) {
      unknown00 = first;
    } else {
      secondPrev->unknown10 = first;
    }
    first->unknown08 = secondPrev;
    if (firstNext == nullptr) {
      unknown08 = second;
    } else {
      firstNext->unknown08 = second;
    }
    second->unknown08 = first;
    second->unknown10 = firstNext;
    first->unknown10 = second;
  } else if (secondPrev == first) {
    T *secondNext = second->unknown10;
    if (firstPrev == nullptr) {
      unknown00 = second;
    } else {
      firstPrev->unknown10 = second;
    }
    second->unknown08 = firstPrev;
    if (secondNext == nullptr) {
      unknown08 = first;
    } else {
      secondNext->unknown08 = first;
    }
    first->unknown08 = second;
    first->unknown10 = secondNext;
    second->unknown10 = first;
  } else {
    unknown001(first);
    unknown001(second);
    if (firstPrev == nullptr) {
      unknown002(second);
    } else {
      unknown003(firstPrev, second);
    }
    if (secondPrev == nullptr) {
      unknown002(first);
    } else {
      unknown003(secondPrev, first);
    }
  }
}

} // namespace ml
