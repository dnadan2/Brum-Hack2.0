#ifndef DEVICE_VR_H
#define DEVICE_VR_H

#include <node.h>
#include <OVR.h>
#include "v8Macros.h"

namespace nodeOculus {
  class Device : public node::ObjectWrap {
    public:
      static void Init(v8::Handle<v8::Object> exports);
      static JS_FUNCTION(NewInstance);

    private:
      explicit Device();
      ~Device();

      static JS_FUNCTION(destroyResources);
      static JS_FUNCTION(discoverSensor);
      static JS_FUNCTION(getDeviceInfo);
      static JS_FUNCTION(getPositionDeltas);
      static JS_FUNCTION(getOrientationQuat);
      static JS_FUNCTION(getTrackingData);
      static JS_FUNCTION(getOvrMatrix4f_Projection);

      static JS_FUNCTION(New);
      static v8::Persistent<v8::Function> constructor;

      ovrHmd hmd; // pointer
      float lastX;
      float lastY;
      float lastZ;
  };
}

#endif