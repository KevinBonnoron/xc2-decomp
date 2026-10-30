#pragma once
#include <stddef.h>

#include "layer/layer_base.h"

namespace layer {

class LayerFontIconObj;
class LayerFontResObj;
class LayerFontStyleObj;
class LayerManager;

class LayerFontManager {
public:
  LayerFontManager(LayerManager *manager);
  ~LayerFontManager();
  void allRelease();
  LayerBase *createFontResObj(const void *data);
  LayerBase *createStyleObj(const void *data);
  LayerBase *createFontIconObj(const void *data);
  LayerBase *createFontColMapObj(const void *data);
  void releaseResObj(LayerFontResObj *res);
  void releaseStyleObj(LayerFontStyleObj *style);
  void releaseIconObj(LayerFontIconObj *icon);
  void update();

  LayerBase::unknown001 unknown00;    // Inferred role: font object list; original member name unknown.
  LayerBase::unknown001 unknown18[2]; // Inferred role: font object lists per index; original member name unknown.
  LayerBase::unknown001 unknown48;    // Inferred role: font object list; original member name unknown.
  LayerFontResObj *unknown60;         // Inferred role: default res object; original member name unknown.
  LayerFontIconObj *unknown68;        // Inferred role: default icon object; original member name unknown.
  LayerFontStyleObj *unknown70;       // Inferred role: default style object; original member name unknown.
  LayerBase::unknown001 unknown78;    // Inferred role: style object list; original member name unknown.
  LayerManager *unknown90;            // Inferred role: layer manager; original member name unknown.
};

static_assert(offsetof(LayerFontManager, unknown00) == 0x00, "");
static_assert(offsetof(LayerFontManager, unknown18) == 0x18, "");
static_assert(offsetof(LayerFontManager, unknown48) == 0x48, "");
static_assert(offsetof(LayerFontManager, unknown68) == 0x68, "");
static_assert(offsetof(LayerFontManager, unknown78) == 0x78, "");
static_assert(offsetof(LayerFontManager, unknown90) == 0x90, "");

} // namespace layer
