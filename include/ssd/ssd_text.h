#pragma once
#include <stddef.h>

#include "ssd/ssd_hash.h"
#include "ssd/ssd_result.h"
#include "types.h"

namespace ssd {

enum TextEncodeType : u8 {
  TEXT_ENCODE_NONE = 0,
  TEXT_ENCODE_UTF8 = 2,
  TEXT_ENCODE_UTF16 = 3,
};

class TextRef {
public:
  TextRef() : unknown10(nullptr), unknown18(TEXT_ENCODE_UTF16) {}
  TextRef(const TextRef &text);
  TextRef(const char *text);
  TextRef(const char16_t *text);
  void Clear();
  void InitImpl(const char *text);
  void InitImpl(const char16_t *text);
  virtual void Set(const TextRef &text);
  virtual void Set(const char *text);
  virtual void Set(const char16_t *text);

  static const char16_t *EmptyText;

  Hash unknown08;           // Inferred role: hash; original member name unknown.
  const void *unknown10;    // Inferred role: text; original member name unknown.
  TextEncodeType unknown18; // Inferred role: encode type; original member name unknown.
};

static_assert(offsetof(TextRef, unknown08) == 0x8, "");
static_assert(offsetof(TextRef, unknown18) == 0x18, "");

Result Utf8ToUTF16(const char *source, char16_t *destination, unsigned long size);

class TextFixedBase : public TextRef {
public:
  void Set(const TextRef &text) override;
  void Set(const char *text) override;
  void Set(const char16_t *text) override;

  // Inferred role: writable text buffer owned by the object; original name unknown.
  char16_t *unknown001() const { return static_cast<char16_t *>(const_cast<void *>(unknown10)); }

  unsigned long unknown20; // Inferred role: capacity in characters; original member name unknown.
};

static_assert(offsetof(TextFixedBase, unknown20) == 0x20, "");

template <int N> class TextFixed : public TextFixedBase {
public:
  char16_t unknown28[N]; // Inferred role: text buffer; original member name unknown.
};

struct MemoryBlock {
  void *unknown00;         // Inferred role: block address; original member name unknown.
  unsigned long unknown08; // Inferred role: block size; original member name unknown.
};

static_assert(sizeof(MemoryBlock) == 0x10, "");

Result Utf8ToUTF16(const char *source, MemoryBlock *block);

class String : public TextRef {
public:
  String();
  virtual ~String();
  void FreeImpl();
  void Set(const TextRef &text) override;
  void Set(const char *text) override;
  void Set(const char16_t *text) override;

  MemoryBlock unknown20; // Inferred role: text buffer; original member name unknown.
};

static_assert(offsetof(String, unknown20) == 0x20, "");
static_assert(sizeof(String) == 0x30, "");

} // namespace ssd
