#pragma once
#include "mm_mtl/internal/red_black_tree.h"

namespace mm {
namespace mtl {
class IAllocator;

template <typename Key, typename Value> struct MapPair {
  MapPair() {}
  template <typename K, typename V> MapPair(const K &key, const V &value) : first(key), second(value) {}
  template <typename K, typename V> MapPair(const MapPair<K, V> &other) : first(other.first), second(other.second) {}
  // The user-provided destructor makes the pair non-POD: its copy then leaves out the tail padding.
  ~MapPair() {}

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
  typedef typename tree_type::const_iterator const_iterator;

  explicit Map(IAllocator *allocator = nullptr) : unknown00(allocator) {}

  void setAllocator(IAllocator *allocator) { unknown00.setAllocator(allocator); }
  void clear() { unknown00.clear(); }
  iterator begin() { return unknown00.begin(); }
  iterator end() { return unknown00.end(); }
  const_iterator end() const { return unknown00.end(); }
  iterator find(const Key &key) { return unknown00.find(key); }
  const_iterator find(const Key &key) const { return unknown00.find(key); }
  // Shape from GfGameInsideBattleLock::isInside(GF_OBJ_HANDLE*) (1.0.0: 0x7100317410): a find, then insert of a pair holding a
  // default value when the key is missing, and the value read from the node insert returns.
  Value &operator[](const Key &key) {
    iterator it = find(key);
    if (it == end()) {
      it = iterator(&unknown00, unknown00.insert(MapPair<Key, Value>(key, Value())));
    }
    return it->second;
  }
  int size() const { return unknown00.m_size; }
  void insert(const MapPair<Key, Value> &pair) { unknown00.insert(pair); }
  void erase(const Key &key) {
    iterator it = find(key);
    if (it != end()) {
      unknown00.erase(it.nodePtr);
    }
  }

  tree_type unknown00; // Inferred role: the tree; original member name unknown.
};

} // namespace mtl
} // namespace mm
