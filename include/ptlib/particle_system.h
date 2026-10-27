#pragma once
#include <stddef.h>

#include "mm_math/mm_mat44.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace grlib {
class CGLibRenderTarget;
} // namespace grlib

namespace ptlib {

namespace emitter {
struct EmitterArg;
class EmitterObj;
struct EmitterParam;
} // namespace emitter

namespace renderer {
class RenderManager;
} // namespace renderer

struct DrDrawWorkInfoEF {
  grlib::CGLibRenderTarget *unknown000; // Inferred role: main target; original member name unknown.
  u8 _008[0x060 - 0x008];
  grlib::CGLibRenderTarget *unknown060; // Inferred role: reduce target; original member name unknown.
  grlib::CGLibRenderTarget *unknown068; // Inferred role: sub target; original member name unknown.
  u8 _070[0x1d0 - 0x070];
  u32 unknown1d0; // Inferred role: buffer offset; original member name unknown.
  u8 _1d4[0x560 - 0x1d4];
  u32 unknown560; // Inferred role: view index; original member name unknown.
};

static_assert(offsetof(DrDrawWorkInfoEF, unknown060) == 0x060, "");
static_assert(offsetof(DrDrawWorkInfoEF, unknown068) == 0x068, "");
static_assert(offsetof(DrDrawWorkInfoEF, unknown1d0) == 0x1d0, "");
static_assert(offsetof(DrDrawWorkInfoEF, unknown560) == 0x560, "");

struct FxHeader {
  u8 _00[0x09 - 0x00];
  u8 unknown09; // Inferred role: loop; original member name unknown.
  u8 unknown0a; // Inferred role: cam axis; original member name unknown.
  u8 _0b[0x14 - 0x0b];
  char unknown14[0x20]; // Inferred role: name; original member name unknown.
  u8 _34[0x48 - 0x34];
  u64 unknown48; // Inferred role: pack; original member name unknown.
};

static_assert(offsetof(FxHeader, unknown09) == 0x09, "");
static_assert(offsetof(FxHeader, unknown14) == 0x14, "");
static_assert(offsetof(FxHeader, unknown48) == 0x48, "");

struct FxParam {
  // Inferred role: sets the default values of the parameters; original name unknown.
  void unknown001() {
    unknown0d = false;
    unknown0e = false;
    unknown0f = 1;
    unknown10 = false;
    unknown11 = 0;
    unknown12 = 0;
    unknown14 = 1;
  }

  u8 _00[0x0d - 0x00];
  bool unknown0d; // Inferred role: pause; original member name unknown.
  bool unknown0e; // Inferred role: pause request; original member name unknown.
  u8 unknown0f;   // Original member name unknown.
  bool unknown10; // Inferred role: stop; original member name unknown.
  u8 unknown11;   // Original member name unknown.
  u8 unknown12;   // Original member name unknown.
  u8 _13[0x14 - 0x13];
  u32 unknown14; // Original member name unknown.
};

static_assert(offsetof(FxParam, unknown0d) == 0x0d, "");
static_assert(offsetof(FxParam, unknown10) == 0x10, "");
static_assert(offsetof(FxParam, unknown14) == 0x14, "");
static_assert(sizeof(FxParam) == 0x18, "");

// Inferred role: efb section header holding the offset of its data; original name unknown.
struct unknown001 {
  u8 _00[0x10 - 0x00];
  u32 unknown10;
};

static_assert(offsetof(unknown001, unknown10) == 0x10, "");

// Inferred role: pointer at an offset from a base, null when the offset is 0; original name unknown.
template <typename T> inline const T *unknown002(const void *base, u32 offset) {
  if (offset == 0) {
    return nullptr;
  }
  return reinterpret_cast<const T *>(static_cast<const u8 *>(base) + offset);
}

struct CamParam {
  mm::Mat44 m_viewMatrix;
};

class ParticleManager {
public:
  using AllocFunc = void *(*)(void *allocator, u32 size, u32 alignment, const char *file, u32 line);
  using FreeFunc = void (*)(void *allocator, void *ptr);
  using GetHandleFunc = mtl::ALLOC_HANDLE (*)();
  using ReadFunc = void *(*)(const char *path, int &size);
  using ReadEndFunc = void (*)(void *data);
  using OutputStringFunc = void (*)(const char *text);

