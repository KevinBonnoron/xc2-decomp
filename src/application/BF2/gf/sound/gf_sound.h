#pragma once
#include "gf/event/gf_event.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/sound/gf_master_volume.h"
#include "ml/fixed_size_alloc.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace arc {
class CArcData;
} // namespace arc

namespace fw {
class SoundPack;
class SoundResSourceManager;
enum SoundCategory : int;
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GF_OBJ_HANDLE;
struct GF_SE_CATEGORY_HANDLE;
class GfAssetResource;
struct GfSetupParam;

GF_SE_CATEGORY_HANDLE *const unknown019 = reinterpret_cast<GF_SE_CATEGORY_HANDLE *>(-1); // Inferred role: invalid category handle; original name unknown.

// The category names are the labels of the game's "name(id)" category setup in fw::SoundManager: "BGM" 1, "VOICE" 2, "SYSTEM" 3, "BATTLE" 4, "FIELD" 5, "GIMMICK" 6, "ENV" 7, "WEATHER" 8, "EVT_CS" 9,
// "EVT_BGM" 10, "EVT_VOICE" 11, "EVT_SE" 12, "CH_SE" 13, "CH_SE NS" 14 (written CH_SE_NS), "ENE_VO" 15, "NAREVO" 16, "MENU_BGM" 17.
constexpr fw::SoundCategory CATEGORY_BGM = static_cast<fw::SoundCategory>(1);   // Original label "BGM" (1) of fw::SoundManager's category setup.
constexpr fw::SoundCategory CATEGORY_VOICE = static_cast<fw::SoundCategory>(2); // Original label "VOICE" (2) of fw::SoundManager's category setup.
constexpr fw::SoundCategory CATEGORY_SYSTEM = static_cast<fw::SoundCategory>(3);
constexpr fw::SoundCategory CATEGORY_BATTLE = static_cast<fw::SoundCategory>(4);     // Original label "BATTLE" (4) of fw::SoundManager's category setup.
constexpr fw::SoundCategory CATEGORY_FIELD = static_cast<fw::SoundCategory>(5);      // Original label "FIELD" (5) of fw::SoundManager's category setup.
constexpr fw::SoundCategory CATEGORY_GIMMICK = static_cast<fw::SoundCategory>(6);    // Original label "GIMMICK" (6) of fw::SoundManager's category setup.
constexpr fw::SoundCategory CATEGORY_ENV = static_cast<fw::SoundCategory>(7);        // Original label "ENV" (7) of fw::SoundManager's category setup.
constexpr fw::SoundCategory CATEGORY_WEATHER = static_cast<fw::SoundCategory>(8);    // Original label "WEATHER" (8) of fw::SoundManager's category setup.
constexpr fw::SoundCategory CATEGORY_EVT_CS = static_cast<fw::SoundCategory>(9);     // Original label "EVT_CS" (9) of fw::SoundManager's category setup.
constexpr fw::SoundCategory CATEGORY_EVT_BGM = static_cast<fw::SoundCategory>(10);   // Original label "EVT_BGM" (10) of fw::SoundManager's category setup.
constexpr fw::SoundCategory CATEGORY_EVT_VOICE = static_cast<fw::SoundCategory>(11); // Original label "EVT_VOICE" (11) of fw::SoundManager's category setup.
constexpr fw::SoundCategory CATEGORY_EVT_SE = static_cast<fw::SoundCategory>(12);    // Original label "EVT_SE" (12) of fw::SoundManager's category setup.
constexpr fw::SoundCategory CATEGORY_CH_SE = static_cast<fw::SoundCategory>(13);     // Original label "CH_SE" (13) of fw::SoundManager's category setup.
constexpr fw::SoundCategory CATEGORY_CH_SE_NS = static_cast<fw::SoundCategory>(14);  // Original label "CH_SE NS" (14) of fw::SoundManager's category setup; spaces become underscores.
constexpr fw::SoundCategory CATEGORY_ENE_VO = static_cast<fw::SoundCategory>(15);    // Original label "ENE_VO" (15) of fw::SoundManager's category setup.
constexpr fw::SoundCategory CATEGORY_NAREVO = static_cast<fw::SoundCategory>(16);    // Original label "NAREVO" (16) of fw::SoundManager's category setup.
constexpr fw::SoundCategory CATEGORY_MENU_BGM = static_cast<fw::SoundCategory>(17);

enum SEINFO {
  SEINFO_UNKNOWN_0, // Inferred role: seinfo search; original name unknown.
  SEINFO_UNKNOWN_1, // Inferred role: seinfo common pack; original name unknown.
  SEINFO_UNKNOWN_2, // Inferred role: seinfo field common pack; original name unknown.
  SEINFO_UNKNOWN_3, // Inferred role: seinfo field map pack; original name unknown.
  SEINFO_UNKNOWN_4, // Inferred role: seinfo obj pack; original name unknown.
  SEINFO_UNKNOWN_5, // Inferred role: seinfo name; original name unknown.
};

enum SOUND_TRANSFORM {
  SOUND_TRANSFORM_UNKNOWN_0, // Inferred role: sound transform none; original name unknown.
  SOUND_TRANSFORM_UNKNOWN_1, // Inferred role: sound transform global; original name unknown.
  SOUND_TRANSFORM_UNKNOWN_2, // Inferred role: sound transform obj; original name unknown.
  SOUND_TRANSFORM_UNKNOWN_3, // Inferred role: sound transform bone; original name unknown.
};

struct SoundParam {
  SoundParam() {
    unknown28 = 1.0f;
    unknown38 = 0;
    unknown39 = SOUND_TRANSFORM_UNKNOWN_0;
    unknown3a = SEINFO_UNKNOWN_0;
    unknown30 = unknown020;
    unknown00 = 0;
  }

