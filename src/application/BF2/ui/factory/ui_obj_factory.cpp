#include "ui/factory/ui_obj_factory.h"

#include <string.h>

#include "mm_mtl/fixstr.h"
#include "ui/ui_resource.h"

namespace ui {

bool UIObjFactory::getPreloadResource(const char *name, PreloadResource &resource) {
  for (const PreloadResource *it = unknown30.begin(); it != unknown30.end(); ++it) {
    if (it->unknown08 != nullptr && strcmp(it->unknown08->unknown0c.c_str(), name) == 0) {
      resource = *it;
      return true;
    }
  }
  return false;
}

bool UIObjFactory::isLoading() const {
  if (unknown10 != nullptr) {
    return true;
  }

  for (const PreloadResource *it = unknown30.begin(); it != unknown30.end(); ++it) {
    if (it->unknown08->isLoading()) {
      return true;
    }
  }
  return false;
}

} // namespace ui
