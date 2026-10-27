#pragma once
#include <stddef.h>

#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;

class GfMenuModelView {
public:
  struct CtrlParam {
    void setMovePosX(f32 value);
    void setMovePosY(f32 value);
    void setMovePosZ(f32 value);
    void setMoveSclX(f32 value);
    void setMoveSclY(f32 value);
    void setMoveSclZ(f32 value);
    void setMoveRotY(f32 value);
    void setMoveAlpha(f32 value);
    void setMoveVanish(f32 value);

    GF_OBJ_HANDLE *unknown00; // Inferred role: object handle; original member name unknown.
    u16 unknown08;            // Inferred role: set value flags; original member name unknown.
    u8 _0a[0x14 - 0x0a];
    f32 m_movePosX;
    f32 m_movePosY;
    f32 m_movePosZ;
    f32 m_moveSclX;
    f32 m_moveSclY;
    f32 m_moveSclZ;
    f32 m_moveAlpha;
    f32 m_moveRotY;
    f32 m_moveVanish;
  };
};

static_assert(offsetof(GfMenuModelView::CtrlParam, unknown08) == 0x08, "");
static_assert(offsetof(GfMenuModelView::CtrlParam, m_movePosX) == 0x14, "");
static_assert(offsetof(GfMenuModelView::CtrlParam, m_movePosY) == 0x18, "");
static_assert(offsetof(GfMenuModelView::CtrlParam, m_movePosZ) == 0x1c, "");
static_assert(offsetof(GfMenuModelView::CtrlParam, m_moveSclX) == 0x20, "");
static_assert(offsetof(GfMenuModelView::CtrlParam, m_moveSclY) == 0x24, "");
static_assert(offsetof(GfMenuModelView::CtrlParam, m_moveSclZ) == 0x28, "");
static_assert(offsetof(GfMenuModelView::CtrlParam, m_moveAlpha) == 0x2c, "");
static_assert(offsetof(GfMenuModelView::CtrlParam, m_moveRotY) == 0x30, "");
static_assert(offsetof(GfMenuModelView::CtrlParam, m_moveVanish) == 0x34, "");

} // namespace gf
