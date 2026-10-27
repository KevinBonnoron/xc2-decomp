#include "gf/menu/gf_credit_reader.h"

namespace gf {

namespace {

// Inferred role: header of the credit data; original type name unknown.
struct unknown001 {
  u32 unknown00; // Inferred role: magic; original member name unknown.
  int unknown04; // Inferred role: row count; original member name unknown.
  int unknown08; // Inferred role: offset of the row table; original member name unknown.
  int unknown0c; // Inferred role: offset of the string table; original member name unknown.
};

// Inferred role: column of a row of the credit data; original type name unknown.
struct unknown002 {
  int unknown00; // Inferred role: column is used; original member name unknown.
  u32 unknown04; // Inferred role: first value; original member name unknown.
  u32 unknown08; // Inferred role: second value; original member name unknown.
  int unknown0c; // Inferred role: offset of the text, -1 for none; original member name unknown.
};

// Inferred role: row of the credit data; original type name unknown.
struct unknown003 {
  u32 unknown00;           // Inferred role: first value; original member name unknown.
  int unknown04;           // Inferred role: row is a blank line; original member name unknown.
  u32 unknown08;           // Inferred role: second value; original member name unknown.
  u32 unknown0c;           // Inferred role: unused; original member name unknown.
  unknown002 unknown10[3]; // Inferred role: columns; original member name unknown.
};

static_assert(sizeof(unknown003) == 0x40, "");

} // namespace

CreditReader::CreditReader() : unknown08(nullptr), unknown10(0), unknown18(nullptr), unknown20(nullptr) {}

CreditReader::~CreditReader() {}

void CreditReader::bind(void *data, int size) {
  unknown08 = data;
  const unknown001 *header = static_cast<const unknown001 *>(data);
  if (header->unknown00 == 0x545243) {
    unknown10 = header->unknown04;
    const u8 *base = static_cast<const u8 *>(data);
    const u8 *rows = base + header->unknown08;
    const u8 *strings = base + header->unknown0c;
    unknown18 = rows;
    unknown20 = reinterpret_cast<const char *>(strings);
  } else {
    unknown08 = nullptr;
    unknown10 = 0;
  }
}

void CreditReader::unbind() {
  unknown08 = nullptr;
  unknown10 = 0;
}

int CreditReader::getRowCount() { return unknown10; }

bool CreditReader::getRow(int index, Row &row) {
  if (unknown10 <= 0 || unknown10 <= index) {
    return false;
  }
  if (unknown18 == nullptr) {
    return false;
  }
  if (unknown20 == nullptr) {
    return false;
  }

  const unknown003 &source = static_cast<const unknown003 *>(unknown18)[index];
  row.unknown00 = source.unknown00;
  row.unknown08 = source.unknown08;
  row.unknown04 = source.unknown04 > 0;
  if (source.unknown04 != 0) {
    row.unknown10.unknown10 = nullptr;
    row.unknown28.unknown10 = nullptr;
    row.unknown40.unknown10 = nullptr;
    return true;
  }

  Column *columns[3] = {&row.unknown10, &row.unknown28, &row.unknown40};
  for (int i = 0; i < 3; i++) {
    const unknown002 &column = source.unknown10[i];
    columns[i]->unknown00 = column.unknown00 > 0;
    columns[i]->unknown04 = column.unknown04;
    columns[i]->unknown08 = column.unknown08;
    const char *text = nullptr;
    if (column.unknown0c != -1) {
      text = unknown20 + column.unknown0c;
    }
    columns[i]->unknown10 = text;
  }
  return true;
}

} // namespace gf
