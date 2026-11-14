#include "gf/game/gf_game_voice.h"

#include <string.h>

#include "framework/lang_util.h"
#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/salvage/gf_salvage_voice.h"
#include "gf/gf_allocator.h"
#include "gf/gf_manager.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "gf/request/gf_req_scom.h"
#include "gf/sound/gf_sound.h"
#include "ml/rand.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/fixed_list.h" // IWYU pragma: keep
#include "mm_mtl/fixstr.h"

namespace fw {
enum SoundCategory : int;
} // namespace fw
namespace mm {
struct Vec3;
} // namespace mm

namespace gf {

namespace _gfgvo {

// The three constants keep the names of the game's symbols gf::_gfgvo::s_szVoicePath, s_szVoiceTest and s_szVoiceExt.
const char *s_szVoicePath = "/stream/voice/";
const char *s_szVoiceTest = "test/";
const char *s_szVoiceExt = ".wav";

} // namespace _gfgvo

namespace {

// Inferred role: middle number of the field voice name per CV_FIELD; original name unknown.
const u8 unknown001[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 2, 0};
// Inferred role: number of driver voice variations per CV_FIELD; original name unknown.
const u8 unknown002[] = {2, 1, 1, 2, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1};
// Inferred role: driver voice number per CV_FIELD; original name unknown.
const u8 unknown003[] = {50, 51, 52, 53, 54, 55, 57, 59, 1, 62, 64, 65, 66, 66, 66, 68, 70, 72, 73, 77, 78, 80, 82, 2, 2, 84, 85, 87, 88, 88, 95, 96, 96, 98, 98, 98, 65};
// Inferred role: number of blade voice variations per CV_FIELD; original name unknown.
const u8 unknown004[] = {2, 1, 1, 2, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1};
// Inferred role: blade voice number per CV_FIELD; original name unknown.
const u8 unknown005[] = {50, 51, 52, 53, 54, 56, 58, 59, 1, 61, 63, 65, 66, 66, 66, 67, 69, 71, 73, 79, 79, 81, 83, 2, 2, 84, 85, 86, 88, 88, 94, 97, 97, 98, 98, 98, 65};

} // namespace

class VoiceInfo {
public:
  class PJOB {
  public:
    PJOB(VoiceInfo *info) : unknown08(info) {}
    virtual ~PJOB() {}
    virtual bool exec() = 0;
    virtual const GfVoiceName *getName() { return nullptr; }
    virtual GAME_VOICE_HANDLE *getVoiceHandle() const { return nullptr; }

    VoiceInfo *unknown08; // Inferred role: owner; original member name unknown.
  };

  class PJOB_PLAY : public PJOB {
  public:
    PJOB_PLAY(VoiceInfo *info, GAME_VOICE_HANDLE *voiceHandle, const ParamObj &object, const GfVoiceName &name, CV_PRIO priority)
        : PJOB(info), m_voiceHandle(voiceHandle), unknown18(object), m_name(name), unknown44(priority) {}
    ~PJOB_PLAY() {}
    bool exec() override;
    const GfVoiceName *getName() override { return &m_name; }
    GAME_VOICE_HANDLE *getVoiceHandle() const override { return m_voiceHandle; }

    GAME_VOICE_HANDLE *m_voiceHandle;
    ParamObj unknown18; // Inferred role: object; original member name unknown.
    GfVoiceName m_name;
    CV_PRIO unknown44; // Inferred role: priority; original member name unknown.
  };

  class PJOB_STOP : public PJOB {
  public:
    PJOB_STOP(VoiceInfo *info, CV_PRIO priority) : PJOB(info), unknown10(priority) {}
    ~PJOB_STOP() {}
    bool exec() override;

    CV_PRIO unknown10; // Inferred role: priority; original member name unknown.
  };

  class PJOB_WAIT_STOP : public PJOB {
  public:
    PJOB_WAIT_STOP(VoiceInfo *info) : PJOB(info) {}
    ~PJOB_WAIT_STOP() {}
    bool exec() override;
  };

