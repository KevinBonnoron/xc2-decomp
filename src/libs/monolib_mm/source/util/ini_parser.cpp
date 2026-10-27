#include "ml/ini_parser.h"

#include <string.h>

namespace ml {

const char *IniParser::getKeyValue(const char *section, const char *key) const {
  for (const KeyParam *param = unknown0000.begin(); param != unknown0000.end(); param++) {
    if (strcmp(param->unknown00.c_str(), key) == 0 && strcmp(param->unknown108.c_str(), section) == 0) {
      return param->unknown84.c_str();
    }
  }
  return "";
}

} // namespace ml
