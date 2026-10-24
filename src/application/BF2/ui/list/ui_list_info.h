#pragma once
#include <stddef.h>

#include <algorithm>
#include <functional>

#include "mm_mtl/reference_object.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace ui {

class UIListInfoBase : public mm::mtl::ReferenceObject {
public:
  struct SetupParam {
    SetupParam() : unknown00(0), unknown04(0), unknown08(1), unknown0c(1), unknown10(false) {}

    u32 unknown00;  // Inferred role: index; original member name unknown.
    u32 unknown04;  // Inferred role: column size; original member name unknown.
    u32 unknown08;  // Inferred role: page row size; original member name unknown.
    u32 unknown0c;  // Inferred role: page column size; original member name unknown.
    bool unknown10; // Inferred role: loop; original member name unknown.
  };

  UIListInfoBase();
  virtual ~UIListInfoBase();
  virtual void clear();
  virtual void update();

  void setup(const SetupParam &param);
  void setIndex(u32 index);
  bool isValid() const;
  bool isEmpty() const;
  u32 getSize() const;
  u32 getColumnSize() const;
  u32 getPageRowSize() const;
  u32 getPageColumnSize() const;
  void addSize(u32 count);
  void subSize(u32 count);
  u32 getPageSize() const;
  u32 getRowSize() const;
  u32 getIndex(bool inPage) const;
  u32 getPageIndex(u32 index) const;
  u32 getRowOffset() const;
  u32 getColumnOffset() const;

  SetupParam unknown0c; // Inferred role: param; original member name unknown.
  u32 m_size;
  u32 unknown24;  // Inferred role: index; original member name unknown.
  u32 unknown28;  // Inferred role: row offset; original member name unknown.
  u32 unknown2c;  // Inferred role: column offset; original member name unknown.
  bool unknown30; // Inferred role: changed; original member name unknown.
};

static_assert(offsetof(UIListInfoBase, unknown0c) == 0x0c, "");
static_assert(offsetof(UIListInfoBase, m_size) == 0x20, "");
static_assert(offsetof(UIListInfoBase, unknown24) == 0x24, "");
static_assert(offsetof(UIListInfoBase, unknown28) == 0x28, "");
static_assert(offsetof(UIListInfoBase, unknown2c) == 0x2c, "");
static_assert(offsetof(UIListInfoBase, unknown30) == 0x30, "");
static_assert(sizeof(UIListInfoBase) == 0x38, "");

template <typename T> class UIListInfo : public UIListInfoBase {
public:
  UIListInfo() : invalid(), contentsChanged(false) {}

  virtual ~UIListInfo() {
    if (!contents.empty()) {
      contents.destroy();
    }
  }

  virtual void clear() {
    contents.clear();
    UIListInfoBase::clear();
  }

  virtual void setup(mm::mtl::IAllocator *allocator, const SetupParam &param) {
    UIListInfoBase::setup(param);
    if (isValid()) {
      if (!contents.empty()) {
        contents.destroy();
      }
      u32 count = getPageColumnSize() * getPageRowSize();
      if (count < 8) {
        count = 8;
      }
      contents.setAllocator(allocator);
      contents.reserve(count);
    }
  }

  void addContents(const T &value) {
    contents.push_back(value);
    addSize(1);
    contentsChanged = true;
  }

  T &getContents(u32 index) {
    if (index < contents.size()) {
      return contents[index];
    }
    return invalid;
  }

  const T &getContents(u32 index) const {
    if (index < contents.size()) {
      return contents[index];
    }
    return invalid;
  }

  void sort(std::function<bool(const T &, const T &)> compare) {
    if (!contents.empty()) {
      std::sort(contents.begin(), contents.end(), compare);
      contentsChanged = true;
    }
  }

  mm::mtl::Vector<T> contents;
  T invalid;
  bool contentsChanged;
};

} // namespace ui
