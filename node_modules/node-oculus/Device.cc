#ifndef BUILDING_NODE_EXTENSION
  #define BUILDING_NODE_EXTENSION
#endif

#include <node.h>
#include "Device.h"
#include <string>
#include <sstream>

namespace nodeOculus {
  v8::Persistent<v8::Function> Device::constructor;

  Device::Device()
    : lastX(0.0), lastY(0.0), lastZ(0.0)
  {
    printf("Initializing OVR.\n");
    ovr_Initialize();
    printf("OVR Initialized\n");
  }

  Device::~Device() {
  }


  JS_METHOD(Device, destroyResources) {
    SCOPE_IN;
    Device* obj = JS_OBJECT(Device, args.This());

    if (obj->hmd != NULL) {
      printf("Destroying HMD.\n");
      ovrHmd_Destroy(obj->hmd);
    }

    printf("Shutting Down OVR.\n");
    ovr_Shutdown();
    printf("OVR Destroyed.\n");
    SCOPE_OUT(JS_BOOL(true));
  }


  JS_METHOD(Device, discoverSensor) {
    SCOPE_IN;

    Device* obj = JS_OBJECT(Device, args.This());

    printf("1: Detecting HMDs.\n");
    int numHMDs = ovrHmd_Detect();

    if (numHMDs > 0) {
      printf("2: Creating HMD.\n");
      obj->hmd = ovrHmd_Create(0);

      if (obj->hmd != NULL) {
        printf("3: HMD Created.\n");

        printf("4: Configuring Tracking\n");
        if (ovrHmd_ConfigureTracking(obj->hmd, ovrTrackingCap_Orientation | ovrTrackingCap_Position, 0) != 0) {
          printf("5: Configured Tracking Successfully\n");

          printf("6: Testing Tracking\n");
          if ((ovrHmd_GetTrackingState(obj->hmd, 0.0f).StatusFlags & ovrStatus_HmdConnected)) {
            printf("7: Sensor Connected\n");
            SCOPE_OUT(JS_BOOL(true));
          }
        }
        ovrHmd_Destroy(obj->hmd);
      }
    }

    printf("FAILED (is the Oculus plugged in?)\n");

    SCOPE_OUT(JS_BOOL(false));
  }

