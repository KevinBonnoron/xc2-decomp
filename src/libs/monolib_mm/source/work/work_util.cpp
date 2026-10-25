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
  if (work->unknown58 != nullptr) {
    return work->unknown58->unknown60.begin()->value == work;
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

  for (reslist<WorkObj *>::Node *node = parent->unknown60.begin(); node != parent->unknown60.end(); node = node->getNext()) {
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

  for (reslist<WorkObj *>::Node *node = parent->unknown60.begin(); node != parent->unknown60.end(); node = node->getNext()) {
    WorkObj *child = node->value;
    if (strcmp(child->unknown08.c_str(), name) == 0) {
      return true;
    }

    if (hasChild(child, name)) {
      return true;
    }
  }

  return false;
}

void WorkUtil::dispTree(const WorkObj *work, int depth) {
  if (work == nullptr) {
    return;
  }

  mm::mtl::FixStr<64> name;
  for (int i = 0; i < depth; i++) {
    name += " ";
  }
  name += work->unknown08.c_str();

  for (reslist<WorkObj *>::Node *node = work->unknown60.begin(); node != work->unknown60.end(); node = node->getNext()) {
    dispTree(node->value, depth + 1);
  }
}

} // namespace ml
