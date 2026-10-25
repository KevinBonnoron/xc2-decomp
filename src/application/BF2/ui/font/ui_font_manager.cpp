#include "ui/font/ui_font_manager.h"

#include "ui/ui_resource.h"

#include "layer/layer_acc_font_style.h"
#include "mm_mtl/hash.h"

namespace ui {

UIFontManager::FontRes *UIFontManager::getFontRes(u16 id) {
  for (FontRes *it = unknown10.begin(); it != unknown10.end(); ++it) {
    if (it->unknown00 == id) {
      return it;
    }
  }
  return nullptr;
}

UIFontManager::FontRes *UIFontManager::getFontRes(const char *name) {
  u32 hash = mm::mtl::hashStrCrc(name);
  for (FontRes *it = unknown10.begin(); it != unknown10.end(); ++it) {
    if (it->unknown04 == hash) {
      return it;
    }
  }
  return nullptr;
}

UIFontManager::FontRes *UIFontManager::getFontStyle() { return &m_fontStyle; }

UIFontManager::FontRes *UIFontManager::getFontResFromStyle(u16 style) {
  if (m_fontStyle.unknown08 == nullptr) {
    return nullptr;
  }
  layer::LayerAccFontStyle fontStyle(m_fontStyle.unknown08);
  return getFontRes(fontStyle.getFontName(style));
}

bool UIFontManager::findFacePattern(const char *name, u32 &index) {
  u32 hash = mm::mtl::hashStrCrc(name);
  index = 0;
  for (FacePattern *it = unknown70.begin(); it != unknown70.end(); ++it) {
    if (it->unknown00 == hash) {
      index = it->unknown04;
      return true;
    }
  }
  return false;
}

bool UIFontManager::isLoading() const {
  if (unknown08 != nullptr) {
    return unknown08->isLoading();
  }
  return false;
}

} // namespace ui
