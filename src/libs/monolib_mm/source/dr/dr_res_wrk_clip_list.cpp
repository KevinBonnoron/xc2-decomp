#include "dr/dr_res_wrk_clip_list.h"

namespace ml {

int DrResWrkClipList::calcWorkSize(const u8 *data, u32 offset) {
  const unknown001 *header = reinterpret_cast<const unknown001 *>(data + offset);
  int size = header->unknown04 / 32 * 4 + 4;
  return size + (32 - size % 32) % 32;
}

void DrResWrkClipList::changeMemCall(const u8 *data, u32 offset) {
  unknown00 = data;
  unknown08 = data + reinterpret_cast<const unknown001 *>(data + offset)->unknown00;
}

int DrResWrkClipList::setupWork(u8 *work, const u8 *data, u32 offset) {
  const unknown001 *header = reinterpret_cast<const unknown001 *>(data + offset);
  unknown00 = data;
  unknown10 = header->unknown04;
  unknown08 = data + header->unknown00;
  unknown18 = work;
  int size = unknown10 / 32 * 4 + 4;
  unknown14 = size + (32 - size % 32) % 32;
  return unknown14;
}

} // namespace ml
