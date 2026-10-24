#include "ui/text/ui_tag_parser.h"

#include <string.h>

#include "mm_mtl/allocator.h"
#include "mtl/mem_manager.h"
#include "ui/text/ui_tag_conv.h"

namespace ui {

UITagParser::UITagParser(mm::mtl::IAllocator *allocator) : unknown20(allocator), unknown28(nullptr), unknownb8(0), unknownba(PARSE_MODE_CONVERT), unknownc0(nullptr), unknownc8(nullptr) {
  unknown28 = static_cast<char *>(allocator->allocate(0x400, 4));
  setStockTbl(unknown28, 0x400);
}

UITagParser::~UITagParser() {
  releaseConverter();
  if (unknown28 != nullptr) {
    mtl::MemManager::deallocate(unknown28, 0, false);
    unknown28 = nullptr;
  }
}

void UITagParser::releaseConverter() {
  for (UITagConv **it = unknown30.begin(); it != unknown30.end(); ++it) {
    if (*it != nullptr) {
      delete *it;
      *it = nullptr;
    }
  }
  unknown30.clear();
}

void UITagParser::registConverter(UITagConv *converter) {
  if (unknown30.size() >= unknown30.capacity()) {
    return;
  }

  for (UITagConv **it = unknown30.begin(); it != unknown30.end(); ++it) {
    if (strcmp((*it)->getTagName(), converter->getTagName()) == 0) {
      return;
    }
  }
  unknown30.push_back(converter);
}

void UITagParser::parse(const char *text) {
  if (text != nullptr) {
    unknownba = PARSE_MODE_CONVERT;
    calcParseString(reinterpret_cast<const u8 *>(text));
  }
}

const char *UITagParser::getResult() { return m_stockTbl; }

const char *UITagParser::parseTagParam(const char *text, const char *tag, const char *param) {
  if (text == nullptr || tag == nullptr || param == nullptr) {
    return nullptr;
  }

  unknownba = PARSE_MODE_PARAM;
  this->unknownc0 = tag;
  this->unknownc8 = param;
  unknownd0.clear();
  calcParseString(reinterpret_cast<const u8 *>(text));
  return !unknownd0.empty() ? unknownd0.c_str() : nullptr;
}

bool UITagParser::parseTag(const char *text, const char *tag) {
  bool found = false;
  if (text != nullptr && tag != nullptr) {
    this->unknownc0 = tag;
    unknownba = PARSE_MODE_TAG;
    unknownd0.clear();
    calcParseString(reinterpret_cast<const u8 *>(text));
    found = !unknownd0.empty();
  }
  return found;
}

bool UITagParser::callTagEnd(const char *tag) {
  for (UITagConv **it = unknown30.begin(); it != unknown30.end(); ++it) {
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
