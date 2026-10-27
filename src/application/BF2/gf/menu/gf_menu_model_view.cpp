#include "gf/menu/gf_menu_model_view.h"

namespace gf {

void GfMenuModelView::CtrlParam::setMovePosX(f32 value) {
  unknown08 |= 0x1;
  m_movePosX = value;
}

void GfMenuModelView::CtrlParam::setMovePosY(f32 value) {
  unknown08 |= 0x2;
  m_movePosY = value;
}

void GfMenuModelView::CtrlParam::setMovePosZ(f32 value) {
  unknown08 |= 0x4;
  m_movePosZ = value;
}

void GfMenuModelView::CtrlParam::setMoveSclX(f32 value) {
  unknown08 |= 0x8;
  m_moveSclX = value;
}

void GfMenuModelView::CtrlParam::setMoveSclY(f32 value) {
  unknown08 |= 0x10;
  m_moveSclY = value;
}

void GfMenuModelView::CtrlParam::setMoveSclZ(f32 value) {
  unknown08 |= 0x20;
  m_moveSclZ = value;
}

void GfMenuModelView::CtrlParam::setMoveRotY(f32 value) {
  unknown08 |= 0x80;
  m_moveRotY = value;
}

void GfMenuModelView::CtrlParam::setMoveAlpha(f32 value) {
  unknown08 |= 0x40;
  m_moveAlpha = value;
}

void GfMenuModelView::CtrlParam::setMoveVanish(f32 value) {
  unknown08 |= 0x100;
  m_moveVanish = value;
}

} // namespace gf
