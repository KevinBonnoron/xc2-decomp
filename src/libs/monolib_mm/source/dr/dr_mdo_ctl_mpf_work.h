#pragma once
#include <stddef.h>

#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace grlib {
class CGLibVtxInstans;
} // namespace grlib

namespace ml {
class DrCalcViewWork;
class DrMdoCtlMpfWork;
class DrMdoMpfMan;
struct _MPFWorkAutoInf;
struct _wkMpfObjBuff;

// Inferred layout from DrResMdoSeamWrkMpf::calcMpfMatSetup (0x18 byte stride); member names unknown.
struct MdsMpfObjData {
  u8 _00[0x06];
  u16 unknown06; // Inferred role: object type; original member name unknown.
  u8 _08[0x18 - 0x08];
};

static_assert(offsetof(MdsMpfObjData, unknown06) == 0x06, "");
static_assert(sizeof(MdsMpfObjData) == 0x18, "");

// Inferred layout: only the type of the position data (byte 0xf) is read; original member names unknown.
struct MdsMpfPosData {
  u8 _00[0x0f];
  u8 unknown0f; // Inferred role: object type; original member name unknown.
};

static_assert(offsetof(MdsMpfPosData, unknown0f) == 0x0f, "");

// Inferred role: store function of an object buffer, for position data or for auto work data; original type name unknown.
union unknown730 {
  void (DrMdoCtlMpfWork::*unknown00)(_wkMpfObjBuff *buff, const MdsMpfPosData *pos, int index);
  void (DrMdoCtlMpfWork::*unknown00_1)(_wkMpfObjBuff *buff, const _MPFWorkAutoInf *work, int index);
};

// Inferred role: list of position or auto work pointers of an object, continued by chunks of the temporary memory.
struct _wkMpfObjBuff {
  s32 unknown00;          // Inferred role: entry count; original member name unknown.
  const void **unknown08; // Inferred role: entries; original member name unknown.
  u8 _10[0x18 - 0x10];
  unknown730 unknown18; // Inferred role: store function; original member name unknown.
};

static_assert(offsetof(_wkMpfObjBuff, unknown18) == 0x18, "");
static_assert(sizeof(_wkMpfObjBuff) == 0x28, "");

struct _wkMpfAlphaObjBuff;

// Inferred role: store function of an alpha object buffer, for position data or for auto work data; original type name unknown.
union unknown731 {
  void (DrMdoCtlMpfWork::*unknown00)(_wkMpfAlphaObjBuff *buff, const MdsMpfPosData *pos, int index, f32 alpha);
  void (DrMdoCtlMpfWork::*unknown00_1)(_wkMpfAlphaObjBuff *buff, const _MPFWorkAutoInf *work, int index);
};

// Inferred role: list of position or auto work pointers of an object with an alpha value each, continued by chunks of the temporary memory.
struct _wkMpfAlphaObjBuff {
  s32 unknown00;                 // Inferred role: entry count; original member name unknown.
  const void **unknown08;        // Inferred role: entries; original member name unknown.
  u8 *unknown10;                 // Inferred role: alpha values; original member name unknown.
  _wkMpfAlphaObjBuff *unknown18; // Inferred role: next chunk; original member name unknown.
  unknown731 unknown20;          // Inferred role: store function; original member name unknown.
};

static_assert(offsetof(_wkMpfAlphaObjBuff, unknown20) == 0x20, "");
static_assert(sizeof(_wkMpfAlphaObjBuff) == 0x30, "");

// Inferred role: chunk of the temporary memory continuing an alpha object buffer without alpha values; original type name unknown.
struct unknown733 {
  _wkMpfAlphaObjBuff unknown00; // Inferred role: buffer header; original member name unknown.
  const void *unknown30[16];    // Inferred role: entries; original member name unknown.
};

static_assert(offsetof(unknown733, unknown30) == 0x30, "");
static_assert(sizeof(unknown733) == 0xb0, "");

// Inferred role: chunk of the temporary memory continuing an alpha object buffer; original type name unknown.
struct unknown734 {
  unknown733 unknown00; // Inferred role: buffer header and entries; original member name unknown.
  u8 unknownb0[16];     // Inferred role: alpha values; original member name unknown.
};

static_assert(offsetof(unknown734, unknownb0) == 0xb0, "");
static_assert(sizeof(unknown734) == 0xc0, "");

// Inferred role: entries and alpha values of the first chunk of an alpha object buffer; original type name unknown.
struct unknown735 {
  const void *unknown00[16]; // Inferred role: entries; original member name unknown.
  u8 unknown80[16];          // Inferred role: alpha values; original member name unknown.
};

static_assert(offsetof(unknown735, unknown80) == 0x80, "");
static_assert(sizeof(unknown735) == 0x90, "");

struct _wkMpfInsMdlVertex;

void SetMpfBuffPosData(_wkMpfInsMdlVertex *vertex, f32, f32, f32 scale, f32 posX, f32 posY, f32 posZ, f32 dirX, f32 dirY, f32 dirZ, f32 angle);

// Inferred role: select buffer of an object, with the counts per type and the buffers of its positions.
struct _wkMpfObjSelect {
  u16 *unknown00; // Inferred role: position counts per type; original member name unknown.
  u8 _08[0x10 - 0x08];
  u16 *unknown10; // Inferred role: alpha position counts per type; original member name unknown.
  u8 _18[0x20 - 0x18];
  u16 unknown20; // Inferred role: object check; original member name unknown.
  u8 _22[0x30 - 0x22];
  _wkMpfObjBuff *unknown30;      // Inferred role: position buffer; original member name unknown.
  _wkMpfAlphaObjBuff *unknown38; // Inferred role: alpha position buffer; original member name unknown.
};

static_assert(offsetof(_wkMpfObjSelect, unknown10) == 0x10, "");
static_assert(offsetof(_wkMpfObjSelect, unknown20) == 0x20, "");
static_assert(offsetof(_wkMpfObjSelect, unknown30) == 0x30, "");
static_assert(offsetof(_wkMpfObjSelect, unknown38) == 0x38, "");
static_assert(sizeof(_wkMpfObjSelect) == 0x40, "");

class DrMdoCtlMpfWork {
public:
  DrMdoCtlMpfWork();
  static int calcRenderListWork(int count, const MdsMpfObjData *data);
  void changeMemWork(const MdsMpfObjData *data);
  u32 getObjChk(int index);
  void createAutoList(int index, DrCalcViewWork *view, grlib::CGLibVtxInstans *instans);
  void createPosList(int index, grlib::CGLibVtxInstans *instans);
  void mpf_countSet(_wkMpfObjBuff *buff, const MdsMpfPosData *pos, int index);
  void auto_countSet(_wkMpfObjBuff *buff, const _MPFWorkAutoInf *work, int index);
  void mpf_alpha_countSet(_wkMpfAlphaObjBuff *buff, const MdsMpfPosData *pos, int index, f32 alpha);
  void auto_alpha_countSet(_wkMpfAlphaObjBuff *buff, const _MPFWorkAutoInf *work, int index);
  void mpf_changeSet(_wkMpfObjBuff *buff, const MdsMpfPosData *pos, int index);
  void auto_changeSet(_wkMpfObjBuff *buff, const _MPFWorkAutoInf *work, int index);
  void mpf_alpha_changeSet(_wkMpfAlphaObjBuff *buff, const MdsMpfPosData *pos, int index, f32 alpha);
  void auto_alpha_changeSet(_wkMpfAlphaObjBuff *buff, const _MPFWorkAutoInf *work, int index);
  void mpf_fastSet(_wkMpfObjBuff *buff, const MdsMpfPosData *pos, int index);
  void auto_fastSet(_wkMpfObjBuff *buff, const _MPFWorkAutoInf *work, int index);
  void mpf_alpha_fastSet(_wkMpfAlphaObjBuff *buff, const MdsMpfPosData *pos, int index, f32 alpha);
  void auto_alpha_fastSet(_wkMpfAlphaObjBuff *buff, const _MPFWorkAutoInf *work, int index);
  void stockObj(int index, const MdsMpfPosData *pos);
  void stockObj(int index, const MdsMpfPosData *pos, f32 alpha);
  int setupRenderListWork(u8 *work, int count, const MdsMpfObjData *data, DrMdoMpfMan *man);
  void beginList();
  void createPosMdlRenderList(_wkMpfObjSelect *select, grlib::CGLibVtxInstans *instans, f32 scale, _wkMpfObjBuff *buff, _wkMpfAlphaObjBuff *alphaBuff);
  void createPosBillRenderList(_wkMpfObjSelect *select, grlib::CGLibVtxInstans *instans, f32 scale, _wkMpfObjBuff *buff, _wkMpfAlphaObjBuff *alphaBuff);
  void createAutoMdlRenderList(_wkMpfObjSelect *select, DrCalcViewWork *view, grlib::CGLibVtxInstans *instans, f32 scale, _wkMpfObjBuff *buff, _wkMpfAlphaObjBuff *alphaBuff);
  void createAutoBillRenderList(_wkMpfObjSelect *select, DrCalcViewWork *view, grlib::CGLibVtxInstans *instans, f32 scale, _wkMpfObjBuff *buff, _wkMpfAlphaObjBuff *alphaBuff);

