#pragma once
#include <stddef.h>

#include "gf/data/gf_data_save.h"
#include "ml/work_event.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace ml {
class FileHandleTh;
} // namespace ml

namespace gf {

struct SDataOption;
struct SDataSave;

class GfGameLoad : public ml::IWorkEvent {
public:
  GfGameLoad(SAVESLOT slot);
  GfGameLoad(const char *path);
  ~GfGameLoad() override {}
  bool OnFileEvent(ml::EventFileTh *event) override;
  bool isBusy() const;
  void terminateNonBlock();
  void waitNonBlockBin();
  void endNonBlockBin();
  void phaseBinData();
  void startNonBlockBin(mm::mtl::FixStr<256> &path);
  void createGameLoadDataBin(SDataSave &saveData, mm::mtl::FixStr<256> &path);
  void getGameFileNameBin(mm::mtl::FixStr<256> &path);
  void execGameLoadNonBlock(SDataSave &saveData);

  SAVESLOT unknown08;             // Inferred role: save slot; original member name unknown.
  mm::mtl::FixStr<256> unknown0c; // Inferred role: file name to load instead of the slot; original member name unknown.
  SDataSave *unknown110;          // Inferred role: game data read from the file; original member name unknown.
  SDataOption *unknown118;        // Inferred role: option data read from the file; original member name unknown.
  s32 unknown120;                 // Inferred role: busy state; original member name unknown.
  u8 _124[0x128 - 0x124];
  ml::FileHandleTh *unknown128; // Inferred role: pending file handle; original member name unknown.
  s32 unknown130;               // Inferred role: result of the file event; original member name unknown.
  u32 unknown134;               // Inferred role: read size; original member name unknown.
  SDataSave *unknown138;        // Inferred role: destination save data; original member name unknown.
  SDataOption *unknown140;      // Inferred role: destination option data; original member name unknown.
  void *unknown148;             // Inferred role: load buffer; original member name unknown.
  u64 unknown150;               // Inferred role: load buffer size; original member name unknown.
};

static_assert(offsetof(GfGameLoad, unknown08) == 0x08, "");
static_assert(offsetof(GfGameLoad, unknown0c) == 0x0c, "");
static_assert(offsetof(GfGameLoad, unknown110) == 0x110, "");
static_assert(offsetof(GfGameLoad, unknown118) == 0x118, "");
static_assert(offsetof(GfGameLoad, unknown120) == 0x120, "");
static_assert(offsetof(GfGameLoad, unknown128) == 0x128, "");
static_assert(offsetof(GfGameLoad, unknown134) == 0x134, "");
static_assert(offsetof(GfGameLoad, unknown138) == 0x138, "");
static_assert(offsetof(GfGameLoad, unknown148) == 0x148, "");
static_assert(sizeof(GfGameLoad) == 0x158, "");

} // namespace gf
