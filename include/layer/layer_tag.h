#pragma once
#include <stddef.h>

#include "mm_mtl/fixstr.h"
#include "types.h"

namespace mm {
struct Col3;
struct Col4;
} // namespace mm

namespace layer {

struct LayerTagTbl {
  const char *name;
  const char *value;
};

class LayerStrInfo {
public:
  union unknown001 {
    f32 m_float;
    s32 m_s32;
    u32 m_u32;
    f32 m_col3[3];
    f32 m_col4[4];
  };

  LayerStrInfo();
  void setCol4(const char *name, const mm::Col4 &color);
  void setCol3(const char *name, const mm::Col3 &color);
  void setFloat(const char *name, f32 value);
  void setU32(const char *name, u32 value);
  void setS32(const char *name, s32 value);

  unknown001 unknown00;          // Inferred role: value; original member name unknown.
  mm::mtl::FixStr<16> unknown10; // Inferred role: name; original member name unknown.
};

static_assert(offsetof(LayerStrInfo, unknown10) == 0x10, "");

class LayerTag {
public:
  void calcParseString(const u8 *string);
  void calcUTF8ParseString(const u8 *string);
  void calcParseString(const wchar_t *string);
  void calcUTF16ParseString(const wchar_t *string);
  u32 calcStringLength(const u8 *string);
  u32 calcStringLength(const wchar_t *string);
  void changeUtf16ToUtf8(u8 *result, u32 &length, u16 code);
  void changeUtf8ToUtf16(u16 &result, const u8 *string, u32 &length);
  virtual ~LayerTag() {}
  virtual void beginParseString() = 0;
  virtual void endParseString() {}
  virtual void parseNotTag(const u8 *string, u32 &index) = 0;
  virtual void parseNotTag(const wchar_t *string, u32 &index) = 0;
  virtual bool callTagStart(const char *tag, const LayerTagTbl *table, u32 index) { return false; }
  virtual bool callTagEnd(const char *tag) { return false; }
  virtual void callTagNoUse(const u8 *tag) {}
};

class LayerTagStr : public LayerTag {
public:
  LayerTagStr();
  ~LayerTagStr() override;
  void setStockTbl(char *table, int size);
  void stockString(const char *string);
  void stockString(const wchar_t *string);
  void beginParseString() override;
  void endParseString() override;
  void parseNotTag(const u8 *string, u32 &index) override;
  void parseNotTag(const wchar_t *string, u32 &index) override;
  void callTagNoUse(const u8 *tag) override;

  char *m_result;
  int unknown10; // Inferred role: stock size; original member name unknown.
  int unknown14; // Inferred role: stock num; original member name unknown.
};

static_assert(offsetof(LayerTagStr, m_result) == 0x8, "");
static_assert(offsetof(LayerTagStr, unknown14) == 0x14, "");

} // namespace layer
