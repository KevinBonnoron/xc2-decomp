#pragma once
#include "gf/event/gf_event.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/sound/gf_master_volume.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace fw {
class SoundPack;
enum SoundCategory : int;
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GF_OBJ_HANDLE;
struct GF_SE_CATEGORY_HANDLE;
struct GfSetupParam;

GF_SE_CATEGORY_HANDLE *const INVALID_CATEGORY_HANDLE = reinterpret_cast<GF_SE_CATEGORY_HANDLE *>(-1);

constexpr fw::SoundCategory CATEGORY_GAME_BGM = static_cast<fw::SoundCategory>(1);
constexpr fw::SoundCategory CATEGORY_PLAYER_VOICE = static_cast<fw::SoundCategory>(2);
constexpr fw::SoundCategory CATEGORY_SYSTEM = static_cast<fw::SoundCategory>(3);
constexpr fw::SoundCategory CATEGORY_BATTLE_SE = static_cast<fw::SoundCategory>(4);
constexpr fw::SoundCategory CATEGORY_FIELD_SE = static_cast<fw::SoundCategory>(5);
constexpr fw::SoundCategory CATEGORY_GIMMICK_SE = static_cast<fw::SoundCategory>(6);
constexpr fw::SoundCategory CATEGORY_GAME_ENV = static_cast<fw::SoundCategory>(7);
constexpr fw::SoundCategory CATEGORY_GAME_WEATHER = static_cast<fw::SoundCategory>(8);
constexpr fw::SoundCategory CATEGORY_EVENT_CS = static_cast<fw::SoundCategory>(9);
constexpr fw::SoundCategory CATEGORY_EVENT_BGM = static_cast<fw::SoundCategory>(10);
constexpr fw::SoundCategory CATEGORY_EVENT_VOICE = static_cast<fw::SoundCategory>(11);
constexpr fw::SoundCategory CATEGORY_EVENT_SE = static_cast<fw::SoundCategory>(12);
constexpr fw::SoundCategory CATEGORY_CHARACTER_SE = static_cast<fw::SoundCategory>(13);
constexpr fw::SoundCategory CATEGORY_NO_SLOW_SE = static_cast<fw::SoundCategory>(14);
constexpr fw::SoundCategory CATEGORY_ENEMY_VOICE = static_cast<fw::SoundCategory>(15);
constexpr fw::SoundCategory CATEGORY_NARE_VOICE = static_cast<fw::SoundCategory>(16);
constexpr fw::SoundCategory CATEGORY_MENU_BGM = static_cast<fw::SoundCategory>(17);

enum SEINFO {
  SEINFO_SEARCH,
  SEINFO_COMMON_PACK,
  SEINFO_FIELD_COMMON_PACK,
  SEINFO_FIELD_MAP_PACK,
  SEINFO_OBJ_PACK,
  SEINFO_NAME,
};

enum SOUND_TRANSFORM {
  SOUND_TRANSFORM_NONE,
  SOUND_TRANSFORM_GLOBAL,
  SOUND_TRANSFORM_OBJ,
  SOUND_TRANSFORM_BONE,
};

struct SoundParam {
  SoundParam() {
    volume = 1.0f;
    category = 0;
    transform = SOUND_TRANSFORM_NONE;
    seInfo = SEINFO_SEARCH;
    handle = INVALID_HANDLE;
    id = 0;
  }

  void clear();
  void setupTransformGlobal(const mm::Vec3 &position);
  void setupTransformObj(GF_OBJ_HANDLE *handle, const mm::Vec3 &offset);
  void setupTransformBone(GF_OBJ_HANDLE *handle, const char *bone, const mm::Vec3 &offset);

  u32 id;
  mm::mtl::FixStr<32> name;
  f32 volume;
  GF_OBJ_HANDLE *handle;
  u8 category;
  u8 transform;
  u8 seInfo;
  mm::Vec3 position;
  const char *bone;
};

static_assert(offsetof(SoundParam, name) == 0x04, "");
static_assert(offsetof(SoundParam, volume) == 0x28, "");
static_assert(offsetof(SoundParam, handle) == 0x30, "");
static_assert(offsetof(SoundParam, category) == 0x38, "");
static_assert(offsetof(SoundParam, position) == 0x40, "");
static_assert(offsetof(SoundParam, bone) == 0x50, "");

class SoundHandle {
public:
  void clear();
  SoundHandle();
  SoundHandle(u32 handle);
  bool isValid() const;

  u32 handle;
  u32 seParam;
};

static_assert(sizeof(SoundHandle) == 0x08, "");
static_assert(alignof(SoundHandle) == 0x04, "");

class GfSound : public mm::mtl::PtrSingleton<GfSound>, public IGfEvent {
public:
  static const u32 CATEGORY_NUM = 18;
  static const u32 CATEGORY_VOLUME_NUM = 32;

  struct SeParam {
    void clear();

