#pragma once
#include <stddef.h>

#include "gf/event/gf_event.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GF_OBJ_HANDLE;
struct GfSetupParam;
struct GAME_VOICE_HANDLE;
class VoiceInfo;
struct ParamObj;

enum CV_PRIO {
  CV_PRIO_UNKNOWN_0 = 0,
  CV_PRIO_UNKNOWN_1 = 1,
  CV_PRIO_UNKNOWN_2 = 2,
  CV_PRIO_UNKNOWN_3 = 3,
  CV_PRIO_UNKNOWN_4 = 4,
};

enum CV_FIELD {
  CV_FIELD_UNKNOWN_0 = 0,
  CV_FIELD_UNKNOWN_1 = 1,
  CV_FIELD_UNKNOWN_2 = 2,
  CV_FIELD_UNKNOWN_3 = 3,
  CV_FIELD_UNKNOWN_4 = 4,
  CV_FIELD_UNKNOWN_5 = 5,
  CV_FIELD_UNKNOWN_6 = 6,
  CV_FIELD_UNKNOWN_8 = 8,
  CV_FIELD_UNKNOWN_9 = 9,
  CV_FIELD_UNKNOWN_10 = 10,
  CV_FIELD_UNKNOWN_11 = 11,
  CV_FIELD_UNKNOWN_12 = 12,
  CV_FIELD_UNKNOWN_13 = 13,
  CV_FIELD_UNKNOWN_14 = 14,
  CV_FIELD_UNKNOWN_15 = 15,
  CV_FIELD_UNKNOWN_16 = 16,
  CV_FIELD_UNKNOWN_17 = 17,
  CV_FIELD_UNKNOWN_18 = 18,
  CV_FIELD_UNKNOWN_19 = 19,
  CV_FIELD_UNKNOWN_20 = 20,
  CV_FIELD_UNKNOWN_25 = 25,
  CV_FIELD_UNKNOWN_26 = 26,
  CV_FIELD_UNKNOWN_27 = 27,
  CV_FIELD_UNKNOWN_29 = 29,
  CV_FIELD_UNKNOWN_30 = 30,
  CV_FIELD_UNKNOWN_31 = 31, // Inferred role: cv field time morning; original name unknown.
  CV_FIELD_UNKNOWN_32 = 32, // Inferred role: cv field time night; original name unknown.
  CV_FIELD_UNKNOWN_36 = 36,
};

// The enum keeps the name of the game's symbol gf::GfGameVoice::addResult(gf::ParamObj const&, gf::GAME_VOICE_HANDLE*, gf::CV_RESULT).
enum CV_RESULT {
  CV_RESULT_UNKNOWN_0 = 0, // Inferred role: not started; original name unknown.
  CV_RESULT_UNKNOWN_1 = 1, // Inferred role: waiting to play; original name unknown.
  CV_RESULT_UNKNOWN_2 = 2, // Inferred role: voice result play; original name unknown.
  CV_RESULT_UNKNOWN_3 = 3, // Inferred role: finished; original name unknown.
};

struct GfVoiceName {
  GfVoiceName(const char *name);
  ~GfVoiceName() {}
  bool isValid() const;
  bool isEnemyVoice() const;
  bool getVoicePath(mm::mtl::FixStr<16> &path) const;
  int getCharaId() const;
  u32 getObjType() const;
  static bool isHanaVoice(const char *name);
  static void addNumber2keta(mm::mtl::FixStr<16> &name, u32 number);
  static const char *getCharacterVoiceStr(GF_OBJ_HANDLE *handle);

  mm::mtl::FixStr<16> unknown00; // Inferred role: voice file name; original member name unknown.
  int unknown14;                 // Inferred role: length of the requested name; original member name unknown.
  int unknown18;                 // Inferred role: digit count of the character part; original member name unknown.
};

static_assert(offsetof(GfVoiceName, unknown14) == 0x14, "");
static_assert(offsetof(GfVoiceName, unknown18) == 0x18, "");
static_assert(sizeof(GfVoiceName) == 0x1c, "");

