#include "dr/dr_mdo_ctl_mpf_auto.h"

#include "dr/dr_mdo_mpf_man.h"
#include "dr/dr_mpf_work_auto_inf.h"
#include "mm_math/mm_vec3.h"

namespace ml {

DrMdoCtlMpfAuto::DrMdoCtlMpfAuto() : unknown68(0), unknown6c(0), unknown70(0), unknown80(0), unknown84(0) {
  unknownd8 = 0.0f;
  unknownd0 = 0.0f;
  unknownd4 = 0.0f;
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
    if (unknown58->unknown08 > unknownd0 || unknown58->unknown00 < unknownd0 || unknown58->unknown0c > unknownd8 || unknown58->unknown04 < unknownd8) {
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
    if (unknown58->unknown08 > unknownd0 || unknown58->unknown00 < unknownd0 || unknown58->unknown0c > unknownd8 || unknown58->unknown04 < unknownd8) {
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
    f32 difference = unknownd4 - unknownf0[i].unknown00;
    if (difference < 2.0f && difference > -2.0f) {
      if (difference > 0.0f) {
        unknownf0[i].unknown04 = unknowndc;
        unknownf0[i].unknown00 = unknownd4;
      }
      return;
    }
  }
  unknownf0[unknownf8].unknown04 = unknowndc;
  unknownf0[unknownf8].unknown00 = unknownd4;
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

} // namespace ml
