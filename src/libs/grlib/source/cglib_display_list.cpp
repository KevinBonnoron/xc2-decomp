#include "grlib/cglib_display_list.h"

namespace grlib {

CGLibDisplayList::CGLibDisplayList() {}

CGLibDisplayList::~CGLibDisplayList() {}

void CGLibDisplayList::release() {}

void CGLibDisplayList::beginDisplay(void *buffer, int size) {}

u32 CGLibDisplayList::endDisplay(void *buffer) { return 0; }

void CGLibDisplayList::callDisplayList() {}

CGLibOneDisplayList::CGLibOneDisplayList() {}

CGLibOneDisplayList::~CGLibOneDisplayList() {}

void CGLibOneDisplayList::release() {}

void CGLibOneDisplayList::beginDisplay(void *buffer, int size) {}

void CGLibOneDisplayList::endDisplay() {}

void CGLibOneDisplayList::callDisplayList() {}

} // namespace grlib
