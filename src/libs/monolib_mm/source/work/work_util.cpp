#include "ml/work_util.h"

#include <string.h>

#include "ml/reslist.h"
#include "ml/work_obj.h"
#include "mm_mtl/fixstr.h"

namespace ml {

namespace _wkut {

bool s_bDispLogH;

} // namespace _wkut

void WorkUtil::setDispLogH(bool isDisp) { _wkut::s_bDispLogH = isDisp; }

bool WorkUtil::isDispLogH() { return _wkut::s_bDispLogH; }

bool WorkUtil::isTopOfParent(const WorkObj *work) {
  if (work->m_parent != nullptr) {
    return work->m_parent->m_children.begin()->value == work;
  }

  return false;
}

bool WorkUtil::searchWork(const WorkObj *parent, const WorkObj *work) {
  if (parent == nullptr) {
    return false;
  }

  if (parent == work) {
    return true;
  }

  for (reslist<WorkObj *>::Node *node = parent->m_children.begin(); node != parent->m_children.end(); node = node->getNext()) {
    if (searchWork(node->value, work)) {
      return true;
    }
  }

  return false;
}

bool WorkUtil::hasChild(WorkObj *parent, const char *name) {
  if (parent == nullptr) {
    return false;
  }

  for (reslist<WorkObj *>::Node *node = parent->m_children.begin(); node != parent->m_children.end(); node = node->getNext()) {
    WorkObj *child = node->value;
    if (strcmp(child->m_name.c_str(), name) == 0) {
      return true;
    }

    if (hasChild(child, name)) {
      return true;
    }
  }

  return false;
}

} // namespace ml
