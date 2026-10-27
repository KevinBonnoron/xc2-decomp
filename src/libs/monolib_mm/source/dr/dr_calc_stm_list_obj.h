#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

class DrCalcTexStmObj;
class EventFileTh;

struct DrCalcStmRes {
  const u8 *unknown00; // Inferred role: data; original member name unknown.
  u8 _08[0x10 - 0x08];
  u8 unknown10; // Inferred role: flags; original member name unknown.
  u8 _11[0x18 - 0x11];
};

static_assert(offsetof(DrCalcStmRes, unknown10) == 0x10, "");
static_assert(sizeof(DrCalcStmRes) == 0x18, "");

class DrCalcStmListObj {
public:
  enum DrTexUseMode {
    DR_TEX_USE_MODE_NONE,
    DR_TEX_USE_MODE_LOW,
    DR_TEX_USE_MODE_MIDDLE,
  };

  void release();
  void setupInfo(const u8 *header, bool isSetup);
  void setHeaderInfo(const u8 *header);
  bool isResSafe() const;
  DrCalcStmRes *getResObj(u32 index);
  DrCalcStmRes *getResVertexObj();
  DrCalcStmRes *getResShaderObj();
  bool isResChange() const;
  bool isResSub() const;
  bool isResTex() const;
  void setUseMode(DrTexUseMode mode);
  grlib::CGLibTextureBuffer *getTexObj(u32 index);
  void *getAdder();
  DrCalcStmRes *getResLowTexObj();
  bool texstm_requestWait();
  bool texstm_size_Wait();
  void setupReadCheck();
  bool texstm_notfileWait();
  bool texstm_oldVerWait();
  bool texstm_stmchk_setWait();
  bool texstm_defErrWait();
  bool texstm_defMidtexErrWait();
  bool texstm_fastErrWait();
  bool texstm_deTexCheck();
  bool texstm_checkTexStm();
  bool texstm_defupdate();
  bool OnFileEvent(EventFileTh *event);
  bool texstm_defRead();
  void chacheDefClear();
  void update();

  u8 _00[0x28];
  DrCalcTexStmObj **unknown28; // Inferred role: tex stream objects; original member name unknown.
  DrCalcStmRes *unknown30[2];  // Inferred role: res; original member name unknown.
  void *unknown40;             // Inferred role: file handle; original member name unknown.
  DrCalcTexStmObj *unknown48;  // Inferred role: tex stream object; original member name unknown.
  DrCalcTexStmObj *unknown50;  // Inferred role: read check tex stream object; original member name unknown.
  u8 _58[0x74 - 0x58];
  u16 unknown74; // Inferred role: vertex res index; original member name unknown.
  u16 unknown76; // Inferred role: shader res index; original member name unknown.
  u16 unknown78; // Inferred role: low texture res index; original member name unknown.
  u8 _7a[0x80 - 0x7a];
  u32 unknown80; // Inferred role: state flags; original member name unknown.
  u32 unknown84; // Inferred role: error wait size; original member name unknown.
  u32 unknown88; // Inferred role: wait state; original member name unknown.
  u32 unknown8c; // Inferred role: wait frames; original member name unknown.
  u8 _90[0x94 - 0x90];
  u32 unknown94; // Inferred role: tex stream count; original member name unknown.
  u8 _98[0x9c - 0x98];
  u8 _9c[0xa2 - 0x9c];
  s16 unknowna2; // Inferred role: tex stream object max; original member name unknown.
  u8 _a4[0xa6 - 0xa4];
  s16 unknowna6; // Inferred role: reference count; original member name unknown.
  s16 unknowna8; // Inferred role: error wait count; original member name unknown.
  s16 unknownaa; // Inferred role: request wait count; original member name unknown.
  u8 _ac[0xb0 - 0xac];
  grlib::CGLibTextureBuffer *unknownb0; // Inferred role: textures; original member name unknown.
  u8 _b8[0xc8 - 0xb8];
  s32 unknownc8;    // Inferred role: current use mode; original member name unknown.
  s32 unknowncc[2]; // Inferred role: use mode per buffer; original member name unknown.
  u8 _d4[0x1e0 - 0xd4];
  bool (DrCalcStmListObj::*unknown1e0)(); // Inferred role: current state function; original member name unknown.
  bool (DrCalcStmListObj::*unknown1f0)(); // Inferred role: read check state function; original member name unknown.
  bool (DrCalcStmListObj::*unknown200)(); // Inferred role: request state function; original member name unknown.
};

static_assert(offsetof(DrCalcStmListObj, unknown28) == 0x28, "");
static_assert(offsetof(DrCalcStmListObj, unknown40) == 0x40, "");
static_assert(offsetof(DrCalcStmListObj, unknown8c) == 0x8c, "");
static_assert(offsetof(DrCalcStmListObj, unknown30) == 0x30, "");
static_assert(offsetof(DrCalcStmListObj, unknown50) == 0x50, "");
static_assert(offsetof(DrCalcStmListObj, unknown84) == 0x84, "");
static_assert(offsetof(DrCalcStmListObj, unknown94) == 0x94, "");
static_assert(offsetof(DrCalcStmListObj, unknowna2) == 0xa2, "");
static_assert(offsetof(DrCalcStmListObj, unknowna6) == 0xa6, "");
static_assert(offsetof(DrCalcStmListObj, unknowna8) == 0xa8, "");
static_assert(offsetof(DrCalcStmListObj, unknownc8) == 0xc8, "");
static_assert(offsetof(DrCalcStmListObj, unknown1f0) == 0x1f0, "");
static_assert(offsetof(DrCalcStmListObj, unknown48) == 0x48, "");
static_assert(offsetof(DrCalcStmListObj, unknown78) == 0x78, "");
static_assert(offsetof(DrCalcStmListObj, unknownaa) == 0xaa, "");
static_assert(offsetof(DrCalcStmListObj, unknown1e0) == 0x1e0, "");
static_assert(offsetof(DrCalcStmListObj, unknown200) == 0x200, "");
static_assert(offsetof(DrCalcStmListObj, unknown74) == 0x74, "");
static_assert(offsetof(DrCalcStmListObj, unknown76) == 0x76, "");
static_assert(offsetof(DrCalcStmListObj, unknown80) == 0x80, "");
static_assert(offsetof(DrCalcStmListObj, unknown88) == 0x88, "");
static_assert(offsetof(DrCalcStmListObj, unknownb0) == 0xb0, "");
static_assert(offsetof(DrCalcStmListObj, unknowncc) == 0xcc, "");

} // namespace ml
