// No game string names this file: named after its header csvb/csvb_data.h, like arc/arc_data.cpp.
#include "csvb/csvb_data.h"

#include "csvb/csvb_utility.h"
#include "mm_mtl/allocator.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

#include <string.h>

namespace csvb {

CCsvbData::CCsvbData() : m_rowCount(0), unknown08(nullptr), unknown10(0), unknown18(nullptr), unknown20(0), unknown28(nullptr), unknown30(nullptr) {}

CCsvbData::~CCsvbData() { Clear(); }

void CCsvbData::Clear() {
  if (unknown08 != nullptr) {
    MemoryFreeLocal(unknown08);
    unknown08 = nullptr;
  }
  m_rowCount = 0;
  if (unknown18 != nullptr) {
    MemoryFreeLocal(unknown18);
    unknown18 = nullptr;
  }
  unknown10 = 0;
  if (unknown28 != nullptr) {
    MemoryFreeLocal(unknown28);
    unknown28 = nullptr;
  }
  unknown20 = 0;
  unknown30 = nullptr;
}

void CCsvbData::MemoryFreeLocal(void *pointer) {
  if (pointer == nullptr) {
    return;
  }
  if (unknown30 != nullptr) {
    unknown30->deallocate(pointer);
  } else {
    mtl::MemManager::deallocate(pointer, 0, false);
  }
}

bool CCsvbData::Load(mtl::ALLOC_HANDLE handle, const char *path) {
  u32 size = 0;
  void *data = nullptr;
  if (!CCsvbUtility::LoadFile(path, &data, &size)) {
    return false;
  }
  bool result = Load(handle, data, size);
  mtl::MemManager::deallocate(data, 0, false);
  return result;
}

bool CCsvbData::Load(mtl::ALLOC_HANDLE handle, const void *data, u32 size) {
  Clear();
  if (CCsvbUtility::GetCsvbFormat(data) != 0) {
    return false;
  }
  stCsvbInfo info = {};
  if (!CCsvbUtility::GetCsvbInfo(info, data, size, false)) {
    return false;
  }
  m_rowCount = info.unknown00.unknown04;
  if (m_rowCount != 0) {
    unknown08 = static_cast<unknown001 *>(CCsvbUtility::CreateCsvbRows(handle, info.unknown10, m_rowCount, false));
  }
  unknown10 = info.unknown00.unknown06;
  if (unknown10 != 0) {
    unknown20 = info.unknown00.unknown0c;
    if (unknown20 != 0) {
      unknown28 = static_cast<char *>(mtl::MemManager::allocate(handle, unknown20, 4, false, "no name", 0));
      memcpy(unknown28, info.unknown28, unknown20);
    }
    unknown18 = static_cast<unknown002 *>(CCsvbUtility::CreateCsvbData(handle, info.unknown18, unknown10, info.unknown20, unknown28, false));
  }
  return true;
}

bool CCsvbData::Load(mm::mtl::IAllocator *allocator, const char *path) {
  u32 size = 0;
  void *data = nullptr;
  if (!CCsvbUtility::LoadFile(path, &data, &size)) {
    return false;
  }
  bool result = Load(allocator, data, size);
  mtl::MemManager::deallocate(data, 0, false);
  return result;
}

bool CCsvbData::Load(mm::mtl::IAllocator *allocator, const void *data, u32 size) {
  Clear();
  if (CCsvbUtility::GetCsvbFormat(data) != 0) {
    return false;
  }
  stCsvbInfo info = {};
  if (!CCsvbUtility::GetCsvbInfo(info, data, size, false)) {
    return false;
  }
  unknown30 = allocator;
  m_rowCount = info.unknown00.unknown04;
  if (m_rowCount != 0) {
    unknown08 = static_cast<unknown001 *>(CCsvbUtility::CreateCsvbRows(allocator, info.unknown10, m_rowCount, false));
  }
  unknown10 = info.unknown00.unknown06;
  if (unknown10 != 0) {
    unknown20 = info.unknown00.unknown0c;
    if (unknown20 != 0) {
      unknown28 = static_cast<char *>(allocator->allocate(unknown20, 8));
      memcpy(unknown28, info.unknown28, unknown20);
    }
    unknown18 = static_cast<unknown002 *>(CCsvbUtility::CreateCsvbData(allocator, info.unknown18, unknown10, info.unknown20, unknown28, false));
  }
  return true;
}

u16 CCsvbData::GetRowCount() const { return m_rowCount; }

u16 CCsvbData::GetColumCount(u16 row) const { return unknown08[row].m_columCount; }

bool CCsvbData::IsValid(u16 row, u16 column) const { return unknown18[unknown08[row].unknown02 + column].unknown00 != 2; }

s32 CCsvbData::GetType(u16 row, u16 column) const { return unknown18[unknown08[row].unknown02 + column].unknown00; }

s32 CCsvbData::GetInt(u16 row, u16 column) const {
  const unknown002 &cell = unknown18[unknown08[row].unknown02 + column];
  switch (cell.unknown00) {
  case 0:
    return cell.unknown08.unknown00;
  case 1:
    return static_cast<s32>(cell.unknown08.unknown00_1);
  }
  return 0;
}

f32 CCsvbData::GetFloat(u16 row, u16 column) const {
  const unknown002 &cell = unknown18[unknown08[row].unknown02 + column];
  switch (cell.unknown00) {
  case 1:
    return cell.unknown08.unknown00_1;
  case 0:
    return static_cast<f32>(cell.unknown08.unknown00);
  }
  return 0.0f;
}

const char *CCsvbData::GetString(u16 row, u16 column) const {
  const unknown002 &cell = unknown18[unknown08[row].unknown02 + column];
  if (cell.unknown00 == 3) {
    return cell.unknown08.unknown00_2;
  }
  return nullptr;
}

void CCsvbData::Print() const {}

} // namespace csvb
