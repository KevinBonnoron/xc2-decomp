#pragma once
#include <stddef.h>

#include "mm_mtl/fixstr.h"
#include "types.h"

namespace layer {

struct LayerTagTbl;

class LayerStrInfo {
public:
  LayerStrInfo();

  u8 _00[0x10 - 0x00];
  mm::mtl::FixStr<16> m_name;
};

static_assert(offsetof(LayerStrInfo, m_name) == 0x10, "");

class LayerTag {
public:
  void calcParseString(const u8 *string);
  void calcUTF8ParseString(const u8 *string);
  void calcParseString(const wchar_t *string);
  void calcUTF16ParseString(const wchar_t *string);
  u32 calcStringLength(const u8 *string);
  u32 calcStringLength(const wchar_t *string);
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
  ~LayerTagStr() override {}
  void setStockTbl(char *table, int size);
  void stockString(const char *string);
  void stockString(const wchar_t *string);
  void beginParseString() override;
  void endParseString() override;
  void parseNotTag(const u8 *string, u32 &index) override;
  void parseNotTag(const wchar_t *string, u32 &index) override;
  void callTagNoUse(const u8 *tag) override;

  char *m_stockTbl;
  int m_stockSize;
  int m_stockNum;
};

static_assert(offsetof(LayerTagStr, m_stockTbl) == 0x8, "");
static_assert(offsetof(LayerTagStr, m_stockNum) == 0x14, "");

} // namespace layer
