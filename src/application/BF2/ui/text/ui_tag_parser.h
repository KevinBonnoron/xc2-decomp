#pragma once
#include <stddef.h>

#include "layer/layer_tag.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace ui {

class UITagConv;

class UITagParser : public layer::LayerTagStr, public mm::mtl::PtrSingleton<UITagParser> {
public:
  enum ParseMode {
    PARSE_MODE_CONVERT = 0,
    PARSE_MODE_PARAM = 1,
    PARSE_MODE_TAG = 2,
  };

  UITagParser(mm::mtl::IAllocator *allocator);
  virtual ~UITagParser();
  void releaseConverter();
  void registConverter(UITagConv *converter);
  void parse(const char *text);
  const char *getResult();
  const char *parseTagParam(const char *text, const char *tag, const char *param);
  bool parseTag(const char *text, const char *tag);
  virtual bool callTagStart(const char *tag, const layer::LayerTagTbl *table, u32 count);
  virtual bool callTagEnd(const char *tag);

  mm::mtl::IAllocator *allocator;
  char *stockBuffer;
  mm::mtl::FixedVector<UITagConv *, 16> converters;
  u16 option;
  u16 mode;
  const char *tag;
  const char *param;
  mm::mtl::FixStr<128> result;
};

static_assert(offsetof(UITagParser, allocator) == 0x20, "");
static_assert(offsetof(UITagParser, stockBuffer) == 0x28, "");
static_assert(offsetof(UITagParser, converters) == 0x30, "");
static_assert(offsetof(UITagParser, option) == 0xb8, "");
static_assert(offsetof(UITagParser, mode) == 0xba, "");
static_assert(offsetof(UITagParser, tag) == 0xc0, "");
static_assert(offsetof(UITagParser, param) == 0xc8, "");
static_assert(offsetof(UITagParser, result) == 0xd0, "");
static_assert(sizeof(UITagParser) == 0x158, "");

} // namespace ui
