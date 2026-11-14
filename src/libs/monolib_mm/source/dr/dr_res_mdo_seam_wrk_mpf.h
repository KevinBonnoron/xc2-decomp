#pragma once
#include <stddef.h>

#include "dr/dr_res_mdo_seam_res.h"
#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace grlib {
class CGLibVtxInstans;
} // namespace grlib

namespace ml {
class DrCalcViewWork;
class DrMdoCtlMpfAuto;
class DrMdoCtlMpfInst;
class DrMdoCtlMpfWork;
class DrMdoCtlSeamMpfMap;
class DrMdoMpfMan;
class DrResMdoSeamParmRead;
class DrResMdoSeamWrkPosMpf;
struct MdoWrkMatRes;
struct MdsMpfObjData;
struct unknown722;
struct _wkMpfAutoBuff;

// Inferred layout of the mpf map resource header; offsets are relative to the header.
struct MdsSeamMpfMapHead {
  u32 unknown00; // Inferred role: model data offset; original member name unknown.
  u32 unknown04; // Inferred role: material data offset; original member name unknown.
  u32 unknown08; // Inferred role: mpf data offset; original member name unknown.
  u32 unknown0c; // Inferred role: vertex data offset; original member name unknown.
  u32 unknown10; // Inferred role: texture data offset; original member name unknown.
  u8 _14[0x1c - 0x14];
  u32 unknown1c; // Inferred role: etc position table offset; original member name unknown.
  u32 unknown20; // Inferred role: etc position num; original member name unknown.
};

static_assert(offsetof(MdsSeamMpfMapHead, unknown08) == 0x08, "");
static_assert(offsetof(MdsSeamMpfMapHead, unknown1c) == 0x1c, "");
static_assert(offsetof(MdsSeamMpfMapHead, unknown20) == 0x20, "");

class DrResMdoSeamWrkMpf : public unknown133<DrResMdoSeamWrkMpf> {
public:
  // Inferred role: mpf data header; original type name unknown.
  struct unknown001 {
    u32 unknown00; // Inferred role: object num; original member name unknown.
    u32 unknown04; // Inferred role: object data offset; original member name unknown.
    u8 _08[0x1c - 0x08];
    s32 unknown1c; // Inferred role: auto mpf data offset; original member name unknown.
  };

  // Inferred role: etc position entry; original type name unknown.
  struct unknown002 {
    s32 unknown00; // Inferred role: etc position id; original member name unknown.
    u8 _04[0x1c - 0x04];
  };

  // Inferred role: polygon table header of the auto mpf data; original type name unknown.
  struct unknown003 {
    u8 _00[0x08];
    u32 unknown08; // Inferred role: polygon entry offset; original member name unknown.
    s32 unknown0c; // Inferred role: polygon entry num; original member name unknown.
  };

  // Inferred role: polygon entry; original type name unknown.
  struct unknown004 {
    s32 unknown00; // Inferred role: polygon id; original member name unknown.
    u8 _04[0x14 - 0x04];
  };

  // Inferred role: header of the data of a cached polygon memory object (offsets relative to the header, bounds); original type name unknown.
  // Layout evidence: setupMpfPoliWork (0x710088c3a0). sizeof 0x40 is the end of the last field it reads (nothing else proves the size).
  struct unknown005 {
    u32 unknown00; // Inferred role: poli data offset; original member name unknown.
    u32 unknown04; // Inferred role: hlv poli data offset; original member name unknown.
    u32 unknown08; // Inferred role: unknown data offset; original member name unknown.
    u32 unknown0c; // Inferred role: unknown data offset; original member name unknown.
    u32 unknown10; // Inferred role: unknown data offset; original member name unknown.
    u32 unknown14; // Inferred role: tree data offset, 0 when absent; original member name unknown.
    u32 unknown18; // Inferred role: poli index table offset; original member name unknown.
    u32 unknown1c; // Inferred role: grid table offset; original member name unknown.
    u32 unknown20; // Inferred role: float table offset; original member name unknown.
    f32 unknown24; // Inferred role: maximum x; original member name unknown.
    f32 unknown28; // Inferred role: maximum z; original member name unknown.
    f32 unknown2c; // Inferred role: minimum x; original member name unknown.
    f32 unknown30; // Inferred role: minimum z; original member name unknown.
    u32 unknown34; // Inferred role: position data offset, 0 when absent; original member name unknown.
    u32 unknown38; // Inferred role: position tree offset; original member name unknown.
    u32 unknown3c; // Inferred role: position index table offset; original member name unknown.
  };

  DrResMdoSeamWrkMpf();
  virtual ~DrResMdoSeamWrkMpf();
  void release();
  void setupWork(MdoWrkMatRes *matRes, mtl::ALLOC_HANDLE handle, const MdsSeamMpfMapHead *head, DrMdoMpfMan *mpfMan);
  void changeMemCall();
  void releaseCache(DrMdoCtlSeamMpfMap *ctl);
  bool update(const DrResMdoSeamParmRead *parmRead, bool isOpen, u32 flags);
  u32 updateRenderList(DrCalcViewWork *view, grlib::CGLibVtxInstans *instans, DrMdoCtlSeamMpfMap *ctl);
  void beginCalc();
  void calcCacheInfo();
  void calcMpfMatSetup(DrCalcViewWork *view, grlib::CGLibVtxInstans *instans);
  void setEtcMpfCache(int id, DrResMdoSeamMemObj *memObj);
  void setMpfPoliCache(int id, DrResMdoSeamMemObj *memObj);
  void setupMpfPoliWork(int index);

