#include "gf/field/gf_field_undulator.h"

#include <math.h>

#include "bdat.h"
#include "framework/reference_frame.h"
#include "fw/fw_transform.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"

namespace gf {

void GfFieldUndulator::BdatInfo::create(int id) {
  u8 *bdat = GfDataBdat::getFP(BDAT_RSC_EN_UND);
  unknown00 = Bdat::getFlagVal(bdat, "Flag", id, "UndX") != 0;
  unknown01 = Bdat::getFlagVal(bdat, "Flag", id, "UndZ") != 0;
  unknown04 = static_cast<s8>(Bdat::getValCheck(bdat, "UndMinX", id, 4)) * 0.017453292f;
  unknown08 = static_cast<s8>(Bdat::getValCheck(bdat, "UndMaxX", id, 4)) * 0.017453292f;
  unknown0c = static_cast<s8>(Bdat::getValCheck(bdat, "UndMinZ", id, 4)) * 0.017453292f;
  unknown10 = static_cast<s8>(Bdat::getValCheck(bdat, "UndMaxZ", id, 4)) * 0.017453292f;
  u8 deg = Bdat::getValCheck(bdat, "UndDeg", id, 1);
  unknown14 = static_cast<f32>(deg) * 0.0017453292f;
}

void GfFieldUndulator::create(const CreateInfo &info) {
  m_bdatInfo.unknown01 = false;
  m_bdatInfo.unknown00 = false;
  m_createInfo = info;
  u16 paramId = Bdat::getValCheck(GfDataBdat::getFP(BDAT_CHR_EN_ARRANGE), "ParamID", info.unknown00, 2);
  u32 resourceId = static_cast<u16>(Bdat::getValCheck(GfDataBdat::getFP(BDAT_CHR_EN_PARAM), "ResourceID", paramId, 2));
  u8 undulation = Bdat::getValCheck(GfDataBdat::getFP(BDAT_RSC_EN), "Unduration", resourceId, 1);
  m_bdatInfo.create(undulation);
}

void GfFieldUndulator::dispose() {
  m_bdatInfo.unknown00 = false;
  m_bdatInfo.unknown01 = false;
}

void GfFieldUndulator::apply(mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame) {
  // The game (0x7100340b30) writes the pitch and the roll blocks out twice. A shared helper taking the angle and the two limits gives 212 instructions against the game's 214
  // (the clamp compare comes out swapped at +0x98, 0x7100340bc8); three ways of writing the clamp tried.
  fw::Transform &world = frame->unknown003();
  f32 pitch;
  if (!m_bdatInfo.unknown00) {
    pitch = atan2f(unknown30.z, unknown30.y);
  } else {
    f32 angle = atan2f(unknown20.z, unknown20.y);
    if (fabsf(angle) < m_bdatInfo.unknown04) {
      pitch = 0.0f;
    } else {
      pitch = angle;
      if (m_bdatInfo.unknown08 < fabsf(angle)) {
        pitch = angle > 0.0f ? m_bdatInfo.unknown08 : -m_bdatInfo.unknown08;
      }
    }
  }
  f32 roll;
  if (!m_bdatInfo.unknown01) {
    roll = atan2f(-unknown30.x, unknown30.y);
  } else {
    f32 angle = atan2f(-unknown20.x, unknown20.y);
    if (fabsf(angle) < m_bdatInfo.unknown0c) {
      roll = 0.0f;
    } else {
      roll = angle;
      if (m_bdatInfo.unknown10 < fabsf(angle)) {
        roll = angle > 0.0f ? m_bdatInfo.unknown10 : -m_bdatInfo.unknown10;
      }
    }
  }
  mm::Quat rotation;
  mm::unknown005(rotation, mm::Vec3(pitch, 0.0f, roll));
  world.unknown10 = mm::Quat::mul(rotation, world.unknown10);
}

} // namespace gf
