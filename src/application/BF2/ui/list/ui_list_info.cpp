#include "ui/list/ui_list_info.h"

namespace ui {

UIListInfoBase::UIListInfoBase() : size(0), index(0), rowOffset(0), columnOffset(0), changed(false) {}

UIListInfoBase::~UIListInfoBase() { ; }

void UIListInfoBase::setup(const SetupParam &param) {
  this->param = param;
  if (this->param.columnSize == 0) {
    this->param.columnSize = this->param.pageColumnSize;
  }
  clear();
  setIndex(param.index);
}

void UIListInfoBase::clear() {
  changed = false;
  size = 0;
  index = 0;
  rowOffset = 0;
  columnOffset = 0;
}

bool UIListInfoBase::isValid() const { return param.pageColumnSize != 0 && param.pageRowSize != 0; }

bool UIListInfoBase::isEmpty() const { return size == 0; }

u32 UIListInfoBase::getSize() const { return size; }

u32 UIListInfoBase::getColumnSize() const {
  if (size == 0) {
    return 0;
  }
  return param.columnSize;
}

u32 UIListInfoBase::getPageRowSize() const {
  if (param.pageColumnSize == 0) {
    return 0;
  }
  return param.pageRowSize;
}

u32 UIListInfoBase::getPageColumnSize() const {
  if (!isValid()) {
    return 0;
  }
  return param.pageColumnSize;
}

void UIListInfoBase::update() { changed = false; }

void UIListInfoBase::addSize(u32 count) { size += count; }

void UIListInfoBase::subSize(u32 count) {
  if (count == 0 || size == 0) {
    return;
  }

  u32 current = index;
  int remain = size - count;
  size = remain < 0 ? 0 : remain;
  if (size != 0 && static_cast<int>(size) > static_cast<int>(getPageSize())) {
    if (rowOffset != 0 && getRowSize() > getPageRowSize()) {
      u32 lastRow;
      if (param.pageColumnSize != 0) {
        lastRow = (size - 1) / param.pageColumnSize;
      }
      u32 maxRowOffset = lastRow - (getPageRowSize() - 1);
      if (rowOffset > maxRowOffset) {
        rowOffset = maxRowOffset;
      }
    }
    if (columnOffset != 0 && param.columnSize > getPageColumnSize()) {
      u32 lastColumn;
      if (param.pageColumnSize != 0) {
        lastColumn = (size - 1) / param.pageRowSize;
      }
      u32 maxColumnOffset = lastColumn - (getPageColumnSize() - 1);
      if (columnOffset > maxColumnOffset) {
        columnOffset = maxColumnOffset;
      }
    }
  } else {
    rowOffset = 0;
    columnOffset = 0;
  }

  if (current >= size) {
    setIndex(size - 1);
  }
}

u32 UIListInfoBase::getPageSize() const {
  u32 rows = getPageRowSize();
  if (rows == 0) {
    return 0;
  }
  return param.pageColumnSize * rows;
}

u32 UIListInfoBase::getRowSize() const {
  if (size == 0) {
    return 0;
  }
  u32 rows = size / param.columnSize;
  if (size % param.columnSize != 0) {
    rows++;
  }
  return rows;
}

u32 UIListInfoBase::getIndex(bool inPage) const {
  u32 result = 0;
  if (size != 0) {
    result = index;
    if (inPage) {
      result = index - (columnOffset + rowOffset * param.pageColumnSize);
    }
  }
  return result;
}

u32 UIListInfoBase::getPageIndex(u32 index) const {
  if (!isValid() || size == 0) {
    return 0;
  }
  u32 row = index / param.pageColumnSize + rowOffset;
  u32 column = index % param.pageColumnSize + columnOffset;
  return row * param.pageColumnSize + column;
}

u32 UIListInfoBase::getRowOffset() const {
  if (!isValid() || size == 0) {
    return 0;
  }
  return rowOffset;
}

u32 UIListInfoBase::getColumnOffset() const {
  if (!isValid() || size == 0) {
    return 0;
  }
  return columnOffset;
}

} // namespace ui
