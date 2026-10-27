#pragma once

namespace ml {

// Inferred helper: unlinks a node from a doubly linked list and clears its links; original name unknown.
template <typename T> inline void unknown001(T *&first, T *&last, T *node) {
  T *previous = node->unknown00;
  T *next = node->unknown08;
  if (previous == nullptr) {
    if (next == nullptr) {
      first = nullptr;
      last = nullptr;
    } else {
      first = next;
      next->unknown00 = nullptr;
    }
  } else if (next == nullptr) {
    last = previous;
    previous->unknown08 = nullptr;
  } else {
    previous->unknown08 = next;
    node->unknown08->unknown00 = node->unknown00;
  }
  node->unknown00 = nullptr;
  node->unknown08 = nullptr;
}

} // namespace ml
