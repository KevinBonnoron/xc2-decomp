#include "gf/game/salvage/gf_game_salvage.h"

#include "bdat.h"
#include "framework/sound/sound_manager.h"
#include "fw/fw_camera.h"
#include "fw/fw_pad.h"
#include "gf/camera/gimmick/gf_camera_gimmick.h"
#include "gf/data/gf_data_map.h"
#include "gf/data/gf_data_util.h"
#include "gf/data/gf_game_flag.h"
#include "gf/event/gf_event.h"
#include "gf/event/gf_evt_model.h"
#include "gf/field/gf_field_sound.h"
#include "gf/game/event/gf_game_event.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_speed.h"
#include "gf/game/gf_game_util.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/behavior/gf_com_behavior_salvage.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/request/gf_req_scom.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_form.h"
#include "gmk/gmk_form_impl.h" // IWYU pragma: keep (the game instantiates GmkForm::create<GmkFormPc, GmkFormPcnpc> in this unit, after applyPartyForm, at 0x710037c27c)
#include "gmk/gmk_form_pc.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_salvage.h"
#include "gmk/gmk_set.h"
#include "ml/dev_pad.h"
#include "ml/rand.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/reference_object.h"

namespace fw {
enum SoundCategory : int;
} // namespace fw

namespace gf {

constexpr u32 POINT_UNKNOWN_255 = 0xff;                 // Inferred role: salvager point max; original name unknown.
constexpr int SE_UNKNOWN_600 = 600;                     // Inferred role: se climb base; original name unknown.
constexpr u16 SCENARIO_CHASE_KIKU_UNKNOWN_4029 = 0xfbd; // Inferred role: scenario chase kiku start; original name unknown.
constexpr u16 SCENARIO_CHASE_KIKU_UNKNOWN_4041 = 0xfc9; // Inferred role: scenario chase kiku end; original name unknown.

static const char *unknown014[] = {
    // Inferred role: camera names; original name unknown.
    nullptr,
    "salvage_dive_start",
    "salvage_dive_success",
    "salvage_dive_great_success",
    "salvage_dive_failure",
    "salvage_climb00",
    "salvage_climb01",
    "salvage_climb02",
    "salvage_climb03",
};

GfGameSalvage::GfGameSalvage(const GfSetupParam &param)
    : unknown08(getAllocator(ALLOCATOR_UNKNOWN_0)), unknowna0(false), unknownb0(0), unknownb4(0), unknownc0(nullptr), unknownc8(nullptr), m_climbAnimationType(ANIMATION_UNKNOWN_5), unknownd4(0),
      unknownd8(0) {
  initialize(param);
}

void GfGameSalvage::initialize(const GfSetupParam &) {
  unknown08.beginSetup(this, STATE_MAX);
  unknown08.registerState<StateSalvageWait>(STATE_UNKNOWN_0);
  unknown08.registerState<StateSalvageTBoxCheck>(STATE_UNKNOWN_1);
  unknown08.registerState<StateSalvageErrorMessage>(STATE_UNKNOWN_2);
  unknown08.registerState<StateSalvageItemSelect>(STATE_UNKNOWN_3);
  unknown08.registerState<StateSalvageSetupFadeOut>(STATE_UNKNOWN_4);
  unknown08.registerState<StateSalvageLoad>(STATE_UNKNOWN_5);
  unknown08.registerState<StateSalvageSetupFadeIn>(STATE_UNKNOWN_6);
  unknown08.registerState<StateSalvageSkillCheck>(STATE_UNKNOWN_7);
  unknown08.registerState<StateSalvageStartVoice>(STATE_UNKNOWN_8);
  unknown08.registerState<StateSalvageDiveStart>(STATE_UNKNOWN_9);
  unknown08.registerState<StateSalvageDiveWait>(STATE_UNKNOWN_10);
  unknown08.registerState<StateSalvageDiveEnd>(STATE_UNKNOWN_11);
  unknown08.registerState<StateSalvageDiveFadeOut>(STATE_UNKNOWN_12);
  unknown08.registerState<StateSalvageDiveFadeWait>(STATE_UNKNOWN_13);
  unknown08.registerState<StateSalvageDiveFadeIn>(STATE_UNKNOWN_14);
  unknown08.registerState<StateSalvageClimbStart>(STATE_UNKNOWN_15);
  unknown08.registerState<StateSalvageResult>(STATE_UNKNOWN_16);
  unknown08.registerState<StateSalvageResultUi>(STATE_UNKNOWN_17);
  unknown08.registerState<StateSalvagePartyFormDelay>(STATE_UNKNOWN_18);
  unknown08.registerState<StateSalvageCamWait>(STATE_UNKNOWN_19);
  unknown08.registerState<StateSalvageFinish>(STATE_UNKNOWN_20);
  unknown08.endSetup();
  unknown08.setState(STATE_UNKNOWN_0);
  unknowna0 = true;
}

GfGameSalvage::~GfGameSalvage() {}

void GfGameSalvage::build(const GfSetupParam &param) {
  // __LINE__ must be 160 as in the original file: its value changes the instruction order.
#line 160
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfGameSalvage(param);
}

void GfGameSalvage::destroy() {
  GfGameSalvage *salvage = get();
  salvage->finalize();
  delete salvage;
}

void GfGameSalvage::finalize() {
  unknown08.cleanup();
  unknowna0 = false;
}

bool GfGameSalvage::isInitialized() { return get() != nullptr && get()->unknowna0; }

void GfGameSalvage::update(const fw::UpdateInfo &info) {
  if (get() != nullptr) {
    get()->unknown08.update(&info);
  }
}

void GfGameSalvage::startSalvage(GF_OBJ_HANDLE *handle) {
  get()->unknowna8 = handle;
  if (GfGameManager::getState() == GF_STATE_UNKNOWN_11 && !GfGameManager::isBattle() && get()->unknown08.getState()->unknown08 == STATE_UNKNOWN_0) {
    get()->unknown08.setState(STATE_UNKNOWN_1);
  }
}

bool GfGameSalvage::isStateWait() { return get()->unknown08.getState()->unknown08 == STATE_UNKNOWN_0; }

void GfGameSalvage::cancelSalvage() {}

void GfGameSalvage::createCameraDive(AnimationType animation, const mm::Vec3 &position, f32 rotation) {
  fw::CameraManager *manager = fw::CameraManager::get();
  unknown88 = GimmickCamera::create(unknown014[animation], position, rotation);
  static_cast<GimmickCamera *>(unknown88.get())->setAuto(false);
  manager->unknown20[0].push(unknown88, 0.0f);
}

void GfGameSalvage::createCameraClimb(AnimationType animation, const mm::Vec3 &position, f32 rotation) {
  fw::CameraManager *manager = fw::CameraManager::get();
  unknown90 = GimmickCamera::create(unknown014[animation], position, rotation);
  static_cast<GimmickCamera *>(unknown90.get())->setAuto(false);
  manager->unknown20[0].push(unknown90, 0.0f);
}

void GfGameSalvage::createCameraCut01(const mm::Vec3 &position, f32 rotation) {
  unknown98 = GimmickCamera::create("salvage_cut01", position, rotation);
  static_cast<GimmickCamera *>(unknown98.get())->setAuto(false);
}

void GfGameSalvage::destroyCameraDiveStart() {
  fw::CameraManager *manager = fw::CameraManager::get();
  if (unknown80.get() != nullptr && unknown80.get()->unknowna0) {
    manager->unknown20[0].pop(unknown80, 0.0f);
  }
  unknown80 = nullptr;
}

void GfGameSalvage::destroyCameraDive() {
  fw::CameraManager *manager = fw::CameraManager::get();
  if (unknown88.get() != nullptr && unknown88.get()->unknowna0) {
    manager->unknown20[0].pop(unknown88, 0.0f);
  }
  unknown88 = nullptr;
}

void GfGameSalvage::destroyCameraClimb() {
  fw::CameraManager *manager = fw::CameraManager::get();
  if (unknown90.get() != nullptr && unknown90.get()->unknowna0) {
    manager->unknown20[0].pop(unknown90, 0.0f);
  }
  unknown90 = nullptr;
}

void GfGameSalvage::destroyCameraCut01() {
  fw::CameraManager *manager = fw::CameraManager::get();
  if (unknown98.get() != nullptr && unknown98.get()->unknowna0) {
    manager->unknown20[0].pop(unknown98, 1.0f);
  }
  unknown98 = nullptr;
}

void GfGameSalvage::playCameraDiveStart() {
  GimmickCamera *camera = static_cast<GimmickCamera *>(unknown80.get());
  if (camera != nullptr && camera->unknowna0) {
    camera->play();
  }
}

void GfGameSalvage::playCameraDive() {
  GimmickCamera *camera = static_cast<GimmickCamera *>(unknown88.get());
  if (camera != nullptr && camera->unknowna0) {
    camera->play();
  }
}

void GfGameSalvage::playCameraClimb() {
  GimmickCamera *camera = static_cast<GimmickCamera *>(unknown90.get());
  if (camera != nullptr && camera->unknowna0) {
    camera->play();
  }
}

void GfGameSalvage::playCameraCut01() {
  if (unknown98.get() != nullptr && !unknown98.get()->unknowna0) {
    fw::CameraManager::get()->unknown20[0].push(unknown98, 0.0f);
    if (unknown98.get() != nullptr) {
      static_cast<GimmickCamera *>(unknown98.get())->play();
    }
  }
}

bool GfGameSalvage::isCameraDiveStartEnd() {
  GimmickCamera *camera = static_cast<GimmickCamera *>(unknown80.get());
  if (camera != nullptr && camera->unknowna0) {
    return camera->isPlayEnd();
  }
  return true;
}

bool GfGameSalvage::isCameraDiveEnd() {
  GimmickCamera *camera = static_cast<GimmickCamera *>(unknown88.get());
  if (camera != nullptr && camera->unknowna0) {
    return camera->isPlayEnd();
  }
  return true;
}

bool GfGameSalvage::isCameraClimbEnd() {
  GimmickCamera *camera = static_cast<GimmickCamera *>(unknown90.get());
  if (camera != nullptr && camera->unknowna0) {
    return camera->isPlayEnd();
  }
  return true;
}

bool GfGameSalvage::isCameraCut01End() {
  GimmickCamera *camera = static_cast<GimmickCamera *>(unknown98.get());
  if (camera != nullptr && camera->unknowna0) {
    return camera->isPlayEnd();
  }
  return true;
}

bool GfGameSalvage::isCameraDive() {
  GimmickCamera *camera = static_cast<GimmickCamera *>(unknown88.get());
  if (camera != nullptr && camera->unknowna0) {
    return camera->isLoaded();
  }
  return true;
}

u8 *GfGameSalvage::getBindedBdatFp() const { return gmk::getBindedGmkInst(get()->unknowna8)->getBindedBdatFp(); }

int GfGameSalvage::getBindedBdatId() const { return gmk::getBindedGmkInst(get()->unknowna8)->unknown20.unknown18; }

namespace {

// Inferred role: traverser telling whether a treasure box of a salvage point near a position is waiting to be opened; original name unknown.
class unknown003 {
public:
  explicit unknown003(const mm::Vec3 &position) : unknown08(position), unknown10(false) {}

