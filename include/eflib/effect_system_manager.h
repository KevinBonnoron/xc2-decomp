#pragma once
#include <stddef.h>
#include <string.h>

#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "ptlib/forcefield/particle_force_field.h"
#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace ptlib {
struct DrDrawWorkInfoEF;
} // namespace ptlib

namespace effect {

class IEffectCallBack;
struct SendParam;

class SystemManager {
public:
  // Layout from updateKizunaPos (0x710091d038), which copies the 0x140-byte Vec3 array, then +0x154..+0x160,
  // accumulates +0x164/+0x168, and copies +0x140, +0x148..+0x152 and +0x16c. The same layout is also used by
  // ptlib::emitter::EmitterManager's kizuna works, but the game mangles that type under EmitterManager, so this
  // is a separate declaration rather than an alias.
  struct KizunaWork {
    mm::mtl::FixedArray<mm::Vec3, 20> unknown000; // Inferred role: 20 Vec3s; original member name unknown.
    u64 unknown140;                               // Copied as one 8-byte run; original semantic/pointer type unknown.
    u8 unknown148;                                // Role and original member name unknown.
    u8 unknown149;                                // Role and original member name unknown.
    u8 unknown14a;                                // Role and original member name unknown.
    u8 unknown14b;                                // Role and original member name unknown.
    u8 unknown14c;                                // Role and original member name unknown.
    u8 unknown14d;                                // Role and original member name unknown.
    u8 unknown14e;                                // Role and original member name unknown.
    u8 unknown14f;                                // Role and original member name unknown.
    u8 unknown150;                                // Role and original member name unknown.
    u8 unknown151;                                // Role and original member name unknown.
    u8 unknown152;                                // Role and original member name unknown.
    f32 unknown154;                               // Role and original member name unknown.
    f32 unknown158;                               // Role and original member name unknown.
    f32 unknown15c;                               // Role and original member name unknown.
    f32 unknown160;                               // Role and original member name unknown.
    f32 unknown164;                               // Role and original member name unknown; accumulated with a wrap at +-100.
    f32 unknown168;                               // Role and original member name unknown; accumulated with a wrap at +-100.
    u32 unknown16c;                               // Role and original member name unknown; 32-bit storage view.
  };

  static_assert(offsetof(KizunaWork, unknown140) == 0x140, "");
  static_assert(offsetof(KizunaWork, unknown148) == 0x148, "");
  static_assert(offsetof(KizunaWork, unknown152) == 0x152, "");
  static_assert(offsetof(KizunaWork, unknown154) == 0x154, "");
  static_assert(offsetof(KizunaWork, unknown16c) == 0x16c, "");
  static_assert(sizeof(KizunaWork) == 0x170, "");

  // Layout from the disassembly of addCommand (0x710091a2b8), es_isalive (0x710091c740, stride 0xf0 and type/handle) and the es_*
  // setters (es_set_alpha 0x710091b438 inlines the copy). No accessor or string names these members, and the gaps are bytes
  // that no observed function reads or writes.
  struct alignas(16) EsCommand {
    // The game copies bytes 0 to 0x14 as one run, the 0xb0 block from 0x20 unless source and destination are the same object,
    // and bytes 0xd0 to 0xf0 as another run; the descending stores are how clang expands the memcpy calls.
    EsCommand(const EsCommand &other) { *this = other; }

    EsCommand &operator=(const EsCommand &other) {
      memcpy(this, &other, offsetof(EsCommand, _14));
      // memcpy requires non-overlapping ranges, so a self-assignment skips the block copy.
      if (this != &other) {
        memcpy(unknown20, other.unknown20, offsetof(EsCommand, unknownd0) - offsetof(EsCommand, unknown20));
      }
      memcpy(&unknownd0, &other.unknownd0, sizeof(EsCommand) - offsetof(EsCommand, unknownd0));
      return *this;
    }

    u32 unknown00; // Inferred role: command type; original member name unknown.
    u32 unknown04; // Role unknown; copied with unknown00 as one 8-byte run because es_set_alpha stores only a w at 0.
    u64 unknown08; // Inferred role: zero in every setter; original member name unknown.
    u32 unknown10; // Inferred role: target effect handle; original member name unknown.
    u8 _14[0x20 - 0x14];

