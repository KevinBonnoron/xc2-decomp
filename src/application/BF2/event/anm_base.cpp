#include "event/anm_base.h"

#include "mm_math/mm_math.h"

namespace event {

AnmBase::AnmBase() { clear(); }

void AnmBase::clear() {
  frames.clear();
  state = STATE_FIRST;
  cv = CV_TYPE_LINEAR;
  frame = 0.0f;
  index = 0;
  alpha = 0.0f;
  endFrame = 0.0f;
}

void AnmBase::update(f32 delta) {
  if (delta < 0.0f) {
    return;
  }
  size_t prevIndex = index;
  u32 state = this->state;
  this->state = state & ~STATE_UPDATE;
  if (state & STATE_FIRST) {
    if (delta != 0.0f) {
      this->state = state & ~(STATE_FIRST | STATE_UPDATE);
    }
    this->state |= STATE_UPDATE;
  }
  if (delta != 0.0f && !frames.empty()) {
    this->frame += delta;
    mm::clampRef(this->frame, 0.0f, endFrame);
    if (cv == CV_TYPE_LINEAR || endFrame <= 0.0f) {
      getIndex_Alpha(index, alpha, this->frame, index, alpha);
    } else {
      f32 frame = endFrame * Curve::getValue(cv, this->frame / endFrame);
      mm::clampRef(frame, 0.0f, endFrame);
      getIndex_Alpha(index, alpha, frame, index, alpha);
    }
  }
  if (prevIndex < index) {
    this->state |= STATE_UPDATE;
  }
}

void AnmBase::getIndex_Alpha(size_t &index, f32 &alpha, f32 frame, size_t startIndex, f32 startAlpha) const {
  index = startIndex;
  alpha = startAlpha;
  if (frames.empty()) {
    return;
  }
  if (frames.front() > frame) {
    index = 0;
    alpha = 0.0f;
  } else if (frames.back() > frame) {
    f32 start = frames[index];
    f32 end;
    for (;;) {
      end = frames[index + 1];
      if (start <= frame && end > frame) {
        break;
      }
      index++;
      start = end;
    }
    f32 range = end - start;
    alpha = range != 0.0f ? (frame - start) / range : 0.0f;
  } else {
    index = frames.size() - 1;
    alpha = 0.0f;
  }
}

void AnmBase::replay() {
  if (!frames.empty()) {
    state = STATE_FIRST | STATE_PLAY;
    frame = 0.0f;
    index = 0;
    alpha = 0.0f;
  }
}

size_t AnmBase::count() const { return frames.size(); }

void AnmBase::append(f32 frame) {
  frame = __builtin_fmaxf(frame, 0.0f);
  if (!frames.empty() && frame < frames.back()) {
    frame = frames.back();
  }
  state |= STATE_PLAY;
  frames.push_back(frame);
  endFrame = frame;
}

void AnmBase::setCv(CV_TYPE cv) { this->cv = cv; }

} // namespace event
