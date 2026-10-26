#include "ui/ctrl/ui_ctrl_slide_select.h"

#include "mm_math/mm_vec2.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_simple.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace ui {

UICtrlSlideSelect::UICtrlSlideSelect(u32 object) : UICtrlObject(object), unknown2c(), unknown48(nullptr), unknown50(0), unknown58() {}

UICtrlSlideSelect::~UICtrlSlideSelect() { mm::mtl::safeRelease(unknown48); }

void UICtrlSlideSelect::updateObjectPos() {
  if (unknown48 != nullptr && unknown48->getSize() != 0 && unknown48->getSize() != 0) {
    u32 i = 0;
    do {
      if (i >= unknown58.size()) {
        return;
      }
      {
        UIObjectAcc acc(unknown48->getObject(i));
        if (acc.isValid()) {
          mm::Pnt<s16> pos;
          pos.x = unknown58[i].values[0];
          pos.y = unknown58[i].values[1];
          acc.setPosCenter(pos);
          alignas(16) mm::Vec2 scale;
          scale.x = unknown58[i].values[2];
          scale.y = scale.x;
          acc.setScale(scale);
          f32 alpha = unknown58[i].values[3];
          if (alpha == 0.0f) {
            acc.setDisp(false);
          } else {
            acc.setAlpha(alpha);
            acc.setDisp(true);
          }
        }
      }
      i++;
    } while (i < unknown48->getSize());
  }
}

} // namespace ui