  VoiceInfo();
  void clear();
  void destroyJob();
  void update(const fw::UpdateInfo &info);
  void checkInvalid(const fw::UpdateInfo &info);
  bool isEmpty() const;
  bool isSoundValid() const;
  bool isEnableVoiceHandle(GAME_VOICE_HANDLE *voice) const;
  const GfVoiceName &getName() const;
  void applyPosition(const mm::Vec3 &position);
  void applyPause(const GfGameVoice::VoiceInfoPause &pause);
  void setPlayInfoStart(GAME_VOICE_HANDLE *voice, SoundHandle sound, const ParamObj &object, CV_PRIO priority);
  void setPlayInfoStop(CV_PRIO priority);
  void addPlay(GAME_VOICE_HANDLE *voice, const ParamObj &object, const GfVoiceName &name, CV_PRIO priority);
  void addPlay(GAME_VOICE_HANDLE *voice, const char *name, CV_PRIO priority);
  void addPlay(GAME_VOICE_HANDLE *voice, SoundHandle sound, const GfVoiceName &name);
  void addStop(CV_PRIO priority);
  void addWaitStop();

  bool unknown00;                            // Inferred role: waiting to play; original member name unknown.
  CV_PRIO unknown04;                         // Inferred role: priority; original member name unknown.
  u32 unknown08;                             // Inferred role: cleared by clear; original member name unknown.
  f32 unknown0c;                             // Inferred role: time since the play request; original member name unknown.
  ParamObj unknown10;                        // Inferred role: object; original member name unknown.
  SoundHandle unknown20;                     // Inferred role: sound; original member name unknown.
  GAME_VOICE_HANDLE *unknown28;              // Inferred role: voice handle; original member name unknown.
  mm::mtl::FixedQueue<PJOB *, 16> unknown30; // Inferred role: jobs; original member name unknown.
};

static_assert(offsetof(VoiceInfo, unknown04) == 0x04, "");
static_assert(offsetof(VoiceInfo, unknown0c) == 0x0c, "");
static_assert(offsetof(VoiceInfo, unknown10) == 0x10, "");
static_assert(offsetof(VoiceInfo, unknown20) == 0x20, "");
static_assert(offsetof(VoiceInfo, unknown28) == 0x28, "");
static_assert(offsetof(VoiceInfo, unknown30) == 0x30, "");
static_assert(sizeof(VoiceInfo) == 0xc0, "");
static_assert(sizeof(VoiceInfo::PJOB_PLAY) == 0x48, "");
static_assert(sizeof(VoiceInfo::PJOB_STOP) == 0x18, "");
static_assert(sizeof(VoiceInfo::PJOB_WAIT_STOP) == 0x10, "");

// Inferred role: tells whether a voice belongs to an object, by handle or by type and id; original name unknown.
inline bool unknown007(const ParamObj &voice, const ParamObj &object) {
  if (voice.unknown00 == unknown020) {
    return voice.unknown08 == object.unknown08 && voice.unknown0c == object.unknown0c;
  }
  return voice.unknown00 == object.unknown00;
}

// Inferred role: predicate selecting the voice of an object; original name unknown.
struct unknown008 {
  unknown008(const ParamObj &object) : unknown00(object) {}
  bool operator()(VoiceInfo *info) const { return unknown007(info->unknown10, unknown00); }

