#pragma once
#include <stddef.h>

#include "event/i_stm_memory.h"
#include "event/stm_pack_data.h"
#include "event/stm_pack_header.h"
#include "event/stm_pack_res.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace event {

class StmPackMemory : public IStmMemory {
public:
  static constexpr u32 RES_UNKNOWN_256 = 256;         // Inferred role: res count; original name unknown.
  static constexpr u32 STREAM_UNKNOWN_16 = 16;        // Inferred role: stream count; original name unknown.
  static constexpr size_t PAGE_UNKNOWN_4096 = 0x1000; // Inferred role: page size; original name unknown.

  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: allocated flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: wait cut flag; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2, // Inferred role: stop flag; original name unknown.
  };

  struct Stream {
    Stream(const char *name) : unknown00(name) {}

    mm::mtl::FixStr<128> unknown00; // Inferred role: name; original member name unknown.
    StmPackHeader unknown88;        // Inferred role: header; original member name unknown.
    StmPackData unknown98;          // Inferred role: data; original member name unknown.
  };

  StmPackMemory(mtl::ALLOC_HANDLE handle);
  void loadStream(const char *name, const char *headerPath, const char *dataPath);
  void changeStream(const char *name);
  void stopStream();
  bool isBusy();
  virtual ~StmPackMemory();
  virtual void update();
  void freeCut();
  bool loadCut();
  bool waitCut();
  virtual void render(const mm::Rect<int> &rect, f32 frame);
  bool loadCut(void *buffer, size_t size, size_t firstPage, size_t &nextPage);
  void loadCut(void *buffer, size_t size, size_t firstFile, size_t lastFile, size_t firstPage, size_t lastPage, int prio);
  virtual void *adr(const char *path, size_t *size);
  virtual void free(void *adr, int frame);
  virtual bool isLoadingPrio(f32 prio) const;
  virtual bool isFailure() const;

private:
  Stream *getLoadStream() { return unknown5860[unknown58e8]; }
  const Stream *getLoadStream() const { return unknown5860[unknown58e8]; }
  Stream *getCurrentStream() { return unknown5860[unknown58f0]; }

  u32 unknown08;                                                 // Inferred role: flags; original member name unknown.
  mtl::ALLOC_HANDLE unknown0c;                                   // Inferred role: handle; original member name unknown.
  void *unknown10;                                               // Inferred role: buffer; original member name unknown.
  size_t unknown18;                                              // Inferred role: page count; original member name unknown.
  size_t unknown20;                                              // Inferred role: free page; original member name unknown.
  size_t unknown28;                                              // Inferred role: load page; original member name unknown.
  mm::mtl::FixedVector<StmPackRes, RES_UNKNOWN_256> unknown30;   // Inferred role: res list; original member name unknown.
  size_t unknown5838;                                            // Inferred role: file index; original member name unknown.
  u32 unknown5840;                                               // Inferred role: next prio; original member name unknown.
  size_t unknown5848;                                            // Inferred role: data size; original member name unknown.
  size_t unknown5850;                                            // Inferred role: read size; original member name unknown.
  u32 unknown5858;                                               // Inferred role: cut count; original member name unknown.
  mm::mtl::FixedVector<Stream *, STREAM_UNKNOWN_16> unknown5860; // Inferred role: streams; original member name unknown.
  size_t unknown58e8;                                            // Inferred role: load stream; original member name unknown.
  size_t unknown58f0;                                            // Inferred role: current stream; original member name unknown.
};

static_assert(sizeof(StmPackMemory::Stream) == 0x130, "");
static_assert(sizeof(StmPackMemory) == 0x58f8, "");

} // namespace event
