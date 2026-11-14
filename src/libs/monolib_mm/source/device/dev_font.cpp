#include "ml/dev_font.h"

#include "ml/dev_font_layer.h"
#include "ml/dev_graph.h"
#include "ml/device.h"
#include "ml/lib_main.h"
#include "ml/reslist.h"
#include "ml/work_obj.h"
#include "ml/work_system.h"
#include "ml/work_util.h"
#include "mm_math/mm_col4.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace ml {

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

// Inferred role: the layer of a FontLayer through the DevFont singleton, null when there is no DevFont or no layer; original name
// unknown. Decision 2026-11-14 #31: the game has this lookup in releaseLayer and the nine fontLayer functions below; the helper with
// ten users matches, so no re-inlined body is needed.
static DevFontLayer *unknown009(const FontLayer *layer) {
  DevFont *font = DevFont::get();
  if (font == nullptr) {
    return nullptr;
  }
  return font->getFontLayer(layer);
}

bool DevFont::releaseLayer(const FontLayer *layer) {
  DevFontLayer *fontLayer = unknown009(layer);
  if (fontLayer != nullptr) {
    fontLayer->unknown1ec = true;
    return true;
  }
  return false;
}

DevFontLayer *DevFont::getFontLayer(const FontLayer *layer) {
  for (reslist<WorkObj *>::Node *node = wkGetChild()->begin(); node != wkGetChild()->end(); node = node->getNext()) {
    DevFontLayer *fontLayer = static_cast<DevFontLayer *>(node->value);
    if (fontLayer == nullptr) {
      continue;
    }
    if (fontLayer->unknown1c0 == layer) {
      return fontLayer;
    }
  }
  return layer->unknown08;
}

const DevFontLayer *DevFont::getFontLayer(const FontLayer *layer) const {
  for (reslist<WorkObj *>::Node *node = wkGetChild()->begin(); node != wkGetChild()->end(); node = node->getNext()) {
    const DevFontLayer *fontLayer = static_cast<const DevFontLayer *>(node->value);
    if (fontLayer == nullptr) {
      continue;
    }
    if (fontLayer->unknown1c0 == layer) {
      return fontLayer;
    }
  }
  return nullptr;
}

void DevFont::fontLayerSetMaxQue(const FontLayer *layer, u32 maxQue) {
  DevFont *font = get();
  if (font != nullptr) {
    font->getFontLayer(layer)->fontSetMaxQue(maxQue);
  }
}

void DevFont::fontLayer(const FontLayer *layer, int x, int y, const char *text) {
  DevFontLayer *fontLayer = unknown009(layer);
  if (fontLayer != nullptr) {
    fontLayer->font(x, y, text);
  }
}

u32 DevFont::fontLayerGetWidth(const FontLayer *layer, const char *text) {
  DevFontLayer *fontLayer = unknown009(layer);
  if (fontLayer != nullptr) {
    DevGraph *graph = DevGraph::get();
    if (graph != nullptr) {
      return graph->fontGetWidthSys(text, fontLayer->unknown1bc, fontLayer->unknown1b4);
    }
  }
  return 0;
}

u32 DevFont::fontLayerGetHeight(const FontLayer *layer) {
  DevFontLayer *fontLayer = unknown009(layer);
  if (fontLayer != nullptr) {
    DevGraph *graph = DevGraph::get();
    if (graph != nullptr) {
      return graph->fontGetHeightSys(fontLayer->unknown1bc, fontLayer->unknown1b8);
    }
  }
  return 0;
}

void DevFont::fontLayerColor(const FontLayer *layer, const mm::Col4 &color) {
  DevFontLayer *fontLayer = unknown009(layer);
  if (fontLayer != nullptr) {
    fontLayer->fontColor(color, true);
  }
}

void DevFont::fontLayerBack(const FontLayer *layer, const mm::Col4 &color) {
  DevFontLayer *fontLayer = unknown009(layer);
  if (fontLayer != nullptr) {
    fontLayer->fontBack(color);
  }
}

const mm::Col4 &DevFont::fontLayerGetColor(const FontLayer *layer) {
  DevFont *font = get();
  if (font != nullptr) {
    return font->getFontLayer(layer)->unknown1dc;
  }
  return mm::Col4::black;
}

void DevFont::fontLayerScale(const FontLayer *layer, f32 x, f32 y) {
  DevFontLayer *fontLayer = unknown009(layer);
  if (fontLayer != nullptr) {
    fontLayer->fontScale(x, y);
  }
}

