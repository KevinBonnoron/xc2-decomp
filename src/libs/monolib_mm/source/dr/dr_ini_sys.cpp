#include "dr/dr_ini_sys.h"

#include "csvb/csvb_data.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_post_man.h"
#include "dr/dr_pixl_post_obj_rain_drop.h"
#include "dr/dr_res_filter_data.h"
#include "grlib/cglib_texture.h"
#include "ml/file_res_th.h"
#include "ml/scn.h"
#include "ml/scn_obj_model.h"
#include "ml/work_util.h"
#include "mm_math/mm_col3.h"
#include "mtl/alloc_handle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace ml {

namespace {

// Inferred role: path buffer of the loaded files; original name unknown.
char unknown015[0x200];

// Inferred helper: reloads the volume textures; original name unknown.
inline void unknown001(DrIniSys *self) {
  for (int i = 0; i < 5; i++) {
    char name[128];
    snprintf(name, sizeof(name), "%s%d", VOLUME_FILE, i);
    self->loadTextureImpl(7 + i, name);
  }
}

// Inferred helper: takes the file from the scene entry resources, or loads it; original name unknown.
// Evidence: the same block follows the path formatting in readTextureMapFile, loadFilterLutTexture, loadGlassBreakage,
// loadCameraLight and loadMirrorBallModel.
inline FileResTh *unknown003(const DrIniSys *self, const char *path) {
  Scn *scn = Scn::get();
  if (scn != nullptr) {
    FileResTh *res = scn->allocEntryRes(path);
    if (res != nullptr) {
      return res;
    }
  }
  FileResTh *res = new (WorkUtil::getWorkMem()) FileResTh();
  res->loadBlock(self->unknown00->unknown1c, path, 0x1000, 0);
  return res;
}

} // namespace

DrIniSys::DrIniSys(DrMan *drMan)
    : unknown00(drMan), unknown878(nullptr), unknown880(nullptr), m_updateMirrorBallPos(true), unknown890(nullptr), unknown898(nullptr), unknown8a0(nullptr), m_IBLEnvTexturePath(DUMMY_CUBEMAP_FILE),
      unknown1b88(nullptr) {
  memset(unknown08, 0, sizeof(unknown08));
  m_IBLEnvTexturePath.format("%sshader/%s.witex", "/monolib/", DUMMY_CUBEMAP_FILE);
}

DrIniSys::~DrIniSys() { dataWorkClear(); }

void DrIniSys::dataWorkClear() {
  for (int i = 0; i < 18; i++) {
    if (unknown08[i] != nullptr) {
      unknown98[i].release();
      if (unknown08[i] != nullptr) {
        unknown08[i]->Release();
        unknown08[i] = nullptr;
      }
    }
  }
  if (unknown878 != nullptr) {
    unknown878->Release();
    unknown878 = nullptr;
  }
  if (unknown890 != nullptr) {
    unknown890->Release();
    unknown890 = nullptr;
  }
  if (unknown898 != nullptr) {
    unknown898->Release();
    unknown898 = nullptr;
  }
  if (unknown8a0 != nullptr) {
    unknown8a0->Release();
    unknown8a0 = nullptr;
  }
  if (unknown1b88 != nullptr) {
    delete unknown1b88;
    unknown1b88 = nullptr;
  }
}

bool DrIniSys::chkOnOff(const char *value) { return strcmp("on", value) == 0; }

f32 DrIniSys::getFloatWork(const char *value) { return atof(value); }

void DrIniSys::getdrColor3Work(mm::Col3 &color, const char *value) {
  f32 rgb[3] = {0.5f, 0.5f, 0.5f};
  int length = 0;
  int count = 0;
  for (int i = 0; i < 0x400; i++) {
    char c = value[i];
    if (c == ',') {
      unknown015[length] = '\0';
      rgb[count] = getFloatWork(unknown015);
      count++;
      if (count >= 3) {
        break;
      }
      length = 0;
    } else if (c == '\0') {
      break;
    } else {
      unknown015[length++] = c;
    }
  }
  if (length > 1 && count < 3) {
    unknown015[length] = '\0';
    rgb[count] = getFloatWork(unknown015);
  }
  color.r = rgb[0];
  color.g = rgb[1];
  color.b = rgb[2];
}

