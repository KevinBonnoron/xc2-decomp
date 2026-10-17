#include "ui/text/ui_tag_parser.h"

#include <string.h>

#include "mm_mtl/allocator.h"
#include "mtl/mem_manager.h"
#include "ui/text/ui_tag_conv.h"

namespace ui {

UITagParser::UITagParser(mm::mtl::IAllocator *allocator)
    : allocator(allocator), stockBuffer(nullptr), option(0), mode(PARSE_MODE_CONVERT), tag(nullptr), param(nullptr) {
  stockBuffer = static_cast<char *>(allocator->allocate(0x400, 4));
  setStockTbl(stockBuffer, 0x400);
}

UITagParser::~UITagParser() {
  releaseConverter();
  if (stockBuffer != nullptr) {
    mtl::MemManager::deallocate(stockBuffer, 0, false);
    stockBuffer = nullptr;
  }
}

void UITagParser::releaseConverter() {
  for (UITagConv **it = converters.begin(); it != converters.end(); ++it) {
    if (*it != nullptr) {
      delete *it;
      *it = nullptr;
    }
  }
  converters.clear();
}

void UITagParser::registConverter(UITagConv *converter) {
  if (converters.size() >= converters.capacity()) {
    return;
  }

  for (UITagConv **it = converters.begin(); it != converters.end(); ++it) {
    if (strcmp((*it)->getTagName(), converter->getTagName()) == 0) {
      return;
    }
  }
  converters.push_back(converter);
}

void UITagParser::parse(const char *text) {
  if (text != nullptr) {
    mode = PARSE_MODE_CONVERT;
    calcParseString(reinterpret_cast<const u8 *>(text));
  }
}

const char *UITagParser::getResult() { return m_stockTbl; }

const char *UITagParser::parseTagParam(const char *text, const char *tag, const char *param) {
  if (text == nullptr || tag == nullptr || param == nullptr) {
    return nullptr;
  }

  mode = PARSE_MODE_PARAM;
  this->tag = tag;
  this->param = param;
  result.clear();
  calcParseString(reinterpret_cast<const u8 *>(text));
  return !result.empty() ? result.c_str() : nullptr;
}

bool UITagParser::parseTag(const char *text, const char *tag) {
  bool found = false;
  if (text != nullptr && tag != nullptr) {
    this->tag = tag;
    mode = PARSE_MODE_TAG;
    result.clear();
    calcParseString(reinterpret_cast<const u8 *>(text));
    found = !result.empty();
  }
  return found;
}

bool UITagParser::callTagEnd(const char *tag) {
  for (UITagConv **it = converters.begin(); it != converters.end(); ++it) {
    if (strcmp((*it)->getTagName(), tag) == 0) {
      const char *text = (*it)->convEnd();
      if (text == nullptr) {
        return false;
      }
      stockString(text);
      return true;
    }
  }
  return false;
}

} // namespace ui
