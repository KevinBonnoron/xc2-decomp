#pragma once
#include <stddef.h>

#include "grlib/cglib_texture_buffer.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {

class DrMan;
class FileResTh;
class ScnObjModel;

extern const char *TOON_RIM_FILE;
extern const char *VOLUME_FILE;

class DrIniSys {
public:
  bool chkOnOff(const char *value);
  f32 getFloatWork(const char *value);
  int getIntWork(const char *value);
  FileResTh *readTextureMapFile(const char *name);
  void setDefTexture(int index, void *data, int size);
  void loadRainDropTexture();
  void loadToonGradTexture();
  void loadToonRimTexture();
  void loadVolumeTexture();
  void loadIBLEnvTexture();
  void loadFlagWaveTexture();
  void reloadToonGradTexture();
  void reloadToonRimTexture();
  void reloadVolumeTexture();
  void reloadIBLEnvTexture();
  bool getDispMirrorBall() const;
  void setDispMirrorBall(bool isDisp);
  void loadMirrorBallModel();
  bool getUpdateMirrorBallPos() const;
  void setUpdateMirrorBallPos(bool isUpdate);
  void setMirrorBallPosition(const mm::Vec3 &position);
  void setStrWork(char *dst, const char *src);
  void setLutTexture(int index, void *data, int size);
  void setCubeTexture(int index, void *data, int size);
  void reloadMirrorBallModel();
  void reloadRainDropTexture();
  void reloadFlagWaveTexture();
  const void *getGlassBreakage() const;

  DrMan *unknown00; // Inferred role: dr man; original member name unknown.
  u8 _08[0x38 - 0x08];
  FileResTh *unknown38;    // Inferred role: toon rim res; original member name unknown.
  FileResTh *unknown40[5]; // Inferred role: volume res; original member name unknown.
  u8 _68[0x98 - 0x68];
  grlib::CGLibTextureBuffer unknown98[18]; // Inferred role: textures; original member name unknown.
  u8 _878[0x880 - 0x878];
  ScnObjModel *unknown880; // Inferred role: mirror ball; original member name unknown.
  bool m_updateMirrorBallPos;
  u8 _889[0x898 - 0x889];
  FileResTh *unknown898; // Inferred role: glass breakage res; original member name unknown.
  u8 _8a0[0xb6c - 0x8a0];
  bool unknownb6c; // Inferred role: mot blur default; original member name unknown.
};

static_assert(offsetof(DrIniSys, unknown38) == 0x38, "");
static_assert(offsetof(DrIniSys, unknown98) == 0x98, "");
static_assert(offsetof(DrIniSys, unknown880) == 0x880, "");
static_assert(offsetof(DrIniSys, unknown898) == 0x898, "");
static_assert(offsetof(DrIniSys, unknownb6c) == 0xb6c, "");

} // namespace ml
