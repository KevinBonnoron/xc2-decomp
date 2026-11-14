// No game string names this file: named after its header arc/arc_data.h. The game places arc::CArcData between the
// gmk objects and CsvReader/MediaClock, so it sits in application/BF2/libs next to movie/cmovie_nx.cpp
// (game string C:/Monolithsoft/BF2/prog/application/BF2/libs/movie/cmovie_nx.cpp).
#include "arc/arc_data.h"

#include "mm_mtl/hash.h"

#include <string.h>

namespace arc {

CArcData::CArcData(void *data) : unknown00(nullptr), unknown08(nullptr) {
  if (data != nullptr) {
    unknown00 = static_cast<unknown001 *>(data);
    unknown08 = reinterpret_cast<unknown002 *>(static_cast<u8 *>(data) + unknown00->unknown10);
  }
}

void CArcData::setData(void *data) {
  if (data != nullptr) {
    unknown00 = static_cast<unknown001 *>(data);
    unknown08 = reinterpret_cast<unknown002 *>(static_cast<u8 *>(data) + unknown00->unknown10);
  }
}

u32 CArcData::getFiles() const {
  if (unknown00 != nullptr) {
    return unknown00->m_files;
  }
  return 0;
}

const char *CArcData::getStr() const {
  if (unknown00 != nullptr) {
    return unknown00->m_str;
  }
  return "";
}

const CArcData::unknown002 *CArcData::getFileHeader(u32 index) const { return &unknown08[index]; }

void *CArcData::getFileAdr(u32 index) const {
  if (unknown00 != nullptr && index < unknown00->m_files && unknown08[index].m_fileSize != 0) {
    return reinterpret_cast<u8 *>(unknown00) + unknown08[index].unknown00;
  }
  return nullptr;
}

void *CArcData::getFileAdr(const char *name) const {
  u32 index = find(name);
  if (index != 0xffffffff) {
    return getFileAdr(index);
  }
  return nullptr;
}

u32 CArcData::find(const char *name) const {
  if (name == nullptr || unknown00 == nullptr) {
    return -1;
  }
  if (unknown00->unknown08 >= 0x102) {
    u32 hash = mm::mtl::hashStrCrc(name);
    int low = 0;
    int high = getFiles();
    while (low <= high) {
      int mid = (low + high) >> 1;
      const unknown002 &entry = unknown08[mid];
      if (hash == entry.m_fileHash) {
        int result = strcmp(name, entry.m_fileName);
        if (result == 0) {
          return mid;
        }
        if (result > 0) {
          low = mid + 1;
        } else {
          high = mid - 1;
        }
      } else if (hash > entry.m_fileHash) {
        low = mid + 1;
      } else {
        high = mid - 1;
      }
    }
    return -1;
  }
  u32 files = unknown00->m_files;
  for (u32 i = 0; i < files; i++) {
    if (strcmp(getFileName(i), name) == 0) {
      return i;
    }
  }
  return -1;
}

u32 CArcData::getFileSize(u32 index) const {
  if (unknown00 != nullptr && index < unknown00->m_files) {
    return unknown08[index].m_fileSize;
  }
  return 0;
}

const char *CArcData::getFileName(u32 index) const {
  if (unknown00 != nullptr && index < unknown00->m_files) {
    return unknown08[index].m_fileName;
  }
  return "";
}

u32 CArcData::getFileHash(u32 index) const {
  if (unknown00 != nullptr && index < unknown00->m_files) {
    return unknown08[index].m_fileHash;
  }
  return 0;
}

u32 CArcData::calcHash(const char *name) { return mm::mtl::hashStrCrc(name); }

CArcData::unknown002 *CArcData::begin() { return unknown08; }

CArcData::unknown002 *CArcData::end() {
  u32 files = 0;
  if (unknown00 != nullptr) {
    files = unknown00->m_files;
  }
  if (unknown08 != nullptr) {
    return unknown08 + files;
  }
  return nullptr;
}

const CArcData::unknown002 *CArcData::begin() const { return unknown08; }

const CArcData::unknown002 *CArcData::end() const {
  u32 files = 0;
  if (unknown00 != nullptr) {
    files = unknown00->m_files;
  }
  if (unknown08 != nullptr) {
    return unknown08 + files;
  }
  return nullptr;
}

} // namespace arc
