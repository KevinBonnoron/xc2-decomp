#pragma once
#include <stddef.h>

#include "mtl/alloc_handle.h"
#include "types.h"

namespace ptlib {

struct DrDrawWorkInfoEF;
struct FxHeader;

namespace emitter {
struct EmitterArg;
class EmitterObj;
struct EmitterParam;
} // namespace emitter

namespace renderer {
class RenderManager;
} // namespace renderer

struct FxParam {
  u8 _00[0x0d - 0x00];
  bool m_isPause;
  bool m_isPauseRequest;
  u8 _0f[0x10 - 0x0f];
  bool m_isStop;
  u8 _11[0x18 - 0x11];
};

static_assert(offsetof(FxParam, m_isPause) == 0x0d, "");
static_assert(offsetof(FxParam, m_isStop) == 0x10, "");
static_assert(sizeof(FxParam) == 0x18, "");

class ParticleManager {
public:
  using AllocFunc = void *(*)(void *allocator, u32 size, u32 alignment, const char *file, u32 line);
  using FreeFunc = void (*)(void *allocator, void *ptr);
  using GetHandleFunc = mtl::ALLOC_HANDLE (*)();
  using ReadFunc = void *(*)(const char *path, int &size);
  using ReadEndFunc = void (*)(void *data);
  using OutputStringFunc = void (*)(const char *text);

  struct DrFunc {
    void *(*m_createMdl)(const void *model, const char *name, int index, const void *texture, int textureIndex);
    void (*m_deleteMdl)(void *model);
    void *(*m_createLgt)(u32 type, int index);
    void (*m_deleteLgt)(u32 type, void *light);
    void (*m_setMdlPos)(void *model, void *pos);
    void (*m_setMdlMatrix)(void *model, void *matrix);
    void (*m_setMdlColor)(void *model, void *color);
    void (*m_setMdlAlpha)(void *model, f32 alpha);
    void (*m_setMdlSpd)(void *model, void *speed);
    void (*m_setLgtPos)(u32 type, void *light, void *pos);
    void (*m_setLgtMatrix)(u32 type, void *light, void *matrix);
    void (*m_setLgtParam)(u32 type, void *light, void *param);
    void *(*m_createGrp)(int index, int count);
    void (*m_destroyGrp)(void *group);
    void (*m_debugRenderer)(void *renderer);
    u8 _78[0x80 - 0x78];
  };

  static AllocFunc s_pAllocFuncSys;
  static FreeFunc s_pFreeFuncSys;
  static AllocFunc s_pAllocFuncRes;
  static FreeFunc s_pFreeFuncRes;
  static GetHandleFunc s_pGetSysHandle;
  static GetHandleFunc s_pGetResHandle;
  static ReadFunc s_pReadFunc;
  static ReadEndFunc s_pReadEndFunc;
  static OutputStringFunc s_pOutputDebugStringFunc;
  static OutputStringFunc s_pOutputWarnStringFunc;
  static DrFunc s_pDrFunc;

