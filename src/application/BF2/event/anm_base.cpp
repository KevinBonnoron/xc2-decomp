#include "event/anm_base.h"

#include "mm_math/mm_math.h"

namespace event {

AnmBase::AnmBase() { clear(); }

void AnmBase::clear() {
  unknown10.clear();
  m_cv = CV_TYPE_LINEAR;
  unknown08 = STATE_FIRST;
  unknown5c = 0.0f;
  unknown68 = 0;
  unknown70 = 0.0f;
  unknown60 = 0.0f;
}

void AnmBase::update(f32 delta) {
  if (delta < 0.0f) {
    return;
  }
  size_t prevIndex = unknown68;
  u32 state = this->unknown08;
  this->unknown08 = state & ~STATE_UPDATE;
  if (state & STATE_FIRST) {
    if (delta != 0.0f) {
      this->unknown08 = state & ~(STATE_FIRST | STATE_UPDATE);
    }
    this->unknown08 |= STATE_UPDATE;
  }
  if (delta != 0.0f && !unknown10.empty()) {
    this->unknown5c += delta;
    mm::clampRef(this->unknown5c, 0.0f, unknown60);
    if (m_cv == CV_TYPE_LINEAR || unknown60 <= 0.0f) {
      getIndex_Alpha(unknown68, unknown70, this->unknown5c, unknown68, unknown70);
    } else {
      f32 frame = unknown60 * Curve::getValue(m_cv, this->unknown5c / unknown60);
      mm::clampRef(frame, 0.0f, unknown60);
      getIndex_Alpha(unknown68, unknown70, frame, unknown68, unknown70);
    }
  }
  if (prevIndex < unknown68) {
    this->unknown08 |= STATE_UPDATE;
  }
}

void AnmBase::getIndex_Alpha(size_t &index, f32 &alpha, f32 frame, size_t startIndex, f32 startAlpha) const {
  index = startIndex;
  alpha = startAlpha;
  if (unknown10.empty()) {
    return;
  }
  if (unknown10.front() > frame) {
    index = 0;
    alpha = 0.0f;
  } else if (unknown10.back() > frame) {
    f32 start = unknown10[index];
    f32 end;
    for (;;) {
      end = unknown10[index + 1];
      if (start <= frame && end > frame) {
        break;
      }
      index++;
      start = end;
    }
    f32 range = end - start;
    alpha = range != 0.0f ? (frame - start) / range : 0.0f;
  } else {
    index = unknown10.size() - 1;
    alpha = 0.0f;
  }
}

void AnmBase::replay() {
  if (!unknown10.empty()) {
    unknown08 = STATE_FIRST | STATE_PLAY;
    unknown5c = 0.0f;
    unknown68 = 0;
    unknown70 = 0.0f;
  }
}

size_t AnmBase::count() const { return unknown10.size(); }

void AnmBase::append(f32 frame) {
  frame = __builtin_fmaxf(frame, 0.0f);
  if (!unknown10.empty() && frame < unknown10.back()) {
    frame = unknown10.back();
  }
  unknown08 |= STATE_PLAY;
  unknown10.push_back(frame);
  unknown60 = frame;
}

void AnmBase::setCv(CV_TYPE cv) { this->m_cv = cv; }

} // namespace event
