#include <string.h>

#include "dr/dr_calc_clip_man.h"
#include "dr/dr_res_wrk_clip_list.h"

namespace ml {

int DrResWrkClipList::calcWorkSize(const u8 *data, u32 offset) {
  const unknown001 *header = reinterpret_cast<const unknown001 *>(data + offset);
  int size = header->unknown04 / 32 * 4 + 4;
  return size + (32 - size % 32) % 32;
}

void DrResWrkClipList::changeMemCall(const u8 *data, u32 offset) {
  unknown00 = data;
  unknown08 = reinterpret_cast<const unknown002 *>(data + reinterpret_cast<const unknown001 *>(data + offset)->unknown00);
}

int DrResWrkClipList::setupWork(u8 *work, const u8 *data, u32 offset) {
  const unknown001 *header = reinterpret_cast<const unknown001 *>(data + offset);
  unknown00 = data;
  unknown10 = header->unknown04;
  unknown08 = reinterpret_cast<const unknown002 *>(data + header->unknown00);
  unknown18 = reinterpret_cast<u32 *>(work);
  int size = unknown10 / 32 * 4 + 4;
  unknown14 = size + (32 - size % 32) % 32;
  return unknown14;
}

// 0x710088c944. Forms measured on the record loop (all 67 instructions): `limit` is an int, as the game compares two 32 bit registers with `cmp w15, w17; b.gt` (0x710088c9b4, `limit > value`); a u16
// limit gives `cmp w17, w15, uxth; b.lo`, and `value < limit` swaps the operands. The two kinds are an if/else: the game computes `kind == 0` before `kind == 1` and the `or` (0x710088c9d4, the
// speculated arms of the select), while `isClipped |= kind == 1` before the test of the bit gives the other order and loads the record fields in another order. `limit` is declared before `isClipped`:
// that gives the game's order of the zero moves of the loop header (0x710088c9a0).
void DrResWrkClipList::update(DrCalcClipMan *clipMan) {
  memset(unknown18, 0, unknown14);
  if (clipMan->unknown70 != nullptr) {
    const unknown002 *list = unknown08;
    for (s32 i = 0; i < unknown10; i++, list++) {
      if (list->unknown04 > 0) {
        s32 limit = 0;
        bool isClipped = false;
        const unknown003 *record = reinterpret_cast<const unknown003 *>(unknown00 + list->unknown00);
        for (s32 j = 0; j < list->unknown04; j++, record++) {
          u16 value = record->unknown04;
          if (limit > value) {
            break;
          }
          if (clipMan->unknown70[record->unknown00 >> 5] & (1 << (record->unknown00 & 0x1f))) {
            limit = value;
            isClipped = record->unknown02 == 0;
          } else {
            isClipped |= record->unknown02 == 1;
          }
        }
        if (isClipped) {
          unknown18[i >> 5] |= 1 << (i & 0x1f);
        }
      }
    }
  }
}

} // namespace ml
