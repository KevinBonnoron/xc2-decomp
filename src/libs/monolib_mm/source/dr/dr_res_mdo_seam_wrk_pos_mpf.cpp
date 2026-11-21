#include "dr/dr_res_mdo_seam_wrk_pos_mpf.h"

namespace ml {

namespace {

// Inferred role: header of the position data of a base mpf; original type name unknown.
struct unknown002 {
  u8 _00[0x0c];
  u32 unknown0c; // Inferred role: first table offset; original member name unknown.
  u8 _10[0x14 - 0x10];
  u32 unknown14; // Inferred role: second table offset; original member name unknown.
  u32 unknown18; // Inferred role: position num; original member name unknown.
};

} // namespace

DrResMdoSeamWrkPosMpf::DrResMdoSeamWrkPosMpf() : unknown20(nullptr) {}

void DrResMdoSeamWrkPosMpf::setupMpfBasePos(const u8 *data) {
  const unknown002 *header = reinterpret_cast<const unknown002 *>(data);
  unknown10 = data;
  unknown20 = nullptr;
  unknown28 = 0;
  unknown00 = data + header->unknown0c;
  unknown08 = reinterpret_cast<const MdsMpfObjTreeData *>(data + header->unknown14);
  unknown18 = header->unknown18;
}

} // namespace ml
