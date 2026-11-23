#pragma once
#include <stddef.h>

#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {
class DrEnvColiObj;
class DrMan;

struct DrEnvColiResult {
  DrEnvColiResult() { unknown001(); }

  // Inferred role: resets the result; original name unknown.
  void unknown001() {
    unknown00 = -1;
    unknown24 = 0;
    unknown04 = -1;
    m_bgmId = -1;
    m_layerId = 0;
    m_reverbId = 0;
    m_caveId = 0;
    m_areaId = 0;
    unknown1c = 0;
    m_windId = 0;
  }

  s32 unknown00;  // Inferred role: priority; original member name unknown.
  s32 unknown04;  // Inferred role: sub priority; original member name unknown.
  s32 m_bgmId;    // Inferred role: bgm id; named after the game accessor ml::ScnRenderDrEnvColi::getBgmId.
  s32 m_layerId;  // Inferred role: layer id; named after the game accessor ml::ScnRenderDrEnvColi::getLayerId.
  s32 m_reverbId; // Inferred role: reverb id; named after the game accessor ml::ScnRenderDrEnvColi::getReverbId.
  s32 m_caveId;   // Inferred role: cave id; named after the game accessor ml::ScnRenderDrEnvColi::getCaveId.
  s32 m_areaId;   // Inferred role: area id; named after the game accessor ml::ScnRenderDrEnvColi::getAreaId.
  s32 unknown1c;  // Inferred role: post parameter index; original member name unknown.
  s32 m_windId;   // Inferred role: wind id; named after the game accessor ml::ScnRenderDrEnvColi::getWindId.
  u32 unknown24;  // Inferred role: flags (bit 2: room); original member name unknown.
};

static_assert(offsetof(DrEnvColiResult, m_bgmId) == 0x08, "");
static_assert(offsetof(DrEnvColiResult, unknown1c) == 0x1c, "");
static_assert(offsetof(DrEnvColiResult, unknown24) == 0x24, "");
static_assert(sizeof(DrEnvColiResult) == 0x28, "");

class DrEnvColiMan {
public:
  DrEnvColiMan(DrMan *drMan);
  ~DrEnvColiMan();
  DrEnvColiObj *createObj(const void *data);
  void update();
  bool testEnvColi(DrEnvColiResult *result, const mm::Vec3 &position, f32 radius);
  void clear();
  void updateTime(bool isReset);
  void updateCloudFade(bool isReset, bool isForce);
  void updateRainDropFade(bool isReset);

  DrEnvColiObj *unknown00;           // Inferred role: first object of the list; original member name unknown.
  DrEnvColiObj *unknown08;           // Inferred role: last object of the list; original member name unknown.
  DrEnvColiObj *unknown10[2][2];     // Inferred role: stock object list (first and last) per buffer; original member name unknown.
  DrMan *m_drMan;                    // Inferred role: dr manager; original member name unknown.
  DrEnvColiObj *unknown38;           // Inferred role: current object; original member name unknown.
  DrEnvColiResult m_drEnvColiResult; // Inferred role: result; original member name unknown.
  f32 unknown68;                     // Inferred role: time; original member name unknown.
  f32 unknown6c;                     // Inferred role: weather fade ratio; original member name unknown.
  f32 unknown70;                     // Inferred role: weather fade frame; original member name unknown.
  s32 unknown74;                     // Inferred role: weather id; original member name unknown.
  f32 unknown78;                     // Inferred role: rain drop fade ratio; original member name unknown.
  f32 unknown7c;                     // Inferred role: rain drop fade frame; original member name unknown.
  u8 _80[0x84 - 0x80];
  f32 unknown84; // Inferred role: cloud fade frame; original member name unknown.
  f32 unknown88; // Inferred role: cloud fade ratio; original member name unknown.
  s32 unknown8c; // Inferred role: current post parameter index; original member name unknown.
};

static_assert(offsetof(DrEnvColiMan, unknown08) == 0x08, "");
static_assert(offsetof(DrEnvColiMan, unknown10) == 0x10, "");
static_assert(offsetof(DrEnvColiMan, m_drMan) == 0x30, "");
static_assert(offsetof(DrEnvColiMan, unknown38) == 0x38, "");
static_assert(offsetof(DrEnvColiMan, m_drEnvColiResult) == 0x40, "");
static_assert(offsetof(DrEnvColiMan, unknown68) == 0x68, "");
static_assert(offsetof(DrEnvColiMan, unknown74) == 0x74, "");
static_assert(offsetof(DrEnvColiMan, unknown78) == 0x78, "");
static_assert(offsetof(DrEnvColiMan, unknown84) == 0x84, "");
static_assert(offsetof(DrEnvColiMan, unknown8c) == 0x8c, "");
static_assert(sizeof(DrEnvColiMan) == 0x90, "");

} // namespace ml