  ParamObj unknown00;
};

bool GfVoiceName::isValid() const { return unknown18 != 0; }

bool GfVoiceName::isHanaVoice(const char *name) {
  if (name == nullptr || strlen(name) < 9) {
    return false;
  }
  return static_cast<u8>(name[8]) > 0x60;
}

bool GfVoiceName::getVoicePath(mm::mtl::FixStr<16> &path) const {
  if (unknown18 == 0) {
    return false;
  }
  mm::mtl::FixStr<16> directory;
  if (unknown00.length() != 0) {
    int length = unknown18 != -1 ? unknown18 : unknown00.length();
    unknown00.unknown001(directory, 0, length);
  }
  path = directory;
  path += "/";
  return true;
}

bool GfVoiceName::isEnemyVoice() const {
  if (unknown18 > 0) {
    int id = getCharaId();
    return static_cast<u32>(id) - 0x65 < 0x3a;
  }
  return false;
}

int GfVoiceName::getCharaId() const {
  if (unknown18 > 0) {
    int id = 0;
    int scale = 1;
    for (int i = unknown18 - 1; i >= 0; i--, scale *= 10) {
      id += (static_cast<u8>(unknown00.c_str()[i]) - '0') * scale;
    }
    return id;
  }
  return 0;
}

u32 GfVoiceName::getObjType() const {
  u32 id = 0;
  if (unknown18 > 0) {
    id = getCharaId();
    if (id - 1 < 8) {
      return OBJECT_TYPE_PC;
    }
  }
  if (id - 0xb < 0x12) {
    return OBJECT_TYPE_BLADE;
  }
  if (id - 0x1f < 0x1c) {
    return OBJECT_TYPE_BLADE;
  }
  if (id - 0x3d < 0x20) {
    return OBJECT_TYPE_BLADE;
  }
  if (id >= 0x65) {
    return OBJECT_TYPE_ENEMY;
  }
  return OBJECT_TYPE_NONE;
}

int GfVoiceName::getVoiceId() const {
  if (unknown18 != 0) {
    int id = 0;
    int scale = 1;
    for (int i = unknown18 + 1; i >= unknown18; i--, scale *= 10) {
      id += (static_cast<u8>(unknown00.c_str()[i]) - '0') * scale;
    }
    return id;
  }
  return 0;
}

void GfVoiceName::addNumber2keta(mm::mtl::FixStr<16> &name, u32 number) {
  mm::mtl::FixStr<16> numberStr;
  if (number < 10) {
    numberStr.format("0%d", number);
  } else {
    numberStr.format("%d", number);
  }
  name += numberStr.c_str();
}

const char *GfVoiceName::getCharacterVoiceStr(GF_OBJ_HANDLE *handle) {
  DataParamAcc acc(handle);
  return acc.getVoiceStr();
}

GAME_VOICE_HANDLE *GfSalvageVoice::playResultVoice(GF_OBJ_HANDLE *handle, CV_SALVAGE_RESULT voice) {
  DataParamAcc acc(handle);
  if (acc.getObjType() == OBJECT_TYPE_PC && acc.getValidDriverId() == DRIVER_UNKNOWN_1) {
    mm::mtl::FixStr<16> name;
    name = acc.getVoiceStr();
    GfVoiceName::addNumber2keta(name, 60);
    GfVoiceName::addNumber2keta(name, 1);
    GfVoiceName::addNumber2keta(name, voice + 12);
    ParamObj object = {handle, 0, 0};
    return GfGameVoice::playVoice(object, name.c_str(), CV_PRIO_UNKNOWN_1);
  }
  return nullptr;
}

VoiceInfo::VoiceInfo() : unknown00(true), unknown04(CV_PRIO_UNKNOWN_0), unknown0c(0.0f), unknown10{unknown020, 0, 0}, unknown20(), unknown28(nullptr) { clear(); }

void VoiceInfo::clear() {
  if (unknown20.isValid()) {
    GfSound *sound = GfSound::get();
    if (sound != nullptr) {
      sound->stopVoice(unknown20, 0.0f);
    }
    unknown20.clear();
  }
  unknown04 = CV_PRIO_UNKNOWN_0;
  unknown28 = nullptr;
  unknown10 = {unknown020, 0, 0};
  unknown08 = 0;
  unknown0c = 0.0f;
  destroyJob();
  unknown00 = true;
}

void VoiceInfo::destroyJob() {
  // The game never advances the iterator (disassembly: the index is hoisted out of the loop, only the end is reloaded).
  for (mm::mtl::FixedQueue<PJOB *, 16>::iterator it = unknown30.begin(); it != unknown30.end();) {
    delete *it;
  }
  unknown30.clear();
}

void VoiceInfo::update(const fw::UpdateInfo &info) {
  for (mm::mtl::FixedQueue<PJOB *, 16>::iterator it = unknown30.begin(); it != unknown30.end();) {
    PJOB *job = *it;
    if (!job->exec()) {
      break;
    }
    delete job;
    it = unknown30.erase(it);
  }
  if (unknown20.isValid()) {
    GfObjAcc acc(unknown10.unknown00);
    if (acc.isValidTransform()) {
      applyPosition(acc.getWorldTransform().unknown00);
    }
  }
  unknown0c += info.unknown04;
}

bool VoiceInfo::isEmpty() const {
  if (unknown20.isValid()) {
    return false;
  }
  return unknown30.size() == 0;
}

void VoiceInfo::applyPause(const GfGameVoice::VoiceInfoPause &) { GfObjUtil::getObjLayer(unknown10.unknown00); }

const GfVoiceName &VoiceInfo::getName() const {
  static GfVoiceName s_empty("");
  for (PJOB *job : unknown30) {
    const GfVoiceName *name = job->getName();
    if (name != nullptr) {
      return *name;
    }
  }
  return s_empty;
}

bool VoiceInfo::isEnableVoiceHandle(GAME_VOICE_HANDLE *voice) const {
  if (voice != nullptr) {
    if (unknown28 == voice) {
      return true;
    }
    for (mm::mtl::FixedQueue<PJOB *, 16>::const_iterator it = unknown30.begin(); it != unknown30.end(); ++it) {
      if ((*it)->getVoiceHandle() == voice) {
        return true;
      }
    }
  }
  return false;
}

bool VoiceInfo::isSoundValid() const { return unknown20.isValid(); }

void VoiceInfo::applyPosition(const mm::Vec3 &) { unknown20.isValid(); }

// The __LINE__ of the operator new calls of addPlay, addStop and addWaitStop are 0x349, 0x351, 0x361 and 0x369 in the game.
void VoiceInfo::addPlay(GAME_VOICE_HANDLE *voice, const ParamObj &object, const GfVoiceName &name, CV_PRIO priority) {
  if (!unknown30.full()) {
    unknown10 = object;
#line 841
    unknown30.push(new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) PJOB_PLAY(this, voice, object, name, priority));
  }
}

