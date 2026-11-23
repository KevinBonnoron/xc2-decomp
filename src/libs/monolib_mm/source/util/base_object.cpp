#include "ml/base_object.h"

#include "ml/critical_section.h"

namespace ml {

int BaseObjectM::AddRef() {
  CS cs(m_criticalSection);
  return ++unknown08;
}

int BaseObjectM::Release() {
  int ref;
  {
    CS cs(m_criticalSection);
    ref = --unknown08;
  }
  if (ref == 0) {
    delete this;
  }
  return ref;
}

void BaseObjectM::SetName(const char *name) {
  CS cs(m_criticalSection);
  unknown0c = name;
}

} // namespace ml
