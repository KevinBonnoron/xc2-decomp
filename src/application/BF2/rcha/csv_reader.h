#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

// Declared from the symbols _ZN9CsvReaderC1Ev (0x7100695684), _ZN9CsvReaderD1Ev (0x7100695698),
// _ZN9CsvReader4loadEN3mtl12ALLOC_HANDLEEPKc (0x7100695704) and _ZN9CsvReader5parseEPhi (0x71006957cc). The file is
// read into unknown00 and split in place: every cell of every line is a pointer into it, at most 16 cells in a line
// and 256 lines (the sizes of the vectors used by getMaxCol and getStr at 0x7100695ea4 and 0x7100695f08).
class CsvReader {
public:
  CsvReader();
  ~CsvReader();
  bool load(mtl::ALLOC_HANDLE handle, const char *path);
  void parse(u8 *data, int size);
  int getMaxLine() const;
  int getMaxCol(int line) const;
  bool getLine(u8 *data, int &position);
  u8 *getStr(int line, int col);

  u8 *unknown00; // Inferred role: file data; original member name unknown.
  int unknown08; // Inferred role: file size; original member name unknown.
  u8 _0c[0x10 - 0x0c];
  mm::mtl::FixedVector<mm::mtl::FixedVector<u8 *, 16>, 256> unknown10; // Inferred role: cells of each line; original member name unknown.
};

static_assert(offsetof(CsvReader, unknown10) == 0x10, "");
static_assert(sizeof(CsvReader) == 0x8818, "");
