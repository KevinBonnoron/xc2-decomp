#pragma once
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include "ui/input/ui_input_pointer.h"

namespace ui {

class IUIInputSelectionChecker;
class UIInputLayer;

class UIInputManager : public mm::mtl::PtrSingleton<UIInputManager> {
public:
  void enable();
  void disable();
  void setupInputSelection(u32 input, int index, u32 size);
  void resetInputSelection(u32 input);
  void setSelectionChecker(u32 input, IUIInputSelectionChecker *checker);
  void setInputActionEnable(u32 input, u32 action, bool enable);
  u32 registInputLayer(UIInputLayer *layer, const char *name);
  void releaseInputLayer(u32 handle);
  void setInputSelectEnable(u32 input, bool enable);
  u32 searchInputHandle(u32 handle);
  void migrateInput(u32 input, u32 handle);
  void enableInput(u32 input);
  void disableInput(u32 input);
  void setPadLineSelection(u32 input, u32 line);
  void setPadLineSelectionLoop(u32 input, bool loop);
  void setPadPageSize(u32 input, u32 size);
  void setPadLoopSetting(u32 input, bool loop);
  void setupPointerSelection(u32 input, const UIInputPointer::SelectionSetup &setup);
  void changePointerPos(u32 input, const mm::Pnt<s16> &pos);
  void changeRegionScale(u32 input, f32 scale);
  void changeRegionRect(u32 input, const mm::Rect<s16> &rect);
};

} // namespace ui