  SoundParam(u32 id) : unknown00(0) {
    clear();
    unknown00 = id;
    if (!unknown04.empty()) {
      unknown04.clear();
    }
  }

  SoundParam(u32 id, const char *name) : unknown00(0) {
    clear();
    unknown00 = id;
    unknown04 = name;
  }

  void clear();
  void setupTransformGlobal(const mm::Vec3 &position);
  void setupTransformObj(GF_OBJ_HANDLE *handle, const mm::Vec3 &offset);
  void setupTransformBone(GF_OBJ_HANDLE *handle, const char *bone, const mm::Vec3 &offset);

  u32 unknown00;                 // Inferred role: id; original member name unknown.
  mm::mtl::FixStr<32> unknown04; // Inferred role: name; original member name unknown.
  f32 unknown28;                 // Inferred role: volume; original member name unknown.
  GF_OBJ_HANDLE *unknown30;      // Inferred role: handle; original member name unknown.
  u8 unknown38;                  // Inferred role: category; original member name unknown.
  u8 unknown39;                  // Inferred role: transform; original member name unknown.
  u8 unknown3a;                  // Inferred role: se info; original member name unknown.
  mm::Vec3 unknown40;            // Inferred role: position; original member name unknown.
  const char *unknown50;         // Inferred role: bone; original member name unknown.
};

static_assert(offsetof(SoundParam, unknown04) == 0x04, "");
static_assert(offsetof(SoundParam, unknown28) == 0x28, "");
static_assert(offsetof(SoundParam, unknown30) == 0x30, "");
static_assert(offsetof(SoundParam, unknown38) == 0x38, "");
static_assert(offsetof(SoundParam, unknown40) == 0x40, "");
static_assert(offsetof(SoundParam, unknown50) == 0x50, "");

class SoundHandle {
public:
  void clear();
  SoundHandle();
  SoundHandle(u32 handle);
  bool isValid() const;

  u32 unknown00; // Inferred role: handle; original member name unknown.
  u32 unknown04; // Inferred role: se param; original member name unknown.
};

static_assert(sizeof(SoundHandle) == 0x08, "");
static_assert(alignof(SoundHandle) == 0x04, "");

class GfSound : public mm::mtl::PtrSingleton<GfSound>, public IGfEvent {
public:
  static const u32 CATEGORY_UNKNOWN_18 = 18; // Inferred role: category num; original name unknown.
  static const u32 CATEGORY_UNKNOWN_32 = 32; // Inferred role: category volume num; original name unknown.

  struct SeParam {
    void clear();

    u8 unknown00;             // Inferred role: se info; original member name unknown.
    u8 unknown01;             // Inferred role: category; original member name unknown.
    bool unknown02;           // Inferred role: loop; original member name unknown.
    u8 unknown03;             // Inferred role: pause bits; original member name unknown.
    GF_OBJ_HANDLE *unknown08; // Inferred role: handle; original member name unknown.
    SoundHandle unknown10;    // Inferred role: sound handle; original member name unknown.
  };

  struct CategoryVolume {
    struct Volume {
      Volume() : unknown00(1.0f), unknown04(1.0f), unknown08(1.0f), unknown0c(0.0f), unknown10(0.0f) {}

      void clear() {
        unknown00 = 1.0f;
        unknown04 = 1.0f;
        unknown08 = 1.0f;
        unknown0c = 0.0f;
        unknown10 = 0.0f;
      }

      void set(f32 volume, f32 fadeTime) {
        unknown10 = fadeTime;
        unknown0c = fadeTime;
        unknown08 = unknown00;
        unknown04 = volume;
      }

