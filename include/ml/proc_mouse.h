#pragma once
#include <stddef.h>

#include "ml/win_proc.h"
#include "mm_math/mm_pnt.h"
#include "mm_mtl/singleton.h"

namespace ml {

class ProcMouse : public WinProc, public mm::mtl::PtrSingleton<ProcMouse> {
public:
  static mm::Pnt<int> *getPos();
  static mm::Pnt<int> *getMove();
  static void setPos(const mm::Pnt<int> &position);

  mm::Pnt<int> unknown1f8; // Inferred role: position; original member name unknown.
  mm::Pnt<int> unknown200; // Inferred role: previous position; original member name unknown.
  mm::Pnt<int> unknown208; // Inferred role: move; original member name unknown.
};

static_assert(offsetof(ProcMouse, unknown1f8) == 0x1f8, "");
static_assert(offsetof(ProcMouse, unknown200) == 0x200, "");
static_assert(offsetof(ProcMouse, unknown208) == 0x208, "");

} // namespace ml
