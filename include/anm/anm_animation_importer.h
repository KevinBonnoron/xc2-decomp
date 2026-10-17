#pragma once

namespace anm {

class Binding;

class AnimationImporter {
public:
  static Binding *import(void *data);
};

} // namespace anm