  struct DrFunc {
    void *(*unknown00)(const void *model, const char *name, int index, const void *texture, int textureIndex); // Inferred role: create mdl; original member name unknown.
    void (*unknown08)(void *model);                                                                            // Inferred role: delete mdl; original member name unknown.
    void *(*unknown10)(u32 type, int index);                                                                   // Inferred role: create lgt; original member name unknown.
    void (*unknown18)(u32 type, void *light);                                                                  // Inferred role: delete lgt; original member name unknown.
    void (*unknown20)(void *model, void *pos);                                                                 // Inferred role: set mdl pos; original member name unknown.
    void (*unknown28)(void *model, void *matrix);                                                              // Inferred role: set mdl matrix; original member name unknown.
    void (*unknown30)(void *model, void *color);                                                               // Inferred role: set mdl color; original member name unknown.
    void (*unknown38)(void *model, f32 alpha);                                                                 // Inferred role: set mdl alpha; original member name unknown.
    void (*unknown40)(void *model, void *speed);                                                               // Inferred role: set mdl spd; original member name unknown.
    void (*unknown48)(u32 type, void *light, void *pos);                                                       // Inferred role: set lgt pos; original member name unknown.
    void (*unknown50)(u32 type, void *light, void *matrix);                                                    // Inferred role: set lgt matrix; original member name unknown.
    void (*unknown58)(u32 type, void *light, void *param);                                                     // Inferred role: set lgt param; original member name unknown.
    void *(*unknown60)(int index, int count);                                                                  // Inferred role: create grp; original member name unknown.
    void (*unknown68)(void *group);                                                                            // Inferred role: destroy grp; original member name unknown.
    void (*unknown70)(void *renderer);                                                                         // Inferred role: debug renderer; original member name unknown.
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
  static void setUserAllocFunc(AllocFunc allocSys, FreeFunc freeSys, AllocFunc allocRes, FreeFunc freeRes, GetHandleFunc getSysHandle, GetHandleFunc getResHandle);
  static void setUserFileFunc(ReadFunc read, ReadEndFunc readEnd);
  static void setUserOutputString(OutputStringFunc outputDebug, OutputStringFunc outputWarn);
  static void setUserDrFunc(void *(*createMdl)(const void *, const char *, int, const void *, int), void (*deleteMdl)(void *), void *(*createLgt)(u32, int), void (*deleteLgt)(u32, void *),
                            void (*setMdlPos)(void *, void *), void (*setMdlMatrix)(void *, void *), void (*setMdlColor)(void *, void *), void (*setMdlAlpha)(void *, f32),
                            void (*setMdlSpd)(void *, void *), void (*setLgtPos)(u32, void *, void *), void (*setLgtMatrix)(u32, void *, void *), void (*setLgtParam)(u32, void *, void *),
                            void (*debugRenderer)(void *), void *(*createGrp)(int, int), void (*destroyGrp)(void *));
  static void init(const DrDrawWorkInfoEF *info);
  static void *sysAlloc(u32 size, u32 alignment, const char *file, u32 line);
  void clear();
  FxParam *getFxParam();
  void fxcore_setup_target();
  static void *createGrp(int index, int count);
  static void term();
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
  CamParam &getCamParam();
  int convert_key_by_material_index(int key, FxHeader *header) const;
  void parse_efb_type0051(u8 *data);
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
  void update_model_spd(emitter::EmitterObj *emitter, f32 speed);
  void emitter_alloc01_set_draw(emitter::EmitterObj *emitter, emitter::EmitterArg *arg);
  void update_pause();
  void move();
  void draw(const DrDrawWorkInfoEF *info, int viewIndex, bool isBlur);
  void setDrInfo(const DrDrawWorkInfoEF *info);

  CamParam m_camParam;
  u8 _040[0x130 - 0x040];
  FxParam m_fxParam;
  f32 unknown148; // Inferred role: responsive aa; original member name unknown.
  f32 unknown14c; // Inferred role: spec scale; original member name unknown.
  f32 unknown150; // Inferred role: dir scale; original member name unknown.
  f32 _154;
  f32 unknown158;       // Inferred role: ibl saturation; original member name unknown.
  f32 unknown15c;       // Inferred role: frame count; original member name unknown.
  const u8 *unknown160; // Inferred role: model table; original member name unknown.
  bool unknown168;      // Inferred role: all disp; original member name unknown.
  bool unknown169;      // Original member name unknown.
  u8 _16a[0x170 - 0x16a];
  void *unknown170[4]; // Inferred role: groups; original member name unknown.
};

static_assert(offsetof(ParticleManager, m_camParam) == 0x000, "");
static_assert(offsetof(ParticleManager, m_fxParam) == 0x130, "");
static_assert(offsetof(ParticleManager, unknown148) == 0x148, "");
static_assert(offsetof(ParticleManager, unknown168) == 0x168, "");
static_assert(offsetof(ParticleManager, unknown169) == 0x169, "");
static_assert(offsetof(ParticleManager, unknown15c) == 0x15c, "");
static_assert(offsetof(ParticleManager, unknown160) == 0x160, "");
static_assert(offsetof(ParticleManager, unknown170) == 0x170, "");
static_assert(sizeof(ParticleManager::DrFunc) == 0x80, "");

void efAstMsg(const char *cond, const char *format, ...);
void efMsg(const char *format, ...);
void efWng(const char *format, ...);

} // namespace ptlib
