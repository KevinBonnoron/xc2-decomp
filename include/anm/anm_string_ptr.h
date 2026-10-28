#pragma once
#include <string.h>

namespace anm {

// Wrapper of a C string compared by content; original member name unknown.
class StringPtr {
public:
  StringPtr() : unknown00(nullptr) {}
  StringPtr(const char *string) : unknown00(string) {}

  bool operator<(const StringPtr &rhs) const { return strcmp(unknown00, rhs.unknown00) < 0; }

  const char *unknown00; // Inferred role: string; original member name unknown.
};

inline bool operator==(const StringPtr &lhs, const StringPtr &rhs) { return strcmp(lhs.unknown00, rhs.unknown00) == 0; }

} // namespace anm
