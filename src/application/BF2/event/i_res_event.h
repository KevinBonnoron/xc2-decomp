#pragma once
#include <stddef.h>

namespace event {

enum RES_RESULT_TYPE {
  RES_RESULT_TYPE_UNKNOWN_0, // Inferred role: wait; original name unknown.
  RES_RESULT_TYPE_UNKNOWN_1, // Inferred role: loading; original name unknown.
  RES_RESULT_TYPE_UNKNOWN_2, // Inferred role: loaded; original name unknown.
  RES_RESULT_TYPE_UNKNOWN_3, // Inferred role: success; original name unknown.
  RES_RESULT_TYPE_UNKNOWN_4, // Inferred role: failure; original name unknown.
};

class IResEvent {
public:
  struct PARAM {
    PARAM(RES_RESULT_TYPE result, const char *path, void *adr, size_t size) : result(result), path(path), adr(adr), size(size) {}

    RES_RESULT_TYPE result;
    const char *path;
    void *adr;
    size_t size;
  };

  virtual void OnResEvent(const PARAM &param) = 0;
  virtual ~IResEvent() {}
};

} // namespace event
