#include "dr/dr_res_display_list.h"

namespace ml {

DrResDisplayList::DrResDisplayList() {}

DrResDisplayList::~DrResDisplayList() { release(); }

DrResOneDisplayList::DrResOneDisplayList() {}

DrResOneDisplayList::~DrResOneDisplayList() { release(); }

DrResRenderDisplayList::DrResRenderDisplayList() {}

DrResRenderDisplayList::~DrResRenderDisplayList() { release(); }

} // namespace ml