  JS_METHOD(Device, getDeviceInfo) {
    SCOPE_IN;

    Device* obj = JS_OBJECT(Device, args.This());
    v8::Local<v8::Object> res = v8::Object::New();

    if (obj->hmd != NULL) {
      deviceInfo info = ovrHmd_GetDeviceInfo(obj->hmd);
      res->Set(v8::String::NewSymbol("displayDeviceName"), v8::String::NewSymbol(info.DisplayDeviceName));
      res->Set(v8::String::NewSymbol("displayId"), JS_FLOAT(info.DisplayId));
      res->Set(v8::String::NewSymbol("lensSeperationDistance"), JS_FLOAT(info.LensSeparationDistance));
      res->Set(v8::String::NewSymbol("eyeToScreenDistance"), JS_FLOAT(info.EyeToScreenDistance));
      res->Set(v8::String::NewSymbol("screenCenter"), JS_FLOAT(info.ScreenCenter));
      res->Set(v8::String::NewSymbol("interpupillaryDistance"), JS_FLOAT(info.InterpupillaryDistance));
      res->Set(v8::String::NewSymbol("leftMaxR"), JS_FLOAT(info.LeftMaxR));
      res->Set(v8::String::NewSymbol("rightMaxR"), JS_FLOAT(info.RightMaxR));

      v8::Local<v8::Array> screenSize = v8::Array::New(2);
      screenSize->Set(0, JS_FLOAT(info.ScreenSizeW));
      screenSize->Set(1, JS_FLOAT(info.ScreenSizeH));
      res->Set(v8::String::NewSymbol("screenSize"), screenSize);

      v8::Local<v8::Array> resolution = v8::Array::New(2);
      resolution->Set(0, JS_FLOAT(info.ResolutionW));
      resolution->Set(1, JS_FLOAT(info.ResolutionH));
      res->Set(v8::String::NewSymbol("resolution"), resolution);

      // distortion coefficients
      v8::Local<v8::Array> leftDistortion = v8::Array::New(11);
      v8::Local<v8::Array> rightDistortion = v8::Array::New(11);
      for(int i = 0; i < 11; i++) {
        leftDistortion->Set(i,  JS_FLOAT(info.LeftDistortionK[i]));
        rightDistortion->Set(i, JS_FLOAT(info.RightDistortionK[i]));
      }
      res->Set(v8::String::NewSymbol("leftDistortion"), leftDistortion);
      res->Set(v8::String::NewSymbol("rightDistortion"), rightDistortion);

      // chromatic aberration coefficients
      v8::Local<v8::Array> leftChromaticAberration = v8::Array::New(4);
      v8::Local<v8::Array> rightChromaticAberration = v8::Array::New(4);
      for(int i = 0; i < 4; i++) {
        leftChromaticAberration->Set(i,  JS_FLOAT(info.LeftChromaticAberration[i]));
        rightChromaticAberration->Set(i, JS_FLOAT(info.RightChromaticAberration[i]));
      }
      res->Set(v8::String::NewSymbol("leftChromaticAberration"), leftChromaticAberration);
      res->Set(v8::String::NewSymbol("rightChromaticAberration"), rightChromaticAberration);

      // some distortion info
      v8::Local<v8::Array> leftDistortionTanEyeAngleScale = v8::Array::New(2);
      v8::Local<v8::Array> rightDistortionTanEyeAngleScale = v8::Array::New(2);
      v8::Local<v8::Array> leftDistortionLensCenter = v8::Array::New(2);
      v8::Local<v8::Array> rightDistortionLensCenter = v8::Array::New(2);
      for(int i = 0; i < 2; i++) {
        leftDistortionTanEyeAngleScale->Set(i,  JS_FLOAT(info.LeftDistortionTanEyeAngleScale[i]));
        rightDistortionTanEyeAngleScale->Set(i, JS_FLOAT(info.RightDistortionTanEyeAngleScale[i]));
        leftDistortionLensCenter->Set(i,  JS_FLOAT(info.LeftDistortionLensCenter[i]));
        rightDistortionLensCenter->Set(i, JS_FLOAT(info.RightDistortionLensCenter[i]));
      }
      res->Set(v8::String::NewSymbol("leftDistortionTanEyeAngleScale"), leftDistortionTanEyeAngleScale);
      res->Set(v8::String::NewSymbol("rightDistortionTanEyeAngleScale"), rightDistortionTanEyeAngleScale);
      res->Set(v8::String::NewSymbol("leftDistortionLensCenter"), leftDistortionLensCenter);
      res->Set(v8::String::NewSymbol("rightDistortionLensCenter"), rightDistortionLensCenter);

      v8::Local<v8::Array> leftEyeFov = v8::Array::New(4);
      leftEyeFov->Set(0, JS_FLOAT(info.LeftEyeFov[0]));
      leftEyeFov->Set(1, JS_FLOAT(info.LeftEyeFov[1]));
      leftEyeFov->Set(2, JS_FLOAT(info.LeftEyeFov[2]));
      leftEyeFov->Set(3, JS_FLOAT(info.LeftEyeFov[3]));
      res->Set(v8::String::NewSymbol("leftEyeFov"), leftEyeFov);

      v8::Local<v8::Array> rightEyeFov = v8::Array::New(4);
      rightEyeFov->Set(0, JS_FLOAT(info.RightEyeFov[0]));
      rightEyeFov->Set(1, JS_FLOAT(info.RightEyeFov[1]));
      rightEyeFov->Set(2, JS_FLOAT(info.RightEyeFov[2]));
      rightEyeFov->Set(3, JS_FLOAT(info.RightEyeFov[3]));
      res->Set(v8::String::NewSymbol("rightEyeFov"), rightEyeFov);
    }

    SCOPE_OUT(res);
  }

  // returns the delta from when the positional tracking data was last requested
  JS_METHOD(Device, getPositionDeltas) {
    SCOPE_IN;

    Device* obj = JS_OBJECT(Device, args.This());
    v8::Local<v8::Array> res = args.Length() > 0 && args[0]->IsArray() ? v8::Array::Cast(*args[0]) : v8::Array::New(3);
    ovrTrackingState trackingInfo;

    if (obj->hmd != NULL) {
      trackingInfo = ovrHmd_GetTrackingState(obj->hmd, 0.0);
      float currX = trackingInfo.HeadPose.ThePose.Position.x;
      float currY = trackingInfo.HeadPose.ThePose.Position.y;
      float currZ = trackingInfo.HeadPose.ThePose.Position.z;
      res->Set(0, JS_FLOAT(currX - obj->lastX));
      res->Set(1, JS_FLOAT(currY - obj->lastY));
      res->Set(2, JS_FLOAT(currZ - obj->lastZ));
      obj->lastX = currX;
      obj->lastY = currY;
      obj->lastZ = currZ;
    } else {
      printf("obj->hmd is NULL\n");
      res->Set(0, JS_FLOAT(0.0));
      res->Set(1, JS_FLOAT(0.0));
      res->Set(2, JS_FLOAT(0.0));
    }

    SCOPE_OUT(res);
  }

