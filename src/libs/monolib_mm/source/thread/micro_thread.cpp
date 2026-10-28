#include "ml/micro_thread.h"

#include "ml/ml_mem.h"
#include "mtl/alloc_handle.h"

namespace ml {

MicroThread *MicroThread::create() {
  MicroThread *thread = get();
  if (thread == nullptr) {
    thread = new (MlMem::getProductMem()) MicroThreadNx();
  }
  return thread;
}

u64 MicroThread::createHandle(MLTHG *group, u32 index) {
  u64 handle = (reinterpret_cast<u64>(group) & 0xff) << 28 | (index & 0xff) << 16 | (unknown294 & 0xffff);
  unknown294++;
  return handle;
}

void MicroThread::exit() {
  unknown2c0->unknown670->unknown2c = true;
  sleep(0, false);
}

void *MicroThread::getCurrentUserData() { return unknown2c0->unknown670->unknown18; }

u64 MicroThread::getCurrentThreadID() {
  MicroThread *thread = get();
  if (thread == nullptr) {
    return 0;
  }
  unknown001 *context = thread->unknown2c0;
  if (context == nullptr) {
    return 0;
  }
  MLTH *current = context->unknown670;
  if (current == nullptr) {
    return 0;
  }
  return current->unknown30;
}

} // namespace ml

template mm::mtl::PtrSingleton<ml::MicroThread>::~PtrSingleton();
