#include "event/object_tree.h"

namespace event {

ObjectTree::ObjectTree(const char *name) : Object(OBJTYPE_TREE, name) {}

ObjectTree::~ObjectTree() {}

} // namespace event