  void onTraverse(const gmk::AGmkBase &gmk) {
    const gmk::GmkSalvage &salvage = static_cast<const gmk::GmkSalvage &>(gmk);
    const mm::Vec3 &position = salvage.unknown08.unknown08->unknown00;
    f32 x = position.x - unknown08.x;
    f32 y = position.y - unknown08.y;
    f32 z = position.z - unknown08.z;
    if (x * x + y * y + z * z > 1.0f) {
      return;
    }
    u32 count = salvage.unknown88.size();
    for (u32 index = 0; index < count; index++) {
      const gmk::GmkSalvageLocator *locator = salvage.unknown88[index];
      if (locator != nullptr && locator->getData()->unknown00 == 2 && locator->unknownc0 != unknown020 && locator->unknownc8 == 0) {
        unknown10 = true;
        break;
      }
    }
  }

  const mm::Vec3 &unknown08;
  bool unknown10;
};

} // namespace

bool GfGameSalvage::isTboxExist() const {
  const mm::Vec3 &position = static_cast<gmk::GmkSalvage *>(gmk::getBindedGmkInst(get()->unknowna8))->unknown08.unknown08->unknown00;
  unknown003 traverser(position);
  mm::mtl::PtrSingleton<gmk::GmkManager>::get()->traverseGmkInst(gmk::GMK_TYPE_SALVAGE, traverser);
  return traverser.unknown10;
}

namespace {

// Inferred role: traverser disposing the treasure boxes of the salvage points near a position; original name unknown.
class unknown004 {
public:
  explicit unknown004(const mm::Vec3 &position) : unknown08(position) {}