    // Inferred role: default block loaded from a GOT pointer by the setters; original member name unknown.
    u8 unknown20[0x40];
    f32 unknown60; // Inferred role: default 1.0; original member name unknown.
    f32 unknown64; // Inferred role: default 1.0; original member name unknown.
    f32 unknown68; // Inferred role: default 1.0; original member name unknown.
    f32 unknown6c; // Inferred role: default 1.0 (es_set_disp), written by es_set_alpha; original member name unknown.
    u64 unknown70; // Inferred role: zero in every setter; original member name unknown.
    u8 _78[0x80 - 0x78];
    f32 unknown80; // Inferred role: default 1.0; original member name unknown.
    f32 unknown84; // Inferred role: default 1.0; original member name unknown.
    f32 unknown88; // Inferred role: default 1.0; original member name unknown.
    u8 _8c[0x90 - 0x8c];
    u64 unknown90; // Inferred role: zero in every setter; original member name unknown.
    u32 unknown98; // Inferred role: zero in every setter; original member name unknown.
    u8 _9c[0xa0 - 0x9c];
    f32 unknowna0; // Inferred role: written by es_set_speed, default -1.0; original member name unknown.
    u32 unknowna4; // Inferred role: default 0; original member name unknown.
    f32 unknowna8; // Inferred role: default -1.0; original member name unknown.
    f32 unknownac; // Inferred role: default -1.0; original member name unknown.
    f32 unknownb0; // Inferred role: default -1.0; original member name unknown.
    f32 unknownb4; // Inferred role: default -1.0; original member name unknown.
    f32 unknownb8; // Inferred role: default -1.0; original member name unknown.
    u32 unknownbc; // Inferred role: default 0; original member name unknown.
    u16 unknownc0; // Inferred role: default 0xffff; original member name unknown.
    u8 unknownc2;  // Inferred role: default 0; original member name unknown.
    u8 unknownc3;  // Inferred role: flag, default 1; original member name unknown.
    u16 unknownc4; // Inferred role: default 0; original member name unknown.
    u16 unknownc6; // Inferred role: default 0; original member name unknown.
    u8 unknownc8;  // Inferred role: default 0; original member name unknown.
    u8 _c9[0xd0 - 0xc9];
    u64 unknownd0; // Inferred role: payload; a w store in es_set_disp and an x store in es_remove_cas. Original member name unknown.
    u64 unknownd8; // Inferred role: payload; es_remove_cas stores a 32-bit -1 here. Original member name unknown.
    u64 unknowne0; // Inferred role: copied by addCommand, no setter store observed; original member name unknown.
    u64 unknowne8; // Inferred role: copied by addCommand, no setter store observed; original member name unknown.
  };

  static_assert(offsetof(EsCommand, unknown08) == 0x08, "");
  static_assert(offsetof(EsCommand, unknown10) == 0x10, "");
  static_assert(offsetof(EsCommand, unknown20) == 0x20, "");
  static_assert(offsetof(EsCommand, unknown60) == 0x60, "");
  static_assert(offsetof(EsCommand, unknown6c) == 0x6c, "");
  static_assert(offsetof(EsCommand, unknown80) == 0x80, "");
  static_assert(offsetof(EsCommand, unknown90) == 0x90, "");
  static_assert(offsetof(EsCommand, unknowna0) == 0xa0, "");
  static_assert(offsetof(EsCommand, unknownc0) == 0xc0, "");
  static_assert(offsetof(EsCommand, unknownd0) == 0xd0, "");
  static_assert(offsetof(EsCommand, unknowne8) == 0xe8, "");
  static_assert(sizeof(EsCommand) == 0xf0, "");

  using CommandList = mm::mtl::FixedVector<EsCommand, 0x400>;

