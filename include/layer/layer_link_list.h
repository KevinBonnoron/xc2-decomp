#pragma once
#include "types.h"

namespace layer {

template <typename T> class LayerLinkList {
public:
  LayerLinkList() : unknown00(nullptr), unknown08(nullptr), unknown10(0) {}
  void deleteList(T *node);

  void unknown001(T *node) {
    T *prev = node->unknown00;
    T *next = node->unknown08;
    if (prev == nullptr) {
      if (next == nullptr) {
        unknown00 = nullptr;
        unknown08 = nullptr;
      } else {
        unknown00 = next;
        next->unknown00 = nullptr;
      }
    } else if (next == nullptr) {
      unknown08 = prev;
      prev->unknown08 = nullptr;
    } else {
      prev->unknown08 = next;
      node->unknown08->unknown00 = node->unknown00;
    }
    node->unknown00 = nullptr;
    node->unknown08 = nullptr;
    unknown10--;
  }

  void unknown002(T *node) {
    if (unknown08 == nullptr) {
      unknown00 = node;
      unknown08 = node;
      node->unknown00 = nullptr;
    } else {
      unknown08->unknown08 = node;
      node->unknown00 = unknown08;
      unknown08 = node;
    }
    node->unknown08 = nullptr;
    unknown10++;
  }

  // Inferred role: deletes every node and empties the list; original name unknown.
  void unknown003() {
    T *node = unknown00;
    while (node != nullptr) {
      T *next = node->unknown08;
      delete node;
      node = next;
    }
    unknown10 = 0;
    unknown00 = nullptr;
    unknown08 = nullptr;
  }

  T *unknown00;  // Inferred role: first node; original member name unknown.
  T *unknown08;  // Inferred role: last node; original member name unknown.
  s32 unknown10; // Inferred role: node count; original member name unknown.
};

template <typename T> void LayerLinkList<T>::deleteList(T *node) {
  unknown001(node);
  delete node;
}

} // namespace layer
