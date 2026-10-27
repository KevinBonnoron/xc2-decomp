#include "grlib/cglib_display.h"

namespace grlib {

void CGLibDisplay::updateWindow(NVNqueue *queue) {}

void CGLibDisplay::updateEnd(NVNqueue *queue) { unknownfc9 = false; }

void CGLibDisplay::updateSignaled() { unknownfcb = !unknownfc9; }

void CGLibDisplay::fasteTargetClear() {}

} // namespace grlib