  JS_METHOD(Device, getOrientationQuat) {
    SCOPE_IN;

    Device* obj = JS_OBJECT(Device, args.This());
    v8::Local<v8::Array> res = args.Length() > 0 && args[0]->IsArray() ? v8::Array::Cast(*args[0]) : v8::Array::New(4);
    ovrTrackingState trackingInfo;

    if (obj->hmd != NULL) {
      trackingInfo = ovrHmd_GetTrackingState(obj->hmd, 0.0);
      res->Set(0, JS_FLOAT(trackingInfo.HeadPose.ThePose.Orientation.x));
      res->Set(1, JS_FLOAT(trackingInfo.HeadPose.ThePose.Orientation.y));
      res->Set(2, JS_FLOAT(trackingInfo.HeadPose.ThePose.Orientation.z));
      res->Set(3, JS_FLOAT(trackingInfo.HeadPose.ThePose.Orientation.w));
    } else {
      printf("obj->hmd is NULL\n");
      res->Set(0, JS_FLOAT(0.0));
      res->Set(1, JS_FLOAT(0.0));
      res->Set(2, JS_FLOAT(0.0));
      res->Set(3, JS_FLOAT(1.0));
    }

    SCOPE_OUT(res);
  }

  // alternative to to_string for pre-c++11 compilers
  template <class T>
  std::string toString(T num) {
    std::ostringstream ss;
    ss << num;
    return ss.str();
  }

