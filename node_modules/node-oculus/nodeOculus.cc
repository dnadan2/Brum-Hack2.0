#ifndef BUILDING_NODE_EXTENSION
	#define BUILDING_NODE_EXTENSION
#endif

#include "Device.h"

void init(v8::Handle<v8::Object> exports) {
  nodeOculus::Device::Init(exports);
 
  NODE_SET_METHOD(exports, "createOculus", nodeOculus::Device::NewInstance);
}

NODE_MODULE(nodeOculus, init)
