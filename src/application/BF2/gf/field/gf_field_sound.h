#pragma once
#include "gf/event/gf_event.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace fw {
class SoundPack;
class SoundResource;
struct UpdateInfo;
} // namespace fw

namespace gf {

class GfFieldBgm;
class GfFieldMapSe;
struct GF_OBJ_HANDLE;
struct GF_SE_CATEGORY_HANDLE;
struct GfSetupParam;

class GfFieldSound : public mm::mtl::PtrSingleton<GfFieldSound> {
public:
  GfFieldSound(const GfSetupParam &param);
  ~GfFieldSound() override;
  static void build(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  static void destroy();
  void finalize();
  void update(const fw::UpdateInfo &info);
  void postUpdate(const fw::UpdateInfo &info);
  void clear();
  void gevGameMapModel(GF_OBJ_HANDLE *handle, bool isEnter);
  void gevPlayEvent(GEV event, u32 value);
  void gevBattleEnd();
  void gevMapjump(GEV event, const MapjumpCallbackInfo &info);
  void gevPause(u32 resumeBits, u32 pauseBits);
  void getMapSeFile(mm::mtl::FixStr<128> &path, const char *name);
  void createCommonSound();
  void destroyCommonSound();
  void createMapSound();
  void destroyMapSound();
  void waitLoadMapSound();
  fw::SoundPack *getCommonPack();
  fw::SoundPack *getMapPack();
  void setCategorySeFadeoutForEvent(f32 volume);
  void setCategorySeFadeoutForMapjump(f32 fadeTime);
  void setCategorySeFadeinForMapjump(f32 fadeTime);
  void destroyCategorySeForMapjump();

  bool unknown08; // Inferred role: initialized; original member name unknown.
  u8 _09[0x10 - 0x09];
  GfFieldBgm *unknown10;        // Inferred role: field bgm; original member name unknown.
  GfFieldMapSe *unknown18;      // Inferred role: field map se; original member name unknown.
  fw::SoundResource *unknown20; // Inferred role: common sound resource; original member name unknown.
  fw::SoundPack *m_commonPack;
  fw::SoundResource *unknown30; // Inferred role: map sound resource; original member name unknown.
  fw::SoundPack *m_mapPack;
  mm::mtl::FixStr<128> unknown40;    // Inferred role: map se pack path; original member name unknown.
  mm::mtl::FixStr<64> unknownc4;     // Inferred role: map se pack name; original member name unknown.
  GF_SE_CATEGORY_HANDLE *unknown108; // Inferred role: se category handle; original member name unknown.
  GF_SE_CATEGORY_HANDLE *unknown110; // Inferred role: se category handle for the map jump; original member name unknown.
  GF_SE_CATEGORY_HANDLE *unknown118; // Inferred role: se category handle for events; original member name unknown.
};

static_assert(offsetof(GfFieldSound, unknown10) == 0x10, "");
static_assert(offsetof(GfFieldSound, unknown20) == 0x20, "");
static_assert(offsetof(GfFieldSound, unknown30) == 0x30, "");
static_assert(offsetof(GfFieldSound, unknown40) == 0x40, "");
static_assert(offsetof(GfFieldSound, unknown18) == 0x18, "");
static_assert(offsetof(GfFieldSound, m_commonPack) == 0x28, "");
static_assert(offsetof(GfFieldSound, m_mapPack) == 0x38, "");
static_assert(offsetof(GfFieldSound, unknownc4) == 0xc4, "");
static_assert(offsetof(GfFieldSound, unknown108) == 0x108, "");
static_assert(offsetof(GfFieldSound, unknown110) == 0x110, "");
static_assert(offsetof(GfFieldSound, unknown118) == 0x118, "");
static_assert(sizeof(GfFieldSound) == 0x120, "");

} // namespace gf
