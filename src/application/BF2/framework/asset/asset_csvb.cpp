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
    csvb->handle = handle;
    if (data != nullptr && size != 0) {
      csvb->data = new (AssetManager::getMemSYS()) csvb::CCsvbData();
      csvb->data->Load(handle, data, size);
    }

    csvb->name = fileName.c_str();
    csvb->hash = AssetManager::getHash(fileName.c_str());
    csvb->addRef();
  }

  return csvb;
}

AssetCsvb *AssetCsvb::CreateFromMemory(mm::mtl::IAllocator *allocator, const void *data, u32 size, const char *name) {
  mm::mtl::FixStr<256> fileName;
  ml::DevFileTh::normalizeDvdFileName(fileName, name);
  AssetCsvb *csvb = new (AssetManager::getMemSYS()) AssetCsvb();
  if (csvb != nullptr) {
    csvb->allocator = allocator;
    if (data != nullptr && size != 0) {
      csvb->data = new (AssetManager::getMemSYS()) csvb::CCsvbData();
      csvb->data->Load(allocator, data, size);
    }

    csvb->name = fileName.c_str();
    csvb->hash = AssetManager::getHash(fileName.c_str());
    csvb->addRef();
  }

  return csvb;
}

AssetCsvb *AssetCsvb::CreateFromCache(mtl::ALLOC_HANDLE handle, const char *name) {
  AssetCsvb *source = nullptr;
  for (AssetCsvb *csvb = AssetManager::get()->searchCsvb(name, nullptr); csvb != nullptr; csvb = AssetManager::get()->searchCsvb(name, csvb)) {
    if (csvb->handle == handle) {
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
    if (data != nullptr) {
      csvb->data = new (AssetManager::getMemSYS()) csvb::CCsvbData();
      csvb->data->Copy(handle, data);
    }

    csvb->handle = handle;
    csvb->name = name;
    csvb->hash = hash;
    csvb->addRef();
  }

  return csvb;
}

AssetCsvb *AssetCsvb::CreateFromCache(mm::mtl::IAllocator *allocator, const char *name) {
  AssetCsvb *source = nullptr;
  for (AssetCsvb *csvb = AssetManager::get()->searchCsvb(name, nullptr); csvb != nullptr; csvb = AssetManager::get()->searchCsvb(name, csvb)) {
    if (csvb->allocator == allocator) {
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
    if (data != nullptr) {
      csvb->data = new (AssetManager::getMemSYS()) csvb::CCsvbData();
      csvb->data->Copy(allocator, data);
    }

    csvb->allocator = allocator;
    csvb->name = name;
    csvb->hash = hash;
    csvb->addRef();
  }

  return csvb;
}

void *AssetCsvb::LoadFromPacdata(mtl::ALLOC_HANDLE handle, const char *name, int &size) {
  size = 0;
  return nullptr;
}

AssetCsvb::AssetCsvb() : allocator(nullptr), hash(0), data(nullptr) { AssetManager::get()->addCsvb(this); }

AssetCsvb::~AssetCsvb() {
  if (data != nullptr) {
    delete data;
    data = nullptr;
  }

  AssetManager::get()->removeCsvb(this);
}

} // namespace fw
