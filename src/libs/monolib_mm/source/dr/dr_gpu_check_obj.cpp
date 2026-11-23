#include "dr/dr_gpu_check_obj.h"

#include "dr/dr_calc_view_work.h"
#include "dr/dr_gpu_check_render.h"
#include "dr/dr_man.h"
#include "dr/dr_mdl_man.h"
#include "mm_math/mm_vec3.h"

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
  unknown72 = 0;
  if (isWorld) {
    unknown3c = FLAG_UNKNOWN_6;
  }
}

DrGpuCheckObj::~DrGpuCheckObj() { m_cGLibOcclusionQuery.release(); }

void DrGpuCheckObj::release() { unknown3c |= 0x100 << DrMan::s_nDblStockIdx; }

bool DrGpuCheckObj::isRender() const { return (unknown3c & FLAG_UNKNOWN_4) != 0; }

void DrGpuCheckObj::setPause(bool isPause) {
  if (isPause) {
    unknown3c |= FLAG_UNKNOWN_7;
  } else {
    unknown3c &= ~FLAG_UNKNOWN_7;
  }
}

u32 DrGpuCheckObj::isDeleteCall() const { return unknown3c & (0x100 << DrMan::s_nDblIdx); }

// The game reads the x and y of the position with one 64-bit load and z with a second one in setPos (0x710086d0b8) and
// setWorldPos (0x710086d0e0): the position is copied into a local before the components are stored (the whole-vector copy
// is what produces the paired load).
void DrGpuCheckObj::setPos(const mm::Vec3 &position, f32 radius) {
  unknown3c |= 1 << DrMan::s_nDblStockIdx;
  mm::Vec3 pos = position;
  unknown40[DrMan::s_nDblStockIdx].unknown00 = pos.x;
  unknown40[DrMan::s_nDblStockIdx].unknown04 = pos.y;
  unknown40[DrMan::s_nDblStockIdx].unknown08 = pos.z;
  unknown40[DrMan::s_nDblStockIdx].unknown0c = radius;
}

void DrGpuCheckObj::setWorldPos(const mm::Vec3 &position, f32 radius) {
  mm::Vec3 pos = position;
  unknown60.unknown00 = pos.x;
  unknown60.unknown04 = pos.y;
  unknown60.unknown08 = pos.z;
  unknown60.unknown0c = radius;
  if (DrMan::get()->m_drMdlMan->m_drGpuCheckRender->m_drCalcViewWork->unknown9aa) {
    unknown70 = 3;
    unknown3c |= FLAG_UNKNOWN_4;
  }
}

void DrGpuCheckObj::render() {
  if (unknown3c & FLAG_UNKNOWN_5) {
    DrGpuCheckRender *checkRender = DrMan::get()->m_drMdlMan->m_drGpuCheckRender;
    m_cGLibOcclusionQuery.beginQuery();
    if (unknown3c & FLAG_UNKNOWN_6) {
      checkRender->render(unknown38, 2);
    } else {
      checkRender->render(unknown38, 1);
    }
    m_cGLibOcclusionQuery.endQuery();
    unknown3c |= 4 << DrMan::s_nDblIdx;
  }
}

} // namespace ml
