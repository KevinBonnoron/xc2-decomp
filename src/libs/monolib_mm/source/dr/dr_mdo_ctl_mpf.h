#pragma once
#include <stddef.h>

#include "dr/dr_mdl_obj.h"
#include "types.h"

namespace ml {

class DrMan;
class DrMdoCtlMpfAuto;
class DrMdoCtlMpfInst;
class DrMdoCtlMpfWork;
class DrResMdoSeamWrkPosMpf;
class DrResMdoSortMpf;

class DrMdoCtlMpf : public DrMdlObj {
public:
  DrMdoCtlMpf(const void *data, const char *path, DrMan *drMan, int viewNum);
  ~DrMdoCtlMpf() override;
  void setupMpf(const u8 *data);
  void releaseMpf();
  void update() override;
  void resourceInit() override;
  void callZPrepassRender();
  void updateMpf();
  void calcMpfRenderList();
  void callRenderMpf();
  void defMpfZPreRender();
  void defMpfrender();
  void createDisplaList();

  s32 unknown1a4; // Inferred role: object count; original member name unknown.
  u8 _1a8[0x1b0 - 0x1a8];
  u8 *unknown1b0;                    // Inferred role: work memory; original member name unknown.
  u8 *unknown1b8;                    // Inferred role: second work memory, released with the first; original member name unknown.
  u32 unknown1c0;                    // Inferred role: unknown value cleared by the constructor; original member name unknown.
  DrMdoCtlMpfWork *unknown1c8;       // Inferred role: render list work, at the start of the work memory; original member name unknown.
  DrMdoCtlMpfAuto *unknown1d0;       // Inferred role: auto mpf, in the work memory; original member name unknown.
  DrMdoCtlMpfInst *unknown1d8;       // Inferred role: instance mpf, in the work memory; original member name unknown.
  DrResMdoSeamWrkPosMpf *unknown1e0; // Inferred role: positions, in the work memory; original member name unknown.
  DrResMdoSortMpf *unknown1e8;       // Inferred role: z sort object, at the end of the work memory; original member name unknown.
  u8 _1f0[0x200 - 0x1f0];
};

static_assert(offsetof(DrMdoCtlMpf, unknown1a4) == 0x1a4, "");
static_assert(offsetof(DrMdoCtlMpf, unknown1b0) == 0x1b0, "");
static_assert(offsetof(DrMdoCtlMpf, unknown1c8) == 0x1c8, "");
static_assert(offsetof(DrMdoCtlMpf, unknown1e8) == 0x1e8, "");
static_assert(sizeof(DrMdoCtlMpf) == 0x200, "");

} // namespace ml
