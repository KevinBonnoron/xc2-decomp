#include "dr/dr_ini_sys.h"

#include "grlib/cglib_texture.h"
#include "ml/file_res_th.h"
#include "ml/scn_obj_model.h"
#include <stdlib.h>
#include <string.h>

namespace ml {

bool DrIniSys::chkOnOff(const char *value) { return strcmp("on", value) == 0; }

f32 DrIniSys::getFloatWork(const char *value) { return atof(value); }

int DrIniSys::getIntWork(const char *value) { return atoi(value); }

void DrIniSys::setDefTexture(int index, void *data, int size) {
  grlib::CGLibTexture::createTextureImagePtrs(m_textures[index], data, size, false, nullptr, true);
}

void DrIniSys::loadToonRimTexture() {
  if (m_toonRimRes != nullptr) {
    m_toonRimRes->Release();
    m_toonRimRes = nullptr;
  }
  m_toonRimRes = readTextureMapFile(TOON_RIM_FILE);
  grlib::CGLibTexture::createTextureImagePtrs(m_textures[6], m_toonRimRes->buffer, m_toonRimRes->size, false, nullptr, true);
}

void DrIniSys::reloadToonGradTexture() { loadToonGradTexture(); }

void DrIniSys::reloadToonRimTexture() {
  if (m_toonRimRes != nullptr) {
    m_toonRimRes->Release();
    m_toonRimRes = nullptr;
  }
  m_toonRimRes = readTextureMapFile(TOON_RIM_FILE);
  grlib::CGLibTexture::createTextureImagePtrs(m_textures[6], m_toonRimRes->buffer, m_toonRimRes->size, false, nullptr, true);
}

void DrIniSys::reloadIBLEnvTexture() { loadIBLEnvTexture(); }

bool DrIniSys::getDispMirrorBall() const {
  if (m_mirrorBall == nullptr) {
    return false;
  }
  return m_mirrorBall->isDisp();
}

void DrIniSys::setDispMirrorBall(bool isDisp) {
  if (isDisp && m_mirrorBall == nullptr) {
    loadMirrorBallModel();
  }
  if (m_mirrorBall != nullptr) {
    m_mirrorBall->setDisp(isDisp);
  }
}

bool DrIniSys::getUpdateMirrorBallPos() const { return m_updateMirrorBallPos; }

void DrIniSys::setUpdateMirrorBallPos(bool isUpdate) { m_updateMirrorBallPos = isUpdate; }

void DrIniSys::setMirrorBallPosition(const mm::Vec3 &position) {
  if (m_mirrorBall != nullptr && m_updateMirrorBallPos) {
    m_mirrorBall->setPos(position);
  }
}

void DrIniSys::setStrWork(char *dst, const char *src) {
  while (*src != '\0') {
    *dst++ = *src++;
  }
  *dst = '\0';
}

void DrIniSys::setLutTexture(int index, void *data, int size) {
  grlib::CGLibTexture::createTextureImagePtrs(m_textures[index], data, size, false, nullptr, true);
}

void DrIniSys::setCubeTexture(int index, void *data, int size) {
  grlib::CGLibTexture::createTextureImagePtrs(m_textures[index], data, size, false, nullptr, true);
}

void DrIniSys::reloadMirrorBallModel() { loadMirrorBallModel(); }

void DrIniSys::reloadRainDropTexture() { loadRainDropTexture(); }

void DrIniSys::reloadFlagWaveTexture() { loadFlagWaveTexture(); }

const void *DrIniSys::getGlassBreakage() const { return m_glassBreakageRes->buffer; }

} // namespace ml