class GfGameVoice : public mm::mtl::PtrSingleton<GfGameVoice> {
public:
  struct VoiceInfoPause {
    u32 unknown00;  // Inferred role: layer; original member name unknown.
    bool unknown04; // Inferred role: pause flag; original member name unknown.
  };

  // Inferred role: voice play result log entry; original type name unknown.
  struct unknown001 {
    GF_OBJ_HANDLE *unknown00;     // Inferred role: object handle; original member name unknown.
    u32 unknown08;                // Inferred role: object type; original member name unknown.
    u32 unknown0c;                // Inferred role: object id; original member name unknown.
    GAME_VOICE_HANDLE *unknown10; // Inferred role: voice handle; original member name unknown.
    CV_RESULT unknown18;          // Inferred role: result; original member name unknown.
  };

  GfGameVoice(const GfSetupParam &param);
  ~GfGameVoice();
  static void build(const GfSetupParam &param);
  static void destroy();
  void initialize(const GfSetupParam &param);
  void finalize();
  static void update(const fw::UpdateInfo &info);
  VoiceInfo *getPlayInfo(const ParamObj &object);
  VoiceInfo *getPlayInfo(GAME_VOICE_HANDLE *voice);
  VoiceInfo *getInfoLowestPrio();
  static void destroyVoiceAll();
  static int getResult(GAME_VOICE_HANDLE *voice);
  static int getResult(GF_OBJ_HANDLE *handle);
  static GAME_VOICE_HANDLE *playVoice(const ParamObj &object, const char *name, CV_PRIO priority);
  static GAME_VOICE_HANDLE *playVoice(GF_OBJ_HANDLE *handle, const char *name, CV_PRIO priority);
  static GAME_VOICE_HANDLE *playVoice(u32 type, u32 id, const char *name, CV_PRIO priority);
  static GAME_VOICE_HANDLE *playVoice(const char *name);
  static GAME_VOICE_HANDLE *playNarrationVoice(const char *name);
  static void playStop(GF_OBJ_HANDLE *handle);
  static void playStop(GAME_VOICE_HANDLE *voice);
  static void gevLayerPause(u32 layer, bool isPause);
  static void gevMapjump(GEV event, const MapjumpCallbackInfo &info);
  bool isPlayEnemyVoice() const;
  bool isPlayVoice(GF_OBJ_HANDLE *handle) const;
  void applyHanaVoiceCondirtion(GfVoiceName &name);
  static bool isInitialized();
  static const mm::mtl::FixStr<16> &getLangPath();
  static void getCharPath(mm::mtl::FixStr<16> &path, const char *name);

  GAME_VOICE_HANDLE *createHandle();

  bool unknown08;                                  // Inferred role: initialized; original member name unknown.
  mm::mtl::FixedList<VoiceInfo *, 6> unknown10;    // Inferred role: unused voice infos; original member name unknown.
  mm::mtl::FixedList<VoiceInfo *, 6> unknown90;    // Inferred role: playing voice infos; original member name unknown.
  u64 unknown110;                                  // Inferred role: handle serial; original member name unknown.
  mm::mtl::FixedQueue<unknown001, 256> unknown118; // Inferred role: play results; original member name unknown.
};

static_assert(offsetof(GfGameVoice, unknown10) == 0x10, "");
static_assert(offsetof(GfGameVoice, unknown90) == 0x90, "");
static_assert(offsetof(GfGameVoice, unknown110) == 0x110, "");
static_assert(offsetof(GfGameVoice, unknown118) == 0x118, "");
static_assert(sizeof(GfGameVoice) == 0x2128, "");

class GfFieldVoice {
public:
  static GAME_VOICE_HANDLE *playVoice(GF_OBJ_HANDLE *handle, CV_FIELD voice, CV_PRIO priority);
  static GAME_VOICE_HANDLE *playVoice(const ParamObj &object, CV_FIELD voice, CV_PRIO priority);
  static GAME_VOICE_HANDLE *playVoice(const ParamObj &object, CV_FIELD voice, u32 middle, u32 variation, CV_PRIO priority);
  static GAME_VOICE_HANDLE *playVoice(u32 type, u32 id, CV_FIELD voice, CV_PRIO priority);
};

} // namespace gf
