#pragma once
#include <stddef.h>

#include "dr/dr_pixl_post_parm.h"
#include "grlib/cglib_texture_buffer.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace csvb {
class CCsvbData;
} // namespace csvb

namespace mm {
struct Col3;
struct Vec3;
} // namespace mm

namespace ml {

class DrMan;
class FileResTh;
class ScnObjModel;
class WinProc;

extern const char *TOON_RIM_FILE;
extern const char *VOLUME_FILE;
extern const char *DUMMY_CUBEMAP_FILE;
extern const char *RAIN_DROP_FILE;
extern const char *RAIN_DROP_DEPTH_FILE;
extern const char *TOON_GRAD_FILE;
extern const char *TOON_GRAD_NIGHT_FILE;
extern const char *WETNESS_CSVB_FILE;
extern const char *GLASS_BREAKAGE;
extern const char *CAM_LGT_FILE;
extern const char *FLAG_WAVE0_FILE;
extern const char *FLAG_WAVE1_FILE;
extern const char *MIRROR_BALL_MDL_FILE;

class DrIniSys {
public:
  struct WetSetting {
    bool unknown00; // Inferred role: getting wet rather than drying; original member name unknown.
    s32 unknown04;  // Inferred role: first fade frames; original member name unknown.
    s32 unknown08;  // Inferred role: second fade frames; original member name unknown.
    f32 unknown0c;  // Inferred role: wetness value; original member name unknown.
  };

  DrIniSys(DrMan *drMan);
  ~DrIniSys();
  void dataWorkClear();
  bool chkOnOff(const char *value);
  f32 getFloatWork(const char *value);
  void getdrColor3Work(mm::Col3 &color, const char *value);
  int getToonDirType(const char *value);
  int getIntWork(const char *value);
  FileResTh *readTextureMapFile(const char *name);
  void setDefTexture(int index, void *data, int size);
  void loadRainDropTexture();
  void loadToonGradTexture();
  void loadToonRimTexture();
  void loadVolumeTexture();
  void loadIBLEnvTexture();
  void loadWetnessCSVBFile();
  void loadFilterLutTexture();
  void loadGlassBreakage();
  void loadCameraLight();
  void loadTextureImpl(u32 index, const char *name);
  void loadFlagWaveTexture();
  void setIBLEnvTexturePath(const char *path);
  void reloadToonGradTexture();
  void reloadToonRimTexture();
  void reloadVolumeTexture();
  void reloadIBLEnvTexture();
  bool getDispMirrorBall() const;
  void setDispMirrorBall(bool isDisp);
  void loadMirrorBallModel();
  bool getUpdateMirrorBallPos() const;
  void setUpdateMirrorBallPos(bool isUpdate);
  void dispMirrorBallPerformanceMDL(WinProc *proc);
  void setMirrorBallPosition(const mm::Vec3 &position);
  void setStrWork(char *dst, const char *src);
  FileResTh *readWorkFile(const char *name);
  void setLutTexture(int index, void *data, int size);
  void setCubeTexture(int index, void *data, int size);
  void reloadMirrorBallModel();
  void reloadRainDropTexture();
  void reloadFlagWaveTexture();
  const void *getGlassBreakage() const;
  void getWetnessSetting(u16 index, WetSetting &setting) const;

  DrMan *unknown00;                        // Inferred role: dr man; original member name unknown.
  FileResTh *unknown08[18];                // Inferred role: texture resources ([4, 5] toon grad, [6] toon rim, [7..11] volume, [12] IBL env, [13, 14] rain drop, [16, 17] flag
                                           // wave); original member name unknown.
  grlib::CGLibTextureBuffer unknown98[18]; // Inferred role: textures; original member name unknown.
  FileResTh *unknown878;                   // Inferred role: mirror ball model res; original member name unknown.
  ScnObjModel *unknown880;                 // Inferred role: mirror ball; original member name unknown.
  bool m_updateMirrorBallPos;
  u8 _889[0x890 - 0x889];
  FileResTh *unknown890; // Inferred role: camera light res; original member name unknown.
  FileResTh *unknown898; // Inferred role: glass breakage res; original member name unknown.
  FileResTh *unknown8a0; // Inferred role: filter lut res; original member name unknown.
  u8 _8a8[0x970 - 0x8a8];
  DrPixlPostParm unknown970; // Inferred role: default post parm; original member name unknown.
  mm::mtl::FixStr<256> m_IBLEnvTexturePath;
  csvb::CCsvbData *unknown1b88; // Inferred role: wetness csvb data; original member name unknown.
};

static_assert(offsetof(DrIniSys::WetSetting, unknown04) == 0x04, "");
static_assert(offsetof(DrIniSys::WetSetting, unknown0c) == 0x0c, "");
static_assert(sizeof(DrIniSys::WetSetting) == 0x10, "");
static_assert(offsetof(DrIniSys, unknown08) == 0x08, "");
static_assert(offsetof(DrIniSys, unknown98) == 0x98, "");
static_assert(offsetof(DrIniSys, unknown878) == 0x878, "");
static_assert(offsetof(DrIniSys, unknown880) == 0x880, "");
static_assert(offsetof(DrIniSys, unknown890) == 0x890, "");
static_assert(offsetof(DrIniSys, unknown898) == 0x898, "");
static_assert(offsetof(DrIniSys, unknown8a0) == 0x8a0, "");
static_assert(offsetof(DrIniSys, unknown970) == 0x970, "");
static_assert(offsetof(DrIniSys, m_IBLEnvTexturePath) == 0x1a80, "");
static_assert(offsetof(DrIniSys, unknown1b88) == 0x1b88, "");

} // namespace ml
