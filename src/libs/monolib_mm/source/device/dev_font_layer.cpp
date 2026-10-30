#include "ml/dev_font_layer.h"

#include <string.h>

#include "ml/dev_graph.h"
#include "ml/reslist.h"

namespace ml {

void DevFontLayer::fontColor(const mm::Col4 &color, bool isFlush) {
  if (unknown1a8 != nullptr) {
    LAYER_COLOR *layer = static_cast<LAYER_COLOR *>(allocLayer(sizeof(LAYER_COLOR)));
    layer->unknown00 = 1;
    layer->unknown04 = color;
    unknown1a8[unknown1b0++] = layer;
    unknown1dc = color;
  }
}

void DevFontLayer::fontBack(const mm::Col4 &color) {
  if (unknown1a8 != nullptr) {
    LAYER_COLOR *layer = static_cast<LAYER_COLOR *>(allocLayer(sizeof(LAYER_COLOR)));
    layer->unknown00 = 2;
    layer->unknown04 = color;
    unknown1a8[unknown1b0++] = layer;
    unknown1cc = color;
  }
}

void DevFontLayer::fontScale(f32 x, f32 y) {
  if (unknown1a8 != nullptr) {
    unknown001 *layer = static_cast<unknown001 *>(allocLayer(sizeof(unknown001)));
    layer->unknown00 = 3;
    layer->unknown04 = x;
    layer->unknown08 = y;
    unknown1a8[unknown1b0++] = layer;
    unknown1b4 = x;
    unknown1b8 = y;
  }
}

void DevFontLayer::fontStyle(FONT_STYLE style) {
  if (unknown1a8 != nullptr) {
    unknown002 *layer = static_cast<unknown002 *>(allocLayer(sizeof(unknown002)));
    layer->unknown00 = 5;
    layer->unknown04 = style;
    unknown1a8[unknown1b0++] = layer;
    unknown1bc = style;
  }
}

void DevFontLayer::fontShadow(bool isShadow) {
  if (unknown1a8 != nullptr) {
    unknown002 *layer = static_cast<unknown002 *>(allocLayer(sizeof(unknown002)));
    layer->unknown00 = 6;
    layer->unknown04 = isShadow;
    unknown1a8[unknown1b0++] = layer;
  }
}

void DevFontLayer::fontZ(u32 z) {
  if (unknown1a8 != nullptr) {
    unknown002 *layer = static_cast<unknown002 *>(allocLayer(sizeof(unknown002)));
    layer->unknown00 = 4;
    layer->unknown04 = z;
    unknown1a8[unknown1b0++] = layer;
  }
}

void DevFontLayer::sync() {
  clear();
  if (DevGraph::get() != nullptr) {
    unknown1a8 = static_cast<const LAYER_QUE **>(DevGraph::cmdAllocBuf(unknown1f0 * sizeof(LAYER_QUE *), 4));
  }
}

DevFontLayer::DevFontLayer(const char *name, WorkObj *parent)
    : WorkObj(name, parent, 0), unknown1a8(nullptr), unknown1b4(1.0f), unknown1b8(1.0f), unknown1bc(FONT_STYLE_NORMAL), unknown1c0(nullptr), unknown1c8(false), unknown1ec(false), unknown1f0(0x400),
      unknown1f4(0) {
  sync();
}

void *DevFontLayer::allocLayer(u32 size) {
  if (unknown1a8 != nullptr) {
    return DevGraph::cmdAllocBuf(size, 4);
  }
  return nullptr;
}

void *DevFontLayer::writeLayer(const void *data, u32 size) {
  void *layer = allocLayer(size);
  memcpy(layer, data, size);
  return layer;
}

void DevFontLayer::writeString(const void *data, u32 size) {
  char *string = static_cast<char *>(allocLayer(size + 1));
  memcpy(string, data, size);
  string[size] = '\0';
}

u32 DevFontLayer::getMem1Size() { return 0x10000; }

void DevFontLayer::clear() {
  unknown1cc = mm::Col4(0.0f, 0.0f, 0.0f, 0.0f);
  unknown1dc = mm::Col4(1.0f, 1.0f, 1.0f, 1.0f);
  unknown1b0 = 0;
}

void DevFontLayer::flushColor(const LAYER_COLOR *color) { unknown1dc = color->unknown04; }

void DevFontLayer::flushFont(const LAYER_FONT *font) {
  if (unknown1a8 != nullptr) {
    DevGraph::fontDraw(font->unknown04, font->unknown06, unknown1b4, unknown1b8, font->unknown08, &unknown1dc, &unknown1cc, unknown1c8);
  }
}

void DevFontLayer::fontSetMaxQue(u32 maxQue) { unknown1f0 = maxQue; }

void DevFontLayer::wkUpdate() {
  if (unknown1ec) {
    wkSetEvent(static_cast<EVT>(0));
  }
}

void DevFontLayer::wkTail() { sync(); }

bool DevFontLayer::wkStandbyLogout() {
  if (unknown60.size() == 0 && unknown1ec) {
    return WorkObj::wkStandbyLogout();
  }
  return false;
}

} // namespace ml
