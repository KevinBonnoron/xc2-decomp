#include "dr/dr_ibl_man.h"

#include "dr/dr_ibl_obj.h"

namespace ml {

bool DrIBLMan::isValid() const { return unknown910 != nullptr; }

void DrIBLMan::releaseObj(DrIBLObj *obj) { obj->unknown58 |= 2; }

} // namespace ml
