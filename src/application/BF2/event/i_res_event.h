#pragma once
#include <stddef.h>

namespace event {

enum RES_RESULT_TYPE {
  RES_RESULT_TYPE_WAIT,
  RES_RESULT_TYPE_LOADING,
  RES_RESULT_TYPE_LOADED,
  RES_RESULT_TYPE_SUCCESS,
  RES_RESULT_TYPE_FAILURE,
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
