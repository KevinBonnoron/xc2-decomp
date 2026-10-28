#pragma once
#include "mm_mtl/internal/red_black_tree.h"

namespace mm {
namespace mtl {

template <typename T> class Set {
public:
  template <typename U> struct TreeValue {
    U unknown00; // Inferred role: key; original member name unknown.
  };

  template <typename U> struct TreeTraits {
    typedef U key_type;
    typedef TreeValue<U> value_type;
    static const key_type &get_key(const value_type &value) { return value.unknown00; }
  };

  void insert(const T &key) {
    TreeValue<T> value;
    value.unknown00 = key;
    unknown00.insert(value);
  }

  RedBlackTreeBase<TreeTraits<T>> unknown00; // Inferred role: the tree; original member name unknown.
};

} // namespace mtl
} // namespace mm
