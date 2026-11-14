#include "navi/nvmsh_ac_man.h"

#include "navi/nvmsh_ac_obj_base.h"

namespace navi {

void NvmshAcMan::tail() { unknown842 = unknown842 == 0; }

void NvmshAcMan::beginUpdate() { unknown840 = unknown842 == 0; }

void NvmshAcMan::releaseObj(NvmshAcObjBase *object) { object->unknown65 |= 1; }

} // namespace navi

// The game builds this file in the same unit, after this one (0x71008e9054 to 0x71008ee654): its setRootListBuff (0x71008e8b70) and workReset (0x71008e8d30) sit in the NvmshAcMan block
// (0x71008e8b80 to 0x71008e9054).
#include "nvmsh_ac_obj_base.cpp"
