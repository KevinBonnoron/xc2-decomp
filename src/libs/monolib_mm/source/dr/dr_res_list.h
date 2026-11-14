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

// Inferred helper: links a node at the end of a doubly linked list, the counterpart of unknown001; original name unknown.
// Named unknown101 because the unity builds of the dr sources already declare types named unknown005.
template <typename T> inline void unknown101(T *&first, T *&last, T *node) {
  if (last == nullptr) {
    first = node;
    last = node;
    node->unknown00 = nullptr;
  } else {
    last->unknown08 = node;
    node->unknown00 = last;
    last = node;
  }
  node->unknown08 = nullptr;
}

// Inferred helper: finds the node of a resource key in a list and adds a reference to it; original name unknown.
template <typename T> inline T *unknown003(T *first, const void *key) {
  for (T *node = first; node != nullptr; node = node->unknown08) {
    if (node->unknown10 == key) {
      node->unknown18++;
      return node;
    }
  }
  return nullptr;
}

// Inferred helper: unlinks a node linked through unknown08 and unknown10 from a doubly linked list and clears its links; original name unknown.
template <typename T> inline void unknown004(T *&first, T *&last, T *node) {
  T *previous = node->unknown08;
  T *next = node->unknown10;
  if (previous == nullptr) {
    if (next == nullptr) {
      first = nullptr;
      last = nullptr;
    } else {
      first = next;
      next->unknown08 = nullptr;
    }
  } else if (next == nullptr) {
    last = previous;
    previous->unknown10 = nullptr;
  } else {
    previous->unknown10 = next;
    node->unknown10->unknown08 = node->unknown08;
  }
  node->unknown08 = nullptr;
  node->unknown10 = nullptr;
}

// Inferred helper: links a node at the end of a doubly linked list linked through unknown08 and unknown10; original name unknown.
template <typename T> inline void unknown100(T *&first, T *&last, T *node) {
  if (last == nullptr) {
    first = node;
    last = node;
    node->unknown08 = nullptr;
  } else {
    last->unknown10 = node;
    node->unknown08 = last;
    last = node;
  }
  node->unknown10 = nullptr;
}

} // namespace ml
