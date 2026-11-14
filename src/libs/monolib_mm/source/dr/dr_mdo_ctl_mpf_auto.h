#pragma once
#include <stddef.h>

#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {
class DrMdoMpfMan;
struct MdsMpfAutoHlvPoliTree;
struct MdsMpfAutoPosData;
struct MdsMpfAutoPosTree;
struct MdsMpfAutoTree;
struct _MPFWorkAutoInf;
struct unknown510;

// Name from the game symbols; layout inferred, the original member names are unknown.
struct _wkMpfAutoBuff {
  f32 unknown00;                      // Inferred role: maximum x; original member name unknown.
  f32 unknown04;                      // Inferred role: maximum z; original member name unknown.
  f32 unknown08;                      // Inferred role: minimum x; original member name unknown.
  f32 unknown0c;                      // Inferred role: minimum z; original member name unknown.
  const u8 *unknown10;                // Inferred role: poli data; original member name unknown.
  const u8 *unknown18;                // Inferred role: hlv poli data; original member name unknown.
  const u8 *unknown20;                // Inferred role: unknown data; original member name unknown.
  const u8 *unknown28;                // Inferred role: unknown data; original member name unknown.
  const u8 *unknown30;                // Inferred role: unknown data; original member name unknown.
  const MdsMpfAutoTree *unknown38;    // Inferred role: trees; original member name unknown.
  const u32 *unknown40;               // Inferred role: poli index table; original member name unknown.
  const u32 *unknown48;               // Inferred role: grid table; original member name unknown.
  const f32 *unknown50;               // Inferred role: float table; original member name unknown.
  const MdsMpfAutoPosData *unknown58; // Inferred role: position data; original member name unknown.
  const MdsMpfAutoPosTree *unknown60; // Inferred role: position trees; original member name unknown.
  const u32 *unknown68;               // Inferred role: position index table; original member name unknown.
};

static_assert(offsetof(_wkMpfAutoBuff, unknown0c) == 0x0c, "");
static_assert(offsetof(_wkMpfAutoBuff, unknown10) == 0x10, "");
static_assert(offsetof(_wkMpfAutoBuff, unknown38) == 0x38, "");
static_assert(offsetof(_wkMpfAutoBuff, unknown60) == 0x60, "");
static_assert(offsetof(_wkMpfAutoBuff, unknown68) == 0x68, "");
static_assert(sizeof(_wkMpfAutoBuff) == 0x70, "");

// Inferred role: height and color of a stocked point; original type name unknown.
struct unknown512 {
  f32 unknown00; // Inferred role: height; original member name unknown.
  u32 unknown04; // Inferred role: color; original member name unknown.
};

static_assert(sizeof(unknown512) == 0x08, "");

class DrMdoCtlMpfAuto {
public:
  // Inferred role: auto mpf resource header; original type name unknown.
  struct unknown001 {
    s32 unknown00; // Inferred role: object count; original member name unknown.
    u32 unknown04; // Inferred role: object data offset; original member name unknown.
    u32 unknown08; // Inferred role: poli data offset; original member name unknown.
    u32 unknown0c; // Inferred role: hlv poli data offset; original member name unknown.
    u32 unknown10; // Inferred role: unknown data offset; original member name unknown.
    u32 unknown14; // Inferred role: unknown data offset; original member name unknown.
    u32 unknown18; // Inferred role: unknown data offset; original member name unknown.
    u32 unknown1c; // Inferred role: tree data offset; original member name unknown.
    u32 unknown20; // Inferred role: poli index table offset; original member name unknown.
    u32 unknown24; // Inferred role: grid table offset; original member name unknown.
    u32 unknown28; // Inferred role: float table offset; original member name unknown.
    u8 _2c[0x3c - 0x2c];
    s32 unknown3c; // Inferred role: position data check, -13 when valid; original member name unknown.
    u32 unknown40; // Inferred role: position data offset; original member name unknown.
    u32 unknown44; // Inferred role: position tree offset; original member name unknown.
    u32 unknown48; // Inferred role: position index table offset; original member name unknown.
    u32 unknown4c; // Inferred role: hlv poli tree offset; original member name unknown.
    u32 unknown50; // Inferred role: hlv poli offset; original member name unknown.
    u32 unknown54; // Inferred role: unknown data offset; original member name unknown.
    u32 unknown58; // Inferred role: unknown data offset; original member name unknown.
    u32 unknown5c; // Inferred role: polygon table offset; original member name unknown.
  };

  DrMdoCtlMpfAuto();
  ~DrMdoCtlMpfAuto();
  void setupAutoMpf(const u8 *data, const u8 *autoData, u8 *work);
  void autoMpfRelease();
  void changeMemAutoMpf(const u8 *data, const u8 *autoData);
  void resetPrePos();
  void setBuffTbl(_wkMpfAutoBuff **table, int count);
  void SeqListCount();
  void memChgMinWork(_MPFWorkAutoInf *&work);
  void DebugUpdateMem(_MPFWorkAutoInf *work, int index);
  void gridColiCalc();
  void gridInstColiCalc();
  bool gridChkColiRange(f32 maxX, f32 minX, f32 maxZ, f32 minZ);
  bool gridColiInstPosRangeChk(const MdsMpfAutoPosTree *tree);
  void StockTempPoint();
  void gridTreeColiCalc(const MdsMpfAutoTree *tree);
  bool gridColiRangeChk(const MdsMpfAutoTree *tree);
  void seachInstTree(const MdsMpfAutoPosTree *tree);
  bool StockPoint();

