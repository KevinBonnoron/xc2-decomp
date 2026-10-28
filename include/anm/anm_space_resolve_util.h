#pragma once

namespace anm {

class Binding;
class Skeleton;
struct QsTransform;

class SpaceResolveUtil {
public:
  static bool clacPoseMSNoTruck(const Binding *binding, const Skeleton *skeleton, QsTransform *transforms);
  static void convertLStoMS(const Skeleton *skeleton, QsTransform *transforms);
  static void convertLStoMSPartial(const Skeleton *skeleton, const bool *mask, QsTransform *transforms);
  static void convertMStoLS(const Skeleton *skeleton, QsTransform *transforms);
  static void convertMStoLSPartial(const Skeleton *skeleton, const bool *mask, QsTransform *transforms);
  static bool setReferencePoseNoTruck(const Binding *binding, const Skeleton *skeleton, QsTransform *transforms);
};

} // namespace anm
