// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/asset/gf_filesize_pool.cpp.
#include "gf/asset/gf_file_size_pool.h"

#include "gf/gf_allocator.h"
#include "gf/gf_manager.h"
#include "gf/util/gf_util.h"
#include "ml/dev_file_th.h"
#include "ml/thread.h"
#include "ml/time_count.h"
#include "ml/work_cpu.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/hash.h"
#include "mm_mtl/reference_object.h"
#include "mm_thread/mm_thread_csection.h"
#include "mm_thread/mm_thread_util.h"
#include "types.h"

namespace gf {

GfFileSizePool::GfFileSizePool(const GfSetupParam &param) : unknown08(false), unknown09(false), unknown1e038(nullptr), unknown1e040(false, true), unknown1e0c8(false), unknown1e0cc(0.0f) {
  initialize(param);
}

GfFileSizePool::~GfFileSizePool() {}

void GfFileSizePool::build(const GfSetupParam &param) {
#line 61
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfFileSizePool(param);
}

void GfFileSizePool::destroy() {
  GfFileSizePool *pool = get();
  pool->finalize();
  delete pool;
}

void GfFileSizePool::initialize(const GfSetupParam &param) {
  createThread();
  unknown08 = true;
}

void GfFileSizePool::finalize() {
  unknown09 = true;
  destroyThread();
  unknown08 = false;
}

void GfFileSizePool::createThread() {
  unknown1e038 = ml::Thread::create("FileSizeJob", false, fnThread, this, 0x10000, ml::CPUID_UNKNOWN_2, 0);
  if (unknown1e038 != nullptr) {
    unknown1e038->resume();
  }
}

void GfFileSizePool::destroyThread() {
  if (unknown1e038 == nullptr) {
    return;
  }
  while (!unknown1e038->isTerminated()) {
    unknown1e040.setSignal(true);
    GfSleep(1);
  }
  mm::mtl::safeRelease(unknown1e038);
  unknown001 *end = unknown10.end();
  for (unknown001 *it = unknown10.begin(); it != end; ++it) {
    if (it->unknown08 != nullptr) {
      delete it->unknown08;
      it->unknown08 = nullptr;
    }
  }
  unknown10.clear();
  unknown1b028.clear();
  unknown18018.clear();
}

u32 GfFileSizePool::getFileSizeByHandle(u64 handle) const { return unknown10[getPoolIndex(handle)].unknown10; }

u32 GfFileSizePool::getPoolIndex(u64 handle) { return handle & 0xffff; }

bool GfFileSizePool::isRequestByHandle(u64 handle) const {
  mm::threading::CS cs(unknown1e0a0);
  for (mm::mtl::FixedQueue<unknown001, 512>::const_iterator it = unknown18018.begin(); it != unknown18018.end(); ++it) {
    if ((*it).unknown00 == handle) {
      return true;
    }
  }
  return false;
}

u64 GfFileSizePool::getHandleFromFileName(u32 index, const char *path) {
  u64 hash = getHash(path);
  // The game calls getFilePtrFromPath on the path here and discards the result (same code in Torna).
  util::getFilePtrFromPath(path);
  return index | hash;
}

u64 GfFileSizePool::getHash(const char *path) {
  if (*path == '\\' || *path == '/') {
    path++;
  }
  u64 hash = mm::mtl::hashStrCrc(path);
  u32 fileHash = mm::mtl::hashStrCrc(util::getFilePtrFromPath(path));
  return hash << 32 | (fileHash & 0xffff0000);
}

u64 GfFileSizePool::getHashFromHandle(u64 handle) { return handle & 0xffffffffffff0000; }

u64 GfFileSizePool::requestFileSize(const char *path) {
  u64 hash = getHash(path);
  u32 index = unknown10.size();
  for (unknown001 *it = unknown10.begin(); it != unknown10.end(); ++it) {
    if (getHashFromHandle(it->unknown00) == hash) {
      return it->unknown00;
    }
  }
  u64 handle = getHandleFromFileName(index, path);
#line 172
  mm::mtl::FixStr<128> *name = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) mm::mtl::FixStr<128>();
  *name = path;
  unknown001 entry;
  entry.unknown00 = handle;
  entry.unknown08 = name;
  entry.unknown10 = -2;
  entry.unknown14 = index;
  unknown10.push_back(entry);
  unknown1b028.push(entry);
  return handle;
}

void GfFileSizePool::recalcFileSizeCache(u64 handle, const char *path) {
  unknown001 &entry = unknown10[getPoolIndex(handle)];
  if (entry.unknown08 != nullptr) {
    delete entry.unknown08;
    entry.unknown08 = nullptr;
  }
  entry.unknown00 = handle;
#line 197
  entry.unknown08 = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) mm::mtl::FixStr<128>();
  *entry.unknown08 = path;
  entry.unknown10 = -2;
  unknown1b028.push(entry);
}

bool GfFileSizePool::getFileSize(int &size, u64 handle) const {
  s32 fileSize = unknown10[getPoolIndex(handle)].unknown10;
  if (fileSize != -2) {
    size = fileSize;
    return true;
  }
  return false;
}

u32 GfFileSizePool::fnThread(void *argument) {
  GfFileSizePool *pool = get();
  pool->unknown1e0c8 = true;
  while (!pool->unknown09) {
    pool->execFileSizeJob(100);
    pool->unknown1e0c8 = false;
    pool->unknown1e040.waitSignal(0);
    pool->unknown1e0c8 = true;
    pool = get();
  }
  return 0;
}

void GfFileSizePool::wakeupThread() { unknown1e040.setSignal(true); }

void GfFileSizePool::update() {
  if (unknown1e0c8) {
    return;
  }
  copyPoolFromRequest();
  unknown1e040.setSignal(true);
}

void GfFileSizePool::copyPoolFromRequest() {
  mm::threading::CS cs(unknown1e0a0);
  mm::mtl::FixedQueue<unknown001, 512>::iterator it = unknown18018.begin();
  while (it != unknown18018.end()) {
    unknown001 &entry = *it;
    if (entry.unknown10 == -2) {
      break;
    }
    unknown10[entry.unknown14].unknown10 = entry.unknown10;
    if (unknown10[entry.unknown14].unknown08 != nullptr) {
      delete unknown10[entry.unknown14].unknown08;
      unknown10[entry.unknown14].unknown08 = nullptr;
    }
    unknown18018.erase(it);
  }
  mm::mtl::FixedQueue<unknown001, 512>::iterator end = unknown1b028.end();
  for (mm::mtl::FixedQueue<unknown001, 512>::iterator request = unknown1b028.begin(); request != end; ++request) {
    unknown18018.push(*request);
  }
  unknown1b028.clear();
}

void GfFileSizePool::execFileSizeJob(u32 count) {
  mm::threading::CS cs(unknown1e0a0);
  ml::TimeCount timer;
  timer.start();
  u32 executed = 0;
  mm::mtl::FixedQueue<unknown001, 512>::iterator end = unknown18018.end();
  for (mm::mtl::FixedQueue<unknown001, 512>::iterator it = unknown18018.begin(); it != end; ++it) {
    if ((*it).unknown10 == -2) {
      int size = ml::DevFileTh::getFileSize((*it).unknown08->c_str(), nullptr);
      if (size < 0) {
        size = -1;
      }
      executed++;
      (*it).unknown10 = size;
      if (executed >= count) {
        break;
      }
    }
  }
  unknown1e0cc += timer.getSecLap();
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfFileSizePool>::~PtrSingleton();
