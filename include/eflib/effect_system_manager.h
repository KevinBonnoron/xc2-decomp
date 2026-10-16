#pragma once
#include "types.h"

namespace effect {

struct SendParam;

class SystemManager {
public:
  static SystemManager *&getPtr();
  static bool isValid();
  static void destroy();
  static void setUserFuncClear();

  void setIBLSaturation(f32 saturation);
  void setDirScale(f32 scale);
  void setSpecScale(f32 scale);
  void setResponsiveAA(f32 responsiveAA);
  void setAllDisp(bool isDisp);
  void setDisableCollision(bool isDisable);
  void es_pause(bool isPause);
  u32 es_create(void *data, bool isLoop);
  void es_set_param_pos_only(u32 handle, const SendParam *param);
  void es_set_param_pos_only2(u32 handle, const SendParam *param);
  void es_set_category(u32 handle, u32 category);
  void es_set_param(u32 handle, const SendParam *param);
  void es_set_alpha(u32 handle, f32 alpha);
  void es_set_speed(u32 handle, f32 speed);
  void es_set_viewnum(u32 handle, int viewnum);
  u32 es_create(void *data, const SendParam *param, bool isLoop);
  void es_set_disp(u32 handle, int isDisp);
  void es_fade_core(void *data, u32 handle, int frame);
  int es_isalive(u32 handle);
  bool es_getDeadFlag(u32 handle);
  bool es_is_loop(void *data) const;
  bool es_contais_cam_axis(void *data);
  void getNum(u32 &emitterNum, u32 &particleNum, u32 &drawNum);
  void getNumDetail(u32 &emitterNum, u32 &particleNum, u32 &drawNum, u32 &workNum);
  u32 getEmitterForm(u32 handle);

  u8 _00[0x0b - 0x00];
  bool dispEmitter;
  bool isDispEmitterSet;
  u8 _0d[0x7824a - 0x0d];
  bool dispParticleTexture;
  bool workTexture;
};

} // namespace effect
