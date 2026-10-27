#pragma once
#include <stddef.h>

#include "types.h"

namespace gf {

class CreditReader {
public:
  struct Column {
    bool unknown00;        // Inferred role: column is used; original member name unknown.
    u32 unknown04;         // Inferred role: first value of the column; original member name unknown.
    u32 unknown08;         // Inferred role: second value of the column; original member name unknown.
    const char *unknown10; // Inferred role: text; original member name unknown.
  };

  struct Row {
    u32 unknown00;    // Inferred role: first value of the row; original member name unknown.
    bool unknown04;   // Inferred role: row is a blank line; original member name unknown.
    u32 unknown08;    // Inferred role: second value of the row; original member name unknown.
    Column unknown10; // Inferred role: first column; original member name unknown.
    Column unknown28; // Inferred role: second column; original member name unknown.
    Column unknown40; // Inferred role: third column; original member name unknown.
  };

  CreditReader();
  virtual ~CreditReader();
  void bind(void *data, int size);
  void unbind();
  int getRowCount();
  bool getRow(int index, Row &row);

  void *unknown08;       // Inferred role: bound data; original member name unknown.
  int unknown10;         // Inferred role: row count; original member name unknown.
  const void *unknown18; // Inferred role: row table; original member name unknown.
  const char *unknown20; // Inferred role: string table; original member name unknown.
};

static_assert(offsetof(CreditReader::Column, unknown10) == 0x10, "");
static_assert(sizeof(CreditReader::Column) == 0x18, "");
static_assert(offsetof(CreditReader::Row, unknown10) == 0x10, "");
static_assert(offsetof(CreditReader::Row, unknown28) == 0x28, "");
static_assert(offsetof(CreditReader::Row, unknown40) == 0x40, "");
static_assert(sizeof(CreditReader::Row) == 0x58, "");
static_assert(offsetof(CreditReader, unknown08) == 0x08, "");
static_assert(offsetof(CreditReader, unknown10) == 0x10, "");
static_assert(offsetof(CreditReader, unknown18) == 0x18, "");
static_assert(offsetof(CreditReader, unknown20) == 0x20, "");
static_assert(sizeof(CreditReader) == 0x28, "");

} // namespace gf
