#pragma once
#include "mm_mtl/fixstr.h"
#include "types.h"
#include <stddef.h>

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace event {

class StmPackMemory;

class StmManager {
public:
  enum {
    FLAG_PAUSE = 1 << 0,
  };

  StmManager(const char *name);
  virtual ~StmManager();
  void create(mtl::ALLOC_HANDLE handle, mtl::ALLOC_HANDLE memoryHandle);
  void destroy();
  void loadStream(const char *name, const char *headerPath, const char *dataPath);
  void changeStream(const char *name);
  void stopStream();
  bool isBusy();
  void update();
  void render(int x, f32 frame);
  void tail();
  void pause(bool isPause);
  void *adr(const char *path, size_t *size);
  void free(void *adr, int frame);
  bool isLoadingPrio(f32 prio) const;
  bool isLoadingAll() const;
  bool isFailure() const;

private:
  u32 unknown08;                 // Inferred role: flags; original member name unknown.
  mm::mtl::FixStr<64> unknown0c; // Inferred role: name; original member name unknown.
  StmPackMemory *unknown50;      // Inferred role: memory; original member name unknown.
};

static_assert(sizeof(StmManager) == 0x58, "");

} // namespace event
