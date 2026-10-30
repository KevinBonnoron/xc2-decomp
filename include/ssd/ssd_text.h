#pragma once
#include <stddef.h>

#include "ssd/ssd_hash.h"
#include "types.h"

namespace ssd {

enum TextEncodeType : u8 {
  TEXT_ENCODE_NONE = 0,
  TEXT_ENCODE_UTF8 = 2,
  TEXT_ENCODE_UTF16 = 3,
};

struct MemoryBlock;

class TextRef {
public:
  TextRef() : unknown10(nullptr), unknown18(TEXT_ENCODE_UTF16) {}
  TextRef(const TextRef &text);
  TextRef(const char *text);
  TextRef(const char16_t *text);
  void Clear();
  void InitImpl(const char *text);
  void InitImpl(const char16_t *text);
  void GetText(MemoryBlock *block, TextEncodeType type) const;
  void GetText(void *buffer, unsigned long size, TextEncodeType type) const;
  virtual void Set(const TextRef &text);
  virtual void Set(const char *text);
  virtual void Set(const char16_t *text);

  // Inferred role: length of a text in characters; original name unknown.
  template <typename T> static unsigned long unknown002(const T *text) {
    const T *end = text;
    while (*end != 0) {
      end++;
    }
    return end - text;
  }

  // Inferred role: copy a text into a buffer of size characters, truncating it; original name unknown.
  template <typename T> static void unknown003(T *buffer, const T *text, unsigned long size) {
    T *destination = buffer;
    unsigned long limit = size - 1;
    while (*text != 0 && static_cast<u32>(destination - buffer) < limit) {
      *destination = *text;
      destination++;
      text++;
    }
    *destination = 0;
  }

  static const char16_t *EmptyText;

  Hash unknown08; // Inferred role: hash; original member name unknown.
  union {
    const void *unknown10;           // Inferred role: text; original member name unknown.
    const char *unknown10_utf8;      // Inferred role: text when unknown18 is TEXT_ENCODE_UTF8; original member name unknown.
    const char16_t *unknown10_utf16; // Inferred role: text when unknown18 is TEXT_ENCODE_UTF16; original member name unknown.
  };
  TextEncodeType unknown18; // Inferred role: encode type; original member name unknown.
};

static_assert(offsetof(TextRef, unknown08) == 0x8, "");
static_assert(offsetof(TextRef, unknown18) == 0x18, "");

void SjisToUTF16(const char *source, char16_t *destination, unsigned long size);
void Utf8ToUTF16(const char *source, char16_t *destination, unsigned long size);
void Utf16ToSjis(const char16_t *source, char *destination, unsigned long size);
void Utf16ToUTF8(const char16_t *source, char *destination, unsigned long size);
char16_t *SjisToUTF16(const char *source, unsigned long *length);

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

bool Utf8ToUTF16(const char *source, MemoryBlock *block);
bool Utf16ToUTF8(const char16_t *source, MemoryBlock *block);

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
