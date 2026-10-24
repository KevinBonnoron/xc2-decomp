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

  mm::mtl::IAllocator *unknown20;                  // Inferred role: allocator; original member name unknown.
  char *unknown28;                                 // Inferred role: stock buffer; original member name unknown.
  mm::mtl::FixedVector<UITagConv *, 16> unknown30; // Inferred role: converters; original member name unknown.
  u16 unknownb8;                                   // Inferred role: option; original member name unknown.
  u16 unknownba;                                   // Inferred role: mode; original member name unknown.
  const char *unknownc0;                           // Inferred role: tag; original member name unknown.
  const char *unknownc8;                           // Inferred role: param; original member name unknown.
  mm::mtl::FixStr<128> unknownd0;                  // Inferred role: result; original member name unknown.
};

static_assert(offsetof(UITagParser, unknown20) == 0x20, "");
static_assert(offsetof(UITagParser, unknown28) == 0x28, "");
static_assert(offsetof(UITagParser, unknown30) == 0x30, "");
static_assert(offsetof(UITagParser, unknownb8) == 0xb8, "");
static_assert(offsetof(UITagParser, unknownba) == 0xba, "");
static_assert(offsetof(UITagParser, unknownc0) == 0xc0, "");
static_assert(offsetof(UITagParser, unknownc8) == 0xc8, "");
static_assert(offsetof(UITagParser, unknownd0) == 0xd0, "");
static_assert(sizeof(UITagParser) == 0x158, "");

} // namespace ui
