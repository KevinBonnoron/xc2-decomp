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

class GfGameSave : public ml::IWorkEvent {
public:
  GfGameSave(SAVESLOT slot);
  ~GfGameSave() override;
  bool OnFileEvent(ml::EventFileTh *event) override;
  void destroySaveData();
  void createGameSaveData(mm::mtl::FixStr<256> &path);
  void createOptionSaveData(mm::mtl::FixStr<256> &path);
  void execGameSaveNonBlock();
  void execOptionSaveNonBlock();
  void execGameSaveWithMicroThread();
  static void flushSaveData();
  void terminateNonBlock();
  void startNonBlockBin(mm::mtl::FixStr<256> &path);
  void waitNonBlockBin();
  void endNonBlockBin();
  bool isBusy() const;
  static SDataSave *getGameSaveData();
  static SDataOption *getGameOptionData();

  s32 unknown08;               // Inferred role: busy state; original member name unknown.
  SAVESLOT unknown0c;          // Inferred role: save slot; original member name unknown.
  SDataSave *unknown10;        // Inferred role: game data to save; original member name unknown.
  SDataOption *unknown18;      // Inferred role: option data to save; original member name unknown.
  const void *unknown20;       // Inferred role: data of the file being written; original member name unknown.
  u64 unknown28;               // Inferred role: size of the file being written; original member name unknown.
  ml::FileHandleTh *unknown30; // Inferred role: pending file handle; original member name unknown.
  s32 unknown38;               // Inferred role: result of the file event; original member name unknown.
};

static_assert(offsetof(GfGameSave, unknown08) == 0x08, "");
static_assert(offsetof(GfGameSave, unknown10) == 0x10, "");
static_assert(offsetof(GfGameSave, unknown18) == 0x18, "");
static_assert(offsetof(GfGameSave, unknown20) == 0x20, "");
static_assert(offsetof(GfGameSave, unknown28) == 0x28, "");
static_assert(offsetof(GfGameSave, unknown30) == 0x30, "");
static_assert(offsetof(GfGameSave, unknown38) == 0x38, "");
static_assert(sizeof(GfGameSave) == 0x40, "");

} // namespace gf
