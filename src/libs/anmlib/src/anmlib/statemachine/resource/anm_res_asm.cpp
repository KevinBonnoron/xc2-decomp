#include "anm/anm_res_asm.h"

#include <algorithm>
#include <string.h>

#include "anm/anm_array.h"
#include "anm/anm_res_state_data.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/vector.h"

namespace anm {

struct Comp {
  bool operator()(const ResStateData &lhs, const char *rhs) const { return strcmp(lhs.unknown00->name, rhs) < 0; }
};

ResStateData *ResASM::findStateData(const char *name) {
  ArrayIterartor<ResStateData> it = std::lower_bound(unknown28.begin(), unknown28.end(), name, Comp());
  if (it != unknown28.end() && strcmp(it->unknown00->name, name) == 0) {
    return it.operator->();
  }
  return nullptr;
}

const ResStateData *ResASM::findResStateData(const char *name) const {
  ArrayIterartor<const ResStateData> it = std::lower_bound(unknown28.begin(), unknown28.end(), name, Comp());
  if (it != unknown28.end() && strcmp(it->unknown00->name, name) == 0) {
    return it.operator->();
  }
  return nullptr;
}

bool ResASM::setAttribute(u32 category, const char *state, u64 attribute) {
  ResStateData *stateData = findStateData(state);
  if (stateData == nullptr) {
    return false;
  }
  stateData->setAttribute(category, attribute);
  return true;
}

bool ResASM::setEnterAnnotation(u32 type, const char *state, const AsmAnnotetion &annotation) {
  ResStateData *stateData = findStateData(state);
  if (stateData == nullptr) {
    return false;
  }
  stateData->unknown50[type].push_back(annotation);
  return true;
}

bool ResASM::setLeaveAnnotation(u32 type, const char *state, const AsmAnnotetion &annotation) {
  ResStateData *stateData = findStateData(state);
  if (stateData == nullptr) {
    return false;
  }
  stateData->unknown118[type].push_back(annotation);
  return true;
}

bool ResASM::setFrameAnnotation(u32 type, const char *state, f32 frame, const AsmAnnotetion &annotation) {
  ResStateData *stateData = findStateData(state);
  if (stateData == nullptr) {
    return false;
  }
  stateData->setFrameAnnotation(type, 0, frame, annotation);
  return true;
}

void ResASM::restore(const ResResolver &resolver) {
  for (u32 i = 0; i < unknown28.size(); i++) {
    unknown28[i].restore(resolver);
  }
}

void ResASM::clearAnnotations(u32 type) {
  clearAttribute(type);
  clearEnterAnnotation(type);
  clearLeaveAnnotation(type);
  clearFrameAnnotation(type);
}

void ResASM::clearEnterAnnotation(u32 type) {
  for (ArrayIterartor<ResStateData> it = unknown28.begin(), last = unknown28.end(); it != last; ++it) {
    it->unknown001(type);
  }
}

void ResASM::clearLeaveAnnotation(u32 type) {
  for (ArrayIterartor<ResStateData> it = unknown28.begin(), last = unknown28.end(); it != last; ++it) {
    it->unknown002(type);
  }
}

void ResASM::sortAnnotation(u32 type) {
  for (ArrayIterartor<ResStateData> it = unknown28.begin(), last = unknown28.end(); it != last; ++it) {
    it->sortAnnotation(type);
  }
}

void ResASM::clearAttribute(u32 category) {
  for (ArrayIterartor<ResStateData> it = unknown28.begin(), last = unknown28.end(); it != last; ++it) {
    it->setAttribute(category, 0);
  }
}

void ResASM::clearFrameAnnotation(u32 type) {
  for (ArrayIterartor<ResStateData> it = unknown28.begin(), last = unknown28.end(); it != last; ++it) {
    it->clearFrameAnnotation(type);
  }
}

} // namespace anm