int DrIniSys::getToonDirType(const char *value) {
  const char *types[] = {"Sun", "Camera"};
  for (const char **type = types; type != types + 2; type++) {
    if (strcmp(*type, value) == 0) {
      return type - types;
    }
  }
  return 0;
}

FileResTh *DrIniSys::readTextureMapFile(const char *name) {
  snprintf(unknown015, sizeof(unknown015), "/monolib/shader/%s.witex", name);
  return unknown003(this, unknown015);
}

int DrIniSys::getIntWork(const char *value) { return atoi(value); }

void DrIniSys::setDefTexture(int index, void *data, int size) { grlib::CGLibTexture::createTextureImagePtrs(unknown98[index], data, size, false, nullptr, true); }

void DrIniSys::loadRainDropTexture() {
  loadTextureImpl(13, RAIN_DROP_FILE);
  loadTextureImpl(14, RAIN_DROP_DEPTH_FILE);
  DrPixlPostObjRainDrop *rainDrop = unknown00->unknown78->unknown10[0].unknown180->unknowna0;
  if (rainDrop != nullptr) {
    rainDrop->requestUseLoadedDepth();
  }
}

void DrIniSys::loadToonGradTexture() {
  const char *names[] = {TOON_GRAD_FILE, TOON_GRAD_NIGHT_FILE};
  for (int i = 0; i < 2; i++) {
    loadTextureImpl(4 + i, names[i]);
  }
}

void DrIniSys::loadToonRimTexture() {
  if (unknown08[6] != nullptr) {
    unknown08[6]->Release();
    unknown08[6] = nullptr;
  }
  unknown08[6] = readTextureMapFile(TOON_RIM_FILE);
  setDefTexture(6, unknown08[6]->unknownc8, unknown08[6]->unknownd0);
}

void DrIniSys::loadVolumeTexture() { unknown001(this); }

void DrIniSys::loadIBLEnvTexture() {
  Scn *scn = Scn::get();
  if (scn != nullptr && scn->allocEntryRes(m_IBLEnvTexturePath.c_str()) != nullptr) {
    return;
  }
  FileResTh *res = new (WorkUtil::getWorkMem()) FileResTh();
  if (res->loadBlock(unknown00->unknown1c, m_IBLEnvTexturePath.c_str(), 0x1000, 0)) {
    if (unknown08[12] != nullptr) {
      unknown08[12]->Release();
      unknown08[12] = nullptr;
    }
    unknown08[12] = res;
    setCubeTexture(12, res->unknownc8, res->unknownd0);
  }
}

void DrIniSys::loadWetnessCSVBFile() {
  if (unknown1b88 == nullptr) {
    unknown1b88 = new (unknown00->unknown1c) csvb::CCsvbData();
  }
  snprintf(unknown015, sizeof(unknown015), "/monolib/shader/%s.bin", WETNESS_CSVB_FILE);
  unknown1b88->Load(unknown00->unknown1c, unknown015);
}

void DrIniSys::loadFilterLutTexture() {
  snprintf(unknown015, sizeof(unknown015), "/monolib/shader/filterlut.wiltp");
  FileResTh *res = unknown003(this, unknown015);
  if (unknown8a0 != nullptr) {
    unknown8a0->Release();
    unknown8a0 = nullptr;
  }
  unknown8a0 = res;
  unknown00->unknown98->setFilterData(res->unknownc8);
}

void DrIniSys::loadGlassBreakage() {
  snprintf(unknown015, sizeof(unknown015), "/monolib/shader/%s", GLASS_BREAKAGE);
  unknown898 = unknown003(this, unknown015);
}

void DrIniSys::loadCameraLight() {
  snprintf(unknown015, sizeof(unknown015), "/monolib/shader/%s.wilgt", CAM_LGT_FILE);
  unknown890 = unknown003(this, unknown015);
}