  // return a flat row-major projection matrix
  JS_METHOD(Device, getOvrMatrix4f_Projection) {
    SCOPE_IN;
    Device * obj = JS_OBJECT(Device, args.This());
    v8::Local<v8::Array> res = v8::Array::New(16);

    if (obj->hmd == NULL) {
      SCOPE_OUT(res);
    }

    ovrFovPort fov;
    float znear;
    float zfar;
    ovrBool rightHanded;

    // if an object is passed, use that to construct our fov struct; if not, use hmd's default with input eye index (or 0 if no index specified)
    if (args[0]->IsObject()) {
      v8::Handle<v8::Object> object = v8::Handle<v8::Object>::Cast(args[0]);
      fov.UpTan = (float) object->Get(v8::String::New("UpTan"))->NumberValue();
      fov.DownTan = (float) object->Get(v8::String::New("DownTan"))->NumberValue();
      fov.LeftTan = (float) object->Get(v8::String::New("LeftTan"))->NumberValue();
      fov.RightTan = (float) object->Get(v8::String::New("RightTan"))->NumberValue();
    } else if (args[0]->IsNumber()) {
      int eye = args[0]->Int32Value();
      fov = obj->hmd->DefaultEyeFov[eye];
    } else {
      fov = obj->hmd->DefaultEyeFov[0];
    }
    
    // defaults to 0.1
    if (args[1]->IsNumber()) {
      znear = (float) args[1]->NumberValue();
    } else {
      znear = 0.1;
    }

    // defaults to 1000
    if (args[2]->IsNumber()) {
      zfar = (float) args[2]->NumberValue();
    } else {
      zfar = 1000.0f;
    }

    // defaults to true
    if (args[3]->IsNumber()) {
      rightHanded = (ovrBool) args[3]->Int32Value();
    } else {
      rightHanded = (ovrBool) 1;
    }

    ovrMatrix4f proj = ovrMatrix4f_Projection(fov, znear, zfar, rightHanded);

    // stores in row-major order
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        res->Set(4 * i + j, JS_FLOAT(proj.M[i][j]));
      }
    }

    SCOPE_OUT(res);
  }

  JS_METHOD(Device, getTrackingData) {
    SCOPE_IN;

    Device * obj = JS_OBJECT(Device, args.This());
    
    ovrTrackingState trackingInfo;
    std::string data = "";

    if (obj->hmd != NULL) {
      trackingInfo = ovrHmd_GetTrackingState(obj->hmd, 0.0f);
      data += ".HeadPose\n";
      data += "  .ThePose\n";
      data += "    .Orientation\n";
      data += "      [ " + toString<float>(trackingInfo.HeadPose.ThePose.Orientation.x) + "\n";
      data += "        " + toString<float>(trackingInfo.HeadPose.ThePose.Orientation.y) + "\n";
      data += "        " + toString<float>(trackingInfo.HeadPose.ThePose.Orientation.z) + "\n";
      data += "        " + toString<float>(trackingInfo.HeadPose.ThePose.Orientation.w) + " ]\n";
      data += "    .Position\n";
      data += "      [ " + toString<float>(trackingInfo.HeadPose.ThePose.Position.x) + "\n";
      data += "        " + toString<float>(trackingInfo.HeadPose.ThePose.Position.y) + "\n";
      data += "        " + toString<float>(trackingInfo.HeadPose.ThePose.Position.z) + " ]\n";
      data += "  .AngularVelocity\n";
      data += "    [ " + toString<float>(trackingInfo.HeadPose.AngularVelocity.x) + "\n";
      data += "      " + toString<float>(trackingInfo.HeadPose.AngularVelocity.y) + "\n";
      data += "      " + toString<float>(trackingInfo.HeadPose.AngularVelocity.z) + " ]\n";
      data += "  .LinearVelocity\n";
      data += "    [ " + toString<float>(trackingInfo.HeadPose.LinearVelocity.x) + "\n";
      data += "      " + toString<float>(trackingInfo.HeadPose.LinearVelocity.y) + "\n";
      data += "      " + toString<float>(trackingInfo.HeadPose.LinearVelocity.z) + " ]\n";
      data += "  .AngularAcceleration\n";
      data += "    [ " + toString<float>(trackingInfo.HeadPose.AngularAcceleration.x) + "\n";
      data += "      " + toString<float>(trackingInfo.HeadPose.AngularAcceleration.y) + "\n";
      data += "      " + toString<float>(trackingInfo.HeadPose.AngularAcceleration.z) + " ]\n";
      data += "  .LinearAcceleration\n";
      data += "    [ " + toString<float>(trackingInfo.HeadPose.LinearAcceleration.x) + "\n";
      data += "      " + toString<float>(trackingInfo.HeadPose.LinearAcceleration.y) + "\n";
      data += "      " + toString<float>(trackingInfo.HeadPose.LinearAcceleration.z) + " ]\n";
      data += "  .TimeInSeconds\n";
      data += "    " + toString<double>(trackingInfo.HeadPose.TimeInSeconds) + "\n\n";
      data += ".CameraPose\n";
      data += "  .Orientation\n";
      data += "    [ " + toString<float>(trackingInfo.CameraPose.Orientation.x) + "\n";
      data += "      " + toString<float>(trackingInfo.CameraPose.Orientation.y) + "\n";
      data += "      " + toString<float>(trackingInfo.CameraPose.Orientation.z) + "\n";
      data += "      " + toString<float>(trackingInfo.CameraPose.Orientation.w) + " ]\n";
      data += "  .Position\n";
      data += "    [ " + toString<float>(trackingInfo.CameraPose.Position.x) + "\n";
      data += "      " + toString<float>(trackingInfo.CameraPose.Position.y) + "\n";
      data += "      " + toString<float>(trackingInfo.CameraPose.Position.z) + " ]\n";
      data += ".LeveledCameraPose\n";
      data += "  .Orientation\n";
      data += "    [ " + toString<float>(trackingInfo.LeveledCameraPose.Orientation.x) + "\n";
      data += "      " + toString<float>(trackingInfo.LeveledCameraPose.Orientation.y) + "\n";
      data += "      " + toString<float>(trackingInfo.LeveledCameraPose.Orientation.z) + "\n";
      data += "      " + toString<float>(trackingInfo.LeveledCameraPose.Orientation.w) + " ]\n";
      data += "  .Position\n";
      data += "    [ " + toString<float>(trackingInfo.LeveledCameraPose.Position.x) + "\n";
      data += "      " + toString<float>(trackingInfo.LeveledCameraPose.Position.y) + "\n";
      data += "      " + toString<float>(trackingInfo.LeveledCameraPose.Position.z) + " ]\n";
    }

    v8::Local<v8::String> res = v8::String::New(data.c_str(), data.length());
    SCOPE_OUT(res);
  }

  void Device::Init(v8::Handle<v8::Object> exports) {
    // Prepare constructor template
    v8::Local<v8::FunctionTemplate> tpl = v8::FunctionTemplate::New(New);
    tpl->SetClassName(v8::String::NewSymbol("Device"));    
    tpl->InstanceTemplate()->SetInternalFieldCount(4);

    // Prototype
    JS_PROTOTYPE(tpl, destroyResources);
    JS_PROTOTYPE(tpl, discoverSensor);
    JS_PROTOTYPE(tpl, getDeviceInfo);
    JS_PROTOTYPE(tpl, getPositionDeltas);
    JS_PROTOTYPE(tpl, getOrientationQuat);
    JS_PROTOTYPE(tpl, getTrackingData);
    JS_PROTOTYPE(tpl, getOvrMatrix4f_Projection);

    // Declare contructor
    constructor = v8::Persistent<v8::Function>::New(tpl->GetFunction());
    exports->Set(v8::String::NewSymbol("Device"), constructor);
  }

  JS_METHOD(Device, New) {
    SCOPE_IN;

    Device* device = new Device();
    device->Wrap(args.This());

    SCOPE_OUT(args.This());
  }

  JS_METHOD(Device, NewInstance) {
    SCOPE_IN;

    const unsigned argc = 1;
    v8::Handle<v8::Value> argv[argc] = { args[0] };
    v8::Local<v8::Object> instance = constructor->NewInstance(argc, argv);

    SCOPE_OUT(instance);
  }
}

