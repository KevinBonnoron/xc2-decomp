#pragma once

namespace fw {

// Inferred helper: searches the list of a layer (lights, models, visible objects) for an object; original name unknown.
// Evidence: the search inlined in LightObject::create and VisibleObject::create (1.0.0: 0x710017a91c, 0x710018ec10).
template <typename Iterator, typename T> static inline Iterator unknown001(Iterator first, Iterator last, T *value) {
  while (true) {
    if (first == last) {
      return last;
    }
    if (first.get() == value) {
      return first;
    }
    ++first;
  }
}

} // namespace fw