void DevFont::fontLayerStyle(const FontLayer *layer, FONT_STYLE style) {
  DevFontLayer *fontLayer = unknown009(layer);
  if (fontLayer != nullptr) {
    fontLayer->fontStyle(style);
  }
}

void DevFont::fontLayerShadow(const FontLayer *layer, bool isShadow) {
  DevFontLayer *fontLayer = unknown009(layer);
  if (fontLayer != nullptr) {
    fontLayer->fontShadow(isShadow);
  }
}

void DevFont::fontLayerZ(const FontLayer *layer, u32 z) {
  DevFontLayer *fontLayer = unknown009(layer);
  if (fontLayer != nullptr) {
    fontLayer->fontZ(z);
  }
}

IDevFontInfo *DevFont::getFont(FONT_STYLE style) {
  if (get() != nullptr) {
    for (reslist<IDevFontInfo *>::iterator it = get()->unknown1c8.begin(); it != get()->unknown1c8.end(); ++it) {
      if (!(*it)->unknown48() && (*it)->unknown10() == style) {
        return *it;
      }
    }
    for (reslist<IDevFontInfo *>::iterator it = get()->unknown1c8.begin(); it != get()->unknown1c8.end(); ++it) {
      if (!(*it)->unknown48()) {
        return *it;
      }
    }
  }
  return nullptr;
}

bool DevFont::createFont(FONT_STYLE style, void *data) { return get() != nullptr; }

bool DevFont::isStyleValid(FONT_STYLE style) { return getFont(style) != nullptr; }

void DevFont::wkUpdate() {
  for (reslist<IDevFontInfo *>::iterator it = unknown1c8.begin(); it != unknown1c8.end(); ++it) {
    (*it)->unknown38();
  }
  for (reslist<IDevFontInfo *>::iterator it = unknown1c8.begin(); it != unknown1c8.end(); ++it) {
    if ((*it)->unknown50()) {
      if (*it != nullptr) {
        delete *it;
        *it = nullptr;
      }
      unknown1c8.erase(it);
      break;
    }
  }
}

bool DevFont::wkStandbyLogin() {
  if (dg::s_bIgnore) {
    return WorkObj::wkStandbyLogin();
  }
  if (!Device::isColdStartReady()) {
    return false;
  }
  DevGraph *graph = DevGraph::get();
  if (graph == nullptr || graph->wkIsWaitException() || !graph->wkIsActive()) {
    return false;
  }
  unknown1c8.create(8, unknown54);
  createFont();
  createLayer(this);
  return WorkObj::wkStandbyLogin();
}

bool DevFont::wkStandbyLogout() {
  releaseLayer(this);
  if (unknown60.size() != 0 || WorkSystem::get() != nullptr || LibMain::get() != nullptr) {
    return false;
  }
  releaseFont();
  for (reslist<IDevFontInfo *>::iterator it = unknown1c8.begin(); it != unknown1c8.end(); ++it) {
    if (*it != nullptr) {
      delete *it;
      *it = nullptr;
    }
  }
  unknown1c8.clear();
  return WorkObj::wkStandbyLogout();
}

void DevFont::wkTail() {
  for (reslist<WorkObj *>::Node *node = wkGetChild()->begin(); node != wkGetChild()->end(); node = node->getNext()) {
    static_cast<DevFontLayer *>(node->value)->sync();
  }
}

FontLayer::~FontLayer() { DevFont::releaseLayer(this); }

void FontLayer::fontSetMaxQue(u32 maxQue) { DevFont::fontLayerSetMaxQue(this, maxQue); }

u32 FontLayer::fontGef32gth(const char *text) const { return DevFont::fontLayerGetWidth(this, text); }

u32 FontLayer::fontGetWidth(const char *text) const { return DevFont::fontLayerGetWidth(this, text); }

u32 FontLayer::fontGetHeight() const { return DevFont::fontLayerGetHeight(this); }

const mm::Col4 &FontLayer::fontGetColor() const { return DevFont::fontLayerGetColor(this); }

void FontLayer::fontStyle(FONT_STYLE style) { DevFont::fontLayerStyle(this, style); }

void FontLayer::fontZ(u32 z) { DevFont::fontLayerZ(this, z); }

} // namespace ml

template mm::mtl::PtrSingleton<ml::DevFont>::~PtrSingleton();
