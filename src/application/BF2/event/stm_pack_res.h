#pragma once
#include "types.h"
#include <stddef.h>

namespace event {

class StmPackRes {
public:
  enum {
    FLAG_LOADING = 1 << 0,
    FLAG_FREE = 1 << 1,
  };

  StmPackRes();
  StmPackRes(void *buffer, size_t size, size_t dataOfs, size_t firstFile, size_t lastFile, size_t firstPage, size_t lastPage, int prio, int cut, size_t stream);
  bool isLoading() const;
  void loadCompleate();
  void *getFileAdr(size_t dataOfs) const;

  s32 unknown00;    // Inferred role: ref count; original member name unknown.
  u32 unknown04;    // Inferred role: flags; original member name unknown.
  s32 unknown08;    // Inferred role: delay; original member name unknown.
  void *unknown10;  // Inferred role: buffer; original member name unknown.
  size_t unknown18; // Inferred role: size; original member name unknown.
  size_t unknown20; // Inferred role: data ofs; original member name unknown.
  size_t unknown28; // Inferred role: first file; original member name unknown.
  size_t unknown30; // Inferred role: last file; original member name unknown.
  size_t unknown38; // Inferred role: first page; original member name unknown.
  size_t unknown40; // Inferred role: last page; original member name unknown.
  int unknown48;    // Inferred role: prio; original member name unknown.
  int unknown4c;    // Inferred role: cut; original member name unknown.
  size_t unknown50; // Inferred role: stream; original member name unknown.
};

static_assert(sizeof(StmPackRes) == 0x58, "");

} // namespace event
