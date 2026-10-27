#include "dr/dr_gpu_check_obj.h"

#include "dr/dr_man.h"

namespace ml {

DrGpuCheckObj::DrGpuCheckObj(int type, bool isWorld) : unknown08(nullptr), unknown10(nullptr), unknown18(type) {
  unknown38 = 0;
  unknown3c = 0;
  unknown40[0].unknown00 = 0;
  unknown40[0].unknown04 = 0;
  unknown40[0].unknown08 = 0.0f;
  unknown40[0].unknown0c = 1.0f;
  unknown40[1].unknown00 = 0;
  unknown40[1].unknown04 = 0;
  unknown40[1].unknown08 = 0.0f;
  unknown40[1].unknown0c = 1.0f;
  unknown60.unknown00 = 0;
  unknown60.unknown04 = 0;
  unknown60.unknown08 = 0.0f;
  unknown60.unknown0c = 1.0f;
  unknown70 = 3;
  if (isWorld) {
    unknown3c = 0x40;
  }
}

DrGpuCheckObj::~DrGpuCheckObj() { unknown20.release(); }

void DrGpuCheckObj::release() { unknown3c |= 0x100 << DrMan::s_nDblStockIdx; }

bool DrGpuCheckObj::isRender() const { return (unknown3c & FLAG_RENDER) != 0; }

void DrGpuCheckObj::setPause(bool isPause) {
  if (isPause) {
    unknown3c |= FLAG_PAUSE;
  } else {
    unknown3c &= ~FLAG_PAUSE;
  }
}

u32 DrGpuCheckObj::isDeleteCall() const { return unknown3c & (0x100 << DrMan::s_nDblIdx); }

} // namespace ml