void VoiceInfo::addPlay(GAME_VOICE_HANDLE *voice, const char *name, CV_PRIO priority) {
  if (!unknown30.full()) {
    unknown10 = {unknown020, 0, 0};
#line 849
    unknown30.push(new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) PJOB_PLAY(this, voice, unknown10, GfVoiceName(name), priority));
  }
}

void VoiceInfo::addPlay(GAME_VOICE_HANDLE *voice, SoundHandle sound, const GfVoiceName &) {
  unknown20 = sound;
  unknown28 = voice;
  unknown04 = CV_PRIO_UNKNOWN_3;
}

void VoiceInfo::addStop(CV_PRIO priority) {
  if (!unknown30.full() && unknown20.isValid()) {
#line 865
    unknown30.push(new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) PJOB_STOP(this, priority));
  }
}

void VoiceInfo::addWaitStop() {
  if (!unknown30.full() && unknown20.isValid()) {
#line 873
    unknown30.push(new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) PJOB_WAIT_STOP(this));
  }
}

bool VoiceInfo::PJOB_PLAY::exec() {
  GfSound *sound = GfSound::get();
  if (sound != nullptr) {
    DataParamAcc acc(unknown18);
    fw::SoundCategory category = acc.getObjType() == OBJECT_TYPE_ENEMY ? CATEGORY_ENE_VO : CATEGORY_VOICE;
    const mm::mtl::FixStr<16> &langPath = fw::LangUtil::getVoiceFolder();
    mm::mtl::FixStr<16> voicePath;
    GfGameVoice::getCharPath(voicePath, m_name.unknown00.c_str());
    mm::mtl::FixStr<128> path;
    path.format("%s%s/%s%s%s", _gfgvo::s_szVoicePath, langPath.c_str(), voicePath.c_str(), m_name.unknown00.c_str(), _gfgvo::s_szVoiceExt);
    SoundHandle handle = sound->playVoice(path.c_str(), 1.0f, false, category);
    unknown08->setPlayInfoStart(m_voiceHandle, handle, unknown18, unknown44);
  }
  return true;
}

bool VoiceInfo::PJOB_STOP::exec() {
  GfSound *sound = GfSound::get();
  if (sound != nullptr && unknown08->unknown20.isValid()) {
    sound->stopVoice(unknown08->unknown20, 0.0f);
    unknown08->setPlayInfoStop(unknown10);
  }
  return true;
}

bool VoiceInfo::PJOB_WAIT_STOP::exec() { return !unknown08->unknown20.isValid(); }

void GfGameVoice::build(const GfSetupParam &param) {
// __LINE__ of the operator new call is 0x78 in the game.
#line 120
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfGameVoice(param);
}

GfGameVoice::GfGameVoice(const GfSetupParam &param) : unknown08(false), unknown110(0) { initialize(param); }

GfGameVoice::~GfGameVoice() {}

