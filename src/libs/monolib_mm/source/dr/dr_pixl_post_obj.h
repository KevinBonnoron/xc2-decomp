#pragma once

namespace ml {

class DrMan;
class DrPixlMan;
class DrPixlPostMan;

class DrPixlPostObj {
public:
  DrPixlPostObj(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan);

  DrMan *unknown00;         // Inferred role: driver manager; original member name unknown.
  DrPixlMan *unknown08;     // Inferred role: pixel manager; original member name unknown.
  DrPixlPostMan *unknown10; // Inferred role: post manager; original member name unknown.
  bool unknown18;           // Inferred role: initialize flag; original member name unknown.
};

} // namespace ml
