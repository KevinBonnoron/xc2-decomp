#include "rcha/csv_reader.h"

#include "ml/dev_file_th.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

CsvReader::CsvReader() : unknown00(nullptr), unknown08(0) {}

CsvReader::~CsvReader() {
  if (unknown00 != nullptr) {
    mtl::MemManager::deallocate(unknown00, 0, false);
    unknown00 = nullptr;
  }
}

bool CsvReader::load(mtl::ALLOC_HANDLE handle, const char *path) {
  if (unknown00 != nullptr) {
    mtl::MemManager::deallocate(unknown00, 0, false);
    unknown00 = nullptr;
  }
  ml::DevFileParamTh param;
  param._08 = handle;
  param.unknown00 = path;
  param._54 = 0x1000;
  u8 *buffer = static_cast<u8 *>(ml::DevFileTh::readFileBlock(param, &unknown08, nullptr));
  unknown00 = buffer;
  if (buffer != nullptr) {
    parse(buffer, unknown08);
    return true;
  }
  return false;
}

int CsvReader::getMaxLine() const { return unknown10.size(); }

int CsvReader::getMaxCol(int line) const {
  if (line < getMaxLine()) {
    return unknown10[line].size();
  }
  return 0;
}

u8 *CsvReader::getStr(int line, int col) {
  if (line < getMaxLine() && col < getMaxCol(line)) {
    return unknown10[line][col];
  }
  return nullptr;
}