  static bool isValid();
  static ParticleManager *&getPtr();
  static ParticleManager *get();
  static void setUserAllocFunc(AllocFunc allocSys, FreeFunc freeSys, AllocFunc allocRes, FreeFunc freeRes, GetHandleFunc getSysHandle,
                               GetHandleFunc getResHandle);
  static void setUserFileFunc(ReadFunc read, ReadEndFunc readEnd);
  static void setUserOutputString(OutputStringFunc outputDebug, OutputStringFunc outputWarn);
  static void setUserDrFunc(void *(*createMdl)(const void *, const char *, int, const void *, int), void (*deleteMdl)(void *),
                            void *(*createLgt)(u32, int), void (*deleteLgt)(u32, void *), void (*setMdlPos)(void *, void *),
                            void (*setMdlMatrix)(void *, void *), void (*setMdlColor)(void *, void *), void (*setMdlAlpha)(void *, f32),
                            void (*setMdlSpd)(void *, void *), void (*setLgtPos)(u32, void *, void *), void (*setLgtMatrix)(u32, void *, void *),
                            void (*setLgtParam)(u32, void *, void *), void (*debugRenderer)(void *), void *(*createGrp)(int, int),
                            void (*destroyGrp)(void *));
  static void *sysAlloc(u32 size, u32 alignment, const char *file, u32 line);
  void clear();
  FxParam *getFxParam();
  void fxcore_setup_target();
  static void *createGrp(int index, int count);
  static void destroyGrp(void *group);
  static void sysFree(void *ptr);
  static void *resAlloc(u32 size, u32 alignment, const char *file, u32 line);
  static void resFree(void *ptr);
  static mtl::ALLOC_HANDLE getSysHandle();
  static mtl::ALLOC_HANDLE getResHandle();
  static void *readFileBlock(const char *path, int &size);
  static void outputString(const char *text);
  static void outputWarning(const char *text);
  static void *createMdl(const void *model, const char *name, int index, const void *texture, int textureIndex);
  static void deleteMdl(void *model);
  static void setMdlPos(void *model, void *pos);
  static void setMdlMatrix(void *model, void *matrix);
  static void setMdlColor(void *model, void *color);
  static void setMdlAlpha(void *model, f32 alpha);
  static void setMdlSpd(void *model, void *speed);
  static void *createLgt(u32 type, int index);
  static void deleteLgt(u32 type, void *light);
  static void setLgtPos(u32 type, void *light, void *pos);
  static void setLgtMatrix(u32 type, void *light, void *matrix);
  static void setLgtParam(u32 type, void *light, void *param);
  static void debugRenderer(void *renderer);
  static void *getGrp(int index);
  int get_prio_idx(int priority);
  renderer::RenderManager &getRenderManager();
  bool emitter_set_check(FxHeader *header);
  void emitter_set_free_all(bool isForce);
  FxHeader *emitter_set_search(int type, const char *name, void *owner, u32 category);
  void emitter_set_param_pos_only(u32 handle, emitter::EmitterParam *param);
  void emitter_set_param_pos_only2(u32 handle, emitter::EmitterParam *param);
  void emitter_set_param(u32 handle, emitter::EmitterParam *param);
  void emitter_set_param(FxHeader *header, emitter::EmitterParam *param);
  void emitter_set_casname(u32 handle, const void *model, const char *name, int index, f32 frame, int flags);
  void emitter_set_casparam(u32 handle, const void *model, emitter::EmitterParam *param);
  void emitter_set_disp(u32 handle, int isDisp);
  void emitter_set_alpha(u32 handle, f32 alpha);
  void emitter_set_speed(u32 handle, f32 speed);
  void emitter_set_category(u32 handle, u32 category);
  void emitter_set_viewnum(u32 handle, int viewnum);
  void emitter_set_nowait(u32 handle, int isNoWait);
  void emitter_set_fadeout(u32 handle, int frame);
  void emitter_set_fadeout(FxHeader *header, int frame);
  void emitter_set_fadeout(void *owner, int frame);
  void set_pause(bool isPause);
  void emitter_pack_free(u64 pack);
  void emitter_set_free(FxHeader *header, int frame);
  void emitter_alloc01_set_draw(emitter::EmitterObj *emitter, emitter::EmitterArg *arg);
  void move();
  void draw(const DrDrawWorkInfoEF *info, int priority, bool isTranslucent);
  void setDrInfo(const DrDrawWorkInfoEF *info);

  u8 _000[0x130 - 0x000];
  FxParam m_fxParam;
  f32 _148;
  f32 _14c;
  f32 _150;
  f32 _154;
  f32 _158;
  f32 m_frameCount;
  const u8 *m_modelTable;
  u8 _168[0x170 - 0x168];
  void *m_groups[4];
};

static_assert(offsetof(ParticleManager, m_fxParam) == 0x130, "");
static_assert(offsetof(ParticleManager, _148) == 0x148, "");
static_assert(offsetof(ParticleManager, m_frameCount) == 0x15c, "");
static_assert(offsetof(ParticleManager, m_modelTable) == 0x160, "");
static_assert(offsetof(ParticleManager, m_groups) == 0x170, "");
static_assert(sizeof(ParticleManager::DrFunc) == 0x80, "");

} // namespace ptlib
