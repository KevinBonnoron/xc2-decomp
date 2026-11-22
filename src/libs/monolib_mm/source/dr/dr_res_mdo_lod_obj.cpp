#include "dr/dr_res_mdo_lod_obj.h"

#include "dr/dr_res_mdo_lod_grp.h"
#include "dr/dr_res_mdo_lod_parts.h"

namespace ml {

// The game stores unknown18 and unknown1c as `stp w8, wzr, [x0, #0x18]` (0x710086ee38). Written in declaration order (or in an
// initialiser list) the two adjacent constant stores are merged by the DAG combiner into one 64-bit store (`stp xzr, x8`). With
// unknown1c = 0 before unknown18 = 1, as update() clears the flags first, MemCpyOpt places the 24-byte memset of the zero members
// between the two stores, so they stay separate and AArch64LoadStoreOpt pairs them. Measured over the 720 orders of the six
// assignments: 222 give the game's code, among them all 120 that write unknown18 last; the declaration order does not.
DrResMdoLodObj::DrResMdoLodObj() {
  m_drResMdoLodParts = nullptr;
  m_drResMdoLodGrp = nullptr;
  unknown10 = 0;
  unknown14 = 0;
  unknown1c = 0;
  unknown18 = 1;
}

DrResMdoLodObj::~DrResMdoLodObj() {}

int DrResMdoLodObj::calcWorkSize(const u8 *resource) {
  const unknown001 *header = reinterpret_cast<const unknown001 *>(resource);
  const unknown002 *lod = nullptr;
  if (header->unknown02 & 2) {
    lod = reinterpret_cast<const unknown002 *>(resource + header->unknown8c);
  }
  int partsNum = 1;
  int grpNum = 1;
  if (lod != nullptr) {
    partsNum = lod->unknown08 + 1;
    grpNum = lod->unknown10 + 1;
  }
  return sizeof(DrResMdoLodObj) + partsNum * sizeof(DrResMdoLodParts) + grpNum * sizeof(DrResMdoLodGrp);
}

bool DrResMdoLodObj::update(DrResMdlLodArg &arg) {
  unknown1c = 0;
  if (unknown18 & 1) {
    unknown18 &= ~1;
    arg.unknown10 = true;
  }
  bool isUpdate = false;
  for (u32 i = 0; i < unknown14; i++) {
    isUpdate |= m_drResMdoLodGrp[i].update(arg, unknown1c);
  }
  if (unknown14 == 1) {
    unknown1c |= 1;
  }
  bool isChange = false;
  for (u32 i = 0; i < unknown14; i++) {
    if (m_drResMdoLodGrp[i].unknown10_5) {
      isChange = true;
    }
  }
  if (isChange) {
    unknown18 |= 2;
  } else {
    unknown18 &= ~2;
  }
  return isUpdate;
}

int DrResMdoLodObj::create(u8 *work, const u8 *resource) { return reinterpret_cast<DrResMdoLodObj *>(work)->setup(resource, work + sizeof(DrResMdoLodObj)); }

void DrResMdoLodObj::release(DrResMdoLodObj *&lodObj) {
  if (lodObj != nullptr) {
    lodObj = nullptr;
  }
}

} // namespace ml
