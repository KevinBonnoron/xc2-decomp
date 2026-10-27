#pragma once

namespace ml {

class DrMan;
class DrPixlMan;
class DrPixlPostMan;

class DrPixlPostObj {
public:
  DrPixlPostObj(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan);
  static float gaussianDistribution(float x, float y, float rho);
  static void getSampleOffsetDownScale4x4(int width, int height, float *offsets);
  static void calc1PixlOfs(float &x, float &y);
  static void getSampleOffsets_DownScale2x2(int width, int height, float *offsets);

  DrMan *unknown00;         // Inferred role: driver manager; original member name unknown.
  DrPixlMan *unknown08;     // Inferred role: pixel manager; original member name unknown.
  DrPixlPostMan *unknown10; // Inferred role: post manager; original member name unknown.
};

} // namespace ml