void GfGameVoice::initialize(const GfSetupParam &) {
  for (int i = 0; i < 6; i++) {
#line 139
    VoiceInfo *info = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) VoiceInfo();
    unknown10.push_back(info);
  }
  unknown08 = true;
}

void GfGameVoice::destroy() {
  GfGameVoice *voice = get();
  voice->finalize();
  delete voice;
}

void GfGameVoice::finalize() {
  while (unknown10.size() != 6) {
    GfSleep(1);
  }
  for (mm::mtl::FixedList<VoiceInfo *, 6>::iterator it = unknown10.begin(); it != unknown10.end(); ++it) {
    if (*it != nullptr) {
      delete *it;
    }
  }
  unknown10.clear();
  unknown08 = false;
}

void GfGameVoice::update(const fw::UpdateInfo &info) {
  GfGameVoice *voice = get();
  for (mm::mtl::FixedList<VoiceInfo *, 6>::iterator it = voice->unknown90.begin(); it != voice->unknown90.end(); ++it) {
    (*it)->checkInvalid(info);
  }
  for (mm::mtl::FixedList<VoiceInfo *, 6>::iterator it = voice->unknown90.begin(); it != voice->unknown90.end();) {
    if ((*it)->isEmpty()) {
      voice->unknown10.push_back(*it);
      it = voice->unknown90.erase(it);
    } else {
      ++it;
    }
  }
  for (mm::mtl::FixedList<VoiceInfo *, 6>::iterator it = voice->unknown90.begin(); it != voice->unknown90.end(); ++it) {
    (*it)->update(info);
  }
}

VoiceInfo *GfGameVoice::getPlayInfo(const ParamObj &object) {
  if (object.unknown00 != unknown020 || object.unknown0c != 0) {
    mm::mtl::FixedList<VoiceInfo *, 6>::iterator it = mm::mtl::find_if(unknown90.begin(), unknown90.end(), unknown008(object));
    if (unknown90.end() != it) {
      return *it;
    }
  }
  return nullptr;
}

VoiceInfo *GfGameVoice::getPlayInfo(GAME_VOICE_HANDLE *voice) {
  for (mm::mtl::FixedList<VoiceInfo *, 6>::iterator it = unknown90.begin(); it != unknown90.end(); ++it) {
    if ((*it)->unknown28 == voice) {
      return *it;
    }
  }
  return nullptr;
}

VoiceInfo *GfGameVoice::getInfoLowestPrio() {
  VoiceInfo *lowest = nullptr;
  for (mm::mtl::FixedList<VoiceInfo *, 6>::iterator it = unknown90.begin(); it != unknown90.end(); ++it) {
    if (lowest == nullptr || lowest->unknown04 > (*it)->unknown04) {
      lowest = *it;
    }
  }
  return lowest;
}

GAME_VOICE_HANDLE *GfGameVoice::playVoice(const char *name) {
  GfVoiceName voiceName(name);
  GfSound *sound = GfSound::get();
  if (sound != nullptr) {
    const mm::mtl::FixStr<16> &langPath = getLangPath();
    mm::mtl::FixStr<16> voicePath;
    getCharPath(voicePath, voiceName.unknown00.c_str());
    mm::mtl::FixStr<128> path;
    path.format("%s%s/%s%s%s", _gfgvo::s_szVoicePath, langPath.c_str(), voicePath.c_str(), voiceName.unknown00.c_str(), _gfgvo::s_szVoiceExt);
    GfGameVoice *voice = get();
    if (voice != nullptr && !voice->unknown10.empty()) {
      GAME_VOICE_HANDLE *handle = voice->createHandle();
      VoiceInfo *info = voice->unknown10.front();
      voice->unknown10.pop_front();
      voice->unknown90.push_back(info);
      info->addPlay(handle, sound->playVoice(path.c_str(), 1.0f, false, CATEGORY_VOICE), voiceName);
      return handle;
    }
  }
  return nullptr;
}