      f32 unknown00; // Inferred role: current; original member name unknown.
      f32 unknown04; // Inferred role: target; original member name unknown.
      f32 unknown08; // Inferred role: start; original member name unknown.
      f32 unknown0c; // Inferred role: duration; original member name unknown.
      f32 unknown10; // Inferred role: time; original member name unknown.
    };

    // The game constructor (0x71005d6094) stores the 18 volumes twice, once for the member initialisation and once for this clear loop.
    CategoryVolume() : unknown168(-1), unknown16c(true) {
      for (Volume &volume : unknown00) {
        volume.clear();
      }
    }

    // Inferred role: tells whether the category volume is in use; original name unknown. A member function:
    // isNeedUpdateCategoryVolume (0x71005d62bc) only gets the game's loop (pointer step before the counter step) with
    // the index test coming from an inlined call.
    bool unknown001() const { return unknown168 >= 0; }

    Volume unknown00[CATEGORY_UNKNOWN_18]; // Inferred role: volumes; original member name unknown.
    int unknown168;                        // Inferred role: index; original member name unknown.
    bool unknown16c;                       // Inferred role: changed; original member name unknown.
  };

  GfSound(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfSound();
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  GF_SE_CATEGORY_HANDLE *createCategoryHandle();
  void releaseCategoryHandle(GF_SE_CATEGORY_HANDLE *&handle);
  u16 allocateSeParam();
  void deAllocateSeParam(u16 id);
  void update(const fw::UpdateInfo &info);
  SeParam *getSeParam(u16 id);
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
  void destroyCategorySe(fw::SoundCategory category);
  void stopSe(SoundHandle handle, f32 fadeTime);
  void setCategory(SoundHandle handle, fw::SoundCategory category);
  void setPause(SoundHandle handle, bool isPause, f32 fadeTime);
  void setPauseType(SoundHandle handle, bool isPause, f32 fadeTime, u8 type);
  void setPan(SoundHandle handle, f32 pan, f32 fadeTime);
  void setPlayTime(SoundHandle handle, f32 time);
  bool getPlayTime(SoundHandle handle, f32 &time) const;
  bool getTotalTime(SoundHandle handle, f32 &time) const;
  bool isLoop(SoundHandle handle) const;
  void setVolume(SoundHandle handle, f32 volume, f32 fadeTime);
  f32 getVolume(SoundHandle handle);
  bool isPlaying(SoundHandle handle) const;
  bool isPreparing(SoundHandle handle) const;
  fw::SoundPack *createObjSePack(GfAssetResource *resource);
  void destroyObjSePack(fw::SoundPack *&pack);
  void gevPause(u32 resumeBits, u32 pauseBits) override;
  void gevLayerPause(u32 layer, bool isPause) override;
  void setPauseGameSe(bool isPause);
  void setPauseGameWeatherSe(bool isPause);
  void setPauseEventSe(bool isPause);

  bool unknown10;                                                     // Inferred role: initialized; original member name unknown.
  bool unknown11;                                                     // Inferred role: released; original member name unknown.
  u64 unknown18;                                                      // Inferred role: handle serial; original member name unknown.
  mm::mtl::FixedArray<CategoryVolume, CATEGORY_UNKNOWN_32> unknown20; // Inferred role: category volumes; original member name unknown.
  ml::fixed_size_alloc_inside<SeParam, 384> unknown2e20;              // Inferred role: se params; original member name unknown.
  mm::mtl::FixedList<u16, 512> unknown5278;                           // Inferred role: playing se param indices; original member name unknown.
  GfMasterVolume unknown6690;                                         // Inferred role: master volume; original member name unknown.
  GF_SE_CATEGORY_HANDLE *unknown66d0;                                 // Inferred role: category handle; original member name unknown.
};

static_assert(sizeof(GfSound::SeParam) == 0x18, "");
static_assert(sizeof(GfSound::CategoryVolume) == 0x170, "");
static_assert(offsetof(GfSound, unknown10) == 0x10, "");
static_assert(offsetof(GfSound, unknown20) == 0x20, "");
static_assert(offsetof(GfSound, unknown2e20) == 0x2e20, "");
static_assert(offsetof(GfSound, unknown5278) == 0x5278, "");
static_assert(offsetof(GfSound, unknown6690) == 0x6690, "");
static_assert(offsetof(GfSound, unknown66d0) == 0x66d0, "");
static_assert(sizeof(GfSound) == 0x66d8, "");

extern const char *const SS_NAME_TABLE[];

u32 getSoundSourceCount();
const char *getSoundSourceFileName(u32 index);
void registerSSPack(arc::CArcData &archive, fw::SoundResSourceManager *manager);
void bindGFSoundSource();
void unrbindGFSoundSource();
void reloadGFSoundSource();

} // namespace gf