  static SystemManager *get();
  static SystemManager *&getPtr();
  static bool isValid();
  static void testRender(const ptlib::DrDrawWorkInfoEF *info);
  SystemManager();
  virtual ~SystemManager();
  static SystemManager *create(const ptlib::DrDrawWorkInfoEF *info);
  void Init(const ptlib::DrDrawWorkInfoEF *info);
  static void destroy();
  void Term();
  static void setUserFuncClear();
  static void setUserAllocFunc(void *(*allocSys)(void *, u32, u32, const char *, u32), void (*freeSys)(void *, void *), void *(*allocRes)(void *, u32, u32, const char *, u32),
                               void (*freeRes)(void *, void *), mtl::ALLOC_HANDLE (*getSysHandle)(), mtl::ALLOC_HANDLE (*getResHandle)());
  static void setUserFileFunc(void *(*read)(const char *, int &), void (*readEnd)(void *));
  static void setUserOutputString(void (*outputDebug)(const char *), void (*outputWarn)(const char *));
  static void setUserDrFunc(void *(*createMdl)(const void *, const char *, int, const void *, int), void (*deleteMdl)(void *), void *(*createLgt)(u32, int), void (*deleteLgt)(u32, void *),
                            void (*setMdlPos)(void *, void *), void (*setMdlMatrix)(void *, void *), void (*setMdlColor)(void *, void *), void (*setMdlAlpha)(void *, f32),
                            void (*setMdlSpd)(void *, void *), void (*setLgtPos)(u32, void *, void *), void (*setLgtMatrix)(u32, void *, void *), void (*setLgtParam)(u32, void *, void *),
                            void (*debugRenderer)(void *), void *(*createGrp)(int, int), void (*destroyGrp)(void *));
  void syncRenderBegin();
  void syncRenderEnd();
  void syncUpdateBegin();
  void syncUpdateEnd();
  void setIBLSaturation(f32 saturation);
  void setDirScale(f32 scale);
  void setSpecScale(f32 scale);
  void setResponsiveAA(f32 responsiveAA);
  void setAllDisp(bool isDisp);
  void setDisableCollision(bool isDisable);
  void updateCam(const ptlib::DrDrawWorkInfoEF *info);
  void MainDraw(const ptlib::DrDrawWorkInfoEF *info, int viewIndex, bool isBlur);
  void MainLoop(const ptlib::DrDrawWorkInfoEF *info);
  void es_command_core();
  void es_pause(bool isPause);
  void es_pack_free_(u64 pack);
  void es_pack_free(u64 pack);
  void es_pack_regist(const char *name, void *data, u32 size);
  void es_pack_regist(void *data, u32 size);
  void *es_regist(const char *name, void *data, u32 value);
  u64 es_regist(void *data, u32 size);
  void es_free(void *data);
  u32 es_create(void *data, bool isLoop);
  void es_set_param_pos_only(u32 handle, const SendParam *param);
  void es_set_param_pos_only2(u32 handle, const SendParam *param);
  void es_set_category(u32 handle, u32 category);
  void es_set_param(u32 handle, const SendParam *param);
  void es_set_alpha(u32 handle, f32 alpha);
  void es_set_speed(u32 handle, f32 speed);
  void es_set_viewnum(u32 handle, int viewnum);
  u32 es_create(void *data, const SendParam *param, bool isLoop);
  u32 es_create(void *data, const SendParam *param, const IEffectCallBack *callback, int unknown, int category, bool isLoop);
  void es_set_param(u32 handle, const SendParam *param, const IEffectCallBack *callback, int unknown, int category);
  void es_set_param_cas(u32 handle, const IEffectCallBack *callback, const SendParam *param);
  void es_set_param_cas(u32 handle, const IEffectCallBack *callback, const char *name, int unknown, f32 value, int category);
  CommandList *getCommand(u32 index);
  f32 getGlobalSpeed();
  void es_set_disp(u32 handle, int isDisp);
  void es_fade_core(void *data, u32 handle, int frame);
  void es_remove_cas(void *callback);
  int es_isalive(u32 handle);
  int es_getDeadFlag(u32 handle);
  bool es_is_loop(void *data) const;
  bool es_contais_cam_axis(void *data);
  const char *es_get_name(void *data);
  void es_clearall(bool isForce);
  void log();
  void kizunaTail();
  void updateKizunaPos(int index, KizunaWork &work);
  CommandList *getCommandPtr(u32 index);
  void addCommand(const EsCommand &command);
  void setGlobalSpeed(f32 speed);
  void setCategorySpd(u32 category, f32 speed);
  void memoryDump();
  void begin();
  void end();
  void tail(bool flag);
  void apply(const ptlib::DrDrawWorkInfoEF *info);
  void opacityRender(const ptlib::DrDrawWorkInfoEF *info);
  void alphaRender(const ptlib::DrDrawWorkInfoEF *info);
  void lastRender(const ptlib::DrDrawWorkInfoEF *info);
  void finalRender(const ptlib::DrDrawWorkInfoEF *info);
  void blurRender(const ptlib::DrDrawWorkInfoEF *info);
  void getNum(u32 &emitterNum, u32 &particleNum, u32 &drawNum);
  void getNumDetail(u32 &emitterNum, u32 &particleNum, u32 &drawNum, u32 &workNum);
  u32 getEmitterForm(u32 handle);

  u8 _08[0x09 - 0x08];
  bool unknown09;                                          // Inferred role: update; original member name unknown.
  bool unknown0a;                                          // Inferred role: draw; original member name unknown.
  bool unknown0b;                                          // Inferred role: disp emitter; original member name unknown.
  bool unknown0c;                                          // Inferred role: disp emitter set; original member name unknown.
  mm::mtl::FixedVector<ptlib::AddForceParam, 8> unknown10; // Inferred role: forces; original member name unknown.
  CommandList unknown220[2];                               // Inferred role: commands; original member name unknown.
  f32 unknown78240[2];                                     // Inferred role: global speed; original member name unknown.
  bool unknown78248;                                       // Inferred role: clear force; original member name unknown.
  u8 _78249;
  bool unknown7824a; // Inferred role: disp particle texture; original member name unknown.
  bool unknown7824b; // Inferred role: work texture; original member name unknown.
  u8 unknown7824c;   // Inferred role: command buffer; original member name unknown.
  u8 unknown7824d;   // Inferred role: write buffer; original member name unknown.
  u8 unknown7824e;   // Inferred role: frame; original member name unknown.
  u8 unknown7824f;   // Inferred role: clear count; original member name unknown.
};

static_assert(offsetof(SystemManager, unknown09) == 0x09, "");
static_assert(offsetof(SystemManager, unknown0b) == 0x0b, "");
static_assert(offsetof(SystemManager, unknown10) == 0x10, "");
static_assert(offsetof(SystemManager, unknown220) == 0x220, "");
static_assert(offsetof(SystemManager, unknown78240) == 0x78240, "");
static_assert(offsetof(SystemManager, unknown7824a) == 0x7824a, "");
static_assert(offsetof(SystemManager, unknown7824d) == 0x7824d, "");
static_assert(offsetof(SystemManager, unknown7824f) == 0x7824f, "");
static_assert(sizeof(SystemManager) == 0x78250, "");

} // namespace effect