GAME_VOICE_HANDLE *GfGameVoice::playNarrationVoice(const char *name) {
  GfVoiceName voiceName(name);
  GfSound *sound = GfSound::get();
  if (sound != nullptr) {
    const mm::mtl::FixStr<16> &langPath = getLangPath();
    mm::mtl::FixStr<16> voicePath;
    getCharPath(voicePath, voiceName.unknown00.c_str());
    mm::mtl::FixStr<128> path;
    path.format("%s%s/%s%s%s", _gfgvo::s_szVoicePath, langPath.c_str(), voicePath.c_str(), voiceName.unknown00.c_str(), _gfgvo::s_szVoiceExt);
    GfGameVoice *voice = get();
    if (voice != nullptr && !voice->unknown10.empty()) {
      GAME_VOICE_HANDLE *handle = voice->createHandle();
      VoiceInfo *info = voice->unknown10.front();
      voice->unknown10.pop_front();
      voice->unknown90.push_back(info);
      info->addPlay(handle, sound->playVoice(path.c_str(), 1.0f, false, CATEGORY_NAREVO), voiceName);
      return handle;
    }
  }
  return nullptr;
}

void GfGameVoice::getCharPath(mm::mtl::FixStr<16> &path, const char *name) {
  GfVoiceName voiceName(name);
  voiceName.getVoicePath(path);
}

void GfGameVoice::playStop(GF_OBJ_HANDLE *handle) {
  if (handle != unknown020) {
    ParamObj object = {handle, 0, 0};
    VoiceInfo *info = get()->getPlayInfo(object);
    if (info != nullptr) {
      info->addStop(CV_PRIO_UNKNOWN_0);
    }
  }
}

void GfGameVoice::playStop(GAME_VOICE_HANDLE *voice) {
  GfGameVoice *self = get();
  if (self != nullptr) {
    VoiceInfo *info = self->getPlayInfo(voice);
    if (info != nullptr) {
      info->addStop(CV_PRIO_UNKNOWN_0);
    }
  }
}

int GfGameVoice::getResult(GAME_VOICE_HANDLE *voice) {
  GfGameVoice *self = get();
  mm::mtl::FixedQueue<unknown001, 256>::iterator result = mm::mtl::find_if(self->unknown118.begin(), self->unknown118.end(), [voice](const unknown001 &entry) { return entry.unknown10 == voice; });
  if (result != self->unknown118.end()) {
    return (*result).unknown18;
  }
  mm::mtl::FixedList<VoiceInfo *, 6>::iterator it = mm::mtl::find_if(self->unknown90.begin(), self->unknown90.end(), [voice](VoiceInfo *info) { return info->isEnableVoiceHandle(voice); });
  return it != self->unknown90.end() ? CV_RESULT_UNKNOWN_2 : CV_RESULT_UNKNOWN_3;
}

int GfGameVoice::getResult(GF_OBJ_HANDLE *handle) {
  GfGameVoice *self = get();
  ParamObj object = {handle, 0, 0};
  VoiceInfo *info = self->getPlayInfo(object);
  if (info != nullptr) {
    if (info->unknown00) {
      return CV_RESULT_UNKNOWN_1;
    }

    return getResult(info->unknown28);
  }

  mm::mtl::FixedQueue<unknown001, 256>::iterator result =
      mm::mtl::find_if(self->unknown118.begin(), self->unknown118.end(), [handle](const unknown001 &entry) { return handle != unknown020 && entry.unknown00 == handle; });
  if (result != self->unknown118.end()) {
    return (*result).unknown18;
  }

  return CV_RESULT_UNKNOWN_0;
}

void GfGameVoice::gevLayerPause(u32 layer, bool isPause) {
  GfGameVoice *voice = get();
  VoiceInfoPause pause = {layer, isPause};
  for (mm::mtl::FixedList<VoiceInfo *, 6>::iterator it = voice->unknown90.begin(); it != voice->unknown90.end(); ++it) {
    (*it)->applyPause(pause);
  }
}

void GfGameVoice::gevMapjump(GEV event, const MapjumpCallbackInfo &) {
  if (event == GEV_UNKNOWN_2) {
    destroyVoiceAll();
  }
}

bool GfGameVoice::isPlayEnemyVoice() const {
  for (mm::mtl::FixedList<VoiceInfo *, 6>::const_iterator it = unknown90.begin(); it != unknown90.end(); ++it) {
    if ((*it)->getName().isEnemyVoice()) {
      return true;
    }
  }
  return false;
}

bool GfGameVoice::isPlayVoice(GF_OBJ_HANDLE *handle) const {
  ParamObj object = {handle, 0, 0};
  for (mm::mtl::FixedList<VoiceInfo *, 6>::const_iterator it = unknown90.begin(); it != unknown90.end(); ++it) {
    if (unknown007((*it)->unknown10, object)) {
      return true;
    }
  }
  return false;
}

