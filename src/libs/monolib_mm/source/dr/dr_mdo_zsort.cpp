#include "dr/dr_mdo_zsort.h"

namespace ml {

void DrMdoZSortObj::setNext(DrMdoZSortObj *next) { m_next = next; }

void DrMdoZSortObj::setParent(DrMdoZSortObj *parent) {
  if (this != parent) {
    m_parent = parent;
  }
}

DrMdoZSortObj *DrMdoZSortObj::getNext() { return m_next; }

DrMdoZSortObj *DrMdoZSortObj::getParent() { return m_parent; }

DrMdoZSortObj::DrMdoZSortObj(void *owner) : m_next(nullptr), m_parent(nullptr), m_owner(owner) {}

} // namespace ml
