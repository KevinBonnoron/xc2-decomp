#include "dr/dr_res_mdo_seam_wrk_pos_mpf.h"

#include "dr/dr_res_mdo_seam_res.h"

namespace ml {

namespace {

// Inferred role: header of the position data of an etc mpf; original type name unknown.
struct unknown001 {
  u8 _00[0x04];
  u32 unknown04; // Inferred role: first table offset; original member name unknown.
  u8 _08[0x0c - 0x08];
  u32 unknown0c; // Inferred role: second table offset; original member name unknown.
  u32 unknown10; // Inferred role: position num; original member name unknown.
};

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

u32 DrResMdoSeamWrkPosMpf::getDataSize() const {
  if (unknown20 != nullptr) {
    return unknown20->m_size;
  }
  return 0;
}

void DrResMdoSeamWrkPosMpf::setupMpfBasePos(const u8 *data) {
  const unknown002 *header = reinterpret_cast<const unknown002 *>(data);
  unknown10 = data;
  unknown20 = nullptr;
  unknown28 = 0;
  unknown00 = data + header->unknown0c;
  unknown08 = data + header->unknown14;
  unknown18 = header->unknown18;
}

void DrResMdoSeamWrkPosMpf::setupMpfEtcPos(int index, DrResMdoSeamMemObj *memObj) {
  unknown20 = memObj;
  unknown28 = index;
  const u8 *data = memObj->m_buffer;
  const unknown001 *header = reinterpret_cast<const unknown001 *>(data);
  unknown10 = data;
  unknown00 = data + header->unknown04;
  unknown08 = data + header->unknown0c;
  unknown18 = header->unknown10;
}

void DrResMdoSeamWrkPosMpf::changeMemCall() {
  const u8 *data = unknown20->m_buffer;
  const unknown001 *header = reinterpret_cast<const unknown001 *>(data);
  unknown10 = data;
  unknown00 = data + header->unknown04;
  unknown08 = data + header->unknown0c;
}

} // namespace ml