bool GfGameVoice::isInitialized() {
  GfGameVoice *voice = get();
  if (voice != nullptr) {
    return voice->unknown08;
  }
  return false;
}

const mm::mtl::FixStr<16> &GfGameVoice::getLangPath() { return fw::LangUtil::getVoiceFolder(); }

GAME_VOICE_HANDLE *GfGameVoice::createHandle() {
  u64 handle = unknown110 + 1;
  if (handle == 0) {
    handle++;
  }
  unknown110 = handle;
  return reinterpret_cast<GAME_VOICE_HANDLE *>(handle);
}

GAME_VOICE_HANDLE *GfGameVoice::playVoice(GF_OBJ_HANDLE *handle, const char *name, CV_PRIO priority) {
  ParamObj object = {handle, 0, 0};
  return playVoice(object, name, priority);
}

GAME_VOICE_HANDLE *GfGameVoice::playVoice(u32 type, u32 id, const char *name, CV_PRIO priority) {
  ParamObj object = {unknown020, type, id};
  return playVoice(object, name, priority);
}

void GfGameVoice::applyHanaVoiceCondirtion(GfVoiceName &) {}

GAME_VOICE_HANDLE *GfFieldVoice::playVoice(GF_OBJ_HANDLE *handle, CV_FIELD voice, CV_PRIO priority) {
  ParamObj object = {handle, 0, 0};
  return playVoice(object, voice, priority);
}

GAME_VOICE_HANDLE *GfFieldVoice::playVoice(u32 type, u32 id, CV_FIELD voice, CV_PRIO priority) {
  ParamObj object = {unknown020, type, id};
  return playVoice(object, voice, priority);
}

GAME_VOICE_HANDLE *GfFieldVoice::playVoice(const ParamObj &object, CV_FIELD voice, CV_PRIO priority) {
  DataParamAcc acc(object);
  if (acc.getObjType() == OBJECT_TYPE_PC || acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 middle = unknown001[voice];
    int variation;
    const u8 *numbers;
    if (acc.getObjType() == OBJECT_TYPE_PC) {
      variation = ml::mtRand(unknown002[voice]);
      numbers = unknown003;
    } else {
      variation = ml::mtRand(unknown004[voice]);
      numbers = unknown005;
    }
    u32 number = numbers[voice];
    mm::mtl::FixStr<16> name;
    name = acc.getVoiceStr();
    GfVoiceName::addNumber2keta(name, number);
    GfVoiceName::addNumber2keta(name, middle + 1);
    GfVoiceName::addNumber2keta(name, variation + 1);
    if (strcmp(acc.getVoiceStr(), "15") == 0) {
      name += "a";
    }
    return GfGameVoice::playVoice(object, name.c_str(), priority);
  }
  return nullptr;
}

GAME_VOICE_HANDLE *GfFieldVoice::playVoice(const ParamObj &object, CV_FIELD voice, u32 middle, u32 variation, CV_PRIO priority) {
  DataParamAcc acc(object);
  if (acc.getObjType() == OBJECT_TYPE_PC || acc.getObjType() == OBJECT_TYPE_BLADE) {
    const u8 *numbers = acc.getObjType() == OBJECT_TYPE_PC ? unknown003 : unknown005;
    u32 number = numbers[voice];
    mm::mtl::FixStr<16> name;
    name = acc.getVoiceStr();
    GfVoiceName::addNumber2keta(name, number);
    GfVoiceName::addNumber2keta(name, middle + 1);
    GfVoiceName::addNumber2keta(name, variation + 1);
    if (strcmp(acc.getVoiceStr(), "15") == 0) {
      name += "a";
    }
    u32 id = acc.getObjType() == OBJECT_TYPE_PC ? acc.getValidDriverId() : acc.getValidBdatId();
    return GfGameVoice::playVoice(acc.getObjType(), id, name.c_str(), priority);
  }
  return nullptr;
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfGameVoice>::~PtrSingleton();
template mm::mtl::FixedList<gf::VoiceInfo *, 6>::iterator mm::mtl::FixedList<gf::VoiceInfo *, 6>::erase(mm::mtl::FixedList<gf::VoiceInfo *, 6>::iterator it);
