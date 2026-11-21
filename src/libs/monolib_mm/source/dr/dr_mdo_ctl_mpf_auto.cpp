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
  unknown28 = nullptr;
}

DrMdoCtlMpfAuto::~DrMdoCtlMpfAuto() { autoMpfRelease(); }

void DrMdoCtlMpfAuto::autoMpfRelease() {
  if (unknown00 != nullptr) {
    int count = unknown00->unknown00;
    for (int i = 0; i < count; i++) {
      _MPFWorkAutoInf *work = unknown158[i];
      while (work != nullptr) {
        _MPFWorkAutoInf *next = work->unknown28;
        unknown168->freeMemWork(work);
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
  _MPFWorkAutoInf *minWork = unknown168->unknownf0;
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
    gridTreeColiCalc(unknown58->unknown38);
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
    if (unknown58->unknown38 != nullptr) {
      gridTreeColiCalc(unknown58->unknown38);
    }
    if (unknown58->unknown58 != nullptr) {
      seachInstTree(unknown58->unknown60);
    }
  }
  StockPoint();
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
      if (buff->unknown38 != nullptr) {
        if (gridColiRangeChk(buff->unknown38)) {
          return true;
        }
        if (buff->unknown58 != nullptr) {
          if (gridColiInstPosRangeChk(buff->unknown60)) {
            return true;
          }
        }
      } else if (gridColiInstPosRangeChk(buff->unknown60)) {
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
      unknown58->unknown38 = nullptr;
    } else {
      unknown58->unknown38 = reinterpret_cast<const MdsMpfAutoTree *>(data + unknown00->unknown1c);
    }
    unknown58->unknown40 = reinterpret_cast<const u32 *>(data + unknown00->unknown20);
    unknown58->unknown48 = reinterpret_cast<const u32 *>(data + unknown00->unknown24);
    unknown58->unknown50 = reinterpret_cast<const f32 *>(data + unknown00->unknown28);
    if (unknown00->unknown40 == 0 || unknown00->unknown3c != -0xd) {
      unknown58->unknown58 = nullptr;
      return;
    }
    unknown58->unknown58 = reinterpret_cast<const MdsMpfAutoPosData *>(data + unknown00->unknown40);
    unknown58->unknown60 = reinterpret_cast<const MdsMpfAutoPosTree *>(data + unknown00->unknown44);
    unknown58->unknown68 = reinterpret_cast<const u32 *>(data + unknown00->unknown48);
    unknown30 = unknown58->unknown68;
    unknown10 = data + unknown00->unknown50;
    unknown18 = data + unknown00->unknown54;
    unknown20 = data + unknown00->unknown58;
    unknown28 = reinterpret_cast<const MdsMpfAutoHlvPoliTree *>(data + unknown00->unknown4c);
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
    unknown28 = reinterpret_cast<const MdsMpfAutoHlvPoliTree *>(data + unknown00->unknown4c);
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
