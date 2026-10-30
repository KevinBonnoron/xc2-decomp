#include "layer/layer_font_manager.h"

#include "layer/layer_font_icon_obj.h"
#include "layer/layer_font_res_obj.h"
#include "layer/layer_font_style_obj.h"
#include "layer/layer_manager.h"
#include "mtl/alloc_handle.h"

namespace layer {

LayerFontManager::LayerFontManager(LayerManager *manager) {
  unknown90 = manager;
  unknown00.unknown10 = 0;
  unknown18[0].unknown10 = 0;
  unknown18[1].unknown10 = 0;
  unknown48.unknown10 = 0;
  unknown78.unknown10 = 0;
  unknown60 = nullptr;
  unknown00.unknown00 = nullptr;
  unknown00.unknown08 = nullptr;
  unknown18[0].unknown00 = nullptr;
  unknown18[0].unknown08 = nullptr;
  unknown18[1].unknown00 = nullptr;
  unknown18[1].unknown08 = nullptr;
  unknown48.unknown00 = nullptr;
  unknown48.unknown08 = nullptr;
  unknown78.unknown00 = nullptr;
  unknown78.unknown08 = nullptr;
  unknown68 = nullptr;
  unknown70 = nullptr;
}

LayerFontManager::~LayerFontManager() {
  unknown00.unknown003();
  unknown18[0].unknown003();
  unknown18[1].unknown003();
  unknown48.unknown003();
  unknown78.unknown003();
}

void LayerFontManager::allRelease() {
  unknown00.unknown003();
  unknown18[0].unknown003();
  unknown18[1].unknown003();
  unknown48.unknown003();
  unknown78.unknown003();
}

LayerBase *LayerFontManager::createFontResObj(const void *data) {
  LayerFontResObj *res = new (unknown90->unknown28) LayerFontResObj(this);
  res->setFontData(data);
  unknown18[LayerManager::s_nStkIdx].unknown002(res);
  if (unknown60 == nullptr) {
    unknown60 = res;
  }
  return res;
}

LayerBase *LayerFontManager::createStyleObj(const void *data) {
  LayerFontStyleObj *style = new (unknown90->unknown28) LayerFontStyleObj(this);
  style->setStyleData(data);
  unknown78.unknown002(style);
  if (unknown70 == nullptr) {
    unknown70 = style;
  }
  return style;
}

LayerBase *LayerFontManager::createFontIconObj(const void *data) {
  LayerFontIconObj *icon = new (unknown90->unknown28) LayerFontIconObj(this, data, LAYER_TYPE_UNKNOWN_11);
  unknown18[LayerManager::s_nStkIdx].unknown002(icon);
  if (unknown68 == nullptr) {
    unknown68 = icon;
  }
  return icon;
}

LayerBase *LayerFontManager::createFontColMapObj(const void *data) {
  LayerFontIconObj *colMap = new (unknown90->unknown28) LayerFontIconObj(this, data, LAYER_TYPE_UNKNOWN_12);
  unknown18[LayerManager::s_nStkIdx].unknown002(colMap);
  return colMap;
}

void LayerFontManager::releaseResObj(LayerFontResObj *res) { res->unknown28 |= 1 << LayerManager::s_nStkIdx; }

void LayerFontManager::releaseIconObj(LayerFontIconObj *icon) { icon->unknown28 |= 1 << LayerManager::s_nStkIdx; }

void LayerFontManager::releaseStyleObj(LayerFontStyleObj *style) {
  unknown78.unknown004(style);
  delete style;
}

} // namespace layer
