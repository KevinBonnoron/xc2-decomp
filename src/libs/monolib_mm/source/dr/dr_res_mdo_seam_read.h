#pragma once
#include <stddef.h>

#include "ml/work_event.h"
#include "types.h"

namespace ml {

class DrResMdoSeamMemObj;
class FileHandleTh;

class DrResMdoSeamRead : public IWorkEvent {
public:
  enum Flag {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: file handles are open; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: file handles are reading; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2, // Inferred role: file handles are kept open; original name unknown.
    FLAG_UNKNOWN_3 = 1 << 3, // Inferred role: file handles are opened by each read; original name unknown.
    FLAG_UNKNOWN_4 = 1 << 4, // Inferred role: update requested; original name unknown.
    FLAG_UNKNOWN_5 = 1 << 5, // Inferred role: file handles are opened by each read, requested; original name unknown.
    FLAG_UNKNOWN_6 = 1 << 6, // Inferred role: file handles are kept open, requested; original name unknown.
    FLAG_UNKNOWN_7 = 1 << 7, // Inferred role: update retry; original name unknown.
    FLAG_UNKNOWN_8 = 1 << 8, // Inferred role: open failed; original name unknown.
  };

  DrResMdoSeamRead();
  ~DrResMdoSeamRead() override;
  void release();
  void setup(bool isKeepOpen);
  void setOpenInit();
  void setReadInit();
  void update(const char *path, bool isReadEach);
  bool isRead();
  void readCancel();
  bool read(int &handleNum, u32 offset, u32 size, DrResMdoSeamMemObj *memObj);
  int getFileHandleNum();
  bool OnFileEvent(EventFileTh *event) override;
  int getReadMax();
  bool readColi(int &handleNum, u32 offset, u32 size, DrResMdoSeamMemObj *memObj);

  FileHandleTh *unknown08[8]; // Inferred role: file handles; original member name unknown.
  u16 unknown48;              // Inferred role: handles in use; original member name unknown.
  u16 unknown4a;              // Inferred role: handles finished; original member name unknown.
  u32 unknown4c;              // Inferred role: flags; original member name unknown.
  const char *unknown50;      // Inferred role: path; original member name unknown.
};

static_assert(offsetof(DrResMdoSeamRead, unknown08) == 0x08, "");
static_assert(offsetof(DrResMdoSeamRead, unknown48) == 0x48, "");
static_assert(offsetof(DrResMdoSeamRead, unknown4a) == 0x4a, "");
static_assert(offsetof(DrResMdoSeamRead, unknown4c) == 0x4c, "");
static_assert(offsetof(DrResMdoSeamRead, unknown50) == 0x50, "");
static_assert(sizeof(DrResMdoSeamRead) == 0x58, "");

} // namespace ml