  void onTraverse(const gmk::AGmkBase &gmk) {
    const gmk::GmkSalvage &salvage = static_cast<const gmk::GmkSalvage &>(gmk);
    const mm::Vec3 &position = salvage.unknown08.unknown08->unknown00;
    f32 x = position.x - unknown08.x;
    f32 y = position.y - unknown08.y;
    f32 z = position.z - unknown08.z;
    if (x * x + y * y + z * z > 1.0f) {
      return;
    }
    u32 count = salvage.unknown88.size();
    for (u32 index = 0; index < count; index++) {
      gmk::GmkSalvageLocator *locator = salvage.unknown88[index];
      if (locator != nullptr && locator->getData()->unknown00 == 2) {
        locator->unknownc8 = 0;
        locator->disposeGobInst(true);
      }
    }
  }

  const mm::Vec3 &unknown08;
};

} // namespace

void GfGameSalvage::execRaffle(const RaffleInfo &info) {
  gmk::GmkSalvage *salvage = static_cast<gmk::GmkSalvage *>(gmk::getBindedGmkInst(get()->unknowna8));
  gmk::GmkSalvage::RaffleInfo raffleInfo = {info.unknown00, info.unknown04, info.unknown08};
  salvage->createRaffle(raffleInfo);
  unknown004 traverser(salvage->unknown08.unknown08->unknown00);
  mm::mtl::PtrSingleton<gmk::GmkManager>::get()->traverseGmkInst(gmk::GMK_TYPE_SALVAGE, traverser);
}

void GfGameSalvage::execPop() { static_cast<gmk::GmkSalvage *>(gmk::getBindedGmkInst(get()->unknowna8))->popByRaffleResult(); }

bool GfGameSalvage::getEventOrigin(mm::Mat44 &matrix) const {
  gmk::GmkSalvage *salvage = static_cast<gmk::GmkSalvage *>(gmk::getBindedGmkInst(get()->unknowna8));
  if (salvage->unknowna8 != nullptr) {
    salvage->unknowna8->getMatrix(matrix, true);
    return true;
  }
  return false;
}

bool GfGameSalvage::getEventTbox(mm::Mat44 &matrix) const {
  const gmk::GmkSalvage *salvage = static_cast<const gmk::GmkSalvage *>(gmk::getBindedGmkInst(get()->unknowna8));
  gmk::GmkSalvageLocator *tbox = salvage->unknown88[0];
  if (tbox != nullptr) {
    tbox->getMatrix(matrix, true);
    return true;
  }
  return false;
}

bool GfGameSalvage::applyPartyForm() const {
  const gmk::GmkFormPc *formPc = static_cast<gmk::GmkSalvage *>(gmk::getBindedGmkInst(get()->unknowna8))->getGmkFormPc();
  if (formPc == nullptr) {
    return false;
  }
  gmk::GmkForm form(nullptr);
  bool result;
  if (form.create<gmk::GmkFormPc, gmk::GmkFormPcnpc>(*formPc)) {
    form.apply(4.0f);
    result = true;
  } else {
    result = false;
  }
  form.dispose();
  return result;
}

void GfGameSalvage::createModel() {
  if (unknownc0 == nullptr) {
    unknownc0 = GfGameEvent::createSalvage();
  }
}

void GfGameSalvage::destroyModel() { mm::mtl::safeRelease(unknownc0); }

bool GfGameSalvage::isValidModel() {
  if (unknownc0 != nullptr) {
    return unknownc0->isValid();
  }
  return false;
}

void GfGameSalvage::setModelTransform(const mm::Vec3 &position, f32 rotation) {
  if (unknownc0 != nullptr) {
    unknownc0->setTransform(position, rotation);
  }
}

static const char *const unknown001[] = {"S_idle",
                                         "C_salvage",
                                         "C_success",
                                         "C_greatsuccess",
                                         "C_failure",
                                         "C_result_00",
                                         "C_result_01",
                                         "C_result_02",
                                         "C_result_03",
                                         "C_result_04",
                                         "C_result_05"}; // Inferred role: animation names of AnimationType; original name unknown.

GfComAsm *GfGameSalvage::getGfComAsm() const {
  if (unknownc0 == nullptr) {
    return nullptr;
  }
  GfObjAcc acc(unknownc0->unknown20);
  if (acc.isValid()) {
    GfObj *obj = acc.getObj();
    if (obj == nullptr) {
      return nullptr;
    }
    return obj->getComponent<GfComAsm>();
  }
  return nullptr;
}

GfComBehaviorSalvage *GfGameSalvage::getGfComBehaviorSalvage() const {
  if (unknownc0 == nullptr) {
    return nullptr;
  }
  GfObjAcc acc(unknownc0->unknown20);
  if (acc.isValid()) {
    GfObj *obj = acc.getObj();
    if (obj == nullptr) {
      return nullptr;
    }
    return obj->getComponent<GfComBehaviorSalvage>();
  }
  return nullptr;
}

static const char *const unknown002[] = {"BtnChallenge0", "BtnChallenge1", "BtnChallenge2"}; // Inferred role: columns of the button challenges; original name unknown.

u32 GfGameSalvage::getButtonChallengeId(int index) {
  u8 *bdat = getBindedBdatFp();
  int id = getBindedBdatId();
  return static_cast<u16>(Bdat::getValCheck(bdat, unknown002[index], id, 2));
}

void GfGameSalvage::setPartyDisp(bool isDisp) {
  if (!isDisp) {
    GfGameParty::refreshPartyMemberPosition();
  }
  int max = GfGameParty::getHierarchyMax();
  for (int i = 1; i <= max; i++) {
    GfObjAcc acc(GfGameParty::getHandleByHierarchy(i));
    acc.setAlphaEvent(isDisp ? 1.0f : 0.0f);
  }
}

void GfGameSalvage::playAnimation(AnimationType animation) {
  GfComAsm *comAsm = getGfComAsm();
  if (comAsm != nullptr) {
    const char *name = unknown001[animation];
    if (name[0] == 'S') {
      comAsm->setState(name, ANIM_LAYER_UNKNOWN_0);
    } else {
      comAsm->execCmd(name, ANIM_LAYER_UNKNOWN_0);
    }
  }
}

void GfGameSalvage::playClimbReady() {
  if (unknownc0 != nullptr && unknownc0->unknown20 != unknown020) {
    playAnimation(m_climbAnimationType);
    GfGameSpeed::setSalvageCharacterSpeed(0.01f);
  }
}

void GfGameSalvage::playSE(SEID id) {
  if (fw::SoundManager::get() != nullptr && GfFieldSound::get() != nullptr) {
    fw::SoundManager::get()->playSe(id, GfFieldSound::get()->getCommonPack(), 1.0f, static_cast<fw::SoundCategory>(0));
  }
}

void GfGameSalvage::playDiveVibration() {
  if (unknownd8 != 0) {
    fw::PadManager::playVibration(ml::PadVibrationInfo(unknownd8));
  }
}

void GfGameSalvage::playClimb() {
  if (unknownc0 != nullptr) {
    GF_OBJ_HANDLE *handle = unknownc0->unknown20;
    if (handle != unknown020) {
      GfGameSpeed::setSalvageCharacterSpeed(1.0f);
      SCOM_SALVAGE_VOICE::createResult(handle, static_cast<CV_SALVAGE_RESULT>(unknownd4));
      playSE(static_cast<SEID>(SE_UNKNOWN_600 + m_climbAnimationType));
    }
  }
}

void GfGameSalvage::playVoice(VoiceType voice) {
  if (unknownc0 != nullptr) {
    GF_OBJ_HANDLE *handle = unknownc0->unknown20;
    if (handle != unknown020) {
      int random = ml::mtRand() % 2;
      int cv;
      switch (voice) {
      case VOICETYPE_UNKNOWN_0:
        cv = random;
        break;
      case VOICETYPE_UNKNOWN_1:
        cv = random + 2;
        break;
      case VOICETYPE_UNKNOWN_2:
        cv = random + 4;
        break;
      case VOICETYPE_UNKNOWN_3:
        cv = random + 6;
        break;
      case VOICETYPE_UNKNOWN_4:
        cv = 8;
        break;
      case VOICETYPE_UNKNOWN_5:
        cv = 9;
        break;
      case VOICETYPE_UNKNOWN_6:
        cv = random + 10;
        break;
      default:
        cv = 0;
        break;
      }
      unknownc8 = SCOM_SALVAGE_VOICE::create(handle, static_cast<CV_SALVAGE>(cv));
    }
  }
}

bool GfGameSalvage::isVoiceEnd() {
  if (unknownc8 != nullptr) {
    return SCOM_SALVAGE_VOICE::isPlayEnd(unknownc8);
  }
  return true;
}

GfGameSalvage::AnimationType GfGameSalvage::getClimbAnimationType() const { return m_climbAnimationType; }

void GfGameSalvage::playWireStart(f32 time, f32 speed, f32 length) {
  if (unknownc0 != nullptr) {
    GfGameUtil::startWireWithClose(unknownc0->unknown20, unknowna8, time, speed, length);
  }
}

void GfGameSalvage::addSalvagerPoint(u32 point) {
  if (point == 0) {
    return;
  }
  u32 current = GfGameFlag::getLocal(8, FLAG_UNKNOWN_2132);
  if (current < POINT_UNKNOWN_255) {
    u32 total = current + point;
    GfGameFlag::setLocal(8, FLAG_UNKNOWN_2132, total > POINT_UNKNOWN_255 ? POINT_UNKNOWN_255 : total);
  }
}

bool GfGameSalvage::isChaseKikuInSupervia() {
  if (GfGameManager::getMapID() == MAP_UNKNOWN_10) {
    u16 scenario = GfDataUtil::getScenarioFlag();
    return scenario >= SCENARIO_CHASE_KIKU_UNKNOWN_4029 && scenario <= SCENARIO_CHASE_KIKU_UNKNOWN_4041;
  }
  return false;
}

u32 GfGameSalvage::getTBoxNum() {
  RaffleRet ret;
  getRaffleResult(ret);
  return ret.unknown00;
}

void GfGameSalvage::createLog() {}

void GfGameSalvage::setLogSkill(bool, u32) {}

void GfGameSalvage::clearLogSkill() {}

void GfGameSalvage::setLogButtonChallenge(int, int) {}

void GfGameSalvage::clearLogButtonChallenge() {}

void GfGameSalvage::setLogButtonChallengeResult(int) {}

void GfGameSalvage::setLogLapsedTime(int) {}

} // namespace gf

template void mm::mtl::Delegate<void()>::memberFuncInvoker<gf::StateSalvageClimbStart>(const mm::mtl::Delegate<void()> *);
