#include "ui/list/ui_list_info.h"

namespace ui {

UIListInfoBase::UIListInfoBase() : m_size(0), unknown24(0), unknown28(0), unknown2c(0), unknown30(false) {}

UIListInfoBase::~UIListInfoBase() { ; }

void UIListInfoBase::setup(const SetupParam &param) {
  this->unknown0c = param;
  if (this->unknown0c.unknown04 == 0) {
    this->unknown0c.unknown04 = this->unknown0c.unknown0c;
  }
  clear();
  setIndex(param.unknown00);
}

void UIListInfoBase::clear() {
  unknown30 = false;
  m_size = 0;
  unknown24 = 0;
  unknown28 = 0;
  unknown2c = 0;
}

bool UIListInfoBase::isValid() const { return unknown0c.unknown0c != 0 && unknown0c.unknown08 != 0; }

bool UIListInfoBase::isEmpty() const { return m_size == 0; }

u32 UIListInfoBase::getSize() const { return m_size; }

u32 UIListInfoBase::getColumnSize() const {
  if (m_size == 0) {
    return 0;
  }
  return unknown0c.unknown04;
}

u32 UIListInfoBase::getPageRowSize() const {
  if (unknown0c.unknown0c == 0) {
    return 0;
  }
  return unknown0c.unknown08;
}

u32 UIListInfoBase::getPageColumnSize() const {
  if (!isValid()) {
    return 0;
  }
  return unknown0c.unknown0c;
}

void UIListInfoBase::update() { unknown30 = false; }

void UIListInfoBase::addSize(u32 count) { m_size += count; }

void UIListInfoBase::subSize(u32 count) {
  if (count == 0 || m_size == 0) {
    return;
  }

  u32 current = unknown24;
  int remain = m_size - count;
  m_size = remain < 0 ? 0 : remain;
  if (m_size != 0 && static_cast<int>(m_size) > static_cast<int>(getPageSize())) {
    if (unknown28 != 0 && getRowSize() > getPageRowSize()) {
      u32 lastRow;
      if (unknown0c.unknown0c != 0) {
        lastRow = (m_size - 1) / unknown0c.unknown0c;
      }
      u32 maxRowOffset = lastRow - (getPageRowSize() - 1);
      if (unknown28 > maxRowOffset) {
        unknown28 = maxRowOffset;
      }
    }
    if (unknown2c != 0 && unknown0c.unknown04 > getPageColumnSize()) {
      u32 lastColumn;
      if (unknown0c.unknown0c != 0) {
        lastColumn = (m_size - 1) / unknown0c.unknown08;
      }
      u32 maxColumnOffset = lastColumn - (getPageColumnSize() - 1);
      if (unknown2c > maxColumnOffset) {
        unknown2c = maxColumnOffset;
      }
    }
  } else {
    unknown28 = 0;
    unknown2c = 0;
  }

  if (current >= m_size) {
    setIndex(m_size - 1);
  }
}

u32 UIListInfoBase::getPageSize() const {
  u32 rows = getPageRowSize();
  if (rows == 0) {
    return 0;
  }
  return unknown0c.unknown0c * rows;
}

u32 UIListInfoBase::getRowSize() const {
  if (m_size == 0) {
    return 0;
  }
  u32 rows = m_size / unknown0c.unknown04;
  if (m_size % unknown0c.unknown04 != 0) {
    rows++;
  }
  return rows;
}

u32 UIListInfoBase::getIndex(bool inPage) const {
  u32 result = 0;
  if (m_size != 0) {
    result = unknown24;
    if (inPage) {
      result = unknown24 - (unknown2c + unknown28 * unknown0c.unknown0c);
    }
  }
  return result;
}

u32 UIListInfoBase::getPageIndex(u32 index) const {
  if (!isValid() || m_size == 0) {
    return 0;
  }
  u32 row = index / unknown0c.unknown0c + unknown28;
  u32 column = index % unknown0c.unknown0c + unknown2c;
  return row * unknown0c.unknown0c + column;
}

u32 UIListInfoBase::getRowOffset() const {
  if (!isValid() || m_size == 0) {
    return 0;
  }
  return unknown28;
}

u32 UIListInfoBase::getColumnOffset() const {
  if (!isValid() || m_size == 0) {
    return 0;
  }
  return unknown2c;
}

} // namespace ui
