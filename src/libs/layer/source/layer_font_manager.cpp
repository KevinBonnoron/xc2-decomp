#include "layer/layer_font_manager.h"

#include "layer/layer_font_icon_obj.h"
#include "layer/layer_font_res_obj.h"
#include "layer/layer_font_style_obj.h"
#include "layer/layer_manager.h"

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

void LayerFontManager::releaseResObj(LayerFontResObj *res) { res->unknown28 |= 1 << LayerManager::s_nStkIdx; }

void LayerFontManager::releaseIconObj(LayerFontIconObj *icon) { icon->unknown28 |= 1 << LayerManager::s_nStkIdx; }

void LayerFontManager::releaseStyleObj(LayerFontStyleObj *style) {
  unknown78.unknown004(style);
  delete style;
}

} // namespace layer
