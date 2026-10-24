#include "framework/render/render_param.h"

#include "framework/framework.h"
#include "idcoli/idcoli.h"
#include "ml/scn.h"
#include "scn/scn_render_dr_env_coli.h"
#include "scn/scn_render_dr_sys_parm_acc.h"

namespace fw {

void RenderParam::initialize() {}

void RenderParam::finalize() {}

void RenderParam::setPlayerPosition(const mm::Vec3 &position, CAMERA_TYPE type) {
  ml::ScnRenderDrSysParmAcc parmAcc(Framework::get()->unknown58->unknown38, type);
  parmAcc.setPlayerPos(position);
}

bool RenderParam::isRoom(const mm::Vec3 &position, CAMERA_TYPE type) {
  ml::ScnRenderDrEnvColi envColi(type);
  if (envColi.testEnvColi(position, 0.5f)) {
    return envColi.isRoom();
  }

  return false;
}

void RenderParam::setMotionBlur(bool isEnable, CAMERA_TYPE type) {
  ml::ScnRenderDrSysParmAcc parmAcc(Framework::get()->unknown58->unknown38, type);
  parmAcc.setMotBlurDefault(isEnable);
}

void RenderParam::setTime(u32 hour, u32 minute, CAMERA_TYPE type) {
  ml::ScnRenderDrSysParmAcc parmAcc(Framework::get()->unknown58->unknown38, type);
  parmAcc.setTimeVal(static_cast<f32>(hour * 60 + minute) / 1440.0f);
}

void RenderParam::setWeather(u32 weather, CAMERA_TYPE type) {
  ml::ScnRenderDrSysParmAcc parmAcc(Framework::get()->unknown58->unknown38, type);
  parmAcc.setWeather(weather);
}

int RenderParam::getWindIndex(CAMERA_TYPE type) {
  ml::ScnRenderDrEnvColi envColi(type);
  return envColi.getWindId();
}

void RenderParam::setGlobalWindPower(const mm::Vec3 &power, CAMERA_TYPE type) {
  ml::ScnRenderDrSysParmAcc parmAcc(Framework::get()->unknown58->unknown38, type);
  parmAcc.setGlobalWind(power);
}

void RenderParam::setColorFilter(int filter, int farFilter, f32 time, CAMERA_TYPE type) {
  ml::ScnRenderDrSysParmAcc parmAcc(Framework::get()->unknown58->unknown38, type);
  parmAcc.setColorFilterOverride(true);
  parmAcc.setColorFilterNum(filter);
  parmAcc.setColorFilterFarNum(farFilter);
  parmAcc.setColorFilterFrm(time * 30.0f);
}

void RenderParam::resetColorFilter(f32 time, CAMERA_TYPE type) {}

void RenderParam::setCloudSea(u32 num) {
  {
    ml::ScnRenderDrSysParmAcc parmAcc(Framework::get()->unknown58->unknown38, 0);
    parmAcc.setPlaneCloudNum(num);
  }

  idcoli::IDColiAccMan accMan;
  accMan.setSubNum(num);
}

void RenderParam::resetScene() {
  ml::ScnRenderDrSysParmAcc parmAcc(Framework::get()->unknown58->unknown38, 0);
  parmAcc.resetScene();
}

} // namespace fw
