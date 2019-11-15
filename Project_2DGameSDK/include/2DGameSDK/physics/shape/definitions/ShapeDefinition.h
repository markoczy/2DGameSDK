#ifndef __SHAPE_DEFINITION__
#define __SHAPE_DEFINITION__

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <chipmunk/chipmunk.h>

class GAMESDK_DLL ShapeDefinition {
public:
  virtual void InitProperties(cpSpace* space, cpBody* body, cpShape* shape) = 0;
};

#endif