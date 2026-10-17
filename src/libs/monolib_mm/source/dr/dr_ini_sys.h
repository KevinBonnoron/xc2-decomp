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

  DrMan *m_drMan;
  u8 _08[0x38 - 0x08];
  FileResTh *m_toonRimRes;
  FileResTh *m_volumeRes[5];
  u8 _68[0x98 - 0x68];
  grlib::CGLibTextureBuffer m_textures[18];
  u8 _878[0x880 - 0x878];
  ScnObjModel *m_mirrorBall;
  bool m_updateMirrorBallPos;
  u8 _889[0x898 - 0x889];
  FileResTh *m_glassBreakageRes;
};

static_assert(offsetof(DrIniSys, m_toonRimRes) == 0x38, "");
static_assert(offsetof(DrIniSys, m_textures) == 0x98, "");
static_assert(offsetof(DrIniSys, m_mirrorBall) == 0x880, "");
static_assert(offsetof(DrIniSys, m_glassBreakageRes) == 0x898, "");

} // namespace ml
