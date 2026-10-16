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

  UIStr();
  UIStr(const UIStr &other);
  UIStr(u8 *data, u32 id);
  UIStr(const char *string, bool allocate);
  ~UIStr();
  void init();
  void copy(const UIStr &other);
  void setupMstxt(u8 *data, u32 id);
  void setupAllocated(const char *string);
  void setupReference(const char *string);
  void release();
  const char *c_str() const;
  bool isValid() const;
  u32 size() const;
  void allocate(const char *string);
  void deepcopy(const UIStr &other);
  bool compare(const UIStr &other);
  u16 getStyle() const;
  void *getMsgFP() const;
  u32 getMsgID() const;

  union {
    struct {
      u32 fileId;
      u32 msgId;
    } mstxt;
    const char *reference;
    char *allocated;
  };
  u32 allocatedSize;
  u8 _0c[0x10 - 0x0c];
  u16 type;
};

static_assert(offsetof(UIStr, allocatedSize) == 0x08, "");
static_assert(offsetof(UIStr, type) == 0x10, "");
static_assert(sizeof(UIStr) == 0x18, "");

} // namespace ui