  u8 _00[0x20 - 0x00];
  _wkMpfObjSelect *unknown20; // Inferred role: object select buffers; original member name unknown.
  u8 _28[0x30 - 0x28];
  DrMdoMpfMan *unknown30;         // Inferred role: mpf manager; original member name unknown.
  const MdsMpfObjData *unknown38; // Inferred role: object data; original member name unknown.
};

static_assert(offsetof(DrMdoCtlMpfWork, unknown20) == 0x20, "");
static_assert(offsetof(DrMdoCtlMpfWork, unknown30) == 0x30, "");
static_assert(offsetof(DrMdoCtlMpfWork, unknown38) == 0x38, "");

// Name from the symbols (DrMdoCtlMpfWindCalc::init, calcUpdate); layout from init and DrMdoMpfMan's ctor (0xf0 byte stride).
class DrMdoCtlMpfWindCalc {
public:
  void init();
  void calcUpdate(f32 unknown1, f32 unknown2, f32 unknown3);

  mm::Vec3 unknown00[3]; // Inferred role: joint positions; original member name unknown.
  mm::Vec3 unknown30[3]; // Inferred role: joint velocities; original member name unknown.
  mm::Vec3 unknown60;    // Inferred role: wind direction; original member name unknown.
  mm::Mat44 unknown70;   // Inferred role: matrix; original member name unknown.
  mm::Mat44 unknownb0;   // Inferred role: matrix; original member name unknown.
};

static_assert(offsetof(DrMdoCtlMpfWindCalc, unknown60) == 0x60, "");
static_assert(offsetof(DrMdoCtlMpfWindCalc, unknown70) == 0x70, "");
static_assert(offsetof(DrMdoCtlMpfWindCalc, unknownb0) == 0xb0, "");
static_assert(sizeof(DrMdoCtlMpfWindCalc) == 0xf0, "");

} // namespace ml
