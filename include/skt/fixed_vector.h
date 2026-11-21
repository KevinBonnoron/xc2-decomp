#pragma once
#include <new>
#include <stddef.h>

#include "mm/mm_std_base.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/fixed_vector.h"

namespace skt {

// Local copy of mm::mtl::FixedVector (include/mm_mtl/fixed_vector.h) without its assertions (decision 56). The game's skt code has none of the
// assertions that every other copy of the template has, and skt was built against an older copy of the mtl containers than the rest of the game.
// This header holds the part of the older template that skt uses. Only skt's own headers include it, and include/mm_mtl stays the one
// implementation elsewhere. The template is inlined everywhere and leaves no symbol, so its placement in skt is inferred; the class keeps its
// original name and the member functions keep the names of the current template.
//
// The assertions the game's skt code lacks, by function (0x71...):
//   push_back  size() < capacity() (fixed_vector.h:227): CommandManager::recvBinary 0x7100984284 stores the element at m_size with no test, and
//              CommandManager::recvCommand 0x7100983fd0 only has the test of its own source (the overflow message); CommandParam::parseCommand
//              0x7100984164 appends arguments with no test.
//   erase      validate_iterator(it) (:345): CommandManager::updateCallback 0x71009844d8 and CommandManager::PortInfo::destroy 0x71009830c8 pop the
//              front of unknown50 with no comparison against begin() and end() (the current template gives 126 instructions against the game's 109
//              in updateCallback); CommandManager::removePort 0x71009838f0 erases a PortInfo with none either.
// Assertions of other members are kept as the current template has them, as the skt code gives no evidence either way (the check of
// CommandParam::isValid before CommandParam::getArg reads the element removes the one of operator[]).
template <typename T, size_t N> class FixedVector {
  typedef typename mm::mtl::FixedVectorUnit<alignof(T)>::type Unit;

public:
  FixedVector() : m_size(0) {}
  ~FixedVector() { clear(); }

  T &front() { return *at(0); }

  // __LINE__ must be 181 as in the original header: it is the line argument of the assert.
  const T &operator[](size_t index) const {
#line 181
    MM_ASSERT(index < size());
    return *at(index);
  }

  size_t size() const { return m_size; }
  size_t capacity() const { return N; }
  T *begin() { return reinterpret_cast<T *>(mBuffer); }
  T *end() { return begin() + size(); }

  void clear() {
    while (m_size != 0) {
      at(--m_size)->~T();
    }
  }

  void push_back(const T &value) {
    construct(at(m_size), value);
    m_size++;
  }

  T *erase(T *it) {
    if (it == end()) {
      return it;
    }
    mm::mtl::copy(it + 1, end(), it);
    --m_size;
    destroy(end());
    return it;
  }

  T *at(size_t index) { return reinterpret_cast<T *>(&mBuffer[index * sizeof(T) / sizeof(Unit)]); }
  const T *at(size_t index) const { return reinterpret_cast<const T *>(&mBuffer[index * sizeof(T) / sizeof(Unit)]); }

private:
  static void construct(T *it, const T &value) {
    if (it != nullptr) {
      new (static_cast<void *>(it)) T(value);
    }
  }

  static void destroy(T *it) {
    if (it != nullptr) {
      it->~T();
    }
  }

  Unit mBuffer[sizeof(T) * N / sizeof(Unit)];
  size_t m_size;
};

} // namespace skt
