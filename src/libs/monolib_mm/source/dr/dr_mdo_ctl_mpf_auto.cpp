#include "dr/dr_mdo_ctl_mpf_auto.h"

#include "dr/dr_mdo_mpf_man.h"
#include "dr/dr_mpf_work_auto_inf.h"
#include "mm_math/mm_vec3.h"

namespace ml {

namespace {

// Inferred helper: rounds a size up to a multiple of 16; original name unknown.
int unknown113(int size) { return size + (0x10 - size % 0x10) % 0x10; }

} // namespace

DrMdoCtlMpfAuto::DrMdoCtlMpfAuto() : unknown68(0), unknown6c(0), unknown70(0), unknown80(0), unknown84(0) {
  unknownd0.unknown08 = 0.0f;
  unknownd0.unknown00 = 0.0f;
  unknownd0.unknown04 = 0.0f;
  unknown00 = nullptr;
  m_mdsMpfAutoHlvPoliTree = nullptr;
}

DrMdoCtlMpfAuto::~DrMdoCtlMpfAuto() { autoMpfRelease(); }

void DrMdoCtlMpfAuto::autoMpfRelease() {
  if (unknown00 != nullptr) {
    int count = unknown00->unknown00;
    for (int i = 0; i < count; i++) {
      _MPFWorkAutoInf *work = unknown158[i];
      while (work != nullptr) {
        _MPFWorkAutoInf *next = work->unknown28;
        m_drMdoMpfMan->freeMemWork(work);
        work = next;
      }
      unknown158[i] = nullptr;
      unknown160[i] = nullptr;
    }
    unknown00 = nullptr;
    unknown68 = 0;
  }
}

void DrMdoCtlMpfAuto::resetPrePos() {
  for (int i = 0; i < unknown00->unknown00; i++) {
    mm::Vec3 &position = unknownc0[i];
    position.x = -100000.0f;
    position.z = -100000.0f;
    position.y = -100000.0f;
  }
}

void DrMdoCtlMpfAuto::setBuffTbl(_wkMpfAutoBuff **table, int count) {
  unknown60 = table;
  unknown68 = count;
}

void DrMdoCtlMpfAuto::SeqListCount() {
  unknown80++;
  if (unknown00->unknown00 <= unknown80) {
    unknown80 = 0;
  }
}

void DrMdoCtlMpfAuto::memChgMinWork(_MPFWorkAutoInf *&work) {
  _MPFWorkAutoInf *minWork = m_drMdoMpfMan->unknownf0;
  if (minWork != nullptr) {
    minWork->unknown00 = 0;
    minWork->unknown1a = 0;
    minWork->unknown18 = work->unknown18;
    minWork->unknown14 = work->unknown14;
    minWork->unknown16 = work->unknown16;
    minWork->unknown04 = work->unknown04;
    minWork->unknown08 = work->unknown08;
    minWork->unknown0c = work->unknown0c;
    minWork->unknown10 = work->unknown10;
    work = minWork;
  }
}

void DrMdoCtlMpfAuto::DebugUpdateMem(_MPFWorkAutoInf *work, int index) {
  for (_MPFWorkAutoInf *current = *unknown158; current != nullptr && current != work; current = current->unknown28) {
  }
  for (_MPFWorkAutoInf *current = *unknown160; current != nullptr && current != work; current = current->unknown30) {
  }
}

void DrMdoCtlMpfAuto::gridColiCalc() {
  unknownf8 = 0;
  for (int i = 0; i < unknown68; i++) {
    unknown58 = unknown60[i];
    if (unknown58->unknown08 > unknownd0.unknown00 || unknown58->unknown00 < unknownd0.unknown00 || unknown58->unknown0c > unknownd0.unknown08 || unknown58->unknown04 < unknownd0.unknown08) {
      continue;
    }
    gridTreeColiCalc(unknown58->m_mdsMpfAutoTree);
  }
  StockPoint();
}

void DrMdoCtlMpfAuto::gridInstColiCalc() {
  unknownf8 = 0;
  for (int i = 0; i < unknown68; i++) {
    unknown58 = unknown60[i];
    if (unknown58->unknown08 > unknownd0.unknown00 || unknown58->unknown00 < unknownd0.unknown00 || unknown58->unknown0c > unknownd0.unknown08 || unknown58->unknown04 < unknownd0.unknown08) {
      continue;
    }
    if (unknown58->m_mdsMpfAutoTree != nullptr) {
      gridTreeColiCalc(unknown58->m_mdsMpfAutoTree);
    }
    if (unknown58->m_mdsMpfAutoPosData != nullptr) {
      seachInstTree(unknown58->m_mdsMpfAutoPosTree);
    }
  }
  StockPoint();
}

// The game reads the float table pointer (ldr x10, [x20, #0x50] at 0x71007fd27c) and the two table indexes (ldrh at 0x71007fd274 and 0x71007fd280, zero-extended) before the first float load
// (ldr s1, [x19, #0x88] at 0x71007fd284) and keeps them for the four range products. Reading them once into locals, the indexes as 64 bit values, gives that order and the register
// assignment (w12 the origin index, w11 the scale index). Without the locals (`buff->unknown50[tree->unknown06]` in each product) the function has 132 instructions as well, but the scale
// index is loaded after the float loads and the two index registers are swapped (13 differing lines); two of the three locals, or 32 bit indexes, leave 9 to 31 differing lines.
bool DrMdoCtlMpfAuto::gridColiRangeChk(const MdsMpfAutoTree *tree) {
  u32 word = tree->unknown08;
  if ((word & unknown70 & 0xffff) == 0) {
    return false;
  }
  const _wkMpfAutoBuff *buff = unknown58;
  const unknown515 *table = buff->unknown50;
  u64 originIndex = tree->unknown06;
  u64 scaleIndex = tree->unknown04;
  s32 width = (word >> 16) & 0xff;
  s32 depth = word >> 24;
  f32 minX = (unknown88 - table[originIndex].unknown00) * table[scaleIndex].unknown00;
  s32 startX = static_cast<s32>(minX);
  startX -= (minX - startX <= 0.01f);
  if (startX >= width) {
    return false;
  }
  if (startX < 0) {
    startX = 0;
  }
  f32 minZ = (unknown8c - table[originIndex].unknown04) * table[scaleIndex].unknown04;
  s32 startZ = static_cast<s32>(minZ);
  startZ -= (minZ - startZ <= 0.01f);
  if (startZ >= depth) {
    return false;
  }
  if (startZ < 0) {
    startZ = 0;
  }
  f32 maxX = (unknown90 - table[originIndex].unknown00) * table[scaleIndex].unknown00;
  s32 endX = static_cast<s32>(maxX);
  endX += (0.99f <= maxX - endX);
  if (endX < 0) {
    return false;
  }
  f32 maxZ = (unknown94 - table[originIndex].unknown04) * table[scaleIndex].unknown04;
  if (endX >= width) {
    endX = width - 1;
  }
  s32 endZ = static_cast<s32>(maxZ);
  endZ += (0.99f <= maxZ - endZ);
  if (endZ < 0) {
    return false;
  }
  if (endZ >= depth) {
    endZ = depth - 1;
  }
  if (startX > endX || startZ > endZ) {
    return false;
  }
  for (s32 x = startX; x <= endX; x++) {
    for (s32 z = startZ; z <= endZ; z++) {
      u32 cell = buff->unknown48[tree->unknown00 + z + x * depth];
      if (cell != 0) {
        if (static_cast<s32>(cell) < 0 || gridColiRangeChk(&buff->m_mdsMpfAutoTree[cell])) {
          return true;
        }
      }
    }
  }
  return false;
}

// The tables are walked with `*indices++` next to the counter: a second induction variable keeps the 32 bit compare of the counter (cmp w24, w23 at 0x71007fd4f8, cmp w9, w8 at 0x71007fd580)
// on the 64 bit index of the loads; with `indices[i]` (or a u32 index accessor) indvars widens the compare (cmp x, x, 94 instructions as well).
bool DrMdoCtlMpfAuto::gridColiInstPosRangeChk(const MdsMpfAutoPosTree *tree) {
  if ((tree->unknown1c & unknown70) == 0 || tree->unknown00 < unknown88 || tree->unknown08 > unknown90 || tree->unknown04 < unknown8c || tree->unknown0c > unknown94) {
    return false;
  }
  int count = tree->unknown18_0;
  if (count != 0) {
    const u32 *indices = unknown58->unknown68 + tree->unknown10;
    for (int i = 0; i < count; i++) {
      if (gridColiInstPosRangeChk(&unknown58->m_mdsMpfAutoPosTree[*indices++])) {
        return true;
      }
    }
  }
  count = tree->unknown18_16;
  if (count != 0) {
    const u32 *indices = unknown58->unknown68 + tree->unknown14;
    for (int i = 0; i < count; i++) {
      const MdsMpfAutoPosData *data = &unknown58->m_mdsMpfAutoPosData[*indices++];
      if ((data->unknownb4 & unknown70) == 0) {
        break;
      }
      if (data->unknowna0 < unknown88 || data->unknowna8 > unknown90 || data->unknowna4 < unknown8c || data->unknownac > unknown94) {
        continue;
      }
      return true;
    }
  }
  return false;
}

bool DrMdoCtlMpfAuto::gridChkColiRange(f32 maxX, f32 minX, f32 maxZ, f32 minZ) {
  int count = unknown68;
  unknown88 = minX;
  unknown8c = minZ;
  unknown90 = maxX;
  unknown94 = maxZ;
  _wkMpfAutoBuff **table = unknown60;
  for (int i = 0; i < count; i++) {
    _wkMpfAutoBuff *buff = table[i];
    unknown58 = buff;
    if (!(buff->unknown08 > maxX || minX > buff->unknown00 || buff->unknown0c > maxZ || minZ > buff->unknown04)) {
      if (buff->m_mdsMpfAutoTree != nullptr) {
        if (gridColiRangeChk(buff->m_mdsMpfAutoTree)) {
          return true;
        }
        if (buff->m_mdsMpfAutoPosData != nullptr) {
          if (gridColiInstPosRangeChk(buff->m_mdsMpfAutoPosTree)) {
            return true;
          }
        }
      } else if (gridColiInstPosRangeChk(buff->m_mdsMpfAutoPosTree)) {
        return true;
      }
    }
  }
  return false;
}

void DrMdoCtlMpfAuto::StockTempPoint() {
  if (unknownf8 > 9) {
    return;
  }
  for (int i = 0; i < unknownf8; i++) {
    f32 difference = unknownd0.unknown04 - unknownf0[i].unknown00;
    if (difference < 2.0f && difference > -2.0f) {
      if (difference > 0.0f) {
        unknownf0[i].unknown04 = unknownd0.unknown0c;
        unknownf0[i].unknown00 = unknownd0.unknown04;
      }
      return;
    }
  }
  unknownf0[unknownf8].unknown04 = unknownd0.unknown0c;
  unknownf0[unknownf8].unknown00 = unknownd0.unknown04;
  unknownf8++;
}

void DrMdoCtlMpfAuto::changeMemAutoMpf(const u8 *data, const u8 *autoData) {
  unknown00 = reinterpret_cast<const unknown001 *>(autoData);
  unknown08 = reinterpret_cast<const unknown510 *>(data + unknown00->unknown04);
  unknown58 = unknown50;
  if (unknown00->unknown5c == 0) {
    unknown50->unknown10 = data + unknown00->unknown08;
    unknown58->unknown18 = data + unknown00->unknown0c;
    unknown58->unknown20 = data + unknown00->unknown10;
    unknown58->unknown28 = data + unknown00->unknown14;
    unknown58->unknown30 = data + unknown00->unknown18;
    unknown38 = unknown58->unknown30;
    if (unknown00->unknown1c == 0) {
      unknown58->m_mdsMpfAutoTree = nullptr;
    } else {
      unknown58->m_mdsMpfAutoTree = reinterpret_cast<const MdsMpfAutoTree *>(data + unknown00->unknown1c);
    }
    unknown58->unknown40 = reinterpret_cast<const u32 *>(data + unknown00->unknown20);
    unknown58->unknown48 = reinterpret_cast<const u32 *>(data + unknown00->unknown24);
    unknown58->unknown50 = reinterpret_cast<const unknown515 *>(data + unknown00->unknown28);
    if (unknown00->unknown40 == 0 || unknown00->unknown3c != -0xd) {
      unknown58->m_mdsMpfAutoPosData = nullptr;
      return;
    }
    unknown58->m_mdsMpfAutoPosData = reinterpret_cast<const MdsMpfAutoPosData *>(data + unknown00->unknown40);
    unknown58->m_mdsMpfAutoPosTree = reinterpret_cast<const MdsMpfAutoPosTree *>(data + unknown00->unknown44);
    unknown58->unknown68 = reinterpret_cast<const u32 *>(data + unknown00->unknown48);
    unknown30 = unknown58->unknown68;
    unknown10 = data + unknown00->unknown50;
    unknown18 = data + unknown00->unknown54;
    unknown20 = data + unknown00->unknown58;
    m_mdsMpfAutoHlvPoliTree = reinterpret_cast<const MdsMpfAutoHlvPoliTree *>(data + unknown00->unknown4c);
  } else {
    if (unknown00->unknown4c == 0) {
      return;
    }
    if (unknown00->unknown3c != -0xd) {
      return;
    }
    unknown38 = data + unknown00->unknown18;
    unknown30 = reinterpret_cast<const u32 *>(data + unknown00->unknown48);
    unknown10 = data + unknown00->unknown50;
    unknown18 = data + unknown00->unknown54;
    unknown20 = data + unknown00->unknown58;
    m_mdsMpfAutoHlvPoliTree = reinterpret_cast<const MdsMpfAutoHlvPoliTree *>(data + unknown00->unknown4c);
  }
}

int DrMdoCtlMpfAuto::calcWorkSize(const u8 *autoData) {
  const unknown001 *header = reinterpret_cast<const unknown001 *>(autoData);
  int size = header->unknown5c == 0 ? 0x78 : 0;
  size += header->unknown00 * 0x10;
  size += 0x50;
  // The game rounds the size up to 16 bytes twice (0x71007f8bb8: two signed remainders by 16 each time), once after the fixed part and once after the
  // second per-object part. The helper is inlined and matches; the statement written out twice matches as well.
  size = unknown113(size);
  size += header->unknown00 * 0x10;
  return unknown113(size);
}

// Stocks the current point in the work list whose mean height is within the tolerance (0x71007fd6ac); a list that reaches its limit is moved to a free block by
// setHeMemWork. The limit test multiplies the count by sizeof(DrMdoCtlMpfAuto) (0x170, the distance between the auto and instance mpf objects in the work block of
// DrResMdoSeamWrkMpf::setupWork, 0x710088afc4 / 0x710088afcc) and compares it with the size of a calculation table (_MPFWorkAutoPos, 0x600; the tables at 0x108 are
// the ones DrMdoMpfMan::getTempCalcTbl hands out, 0x71007fd978). The game does it as a 64-bit unsigned value (ldrsw, mul x, cmp #1536).
bool DrMdoCtlMpfAuto::StockWorkPoint() {
  if (unknown100 == 0) {
    unknown130[0] = unknownd0.unknown04;
    *unknown108[0] = unknownd0;
    unknown144[0] = 1;
    unknown100++;
    return false;
  }
  unknown100++;
  for (int i = 0; i < unknown104; i++) {
    if (__builtin_fabsf(unknownd0.unknown04 - unknown130[i]) <= unknownfc) {
      f32 ratio = 1.0f / static_cast<f32>(unknown144[i] + 1);
      unknown130[i] = unknownd0.unknown04 * ratio + unknown130[i] * (1.0f - ratio);
      unknown108[i][unknown144[i]] = unknownd0;
      unknown144[i]++;
      if (unknown144[i] * sizeof(DrMdoCtlMpfAuto) >= sizeof(_MPFWorkAutoPos)) {
        return setHeMemWork(i);
      }
      return false;
    }
  }
  if (unknown104 > 4) {
    return false;
  }
  unknown130[unknown104] = unknownd0.unknown04;
  *unknown108[unknown104] = unknownd0;
  unknown144[unknown104] = 1;
  unknown104++;
  return false;
}

} // namespace ml
