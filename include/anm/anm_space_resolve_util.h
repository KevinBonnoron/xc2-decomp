#pragma once

namespace anm {

class Binding;
class Skeleton;
struct QsTransform;

class SpaceResolveUtil {
public:
  static bool clacPoseMSNoTruck(const Binding *binding, const Skeleton *skeleton, QsTransform *transforms);
  static void convertLStoMS(const Skeleton *skeleton, QsTransform *transforms);
  static void convertMStoLS(const Skeleton *skeleton, QsTransform *transforms);
  static bool setReferencePoseNoTruck(const Binding *binding, const Skeleton *skeleton, QsTransform *transforms);
};

} // namespace anm
