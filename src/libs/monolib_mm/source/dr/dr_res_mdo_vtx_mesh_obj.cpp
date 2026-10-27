#include "dr/dr_res_mdo_vtx_mesh_obj.h"

namespace ml {

u32 DrResMdoVtxMeshObj::setup(const u8 *, u8 *) { return 0x140; }

u32 DrResMdoVtxMeshObj::calcWorkSize(const u8 *) { return 0x140; }

} // namespace ml
