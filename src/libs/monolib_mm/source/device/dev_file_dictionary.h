#pragma once
#include <stddef.h>
#include <string.h>

#include "types.h"

namespace ml {

// Double-array trie mapping a file name to an index. The template arguments are those of the game's symbols:
// the value type, the allocator, the value returned for a key without value (-1) and for a missing path (-2), and a flag (true).
template <typename T, typename ALLOC, int NO_VALUE, int NO_PATH, bool FLAG> class DevFileDictionary {
public:
  // Inferred type: node of the double array; the original type name is unknown.
  struct unknown002 {
    int unknown00; // Inferred role: base (negative: offset of the key tail) or, in a leaf, the value; original member name unknown.
    int unknown04; // Inferred role: check, the index of the parent node; original member name unknown.
  };

  struct ninfo {
    ninfo() : unknown00(0), unknown01(0) {}

    u8 unknown00; // Inferred role: next sibling label; original member name unknown.
    u8 unknown01; // Inferred role: first child label; original member name unknown.
  };

  struct block {
    block() : unknown00(0), unknown04(0), unknown08(256), unknown0a(257), unknown0c(0), unknown10(0) {}

    s32 unknown00; // Inferred role: previous block of the list; original member name unknown.
    s32 unknown04; // Inferred role: next block of the list; original member name unknown.
    s16 unknown08; // Inferred role: number of empty nodes; original member name unknown.
    s16 unknown0a; // Role and original member name unknown.
    s32 unknown0c; // Role and original member name unknown.
    s32 unknown10; // Inferred role: first empty node; original member name unknown.
  };

  // Type name from the game's symbol (result_triple_type); the layout comes from the stores of commonPrefixPredict (0x7100739238).
  struct result_triple_type {
    int unknown00;    // Inferred role: value found; original member name unknown.
    size_t unknown08; // Inferred role: length of the key found; original member name unknown.
    size_t unknown10; // Inferred role: node (or tail position) the key ends on; original member name unknown.
  };

  static_assert(sizeof(unknown002) == 0x8, "");
  static_assert(sizeof(ninfo) == 0x2, "");
  static_assert(sizeof(block) == 0x14, "");
  static_assert(sizeof(result_triple_type) == 0x18, "");

  ~DevFileDictionary() { clear(false); }

  void clear(bool reuse);
  void loadFromMemory(void *tail, size_t tailSize, void *array, size_t size);
  void restoreBlock();
  void restoreNinfo();
  T findImpl(const char *key, size_t &from, size_t &pos, size_t len) const;
  T begin(size_t &from, size_t &len);
  T next(size_t &from, size_t &len, size_t root);
  template <typename U> void reallocArray(U *&array, int size, int from);

  // Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a symbol.
  // Inserts the label into the sibling chain of from, in label order (user: restoreNinfo, 1.0.0: 0x710073d178; the game has no symbol, it is inlined). The statements follow the
  // sibling insertion of the double-array library the type names come from (cedar). Written inline in restoreNinfo the function is 53 instructions (the flag and the loop test fold
  // into one chain of branches), 51 with a while loop, against the game's 56; the helper takes the flag as an argument, which keeps the game's join.
  void pushSibling(int from, int base, u8 label, bool flag);

  // Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a symbol.
  // Links block bi at the head of a block list (user: restoreBlock, 1.0.0: 0x710073cfa0; inlined). Written inline in restoreBlock (the `head == 0 && num != 0` test in the if) the
  // function is 120 instructions against the game's 118 (the test folds into the head selection); the bool argument keeps the game's ccmp.
  void pushBlock(int bi, int &headOut, bool empty);

  // Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a symbol.
  // Stores one search result (user: commonPrefixPredict, 1.0.0: 0x7100739238; inlined). The id is stored first: with the three stores written in the loop commonPrefixPredict is 57
  // instructions against the game's 56 (the loads of the length and of the id are interleaved with the stores); as a helper in the order value, length, id the pointer is biased on
  // the length (56 instructions, first difference at 0x71007392bc).
  static void setResult(result_triple_type *x, int value, size_t length, size_t id);
  template <typename U> size_t commonPrefixPredict(const char *key, U *result, size_t resultLength);

  // Inferred role: exact search of a whole key, a missing path reported as a missing value (inlined in DevFileArchiver::getFileInfo); original name unknown.
  T unknown001(const char *key) const {
    size_t len = strlen(key);
    size_t from = 0;
    size_t pos = 0;
    T result = findImpl(key, from, pos, len);
    if (result == NO_PATH) {
      result = NO_VALUE;
    }
    return result;
  }

  unknown002 *unknown00; // Inferred role: node array, released by clear; original member name unknown.
  char *unknown08;       // Inferred role: tail array, released by clear; original member name unknown.
  s32 *unknown10;        // Inferred role: tail index array allocated by loadFromMemory; original member name unknown.
  ninfo *unknown18;      // Inferred role: node info array rebuilt by restoreNinfo; original member name unknown.
  block *unknown20;      // Inferred role: block array rebuilt by restoreBlock; original member name unknown.
  s32 unknown28;         // Inferred role: block list head; original member name unknown.
  s32 unknown2c;         // Inferred role: block list head; original member name unknown.
  s32 unknown30;         // Inferred role: block list head; original member name unknown.
  s32 unknown34;         // Inferred role: capacity, set from the node count by loadFromMemory; original member name unknown.
  s32 unknown38;         // Inferred role: tail size set by loadFromMemory; original member name unknown.
  s32 unknown3c;         // Inferred role: first tail word read by loadFromMemory; original member name unknown.
  s32 unknown40;         // Inferred role: set to 1 by loadFromMemory; original member name unknown.
  bool unknown44;        // Inferred role: arrays borrowed from loaded memory, not released by clear; original member name unknown.
  ALLOC *unknown48;      // Inferred role: allocator of the arrays; original member name unknown.
};

template <typename T, typename ALLOC, int NO_VALUE, int NO_PATH, bool FLAG> void DevFileDictionary<T, ALLOC, NO_VALUE, NO_PATH, FLAG>::clear(bool reuse) {
  if (!unknown44) {
    if (unknown00 != nullptr) {
      unknown48->deallocate(unknown00);
      unknown00 = nullptr;
    }
  } else {
    unknown00 = nullptr;
    unknown08 = nullptr;
  }
  if (unknown08 != nullptr) {
    unknown48->deallocate(unknown08);
    unknown08 = nullptr;
  }
  if (unknown10 != nullptr) {
    unknown48->deallocate(unknown10);
    unknown10 = nullptr;
  }
  if (unknown18 != nullptr) {
    unknown48->deallocate(unknown18);
    unknown18 = nullptr;
  }
  if (unknown20 != nullptr) {
    unknown48->deallocate(unknown20);
    unknown20 = nullptr;
  }
  unknown28 = unknown2c = unknown30 = unknown34 = unknown38 = unknown3c = unknown40 = 0;
  unknown44 = false;
}

template <typename T, typename ALLOC, int NO_VALUE, int NO_PATH, bool FLAG>
void DevFileDictionary<T, ALLOC, NO_VALUE, NO_PATH, FLAG>::loadFromMemory(void *tail, size_t tailSize, void *array, size_t size) {
  clear(false);
  unknown00 = static_cast<unknown002 *>(array);
  unknown08 = static_cast<char *>(tail);
  unknown10 = static_cast<s32 *>(unknown48->allocate(4, 8));
  unknown38 = size;
  unknown44 = true;
  *unknown10 = 0;
  if (unknown18 != nullptr && unknown20 != nullptr) {
    return;
  }
  if (unknown20 == nullptr) {
    restoreBlock();
  }
  if (unknown18 == nullptr) {
    restoreNinfo();
  }
  unknown34 = unknown38;
  memcpy(&unknown3c, unknown08, sizeof(unknown3c));
  unknown40 = 1;
}

template <typename T, typename ALLOC, int NO_VALUE, int NO_PATH, bool FLAG>
T DevFileDictionary<T, ALLOC, NO_VALUE, NO_PATH, FLAG>::findImpl(const char *key, size_t &from, size_t &pos, size_t len) const {
  size_t offset = from >> 32;
  if (offset == 0) {
    for (; unknown00[from].unknown00 >= 0;) {
      if (pos == len) {
        const unknown002 &leaf = unknown00[unknown00[from].unknown00];
        if (leaf.unknown04 != static_cast<int>(from)) {
          return NO_VALUE;
        }
        return leaf.unknown00;
      }
      size_t to = unknown00[from].unknown00;
      to ^= static_cast<u8>(key[pos]);
      if (unknown00[to].unknown04 != static_cast<int>(from)) {
        return NO_PATH;
      }
      pos++;
      from = to;
    }
    offset = -unknown00[from].unknown00;
  }
  size_t start = pos;
  const char *tail = &unknown08[offset] - start;
  if (pos < len) {
    do {
      if (key[pos] != tail[pos]) {
        break;
      }
      pos++;
    } while (pos < len);
    if (pos - start != 0) {
      from = (from & 0xffffffff) | (offset + (pos - start)) << 32;
    }
    if (pos < len) {
      return NO_PATH;
    }
  }
  if (tail[pos] != '\0') {
    return NO_VALUE;
  }
  T value;
  memcpy(&value, &tail[len + 1], sizeof(T));
  return value;
}

template <typename T, typename ALLOC, int NO_VALUE, int NO_PATH, bool FLAG> T DevFileDictionary<T, ALLOC, NO_VALUE, NO_PATH, FLAG>::next(size_t &from, size_t &len, size_t root) {
  u8 label = 0;
  int offset = static_cast<int>(from >> 32);
  if (offset != 0) {
    if (root >> 32) {
      return NO_PATH;
    }
    from &= 0xffffffff;
    len -= unknown00[from].unknown00 + offset;
  } else {
    label = unknown18[unknown00[from].unknown00].unknown00;
  }
  for (; !label && from != root; len--) {
    label = unknown18[from].unknown00;
    from = unknown00[from].unknown04;
  }
  if (!label) {
    return NO_PATH;
  }
  from = static_cast<size_t>(unknown00[from].unknown00) ^ label;
  len++;
  return begin(from, len);
}

template <typename T, typename ALLOC, int NO_VALUE, int NO_PATH, bool FLAG> T DevFileDictionary<T, ALLOC, NO_VALUE, NO_PATH, FLAG>::begin(size_t &from, size_t &len) {
  u8 label = 0;
  if (unknown18 == nullptr) {
    restoreNinfo();
  }
  int base = from >> 32 ? -static_cast<int>(from >> 32) : unknown00[from].unknown00;
  if (base >= 0) {
    label = unknown18[from].unknown01;
    if (from == 0 && !(label = unknown18[base ^ label].unknown00)) {
      return NO_PATH;
    }
    for (; base >= 0 && label; ++len) {
      from = static_cast<size_t>(base) ^ label;
      base = unknown00[from].unknown00;
      label = unknown18[from].unknown01;
    }
    if (base >= 0) {
      return unknown00[base ^ label].unknown00;
    }
  }
  size_t tailLength = strlen(&unknown08[-base]);
  from = (from & 0xffffffff) | static_cast<size_t>(tailLength - base) << 32;
  len += tailLength;
  T value;
  memcpy(&value, &unknown08[-base] + tailLength + 1, sizeof(T));
  return value;
}

template <typename T, typename ALLOC, int NO_VALUE, int NO_PATH, bool FLAG> void DevFileDictionary<T, ALLOC, NO_VALUE, NO_PATH, FLAG>::restoreBlock() {
  reallocArray(unknown20, unknown38 >> 8, 0);
  unknown28 = unknown2c = unknown30 = 0;
  for (int bi = 0, e = 0; e < unknown38; ++bi) {
    block &b = unknown20[bi];
    b.unknown08 = 0;
    for (; e < (bi << 8) + 256; ++e) {
      if (unknown00[e].unknown04 < 0 && b.unknown08++ == 0) {
        b.unknown10 = e;
      }
    }
    int &head = b.unknown08 == 1 ? unknown2c : b.unknown08 == 0 ? unknown28 : unknown30;
    pushBlock(bi, head, head == 0 && b.unknown08 != 0);
  }
}

template <typename T, typename ALLOC, int NO_VALUE, int NO_PATH, bool FLAG> void DevFileDictionary<T, ALLOC, NO_VALUE, NO_PATH, FLAG>::pushBlock(int bi, int &headOut, bool empty) {
  block &b = unknown20[bi];
  if (empty) {
    headOut = b.unknown00 = b.unknown04 = bi;
  } else {
    int &tailOut = unknown20[headOut].unknown00;
    b.unknown00 = tailOut;
    b.unknown04 = headOut;
    headOut = tailOut = unknown20[tailOut].unknown04 = bi;
  }
}

template <typename T, typename ALLOC, int NO_VALUE, int NO_PATH, bool FLAG> void DevFileDictionary<T, ALLOC, NO_VALUE, NO_PATH, FLAG>::restoreNinfo() {
  reallocArray(unknown18, unknown38, 0);
  for (int to = 0; to < unknown38; ++to) {
    const int from = unknown00[to].unknown04;
    if (from < 0) {
      continue;
    }
    const int base = unknown00[from].unknown00;
    if (const u8 label = base ^ to) {
      pushSibling(from, base, label, from == 0 || unknown18[from].unknown01 != 0 || unknown00[base].unknown04 == from);
    }
  }
}

template <typename T, typename ALLOC, int NO_VALUE, int NO_PATH, bool FLAG> void DevFileDictionary<T, ALLOC, NO_VALUE, NO_PATH, FLAG>::pushSibling(int from, int base, u8 label, bool flag) {
  u8 *child = &unknown18[from].unknown01;
  if (flag && label > *child) {
    do {
      child = &unknown18[base ^ *child].unknown00;
    } while (*child != 0 && *child < label);
  }
  unknown18[base ^ label].unknown00 = *child;
  *child = label;
}

template <typename T, typename ALLOC, int NO_VALUE, int NO_PATH, bool FLAG>
template <typename U>
size_t DevFileDictionary<T, ALLOC, NO_VALUE, NO_PATH, FLAG>::commonPrefixPredict(const char *key, U *result, size_t resultLength) {
  size_t length = strlen(key);
  size_t from = 0;
  size_t pos = 0;
  size_t keyLength = 0;
  if (findImpl(key, from, pos, length) == NO_PATH) {
    return 0;
  }
  size_t root = from;
  size_t count = 0;
  for (T value = begin(from, keyLength); value != NO_PATH; value = next(from, keyLength, root)) {
    if (count < resultLength) {
      setResult(&result[count], value, keyLength, from);
    }
    ++count;
  }
  return count;
}

template <typename T, typename ALLOC, int NO_VALUE, int NO_PATH, bool FLAG>
void DevFileDictionary<T, ALLOC, NO_VALUE, NO_PATH, FLAG>::setResult(result_triple_type *x, int value, size_t length, size_t id) {
  x->unknown10 = id;
  x->unknown00 = value;
  x->unknown08 = length;
}

template <typename T, typename ALLOC, int NO_VALUE, int NO_PATH, bool FLAG>
template <typename U>
void DevFileDictionary<T, ALLOC, NO_VALUE, NO_PATH, FLAG>::reallocArray(U *&array, int size, int from) {
  array = static_cast<U *>(unknown48->reallocate(array, sizeof(U) * size));
  // Name from the game symbol of this static (_ZZN2ml17DevFileDictionary...12reallocArray...E2T0): the value the grown part of the array is filled with.
  static const U T0 = U();
  // `*p++ = T0` puts the pointer increment before the last store of the unrolled fill loop, so the induction variable and its next value cannot share a register
  // (the game's `add x9, x10, #8 ... mov x10, x9`, 82 instructions for ninfo); with `++p` after the store they coalesce (79 instructions).
  for (U *p(array + from), *const end(array + size); p != end;) {
    *p++ = T0;
  }
}

} // namespace ml