    u8 seInfo;
    u8 category;
    bool isLoop;
    u8 pauseBits;
    GF_OBJ_HANDLE *handle;
    SoundHandle soundHandle;
  };

  struct CategoryVolume {
    struct Volume {
      Volume() : current(1.0f), target(1.0f), start(1.0f), duration(0.0f), time(0.0f) {}

      void clear() {
        current = 1.0f;
        target = 1.0f;
        start = 1.0f;
        duration = 0.0f;
        time = 0.0f;
      }

      void set(f32 volume, f32 fadeTime) {
        time = fadeTime;
        duration = fadeTime;
        start = current;
        target = volume;
      }

      f32 current;
      f32 target;
      f32 start;
      f32 duration;
      f32 time;
    };

    CategoryVolume();

    Volume volumes[CATEGORY_NUM];
    int index;
    bool isChanged;
  };

  GfSound(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfSound();
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  GF_SE_CATEGORY_HANDLE *createCategoryHandle();
  void releaseCategoryHandle(GF_SE_CATEGORY_HANDLE *&handle);
  void update(const fw::UpdateInfo &info);
  bool calcCategoryVolume(const fw::UpdateInfo &info);
  void updateSeParamList(const fw::UpdateInfo &info);
  void setupGame();
  void setCategoryVolume(GF_SE_CATEGORY_HANDLE *handle, fw::SoundCategory category, f32 volume, f32 fadeTime);
  CategoryVolume *getCategoryVolume(GF_SE_CATEGORY_HANDLE *handle);
  f32 getCategoryVolume(GF_SE_CATEGORY_HANDLE *handle, fw::SoundCategory category) const;
  const CategoryVolume *getCategoryVolume(GF_SE_CATEGORY_HANDLE *handle) const;
  bool isNeedUpdateCategoryVolume() const;
  void setCategoryPitch(fw::SoundCategory category, f32 pitch, f32 fadeTime);
  SoundHandle playBgm(u32 bgm, f32 volume, bool ignorePause, int loopCount, fw::SoundCategory category);
  SoundHandle playBgm(const char *name, f32 volume, bool ignorePause, int loopCount, fw::SoundCategory category);
  void startBgm(SoundHandle handle);
  void stopBgm(SoundHandle handle, f32 fadeTime);
  SoundHandle playVoice(const char *name, f32 volume, bool ignorePause, fw::SoundCategory category);
  void startVoice(SoundHandle handle);
  void stopVoice(SoundHandle handle, f32 fadeTime);
  SoundHandle playSe(const SoundParam &param);
  bool getSePack(mm::mtl::FixedVector<fw::SoundPack *, 4> &packs, const SoundParam &param);
  SoundHandle playSeWithPack(const SoundParam &param, mm::mtl::FixedVector<fw::SoundPack *, 4> &packs, SEINFO seInfo);
  SoundHandle playSe(const char *name, fw::SoundCategory category);
  void stopSe(SoundHandle handle, f32 fadeTime);
  void setPause(SoundHandle handle, bool isPause, f32 fadeTime);
  void setPan(SoundHandle handle, f32 pan, f32 fadeTime);
  void setPlayTime(SoundHandle handle, f32 time);
  bool getPlayTime(SoundHandle handle, f32 &time) const;
  bool getTotalTime(SoundHandle handle, f32 &time) const;
  bool isLoop(SoundHandle handle) const;
  void setVolume(SoundHandle handle, f32 volume, f32 fadeTime);
  f32 getVolume(SoundHandle handle);
  bool isPlaying(SoundHandle handle) const;
  bool isPreparing(SoundHandle handle) const;
  void gevPause(u32 resumeBits, u32 pauseBits) override;
  void gevLayerPause(u32 layer, bool isPause) override;
  void setPauseGameSe(bool isPause);
  void setPauseGameWeatherSe(bool isPause);
  void setPauseEventSe(bool isPause);

  bool initialized;
  bool isReleased;
  u64 handleSerial;
  mm::mtl::FixedArray<CategoryVolume, CATEGORY_VOLUME_NUM> categoryVolumes;
  u8 _2e20[0x6690 - 0x2e20];
  GfMasterVolume masterVolume;
  GF_SE_CATEGORY_HANDLE *categoryHandle;
};

static_assert(sizeof(GfSound::SeParam) == 0x18, "");
static_assert(sizeof(GfSound::CategoryVolume) == 0x170, "");
static_assert(offsetof(GfSound, initialized) == 0x10, "");
static_assert(offsetof(GfSound, categoryVolumes) == 0x20, "");
static_assert(offsetof(GfSound, masterVolume) == 0x6690, "");
static_assert(offsetof(GfSound, categoryHandle) == 0x66d0, "");
static_assert(sizeof(GfSound) == 0x66d8, "");

void bindGFSoundSource();
void unrbindGFSoundSource();

} // namespace gf
