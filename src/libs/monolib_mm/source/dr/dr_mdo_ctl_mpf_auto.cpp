#include "dr/dr_mdo_ctl_mpf_auto.h"

#include "dr/dr_mdo_mpf_man.h"
#include "dr/dr_mpf_work_auto_inf.h"
#include "mm_math/mm_vec3.h"

namespace ml {

DrMdoCtlMpfAuto::DrMdoCtlMpfAuto() : unknown68(0), unknown6c(0), unknown70(0), unknown80(0), unknown84(0), unknownd8(0) {
  unknownd0 = 0;
  unknown00 = nullptr;
  unknown28 = 0;
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

} // namespace ml