void DrIniSys::loadTextureImpl(u32 index, const char *name) {
  if (unknown08[index] != nullptr) {
    unknown08[index]->Release();
    unknown08[index] = nullptr;
  }
  unknown08[index] = readTextureMapFile(name);
  setDefTexture(index, unknown08[index]->unknownc8, unknown08[index]->unknownd0);
}

void DrIniSys::loadFlagWaveTexture() {
  loadTextureImpl(16, FLAG_WAVE0_FILE);
  loadTextureImpl(17, FLAG_WAVE1_FILE);
}

void DrIniSys::setIBLEnvTexturePath(const char *path) { m_IBLEnvTexturePath = path; }

void DrIniSys::reloadToonGradTexture() { loadToonGradTexture(); }

void DrIniSys::reloadToonRimTexture() {
  if (unknown08[6] != nullptr) {
    unknown08[6]->Release();
    unknown08[6] = nullptr;
  }
  unknown08[6] = readTextureMapFile(TOON_RIM_FILE);
  setDefTexture(6, unknown08[6]->unknownc8, unknown08[6]->unknownd0);
}

void DrIniSys::reloadVolumeTexture() { unknown001(this); }

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

void DrIniSys::loadMirrorBallModel() {
  snprintf(unknown015, sizeof(unknown015), "/monolib/shader/%s.wimdo", MIRROR_BALL_MDL_FILE);
  FileResTh *res = unknown003(this, unknown015);
  if (res == nullptr) {
    return;
  }
  if (unknown880 != nullptr) {
    unknown880->setDelete();
  }
  if (unknown878 != nullptr) {
    unknown878->Release();
    unknown878 = nullptr;
  }
  unknown878 = res;
  unknown880 = Scn::get()->createMdl(res->unknownc8, unknown015, 0);
}

bool DrIniSys::getUpdateMirrorBallPos() const { return m_updateMirrorBallPos; }

void DrIniSys::setUpdateMirrorBallPos(bool isUpdate) { m_updateMirrorBallPos = isUpdate; }

void DrIniSys::dispMirrorBallPerformanceMDL(WinProc *proc) {
  if (unknown880 != nullptr) {
    unknown880->dispDebugWindow(true, unknown880->getName(), proc);
  }
}

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

FileResTh *DrIniSys::readWorkFile(const char *name) {
  snprintf(unknown015, sizeof(unknown015), "monolib/shader/%s.wilut", name);
  FileResTh *res = new (WorkUtil::getWorkMem()) FileResTh();
  res->loadBlock(unknown00->unknown1c, unknown015, 0x1000, 0);
  return res;
}

void DrIniSys::setLutTexture(int index, void *data, int size) { grlib::CGLibTexture::createTextureImagePtrs(unknown98[index], data, size, false, nullptr, true); }

void DrIniSys::setCubeTexture(int index, void *data, int size) { grlib::CGLibTexture::createTextureImagePtrs(unknown98[index], data, size, false, nullptr, true); }

void DrIniSys::reloadMirrorBallModel() { loadMirrorBallModel(); }

void DrIniSys::reloadRainDropTexture() { loadRainDropTexture(); }

void DrIniSys::reloadFlagWaveTexture() { loadFlagWaveTexture(); }

void DrIniSys::getWetnessSetting(u16 index, WetSetting &setting) const {
  if (unknown1b88->GetRowCount() == 0) {
    setting.unknown00 = false;
    setting.unknown04 = 0;
    setting.unknown08 = 0;
    setting.unknown0c = unknown970.unknown109c;
  } else {
    if (index != 0 && index >= unknown1b88->GetRowCount()) {
      index = 0;
    }
    setting.unknown00 = unknown1b88->GetInt(index, 0) == 1;
    setting.unknown04 = unknown1b88->GetInt(index, 1);
    setting.unknown08 = unknown1b88->GetInt(index, 2);
    setting.unknown0c = unknown1b88->GetColumCount(index) >= 4 ? unknown1b88->GetFloat(index, 3) : unknown970.unknown109c;
  }
}

const void *DrIniSys::getGlassBreakage() const { return unknown898->unknownc8; }

} // namespace ml
