#include "event/cam_eva_player.h"

#include "event/cam_base.h"
#include "event/data_manager.h"
#include "event/dof_manager.h"
#include "event/env_manager.h"
#include "event/memory_manager.h"
#include "gf/data/gf_data_map.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_math.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "rcha/rcha_cam.h"

namespace event {

CamEvaPlayer::CamEvaPlayer() : m_camBase(nullptr), m_rchaCam(nullptr) {}

CamEvaPlayer::~CamEvaPlayer() { stop(); }

void CamEvaPlayer::stop() {
  if (m_rchaCam != nullptr) {
    m_rchaCam->clear();
    if (m_rchaCam != nullptr) {
      delete m_rchaCam;
      m_rchaCam = nullptr;
    }
  }
  m_camBase = nullptr;
}

// Inferred helper: a Vec3 track of the rcha camera at a fractional frame, linearly interpolated between the two frames around it;
// original name unknown. Evidence: the interpolation is inlined in CamEvaPlayer::update (0x71000ad62c) for the position and the
// rotation; the same shape as the helpers of CharaEvaPlayer::update.
static mm::Vec3 unknown044(const RchaCam *rcha, bool (RchaCam::*get)(mm::Vec3 *, f32) const, f32 frame) {
  mm::Vec3 a;
  mm::Vec3 b;
  mm::Vec3 value;
  f32 base = static_cast<f32>(static_cast<int>(frame));
  f32 next = base + 1.0f;
  if (base == frame) {
    (rcha->*get)(&value, base);
  } else {
    (rcha->*get)(&a, base);
    (rcha->*get)(&b, next);
    value = a + (b - a) * (frame - base);
  }
  return value;
}

// Inferred helper: a scalar track of the rcha camera at a fractional frame, linearly interpolated between the two frames
// around it; original name unknown. Evidence: inlined in CamEvaPlayer::update (0x71000ad62c) for the fov, the DOF values and
// the time.
template <typename R> static f32 unknown045(const RchaCam *rcha, R (RchaCam::*get)(f32) const, f32 frame) {
  f32 base = static_cast<f32>(static_cast<int>(frame));
  f32 next = base + 1.0f;
  f32 a = (rcha->*get)(base);
  if (base == frame) {
    return a;
  }
  // The difference of the two frames is the last factor: the game subtracts `frame - base` after the second call (0x71000ad860:
  // fsub s0, s0, s15; fsub s1, s9, s10). With the factor first it is held across the call (641 instructions, deltaFrame kept in s12).
  return a + ((rcha->*get)(next)-a) * (frame - base);
}

void CamEvaPlayer::update(f32 deltaFrame) {
  if (m_rchaCam == nullptr) {
    return;
  }
  // The member is read into frame before the frame count is loaded (0x71000ad66c to 0x71000ad678: count, -1.0f, then the member);
  // `unknown18 < lastFrame ? unknown18 : lastFrame` loads the count first and the member after the add.
  f32 frame = unknown18;
  f32 lastFrame = static_cast<f32>(m_rchaCam->getFrameCount()) - 1.0f;
  frame = frame < lastFrame ? frame : lastFrame;
  // pos and rotation are declared first and assigned from the track: with the track as initialiser, pos gives 634 instructions against 646 and
  // rotation gives the right count with float phis (`ldp s1, s0` against the game's `ldp w10, w8`).
  mm::Vec3 pos;
  pos = unknown044(m_rchaCam, &RchaCam::getPos, frame);
  pos += unknown20;
  // The rotation is scaled where the track left it (0x71000ad7ec): the game keeps it in the integer phis of the track (`ldp w10, w8`
  // and `fmov s0, w10`) as for pos; a separate `rot` vector multiplied into `rotation` gets float phis (`ldp s0, s1`).
  mm::Vec3 rotation;
  rotation = unknown044(m_rchaCam, &RchaCam::getRot, frame);
  rotation *= mm::DEG_TO_RAD;
  mm::Vec3 look;
  f32 roll;
  getCamLook_roll(pos, rotation, m_rchaCam->getRotOrder(frame), look, roll);
  f32 fov = unknown045(m_rchaCam, &RchaCam::getFov, frame);
  if (m_camBase->isFocal()) {
    fov = CamUtil::toFocal(fov);
  }
  int nearfar = m_rchaCam->getNearFarType(frame);
  bool isEnableDOF = m_rchaCam->isEnableDOF(frame);
  f32 distance = unknown045(m_rchaCam, &RchaCam::getDistanceDOF, frame);
  f32 range = unknown045(m_rchaCam, &RchaCam::getRangeDOF, frame);
  f32 pixel = unknown045(m_rchaCam, &RchaCam::getPixelDOF, frame);
  f32 lens = unknown045(m_rchaCam, &RchaCam::getLensDOF, frame);
  f32 strength = unknown045(m_rchaCam, &RchaCam::getStrengthDOF, frame);
  f32 blend = unknown045(m_rchaCam, &RchaCam::getBlendDOF, frame);
  int pixelLv = m_rchaCam->getPixelLvDOF(frame);
  bool isHlv = m_rchaCam->isHlvDOF(frame);
  // The game calls isEnableMBlur, getMBlurStr, getMBlurSub, isSMapVis and isCamLgtStop (0x71000ad62c) and drops the results (ruling 5).
  m_rchaCam->isEnableMBlur(frame);
  unknown045(m_rchaCam, &RchaCam::getMBlurStr, frame);
  unknown045(m_rchaCam, &RchaCam::getMBlurSub, frame);
  f32 timeVal = unknown045(m_rchaCam, &RchaCam::getTimeVal, frame);
  bool isEnableTime = m_rchaCam->isEnableTime(frame);
  int weatherType = m_rchaCam->getWeatherType(frame);
  u32 weatherFrame = m_rchaCam->getWeatherFrame(frame);
  bool isEnableWeather = weatherType != 0 && m_rchaCam->isEnableWeather(frame);
  m_rchaCam->isSMapVis(frame);
  m_rchaCam->isCamLgtStop(frame);
  m_camBase->unknown10 = pos;
  m_camBase->unknown20 = look;
  m_camBase->unknown30 = fov;
  m_camBase->setRoll(roll);
  if (nearfar != 0 && unknown30 != nearfar) {
    setNearfar(static_cast<EVT_nearfar>(nearfar));
  }
  // The enabled arm is written first: with `if (!isEnableDOF)` first the position stores to the camera are an `stp` and the
  // inlined DofManager::play stores of the blend (0x71000add60: stp s14, s14) are two `str` (the only two differing lines).
  if (isEnableDOF) {
    mm::mtl::Singleton<DofManager>::getPtr()->play(1, distance, range, pixel, lens, strength, blend, pixelLv, isHlv, "");
  } else {
    mm::mtl::Singleton<DofManager>::getPtr()->stop();
  }
  if (isEnableWeather) {
    mm::mtl::Singleton<EnvManager>::getPtr()->setMapWeatherID(static_cast<gf::WEATHERID>(weatherType), weatherFrame);
  }
  if (isEnableTime) {
    mm::mtl::Singleton<EnvManager>::getPtr()->setClock(timeVal);
  }
  unknown18 += deltaFrame;
  if (static_cast<f32>(m_rchaCam->getFrameCount()) <= unknown18) {
    stop();
  }
}

void CamEvaPlayer::play(CamBase *cam, void *data, const mm::Vec3 &offset) {
  stop();
  m_rchaCam = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) RchaCam;
  m_camBase = cam;
  m_rchaCam->setup(mtl::ALLOC_HANDLE(), data);
  unknown18 = 0.0f;
  unknown20 = offset;
  unknown30 = static_cast<EVT_nearfar>(0);
}

void CamEvaPlayer::setNearfar(EVT_nearfar nearfar) {
  m_camBase->setNearFar(CamUtil::id2near(nearfar), CamUtil::id2far(nearfar));
  unknown30 = nearfar;
}

void CamEvaPlayer::getCamLook_roll(const mm::Vec3 &pos, const mm::Vec3 &rot, u32 rotOrder, mm::Vec3 &look, f32 &roll) const {
  mm::Mat44 mat;
  switch (rotOrder) {
  case 0:
    mat.unknown011(rot);
    break;
  case 1:
    mat.unknown018(rot);
    break;
  case 2:
    mat.unknown015(rot);
    break;
  case 3:
    mat.unknown019(rot);
    break;
  case 4:
    mat.unknown020(rot);
    break;
  case 5:
    mat.unknown021(rot);
    break;
  }
  mm::Vec3 v = DataManager::unknown001(mat, 0.0f, 0.0f, -10.0f);
  // Component by component: the game stores the three with `str` (0x71000ae044); `look = v` pairs two of them and does not match.
  look.x = v.x;
  look.y = v.y;
  look.z = v.z;
  look += pos;
  roll = mm::matrixToEuler(mat).z;
}

} // namespace event
