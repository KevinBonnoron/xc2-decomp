#pragma once
#include "types.h"

#include <stddef.h>

namespace arc {

class CArcData {
public:
  // Archive header; offsets read by CArcData::find, getFiles, setData and getStr.
  struct unknown001 {
    u8 _00[0x08 - 0x00];
    u32 unknown08; // Inferred role: format version, below 0x102 the files are searched linearly; original member name unknown.
    u32 m_files;
    u32 unknown10; // Inferred role: offset of the file table; original member name unknown.
    u8 _14[0x20 - 0x14];
    char m_str[1];
  };

  // File table entry, 0x40 bytes; offsets read by CArcData::getFileAdr, getFileSize, getFileHash and getFileName.
  struct unknown002 {
    u32 unknown00; // Inferred role: offset of the file from the archive start; original member name unknown.
    u32 m_fileSize;
    u32 m_fileHash;
    char m_fileName[0x40 - 0x0c];
  };

  // Default argument decoded from Vector<CArcData>::resize and extend, which construct new elements with CArcData(nullptr).
  CArcData(void *data = nullptr);
  // User-provided (empty) in the original: the game emits event::LipsyncRes::~LipsyncRes (base destructor, 1.0.0: 0x710013db1c) as a
  // function of its own instead of reusing event::IResEvent's, which only happens with a member of non-trivial destructor.
  ~CArcData() {}
  // Reconstructed from symbol arc::CArcData::setData(void*) at 0x7100695320.
  void setData(void *data);
  u32 find(const char *name) const;
  void *getFileAdr(const char *name) const;
  // Declared from symbols _ZNK3arc8CArcData8getFilesEv, getFileNameEj, getFileSizeEj and getFileAdrEj (0x6953xx..0x6955xx).
  u32 getFiles() const;
  const char *getStr() const;
  const unknown002 *getFileHeader(u32 index) const;
  const char *getFileName(u32 index) const;
  u32 getFileSize(u32 index) const;
  u32 getFileHash(u32 index) const;
  static u32 calcHash(const char *name);
  void *getFileAdr(u32 index) const;
  unknown002 *begin();
  unknown002 *end();
  const unknown002 *begin() const;
  const unknown002 *end() const;

  unknown001 *unknown00; // Inferred role: data; original member name unknown.
  unknown002 *unknown08; // Inferred role: file table; original member name unknown.
};

static_assert(offsetof(CArcData::unknown001, unknown08) == 0x08, "");
static_assert(offsetof(CArcData::unknown001, m_files) == 0x0c, "");
static_assert(offsetof(CArcData::unknown001, unknown10) == 0x10, "");
static_assert(offsetof(CArcData::unknown001, m_str) == 0x20, "");
static_assert(offsetof(CArcData::unknown002, m_fileSize) == 0x04, "");
static_assert(offsetof(CArcData::unknown002, m_fileHash) == 0x08, "");
static_assert(offsetof(CArcData::unknown002, m_fileName) == 0x0c, "");
static_assert(sizeof(CArcData::unknown002) == 0x40, "");
static_assert(sizeof(CArcData) == 0x10, "");

} // namespace arc
