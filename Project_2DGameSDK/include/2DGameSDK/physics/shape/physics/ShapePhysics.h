#ifndef __SHAPE_DEFINITION__
#define __SHAPE_DEFINITION__

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <chipmunk/chipmunk.h>

template <class TDefinition>
class GAMESDK_DLL ShapePhysics {
public:
  virtual void InitProperties(cpSpace* space, cpBody* body, cpShape* shape) = 0;

  virtual TDefinition* Copy() = 0;
};

#endif