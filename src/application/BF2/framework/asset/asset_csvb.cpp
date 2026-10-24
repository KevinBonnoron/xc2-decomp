#include "framework/asset/asset_csvb.h"

#include "csvb/csvb_data.h"
#include "framework/asset/asset_manager.h"
#include "ml/dev_file_th.h"

namespace fw {

AssetCsvb *AssetCsvb::CreateFromMemory(mtl::ALLOC_HANDLE handle, const void *data, u32 size, const char *name) {
  mm::mtl::FixStr<256> fileName;
  ml::DevFileTh::normalizeDvdFileName(fileName, name);
  AssetCsvb *csvb = new (AssetManager::getMemSYS()) AssetCsvb();
  if (csvb != nullptr) {
    csvb->unknown0c = handle;
    if (data != nullptr && size != 0) {
      csvb->unknown20 = new (AssetManager::getMemSYS()) csvb::CCsvbData();
      csvb->unknown20->Load(handle, data, size);
    }

    csvb->unknown28 = fileName.c_str();
    csvb->unknown18 = AssetManager::getHash(fileName.c_str());
    csvb->addRef();
  }

  return csvb;
}

AssetCsvb *AssetCsvb::CreateFromMemory(mm::mtl::IAllocator *allocator, const void *data, u32 size, const char *name) {
  mm::mtl::FixStr<256> fileName;
  ml::DevFileTh::normalizeDvdFileName(fileName, name);
  AssetCsvb *csvb = new (AssetManager::getMemSYS()) AssetCsvb();
  if (csvb != nullptr) {
    csvb->unknown10 = allocator;
    if (data != nullptr && size != 0) {
      csvb->unknown20 = new (AssetManager::getMemSYS()) csvb::CCsvbData();
      csvb->unknown20->Load(allocator, data, size);
    }

    csvb->unknown28 = fileName.c_str();
    csvb->unknown18 = AssetManager::getHash(fileName.c_str());
    csvb->addRef();
  }

  return csvb;
}

AssetCsvb *AssetCsvb::CreateFromCache(mtl::ALLOC_HANDLE handle, const char *name) {
  AssetCsvb *source = nullptr;
  for (AssetCsvb *csvb = AssetManager::get()->searchCsvb(name, nullptr); csvb != nullptr; csvb = AssetManager::get()->searchCsvb(name, csvb)) {
    if (csvb->unknown0c == handle) {
      csvb->addRef();
      return csvb;
    }

    source = csvb;
  }

  if (source != nullptr) {
    return source->Clone(handle);
  }

  return nullptr;
}

AssetCsvb *AssetCsvb::Clone(mtl::ALLOC_HANDLE handle) const {
  AssetCsvb *csvb = new (AssetManager::getMemSYS()) AssetCsvb();
  if (csvb != nullptr) {
    if (unknown20 != nullptr) {
      csvb->unknown20 = new (AssetManager::getMemSYS()) csvb::CCsvbData();
      csvb->unknown20->Copy(handle, unknown20);
    }

    csvb->unknown0c = handle;
    csvb->unknown28 = unknown28;
    csvb->unknown18 = unknown18;
    csvb->addRef();
  }

  return csvb;
}

AssetCsvb *AssetCsvb::CreateFromCache(mm::mtl::IAllocator *allocator, const char *name) {
  AssetCsvb *source = nullptr;
  for (AssetCsvb *csvb = AssetManager::get()->searchCsvb(name, nullptr); csvb != nullptr; csvb = AssetManager::get()->searchCsvb(name, csvb)) {
    if (csvb->unknown10 == allocator) {
      csvb->addRef();
      return csvb;
    }

    source = csvb;
  }

  if (source != nullptr) {
    return source->Clone(allocator);
  }

  return nullptr;
}

AssetCsvb *AssetCsvb::Clone(mm::mtl::IAllocator *allocator) const {
  AssetCsvb *csvb = new (AssetManager::getMemSYS()) AssetCsvb();
  if (csvb != nullptr) {
    if (unknown20 != nullptr) {
      csvb->unknown20 = new (AssetManager::getMemSYS()) csvb::CCsvbData();
      csvb->unknown20->Copy(allocator, unknown20);
    }

    csvb->unknown10 = allocator;
    csvb->unknown28 = unknown28;
    csvb->unknown18 = unknown18;
    csvb->addRef();
  }

  return csvb;
}

void *AssetCsvb::LoadFromPacdata(mtl::ALLOC_HANDLE handle, const char *name, int &size) {
  size = 0;
  return nullptr;
}

AssetCsvb::AssetCsvb() : unknown10(nullptr), unknown18(0), unknown20(nullptr) { AssetManager::get()->addCsvb(this); }

AssetCsvb::~AssetCsvb() {
  if (unknown20 != nullptr) {
    delete unknown20;
    unknown20 = nullptr;
  }

  AssetManager::get()->removeCsvb(this);
}

} // namespace fw
