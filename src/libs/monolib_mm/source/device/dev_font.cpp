#include "ml/dev_font.h"

#include "ml/dev_font_layer.h"
#include "ml/work_util.h"

namespace ml {
enum FONT_STYLE : int;
class WorkObj;

DevFont::DevFont(const char *name, WorkObj *parent) : DevBase(name, parent, 0x200) {}

FontLayer::FontLayer() : unknown08(DevFont::createLayer(this)) {}

bool DevFont::isInitialized() {
  DevFont *font = get();
  if (font == nullptr) {
    return true;
  }

  if (font->wkIsWaitException()) {
    return false;
  }

  return font->wkIsActive();
}

DevFontLayer *DevFont::createLayer(const FontLayer *layer) {
  DevFont *font = get();
  if (font == nullptr) {
    return nullptr;
  }
  DevFontLayer *fontLayer = WorkUtil::createWork<DevFontLayer>("DevFontLayer", font, false);
  fontLayer->unknown1c0 = layer;
  return fontLayer;
}

IDevFontInfo *DevFont::getFont(FONT_STYLE style) {
  if (get() != nullptr) {
    for (reslist<IDevFontInfo *>::Node *node = get()->unknown1c8.begin(); node != get()->unknown1c8.end(); node = node->getNext()) {
      if (!node->value->unknown48() && node->value->unknown10() == style) {
        return node->value;
      }
    }
    for (reslist<IDevFontInfo *>::Node *node = get()->unknown1c8.begin(); node != get()->unknown1c8.end(); node = node->getNext()) {
      if (!node->value->unknown48()) {
        return node->value;
      }
    }
  }
  return nullptr;
}

void DevFont::wkTail() {
  for (reslist<WorkObj *>::Node *node = wkGetChild()->begin(); node != wkGetChild()->end(); node = node->getNext()) {
    static_cast<DevFontLayer *>(node->value)->sync();
  }
}

bool DevFont::createFont(FONT_STYLE style, void *data) { return get() != nullptr; }

void FontLayer::fontStyle(FONT_STYLE style) { DevFont::fontLayerStyle(this, style); }

void FontLayer::fontZ(u32 z) { DevFont::fontLayerZ(this, z); }

} // namespace ml

template mm::mtl::PtrSingleton<ml::DevFont>::~PtrSingleton();
