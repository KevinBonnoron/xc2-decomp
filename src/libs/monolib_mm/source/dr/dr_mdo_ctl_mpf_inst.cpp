#include "dr/dr_mdo_ctl_mpf_inst.h"

namespace ml {

// Inferred role: header of an instance mpf resource; original type name unknown.
struct unknown001 {
  u8 _00[0x4];
  u32 unknown04; // Inferred role: offset of the instance data from the resource; original member name unknown.
};

DrMdoCtlMpfInst::DrMdoCtlMpfInst() {}

void DrMdoCtlMpfInst::setupInstMpf(const u8 *resource) { unknown00 = resource + reinterpret_cast<const unknown001 *>(resource)->unknown04; }

} // namespace ml
