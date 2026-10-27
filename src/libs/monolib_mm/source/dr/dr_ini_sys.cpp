#include "dr/dr_ini_sys.h"

#include "grlib/cglib_texture.h"
#include "ml/file_res_th.h"
#include "ml/scn_obj_model.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace ml {

namespace {

// Inferred helper: reloads the volume textures; original name unknown.
inline void unknown001(DrIniSys *self) {
  for (int i = 0; i < 5; i++) {
    char name[128];
    snprintf(name, sizeof(name), "%s%d", VOLUME_FILE, i);
    if (self->unknown40[i] != nullptr) {
      self->unknown40[i]->Release();
      self->unknown40[i] = nullptr;
    }
    self->unknown40[i] = self->readTextureMapFile(name);
    grlib::CGLibTexture::createTextureImagePtrs(self->unknown98[7 + i], self->unknown40[i]->unknownc8, self->unknown40[i]->unknownd0, false, nullptr, true);
  }
}

} // namespace

bool DrIniSys::chkOnOff(const char *value) { return strcmp("on", value) == 0; }

f32 DrIniSys::getFloatWork(const char *value) { return atof(value); }

int DrIniSys::getIntWork(const char *value) { return atoi(value); }

void DrIniSys::setDefTexture(int index, void *data, int size) { grlib::CGLibTexture::createTextureImagePtrs(unknown98[index], data, size, false, nullptr, true); }

void DrIniSys::loadToonRimTexture() {
  if (unknown38 != nullptr) {
    unknown38->Release();
    unknown38 = nullptr;
  }
  unknown38 = readTextureMapFile(TOON_RIM_FILE);
  grlib::CGLibTexture::createTextureImagePtrs(unknown98[6], unknown38->unknownc8, unknown38->unknownd0, false, nullptr, true);
}

void DrIniSys::loadVolumeTexture() { unknown001(this); }

void DrIniSys::reloadVolumeTexture() { unknown001(this); }

void DrIniSys::reloadToonGradTexture() { loadToonGradTexture(); }

void DrIniSys::reloadToonRimTexture() {
  if (unknown38 != nullptr) {
    unknown38->Release();
    unknown38 = nullptr;
  }
  unknown38 = readTextureMapFile(TOON_RIM_FILE);
  grlib::CGLibTexture::createTextureImagePtrs(unknown98[6], unknown38->unknownc8, unknown38->unknownd0, false, nullptr, true);
}

void DrIniSys::reloadIBLEnvTexture() { loadIBLEnvTexture(); }

bool DrIniSys::getDispMirrorBall() const {
  if (unknown880 == nullptr) {
    return false;
  }
  return unknown880->isDisp();
}

void DrIniSys::setDispMirrorBall(bool isDisp) {
  if (isDisp && unknown880 == nullptr) {
    loadMirrorBallModel();
  }
  if (unknown880 != nullptr) {
    unknown880->setDisp(isDisp);
  }
}

bool DrIniSys::getUpdateMirrorBallPos() const { return m_updateMirrorBallPos; }

void DrIniSys::setUpdateMirrorBallPos(bool isUpdate) { m_updateMirrorBallPos = isUpdate; }

void DrIniSys::setMirrorBallPosition(const mm::Vec3 &position) {
  if (unknown880 != nullptr && m_updateMirrorBallPos) {
    unknown880->setPos(position);
  }
}

void DrIniSys::setStrWork(char *dst, const char *src) {
  while (*src != '\0') {
    *dst++ = *src++;
  }
  *dst = '\0';
}

void DrIniSys::setLutTexture(int index, void *data, int size) { grlib::CGLibTexture::createTextureImagePtrs(unknown98[index], data, size, false, nullptr, true); }

void DrIniSys::setCubeTexture(int index, void *data, int size) { grlib::CGLibTexture::createTextureImagePtrs(unknown98[index], data, size, false, nullptr, true); }

void DrIniSys::reloadMirrorBallModel() { loadMirrorBallModel(); }

void DrIniSys::reloadRainDropTexture() { loadRainDropTexture(); }

void DrIniSys::reloadFlagWaveTexture() { loadFlagWaveTexture(); }

const void *DrIniSys::getGlassBreakage() const { return unknown898->unknownc8; }

} // namespace ml
