#pragma once
#include "event/i_manager.h"
#include "event/stm_manager.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace event {

class MotstmManager : public IManager, public mm::mtl::Singleton<MotstmManager> {
public:
  enum {
    FLAG_CREATE = 0,
    FLAG_START = 1,
    FLAG_PAUSE = 2,
  };

  enum {
    DISP_FLAG_DISP = 1 << 0,
  };

  MotstmManager();
  virtual ~MotstmManager() {}
  void create(mtl::ALLOC_HANDLE handle);
  void loadStream(const char *name);
  void changeStream(const char *name);
  void clear();
  void update();
  void render();
  void start();
  void stop();
  bool isBusy();
  void *adr(const char *path, size_t *size);
  void free(void *adr);
  bool isLoadingPrio(f32 prio) const;
  bool isFailure() const;
  void setDisp(bool isDisp);
  bool isDisp() const;
  virtual void OnEventProc(MSG_TYPE type);

private:
  mm::mtl::unknown027<32> unknown10; // Inferred role: flags; original member name unknown.
  u32 unknown14;                     // Inferred role: disp flags; original member name unknown.
  StmManager unknown18;              // Inferred role: stm; original member name unknown.
};

static_assert(sizeof(MotstmManager) == 0x70, "");

} // namespace event
