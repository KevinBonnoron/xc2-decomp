#include "ml/proc_mouse.h"

namespace ml {

mm::Pnt<int> *ProcMouse::getPos() { return &get()->unknown1f8; }

mm::Pnt<int> *ProcMouse::getMove() { return &get()->unknown208; }

void ProcMouse::setPos(const mm::Pnt<int> &position) {
  ProcMouse *mouse = get();
  mouse->unknown200 = position;
  mouse->unknown1f8 = position;
}

} // namespace ml

template mm::mtl::PtrSingleton<ml::ProcMouse>::~PtrSingleton();