  const unknown001 *unknown00;            // Inferred role: resource header; original member name unknown.
  const unknown510 *unknown08;            // Inferred role: object data; original member name unknown.
  const u8 *unknown10;                    // Inferred role: hlv poli data; original member name unknown.
  const u8 *unknown18;                    // Inferred role: unknown data; original member name unknown.
  const u8 *unknown20;                    // Inferred role: unknown data; original member name unknown.
  const MdsMpfAutoHlvPoliTree *unknown28; // Inferred role: hlv poli trees; original member name unknown.
  const u32 *unknown30;                   // Inferred role: tree index table; original member name unknown.
  const u8 *unknown38;                    // Inferred role: unknown data; original member name unknown.
  u8 _40[0x50 - 0x40];
  _wkMpfAutoBuff *unknown50;  // Inferred role: first buffer; original member name unknown.
  _wkMpfAutoBuff *unknown58;  // Inferred role: current buffer; original member name unknown.
  _wkMpfAutoBuff **unknown60; // Inferred role: buffer table; original member name unknown.
  s32 unknown68;              // Inferred role: buffer table count; original member name unknown.
  s32 unknown6c;              // Inferred role: unknown value cleared by the constructor; original member name unknown.
  s32 unknown70;              // Inferred role: unknown value cleared by the constructor; original member name unknown.
  u8 _74[0x80 - 0x74];
  s32 unknown80; // Inferred role: sequence index; original member name unknown.
  s32 unknown84; // Inferred role: unknown value cleared by the constructor; original member name unknown.
  f32 unknown88; // Inferred role: range maximum x; original member name unknown.
  f32 unknown8c; // Inferred role: range minimum x; original member name unknown.
  f32 unknown90; // Inferred role: range maximum z; original member name unknown.
  f32 unknown94; // Inferred role: range minimum z; original member name unknown.
  u8 _98[0xc0 - 0x98];
  mm::Vec3 *unknownc0; // Inferred role: previous positions; original member name unknown.
  u8 _c8[0xd0 - 0xc8];
  f32 unknownd0; // Inferred role: unknown value cleared by the constructor; original member name unknown.
  f32 unknownd4; // Inferred role: unknown value cleared by the constructor; original member name unknown.
  f32 unknownd8; // Inferred role: unknown value cleared by the constructor; original member name unknown.
  u32 unknowndc; // Inferred role: color of the point; original member name unknown.
  u8 _e0[0xf0 - 0xe0];
  unknown512 *unknownf0; // Inferred role: stocked points; original member name unknown.
  s32 unknownf8;         // Inferred role: stocked point count; original member name unknown.
  u8 _fc[0x158 - 0xfc];
  _MPFWorkAutoInf **unknown158; // Inferred role: work lists; original member name unknown.
  _MPFWorkAutoInf **unknown160; // Inferred role: work list tails; original member name unknown.
  DrMdoMpfMan *unknown168;      // Inferred role: mpf manager; original member name unknown.
};

static_assert(offsetof(DrMdoCtlMpfAuto::unknown001, unknown04) == 0x04, "");
static_assert(offsetof(DrMdoCtlMpfAuto::unknown001, unknown3c) == 0x3c, "");
static_assert(offsetof(DrMdoCtlMpfAuto::unknown001, unknown48) == 0x48, "");
static_assert(offsetof(DrMdoCtlMpfAuto::unknown001, unknown5c) == 0x5c, "");
static_assert(sizeof(DrMdoCtlMpfAuto::unknown001) == 0x60, "");
static_assert(offsetof(DrMdoCtlMpfAuto, unknown28) == 0x28, "");
static_assert(offsetof(DrMdoCtlMpfAuto, unknown58) == 0x58, "");
static_assert(offsetof(DrMdoCtlMpfAuto, unknown60) == 0x60, "");
static_assert(offsetof(DrMdoCtlMpfAuto, unknown68) == 0x68, "");
static_assert(offsetof(DrMdoCtlMpfAuto, unknown70) == 0x70, "");
static_assert(offsetof(DrMdoCtlMpfAuto, unknown80) == 0x80, "");
static_assert(offsetof(DrMdoCtlMpfAuto, unknown88) == 0x88, "");
static_assert(offsetof(DrMdoCtlMpfAuto, unknownc0) == 0xc0, "");
static_assert(offsetof(DrMdoCtlMpfAuto, unknownd0) == 0xd0, "");
static_assert(offsetof(DrMdoCtlMpfAuto, unknownf0) == 0xf0, "");
static_assert(offsetof(DrMdoCtlMpfAuto, unknownf8) == 0xf8, "");
static_assert(offsetof(DrMdoCtlMpfAuto, unknown158) == 0x158, "");
static_assert(offsetof(DrMdoCtlMpfAuto, unknown168) == 0x168, "");

} // namespace ml
