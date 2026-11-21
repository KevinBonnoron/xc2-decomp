#include "dr/dr_mdo_ctl_mpf_inst.h"

#include "dr/dr_mdo_ctl_mpf_work.h"
#include "dr/dr_res_mdo_seam_wrk_pos_mpf.h"

namespace ml {

// Inferred role: header of an instance mpf resource; original type name unknown.
struct unknown064 {
  u8 _00[0x4];
  u32 unknown04; // Inferred role: offset of the instance data from the resource; original member name unknown.
};

DrMdoCtlMpfInst::DrMdoCtlMpfInst() {}

void DrMdoCtlMpfInst::setupInstMpf(const u8 *resource) { unknown00 = reinterpret_cast<const MdsMpfObjData *>(resource + reinterpret_cast<const unknown064 *>(resource)->unknown04); }

void DrMdoCtlMpfInst::calcInstMpf(DrCalcViewWork *view, DrMdoCtlMpfWork *work, DrResMdoSeamWrkPosMpf *pos) {
  if (pos->unknown18 != 0) {
    unknown08 = work;
    unknown10 = pos;
    for (int i = 0; i < pos->unknown18; i++) {
      // The game loads unknown00 before the load of the node's object index (0x71007fa020: ldr x9, [x21], then ldrh w8, [x1, #28]); the local places
      // that load.
      const MdsMpfObjData *objects = unknown00;
      const MdsMpfObjTreeData *tree = &unknown10->unknown08[i];
      calcMpfObjTree(tree, view, objects[tree->unknown1c].unknown0c);
    }
  }
}

void DrMdoCtlMpfInst::calcSeamInstMpf(DrCalcViewWork *view, DrMdoCtlMpfWork *work, DrResMdoSeamWrkPosMpf *pos) {
  if (pos->unknown18 != 0) {
    unknown08 = work;
    unknown10 = pos;
    for (int i = 0; i < pos->unknown18; i++) {
      // Same load order as calcInstMpf, which this function repeats with the seam callee (the same instruction, 0x5c bytes into the function).
      const MdsMpfObjData *objects = unknown00;
      const MdsMpfObjTreeData *tree = &unknown10->unknown08[i];
      calcSeamMpfObjTree(tree, view, objects[tree->unknown1c].unknown0c);
    }
  }
}

} // namespace ml
