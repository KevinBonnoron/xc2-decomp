#pragma once
#include "mm_mtl/internal/red_black_tree.h"

namespace mm {
namespace mtl {
class IAllocator;

template <typename Key, typename Value> struct MapPair {
  Key first;
  Value second;
};

template <typename Key, typename Value> class Map {
public:
  template <typename K, typename V> struct MapTraits {
    typedef K key_type;
    typedef MapPair<K, V> value_type;
    static const key_type &get_key(const value_type &value) { return value.first; }
  };

  typedef RedBlackTreeBase<MapTraits<Key, Value>> tree_type;
  typedef typename tree_type::iterator iterator;

  void setAllocator(IAllocator *allocator) { unknown00.setAllocator(allocator); }
  void clear() { unknown00.clear(); }
  iterator begin() { return unknown00.begin(); }
  iterator end() { return unknown00.end(); }
  iterator find(const Key &key) { return unknown00.find(key); }
  void insert(const MapPair<Key, Value> &pair) { unknown00.insert(pair); }

  tree_type unknown00; // Inferred role: the tree; original member name unknown.
};

} // namespace mtl
} // namespace mm
