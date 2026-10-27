#pragma once

namespace anm {

class Binding;
class Skeleton;
struct QsTransform;

class SpaceResolveUtil {
public:
  static bool setReferencePoseNoTruck(const Binding *binding, const Skeleton *skeleton, QsTransform *transforms);
};

} // namespace anm
