#include "ptlib/particle_system.h"

#include "mm/mm_std_base.h"
#include "ptlib/emitter/particle_emitter_manager.h"
#include "ptlib/renderer/particle_renderer_manager.h"

namespace ptlib {

ParticleManager::AllocFunc ParticleManager::s_pAllocFuncSys;
ParticleManager::FreeFunc ParticleManager::s_pFreeFuncSys;
ParticleManager::AllocFunc ParticleManager::s_pAllocFuncRes;
ParticleManager::FreeFunc ParticleManager::s_pFreeFuncRes;
ParticleManager::GetHandleFunc ParticleManager::s_pGetSysHandle;
ParticleManager::GetHandleFunc ParticleManager::s_pGetResHandle;
ParticleManager::ReadFunc ParticleManager::s_pReadFunc;
ParticleManager::ReadEndFunc ParticleManager::s_pReadEndFunc;
ParticleManager::OutputStringFunc ParticleManager::s_pOutputDebugStringFunc;
ParticleManager::OutputStringFunc ParticleManager::s_pOutputWarnStringFunc;
ParticleManager::DrFunc ParticleManager::s_pDrFunc;

namespace {
ParticleManager *s_instance;
} // namespace

bool ParticleManager::isValid() { return getPtr() != nullptr; }

ParticleManager *&ParticleManager::getPtr() { return s_instance; }

ParticleManager *ParticleManager::get() {
  MM_ASSERT(getPtr());
  return getPtr();
}

void ParticleManager::setUserAllocFunc(AllocFunc allocSys, FreeFunc freeSys, AllocFunc allocRes, FreeFunc freeRes, GetHandleFunc getSysHandle, GetHandleFunc getResHandle) {
  s_pAllocFuncSys = allocSys;
  s_pFreeFuncSys = freeSys;
  s_pAllocFuncRes = allocRes;
  s_pFreeFuncRes = freeRes;
  s_pGetSysHandle = getSysHandle;
  s_pGetResHandle = getResHandle;
}

void ParticleManager::setUserFileFunc(ReadFunc read, ReadEndFunc readEnd) {
  s_pReadFunc = read;
  s_pReadEndFunc = readEnd;
}

void ParticleManager::setUserOutputString(OutputStringFunc outputDebug, OutputStringFunc outputWarn) {
  s_pOutputDebugStringFunc = outputDebug;
  s_pOutputWarnStringFunc = outputWarn;
}

void ParticleManager::setUserDrFunc(void *(*createMdl)(const void *, const char *, int, const void *, int), void (*deleteMdl)(void *), void *(*createLgt)(u32, int), void (*deleteLgt)(u32, void *),
                                    void (*setMdlPos)(void *, void *), void (*setMdlMatrix)(void *, void *), void (*setMdlColor)(void *, void *), void (*setMdlAlpha)(void *, f32),
                                    void (*setMdlSpd)(void *, void *), void (*setLgtPos)(u32, void *, void *), void (*setLgtMatrix)(u32, void *, void *), void (*setLgtParam)(u32, void *, void *),
                                    void (*debugRenderer)(void *), void *(*createGrp)(int, int), void (*destroyGrp)(void *)) {
  s_pDrFunc.unknown00 = createMdl;
  s_pDrFunc.unknown08 = deleteMdl;
  s_pDrFunc.unknown10 = createLgt;
  s_pDrFunc.unknown18 = deleteLgt;
  s_pDrFunc.unknown20 = setMdlPos;
  s_pDrFunc.unknown28 = setMdlMatrix;
  s_pDrFunc.unknown30 = setMdlColor;
  s_pDrFunc.unknown38 = setMdlAlpha;
  s_pDrFunc.unknown40 = setMdlSpd;
  s_pDrFunc.unknown48 = setLgtPos;
  s_pDrFunc.unknown50 = setLgtMatrix;
  s_pDrFunc.unknown58 = setLgtParam;
  s_pDrFunc.unknown60 = createGrp;
  s_pDrFunc.unknown68 = destroyGrp;
  s_pDrFunc.unknown70 = debugRenderer;
}

void *ParticleManager::sysAlloc(u32 size, u32 alignment, const char *file, u32 line) {
  void *ptr = s_pAllocFuncSys(nullptr, size, alignment, file, line);
  MM_ASSERT(ptr);
  return ptr;
}

void ParticleManager::clear() {
  unknown160 = nullptr;
  unknown15c = 0.0f;
  unknown148 = 0.25f;
  unknown14c = 0.0f;
  unknown150 = 1.0f;
  _154 = 1.0f;
  unknown158 = 1.0f;
  for (int i = 0; i < 4; i++) {
    unknown170[i] = nullptr;
  }
}

FxParam *ParticleManager::getFxParam() { return &m_fxParam; }

void ParticleManager::fxcore_setup_target() {
  if (renderer::RenderManager::getPtr() != nullptr) {
    renderer::RenderManager::getPtr()->fxcore_setup_target();
  }
}

void *ParticleManager::createGrp(int index, int count) { return s_pDrFunc.unknown60(index, count); }

void ParticleManager::destroyGrp(void *group) { s_pDrFunc.unknown68(group); }

void ParticleManager::sysFree(void *ptr) { s_pFreeFuncSys(nullptr, ptr); }

void *ParticleManager::resAlloc(u32 size, u32 alignment, const char *file, u32 line) { return s_pAllocFuncRes(nullptr, size, alignment, file, line); }

void ParticleManager::resFree(void *ptr) { s_pFreeFuncRes(nullptr, ptr); }

mtl::ALLOC_HANDLE ParticleManager::getSysHandle() { return s_pGetSysHandle(); }

mtl::ALLOC_HANDLE ParticleManager::getResHandle() { return s_pGetResHandle(); }

void *ParticleManager::readFileBlock(const char *path, int &size) { return s_pReadFunc(path, size); }

void ParticleManager::outputString(const char *text) { s_pOutputDebugStringFunc(text); }

void ParticleManager::outputWarning(const char *text) { s_pOutputWarnStringFunc(text); }

void *ParticleManager::createMdl(const void *model, const char *name, int index, const void *texture, int textureIndex) { return s_pDrFunc.unknown00(model, name, index, texture, textureIndex); }

void ParticleManager::deleteMdl(void *model) { s_pDrFunc.unknown08(model); }

void ParticleManager::setMdlPos(void *model, void *pos) { s_pDrFunc.unknown20(model, pos); }

void ParticleManager::setMdlMatrix(void *model, void *matrix) { s_pDrFunc.unknown28(model, matrix); }

void ParticleManager::setMdlColor(void *model, void *color) { s_pDrFunc.unknown30(model, color); }

void ParticleManager::setMdlAlpha(void *model, f32 alpha) { s_pDrFunc.unknown38(model, alpha); }

void ParticleManager::setMdlSpd(void *model, void *speed) { s_pDrFunc.unknown40(model, speed); }

void *ParticleManager::createLgt(u32 type, int index) { return s_pDrFunc.unknown10(type, index); }

void ParticleManager::deleteLgt(u32 type, void *light) { s_pDrFunc.unknown18(type, light); }

void ParticleManager::setLgtPos(u32 type, void *light, void *pos) { s_pDrFunc.unknown48(type, light, pos); }

void ParticleManager::setLgtMatrix(u32 type, void *light, void *matrix) { s_pDrFunc.unknown50(type, light, matrix); }

void ParticleManager::setLgtParam(u32 type, void *light, void *param) { s_pDrFunc.unknown58(type, light, param); }

void ParticleManager::debugRenderer(void *renderer) { s_pDrFunc.unknown70(renderer); }

int ParticleManager::get_prio_idx(int priority) {
  int index = 0;
  if (priority > 0x20) {
    index++;
  }
  if (priority > 0x40) {
    index++;
  }
  if (priority > 0x60) {
    index++;
  }
  if (priority > 0x7f) {
    index++;
  }
  if (priority > 0x80) {
    index++;
  }
  if (priority > 0xa0) {
    index++;
  }
  if (priority > 0xbf) {
    index++;
  }
  if (priority > 0xe0) {
    index++;
  }
  if (priority > 0xfe) {
    index++;
  }
  return index;
}

renderer::RenderManager &ParticleManager::getRenderManager() { return *renderer::RenderManager::get(); }

bool ParticleManager::emitter_set_check(FxHeader *header) { return emitter::EmitterManager::get()->emitter_set_check(header); }

void ParticleManager::emitter_set_free_all(bool isForce) { emitter::EmitterManager::get()->emitter_set_free_all_sub(isForce); }

FxHeader *ParticleManager::emitter_set_search(int type, const char *name, void *owner, u32 category) { return emitter::EmitterManager::get()->emitter_set_search(type, name, owner, category); }

void ParticleManager::emitter_set_param_pos_only(u32 handle, emitter::EmitterParam *param) { emitter::EmitterManager::get()->emitter_set_param_pos_only(handle, param); }

void ParticleManager::emitter_set_param_pos_only2(u32 handle, emitter::EmitterParam *param) { emitter::EmitterManager::get()->emitter_set_param_pos_only2(handle, param); }

void ParticleManager::emitter_set_param(u32 handle, emitter::EmitterParam *param) { emitter::EmitterManager::get()->emitter_set_param(handle, param); }

void ParticleManager::emitter_set_param(FxHeader *header, emitter::EmitterParam *param) { emitter::EmitterManager::get()->emitter_set_param(header, param); }

void ParticleManager::emitter_set_casname(u32 handle, const void *model, const char *name, int index, f32 frame, int flags) {
  emitter::EmitterManager::get()->emitter_set_casname(handle, model, name, index, frame, flags);
}

void ParticleManager::emitter_set_casparam(u32 handle, const void *model, emitter::EmitterParam *param) { emitter::EmitterManager::get()->emitter_set_casparam(handle, model, param); }

void ParticleManager::emitter_set_disp(u32 handle, int isDisp) { emitter::EmitterManager::get()->emitter_set_disp(handle, isDisp); }

void ParticleManager::emitter_set_alpha(u32 handle, f32 alpha) { emitter::EmitterManager::get()->emitter_set_alpha(handle, alpha); }

void ParticleManager::emitter_set_speed(u32 handle, f32 speed) { emitter::EmitterManager::get()->emitter_set_speed(handle, speed); }

void ParticleManager::emitter_set_category(u32 handle, u32 category) { emitter::EmitterManager::get()->emitter_set_category(handle, category); }

void ParticleManager::emitter_set_viewnum(u32 handle, int viewnum) { emitter::EmitterManager::get()->emitter_set_viewnum(handle, viewnum); }

void ParticleManager::emitter_set_nowait(u32 handle, int isNoWait) { emitter::EmitterManager::get()->emitter_set_nowait(handle, isNoWait); }

void ParticleManager::emitter_set_fadeout(u32 handle, int frame) { emitter::EmitterManager::get()->emitter_set_fadeout(handle, frame); }

void ParticleManager::emitter_set_fadeout(FxHeader *header, int frame) { emitter::EmitterManager::get()->emitter_set_fadeout(header, frame); }

void ParticleManager::emitter_set_fadeout(void *owner, int frame) { emitter::EmitterManager::get()->emitter_set_fadeout(owner, frame); }

void ParticleManager::set_pause(bool isPause) { m_fxParam.unknown0e = isPause; }

void ParticleManager::emitter_pack_free(u64 pack) { emitter::EmitterManager::get()->emitter_pack_free(pack); }

void ParticleManager::emitter_set_free(FxHeader *header, int frame) { emitter::EmitterManager::get()->emitter_set_free(header, frame); }

void ParticleManager::emitter_alloc01_set_draw(emitter::EmitterObj *emitter, emitter::EmitterArg *arg) { renderer::RenderManager::get()->setEmitterDraw(emitter, arg); }

void ParticleManager::move() {
  if (m_fxParam.unknown10) {
    return;
  }
  if (!m_fxParam.unknown0d) {
    unknown15c += 1.0f;
    if (unknown15c >= 1.0f) {
      do {
        emitter::EmitterManager::get()->emitter_update(0, 1.0f, false);
        unknown15c -= 1.0f;
      } while (unknown15c >= 1.0f);
    } else {
      emitter::EmitterManager::get()->emitter_update(0, 1.0f, true);
    }
  }
  emitter::EmitterManager::get()->move();
}

void ParticleManager::draw(const DrDrawWorkInfoEF *info, int viewIndex, bool isBlur) {
  renderer::RenderManager &renderManager = get()->getRenderManager();
  renderManager.setDrInfo(info);
  emitter::EmitterManager *emitterManager = emitter::EmitterManager::get();
  if (isBlur) {
    renderManager.draw(*emitterManager, m_fxParam, viewIndex, 1);
  } else {
    renderManager.draw(*emitterManager, m_fxParam, viewIndex, 0);
  }
}

void ParticleManager::setDrInfo(const DrDrawWorkInfoEF *info) { get()->getRenderManager().setDrInfo(info); }

} // namespace ptlib
