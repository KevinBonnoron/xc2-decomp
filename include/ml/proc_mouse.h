#pragma once
#include <stddef.h>

#include "ml/win_proc.h"
#include "ml/win_view_frame.h"
#include "mm_math/mm_pnt.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {

class WorkObj;

class ProcMouse : public WinProc, public mm::mtl::PtrSingleton<ProcMouse> {
public:
  ProcMouse(const char *name, WorkObj *parent);
  ~ProcMouse() override;
  static void setDisp(bool isDisp);
  static mm::Pnt<int> *getPos();
  static mm::Pnt<int> *getMove();
  static void setPos(const mm::Pnt<int> &position);
  static void setCursorResize(MCURSOR cursor);
  static void update(bool isUpdate);
  void wkRenderAfter() override;
  bool wkStandbyLogin() override;
  bool wkStandbyLogout() override;

  mm::Pnt<int> m_pos;             // Inferred role: position; named after the game accessor ml::ProcMouse::getPos.
  mm::Pnt<int> unknown200;        // Inferred role: previous position; original member name unknown.
  mm::Pnt<int> m_move;            // Inferred role: move; named after the game accessor ml::ProcMouse::getMove.
  mm::mtl::FixStr<32> unknown210; // Inferred role: cursor name ("ARROW", "SIZE1"...); original member name unknown.
  bool unknown234;                // Inferred role: resize cursor shown; original member name unknown.
  u8 unknown235;                  // Inferred role: frames left to draw the cursor after a move; original member name unknown.
};

static_assert(offsetof(ProcMouse, m_pos) == 0x1f8, "");
static_assert(offsetof(ProcMouse, unknown200) == 0x200, "");
static_assert(offsetof(ProcMouse, m_move) == 0x208, "");
static_assert(offsetof(ProcMouse, unknown210) == 0x210, "");
static_assert(offsetof(ProcMouse, unknown234) == 0x234, "");
static_assert(offsetof(ProcMouse, unknown235) == 0x235, "");

} // namespace ml