  static f32 SEAM_MPFMAP_READ_CHECK;

  DrResMdoSeamMemObj *unknown18;      // Inferred role: memory object; original member name unknown.
  DrMdoMpfMan *unknown20;             // Inferred role: mpf manager; original member name unknown.
  const unknown722 *unknown28;        // Inferred role: mpf map entry; original member name unknown.
  const MdsSeamMpfMapHead *unknown30; // Inferred role: mpf map header; original member name unknown.
  const MdsMpfObjData *unknown38;     // Inferred role: object data; original member name unknown.
  const unknown002 *unknown40;        // Inferred role: etc position table; original member name unknown.
  u32 unknown48;                      // Inferred role: calc flags; original member name unknown.
  u16 unknown4c;                      // Inferred role: mpf map index; original member name unknown.
  s16 unknown4e;                      // Inferred role: render object num; original member name unknown.
  s16 unknown50;                      // Inferred role: etc position num; original member name unknown.
  s16 unknown52;                      // Inferred role: object num; original member name unknown.
  s16 unknown54;                      // Inferred role: etc position cache num; original member name unknown.
  s16 unknown56;                      // Inferred role: read counter; original member name unknown.
  s32 unknown58;                      // Inferred role: polygon cache num; original member name unknown.
  u32 unknown5c;                      // Inferred role: state flags; original member name unknown.
  s32 unknown60;                      // Inferred role: etc position calc count; original member name unknown.
  s32 unknown64;                      // Inferred role: value cleared by beginCalc; original member name unknown.
  s32 unknown68;                      // Inferred role: polygon calc count; original member name unknown.
  s32 unknown6c;                      // Inferred role: value cleared by beginCalc; original member name unknown.
  MdoWrkMatRes *unknown70;            // Inferred role: material work; original member name unknown.
  void *unknown78;                    // Inferred role: allocated work buffer; original member name unknown.
  u32 *unknown80;                     // Inferred role: etc position cache bit table; original member name unknown.
  u32 *unknown88;                     // Inferred role: polygon cache bit table; original member name unknown.
  u8 _90[0x98 - 0x90];
  u16 *unknown98; // Inferred role: polygon cache entry indices; original member name unknown.
  u8 _a0[0xb0 - 0xa0];
  _wkMpfAutoBuff **unknownb0;        // Inferred role: polygon buffer table; original member name unknown.
  DrResMdoSeamMemObj **unknownb8;    // Inferred role: polygon cache memory objects; original member name unknown.
  DrMdoCtlMpfWork *unknownc0;        // Inferred role: mpf work; original member name unknown.
  DrMdoCtlMpfAuto *unknownc8;        // Inferred role: auto mpf; original member name unknown.
  DrMdoCtlMpfInst *unknownd0;        // Inferred role: instance mpf; original member name unknown.
  DrResMdoSeamWrkPosMpf *unknownd8;  // Inferred role: etc positions; original member name unknown.
  DrResMdoSeamWrkPosMpf **unknowne0; // Inferred role: cached etc positions; original member name unknown.
  s32 unknowne8;                     // Inferred role: memory size; original member name unknown.
  u8 _ec[0xf0 - 0xec];
};

static_assert(offsetof(DrResMdoSeamWrkMpf, unknown08) == 0x08, "");
static_assert(offsetof(DrResMdoSeamWrkMpf, unknown18) == 0x18, "");
static_assert(offsetof(DrResMdoSeamWrkMpf, unknown20) == 0x20, "");
static_assert(offsetof(DrResMdoSeamWrkMpf, unknown28) == 0x28, "");
static_assert(offsetof(DrResMdoSeamWrkMpf, unknown30) == 0x30, "");
static_assert(offsetof(DrResMdoSeamWrkMpf, unknown48) == 0x48, "");
static_assert(offsetof(DrResMdoSeamWrkMpf, unknown4c) == 0x4c, "");
static_assert(offsetof(DrResMdoSeamWrkMpf, unknown54) == 0x54, "");
static_assert(offsetof(DrResMdoSeamWrkMpf, unknown5c) == 0x5c, "");
static_assert(offsetof(DrResMdoSeamWrkMpf, unknown70) == 0x70, "");
static_assert(offsetof(DrResMdoSeamWrkMpf, unknown80) == 0x80, "");
static_assert(offsetof(DrResMdoSeamWrkMpf, unknown98) == 0x98, "");
static_assert(offsetof(DrResMdoSeamWrkMpf, unknownb0) == 0xb0, "");
static_assert(offsetof(DrResMdoSeamWrkMpf, unknownc8) == 0xc8, "");
static_assert(offsetof(DrResMdoSeamWrkMpf, unknowne0) == 0xe0, "");
static_assert(offsetof(DrResMdoSeamWrkMpf, unknowne8) == 0xe8, "");
static_assert(sizeof(DrResMdoSeamWrkMpf) == 0xf0, "");
static_assert(offsetof(DrResMdoSeamWrkMpf::unknown005, unknown24) == 0x24, "");
static_assert(offsetof(DrResMdoSeamWrkMpf::unknown005, unknown34) == 0x34, "");
static_assert(sizeof(DrResMdoSeamWrkMpf::unknown005) == 0x40, "");

} // namespace ml
