#include "device/nx/dev_graph_nx.h"

#include "font/color.h"
#include "font/write_str.h"
#include "grlib/cglib_manager.h"
#include "grlib/cglib_state.h"
#include "ml/deb_draw_cmd.h"
#include "ml/work_cpu.h"
#include "ml/work_root.h"
#include "ml/work_util.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"
#include "mtl/alloc_handle.h"

namespace ml {

DevGraphNx::DevGraphNx(const char *name, WorkObj *parent) : DevGraph(name, parent), unknown370(0), unknown6d0(nullptr) {}

int DevGraphNx::getRootWidthSys() { return WorkRoot::getWidth(); }

int DevGraphNx::getRootHeightSys() { return WorkRoot::getHeight(); }

f32 DevGraphNx::getCostSys() const {
  u32 time = grlib::CGLibManager::get()->getGpuTimeStamp();
  return static_cast<f32>(time / 1000) * 0.000001f / getFrameSyncSec() * 100.0f + 3.0f;
}

void DevGraphNx::grSetViewportSys(const mm::Rect<int> &viewport, int index) {
  grlib::CGLibState::setOnlyViewport(grlib::LibMainStateViewPort(viewport.x, viewport.y, viewport.width, viewport.height, 0.0f, 1.0f));
}

void DevGraphNx::grSetScissorSys(const mm::Rect<int> &scissor) { grlib::CGLibState::setOnlyScissor(grlib::LibMainStateViewPort(scissor.x, scissor.y, scissor.width, scissor.height, 0.0f, 1.0f)); }

void DevGraphNx::renderBeginSys() {
  if (get() != nullptr) {
    setRenderState(RSTAT_UNKNOWN_0);
    grClearScreen();
  }
}

void DevGraphNx::renderEndSys() {
  if (get() != nullptr) {
    setRenderState(RSTAT_UNKNOWN_1);
  }
}

u32 DevGraphNx::thSync(void *argument, void *userData) {
  grlib::CGLibManager::get()->swap();
  setRenderState(RSTAT_UNKNOWN_2);
  return 0;
}

void DevGraphNx::resetSizeSys(s16 width, s16 height) {}

u32 DevGraphNx::fontGetWidthSys(const char *text, FONT_STYLE style, f32 scale) {
  WriteStr writer;
  writer.set_font(&static_cast<DevGraphNx *>(get())->unknown378);
  writer.set_scale(scale, scale);
  return writer.calc_string_width(text);
}

u32 DevGraphNx::fontGetHeightSys(FONT_STYLE style, f32 scale) {
  WriteStr writer;
  writer.set_font(&static_cast<DevGraphNx *>(get())->unknown378);
  return writer.get_origin_size() * scale;
}

void DevGraphNx::fontDrawSys(s16 x, s16 y, f32 scaleX, f32 scaleY, const char *text, const mm::Col4 *color, bool isShadow) {
  WriteStr writer;
  writer.set_font(&static_cast<DevGraphNx *>(get())->unknown378);
  writer.set_pos(x, y);
  writer.set_scale(scaleX, scaleY);
  if (color != nullptr) {
    writer.set_color(Color(color->r * 255.0f, color->g * 255.0f, color->b * 255.0f, color->a * 255.0f));
  }
  writer.print(text, false);
}

void DevGraphNx::wkUpdate() {}

void DevGraphNx::wkRender() {}

bool DevGraphNx::wkStandbyLogin() {
  if (!DevGraph::wkStandbyLogin()) {
    return false;
  }
  if (!WorkRoot::isWinDestroy()) {
    WorkCpu::runThread(WorkCpu::getRenderCPUID(), thInitialize, this, nullptr, nullptr, false, WKCPU_SYNC_UNKNOWN_0);
    new (WorkUtil::getWorkMem()) DebDrawCmd();
  }
  return true;
}

u32 DevGraphNx::thInitialize(void *argument, void *userData) { return initGL(); }

u32 DevGraphNx::thDestroy(void *argument, void *userData) {
  grlib::CGLibManager::get()->deviceRelease();
  return 1;
}

} // namespace ml
