#pragma once
#include <stddef.h>

#include "mtl/mem_manager.h"
#include "nn/fs.h"
#include "types.h"

namespace ml {
namespace detail {

// Name from the symbols (ml::detail::FileLoader::readFile); the layout is inferred from the destructor and readFile.
class FileLoader {
public:
  ~FileLoader();
  void readFile();

  // Inferred role: frees the data; original name unknown.
  void unknown001() {
    if (unknown10 != nullptr) {
      mtl::MemManager::deallocate(unknown10, 0, false);
      unknown10 = nullptr;
    }
  }

  nn::fs::FileHandle unknown00; // Inferred role: file; original member name unknown.
  bool unknown08;               // Inferred role: file opened; original member name unknown.
  void *unknown10;              // Inferred role: file data; original member name unknown.
  s64 unknown18;                // Inferred role: file size; original member name unknown.
};

static_assert(offsetof(FileLoader, unknown08) == 0x08, "");
static_assert(offsetof(FileLoader, unknown10) == 0x10, "");
static_assert(offsetof(FileLoader, unknown18) == 0x18, "");
static_assert(sizeof(FileLoader) == 0x20, "");

} // namespace detail
} // namespace ml
