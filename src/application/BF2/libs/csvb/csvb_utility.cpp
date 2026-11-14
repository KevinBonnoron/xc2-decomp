// No game string names this file: named after its header csvb/csvb_utility.h, like csvb/csvb_data.cpp.
#include "csvb/csvb_utility.h"

#include "ml/dev_file_th.h"
#include "ml/ml_mem.h"
#include "mm_mtl/fixstr.h"
#include "mtl/alloc_handle.h"

namespace csvb {

void CCsvbUtility::EndianSwap4(void *value) {
  u8 *bytes = static_cast<u8 *>(value);
  u8 first = bytes[0];
  u8 second = bytes[1];
  u8 third = bytes[2];
  u8 fourth = bytes[3];
  bytes[0] = fourth;
  bytes[1] = third;
  bytes[2] = second;
  bytes[3] = first;
}

void CCsvbUtility::EndianSwap2(void *value) {
  u8 *bytes = static_cast<u8 *>(value);
  u8 first = bytes[0];
  bytes[0] = bytes[1];
  bytes[1] = first;
}

bool CCsvbUtility::LoadFile(const char *path, void **data, u32 *size) {
  mm::mtl::FixStr<256> fileName;
  ml::DevFileTh::normalizeDvdFileName(fileName, path);
  int fileSize = 0;
  ml::DevFileParamTh param;
  param._08 = ml::MlMem::getProductMem();
  param.unknown00 = fileName.c_str();
  param._58 = 0;
  *data = ml::DevFileTh::readFileBlock(param, &fileSize, nullptr);
  *size = fileSize;
  return true;
}

void CCsvbUtility::SaveFile(const char *path, const void *data, u32 size) { ml::DevFileTh::writeFileBlock(path, data, size, 0); }

bool CCsvbUtility::GetCsvbInfo(stCsvbInfo &info, const void *data, u32 size, bool endianSwap) {
  const stCsvbInfo::unknown001 *header = static_cast<const stCsvbInfo::unknown001 *>(data);
  info.unknown00 = *header;
  if (endianSwap) {
    EndianSwap2(&info.unknown00.unknown04);
    EndianSwap2(&info.unknown00.unknown06);
    EndianSwap4(&info.unknown00.unknown08);
    EndianSwap4(&info.unknown00.unknown0c);
  }
  info.unknown10 = reinterpret_cast<const stCsvbRowInfo *>(header + 1);
  info.unknown18 = reinterpret_cast<const stCsvbDataInfo *>(reinterpret_cast<const u8 *>(info.unknown10) + info.unknown00.unknown04 * sizeof(stCsvbRowInfo));
  info.unknown20 = reinterpret_cast<const u8 *>(info.unknown18 + info.unknown00.unknown06);
  info.unknown28 = reinterpret_cast<const char *>(info.unknown20 + info.unknown00.unknown08);
  return static_cast<size_t>(reinterpret_cast<const u8 *>(info.unknown28) + info.unknown00.unknown0c - static_cast<const u8 *>(data)) <= size;
}

} // namespace csvb
