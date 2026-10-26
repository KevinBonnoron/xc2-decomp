#include "ui/font/ui_font_manager.h"

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "layer/layer_acc_font_style.h"
#include "mm_mtl/hash.h"
#include "mm_mtl/reference_object.h"
#include "ui/ui_build_info_bdat.h"
#include "ui/ui_resource.h"

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

void UIFontManager::loadFontSet(const char *name, mm::mtl::IAllocator *allocator) {
  UIBuildInfoBdat buildInfo(name);
// __LINE__ is the line argument of the operator new call.
#line 263
  UIResource *resource = new (fw::Allocator::getProcAllocator(), 16, __FILE__, __LINE__) UIResource(name);
  mm::mtl::safeRelease(unknown08);
  resource->addRef();
  resource->load(&buildInfo, allocator);
  if (!resource->isValid()) {
    mm::mtl::safeRelease(unknown08);
  } else {
    unknown08 = resource;
  }
  unknown68 = false;
}

bool UIFontManager::getFontStyleInfo(u16 style, StyleInfo &info) {
  layer::LayerAccFontStyle fontStyle(m_fontStyle.unknown08);
  if (style >= fontStyle.getStyleDataMax()) {
    return false;
  }
  info.unknown00 = fontStyle.getStyleInfo(style).unknown08->unknown0c;
  info.unknown04 = fontStyle.getStyleInfo(style).unknown08->unknown10;
  return true;
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
