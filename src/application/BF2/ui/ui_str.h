#pragma once
#include <stddef.h>

#include "types.h"

namespace ui {

class UIStr {
public:
  enum Type {
    TYPE_NONE = 0,
    TYPE_MSTXT = 1,
    TYPE_REFERENCE = 2,
    TYPE_ALLOCATED = 3,
  };

  struct Mstxt {
    u32 unknown00; // Inferred role: file id; original member name unknown.
    u32 unknown04; // Inferred role: msg id; original member name unknown.
  };

  UIStr();
  void init();
  UIStr(const UIStr &other);
  void copy(const UIStr &other);
  UIStr(u8 *data, u32 id);
  void setupMstxt(u8 *data, u32 id);
  UIStr(const char *string, bool allocate);
  void setupAllocated(const char *string);
  void setupReference(const char *string);
  ~UIStr();
  void release();
  const char *c_str() const;
  bool isValid() const;
  u32 size() const;
  void allocate(const char *string);
  void deepcopy(const UIStr &other);
  bool compare(const UIStr &other);
  u16 getStyle() const;
  u8 *getMsgFP() const;
  u32 getMsgID() const;

  union {
    Mstxt mstxt;
    const char *reference;
    char *allocated;
  };
  u32 unknown08; // Inferred role: allocated size; original member name unknown.
  u8 _0c[0x10 - 0x0c];
  u16 unknown10; // Inferred role: type; original member name unknown.
  u16 unknown12; // Inferred role: option; original member name unknown.
};

static_assert(offsetof(UIStr, unknown08) == 0x08, "");
static_assert(offsetof(UIStr, unknown10) == 0x10, "");
static_assert(offsetof(UIStr, unknown12) == 0x12, "");
static_assert(sizeof(UIStr) == 0x18, "");

} // namespace ui
