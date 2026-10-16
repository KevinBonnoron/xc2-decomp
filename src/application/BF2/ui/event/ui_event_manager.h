#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ui {

class UIEventCondition;
class UIObjectListener;

class UIEventManager : public mm::mtl::PtrSingleton<UIEventManager> {
public:
  void registObjectListener(u32 handle, UIObjectListener *listener);
  void removeObjectListener(u32 handle);
  void addCondition(u32 handle, UIEventCondition *condition);
};

} // namespace ui
