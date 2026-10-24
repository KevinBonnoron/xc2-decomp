#pragma once
#include "event/i_manager.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace event {

class MemoryManager : public IManager, public mm::mtl::Singleton<MemoryManager> {
public:
  static constexpr u32 TXTBUF_COUNT = 512;

  enum {
    FLAG_DISP = 1 << 0,
  };

  MemoryManager();
  virtual ~MemoryManager() {}
  void create();
  void destroy();
  void login();
  void clear();
  void destroyTxtbuf(const char *txtbuf);
  void clearHighestMemHeap();
  void update();
  void render();
  static mtl::ALLOC_HANDLE getFwProcMem();
  u32 getSysMemSize() const;
  u32 getResMemSize() const;
  char *createTxtbuf(const char *text);
  bool isActive() const;
  bool isEnough() const;
  void setDisp(bool isDisp);
  bool isDisp() const;
  virtual void OnEventProc(MSG_TYPE type);

  const mtl::ALLOC_HANDLE &getStaticHandle() const { return unknown1c; }
  const mtl::ALLOC_HANDLE &getSysHandle() const { return unknown20; }
  const mtl::ALLOC_HANDLE &getResHandle() const { return unknown24; }

private:
  u32 unknown10;               // Inferred role: flags; original member name unknown.
  u32 unknown14;               // Inferred role: txtbuf state; original member name unknown.
  u32 unknown18;               // Inferred role: is large event; original member name unknown.
  mtl::ALLOC_HANDLE unknown1c; // Inferred role: static handle; original member name unknown.
  mtl::ALLOC_HANDLE unknown20; // Inferred role: sys handle; original member name unknown.
  mtl::ALLOC_HANDLE unknown24; // Inferred role: res handle; original member name unknown.
  mtl::ALLOC_HANDLE unknown28; // Inferred role: motstm handle; original member name unknown.
  u32 unknown2c;               // Inferred role: static size; original member name unknown.
  u32 m_sysMemSize;
  u32 m_resMemSize;
  u32 unknown38;                                        // Inferred role: motstm size; original member name unknown.
  mm::mtl::FixedVector<char *, TXTBUF_COUNT> unknown40; // Inferred role: txtbufs; original member name unknown.
  u64 unknown1048;                                      // Inferred role: highest sys heap; original member name unknown.
  u64 unknown1050;                                      // Inferred role: highest res heap; original member name unknown.
  u32 unknown1058;                                      // Inferred role: txtbuf total size; original member name unknown.
};

static_assert(sizeof(MemoryManager) == 0x1060, "");

} // namespace event
