{
  "targets": [

    {
      "target_name": "nodeOculus",

      "include_dirs": [
        "src/ovr",
        "src/ovr/LibOVR/Src",
        "src/ovr/LibOVR/Src/Kernel",
        "src/ovr/LibOVR/Include"
      ],
	  
      "sources" : [
        

        "src/ovr/LibOVR/Src/Kernel/OVR_Alg.cpp",
        "src/ovr/LibOVR/Src/Kernel/OVR_Allocator.cpp",
        "src/ovr/LibOVR/Src/Kernel/OVR_Log.cpp",
        "src/ovr/LibOVR/Src/Kernel/OVR_RefCount.cpp",
        "src/ovr/LibOVR/Src/Kernel/OVR_System.cpp",
        "src/ovr/LibOVR/Src/Kernel/OVR_ThreadsPthread.cpp",
        "src/ovr/LibOVR/Src/Kernel/OVR_Timer.cpp",
        "src/ovr/LibOVR/Src/Service/Service_NetClient.cpp",
        "src/ovr/LibOVR/Src/OVR_CAPI.cpp",

        "src/ovr/3rdParty/TinyXml/tinyxml2.cpp",
        "src/ovr/LibOVR/Src/CAPI/GL/CAPI_GL_DistortionRenderer.cpp",
        "src/ovr/LibOVR/Src/CAPI/GL/CAPI_GL_HSWDisplay.cpp",
        "src/ovr/LibOVR/Src/CAPI/GL/CAPI_GL_Util.cpp",
        "src/ovr/LibOVR/Src/CAPI/CAPI_DistortionRenderer.cpp",
        "src/ovr/LibOVR/Src/CAPI/CAPI_FrameTimeManager.cpp",
        "src/ovr/LibOVR/Src/CAPI/CAPI_HMDRenderState.cpp",
        "src/ovr/LibOVR/Src/CAPI/CAPI_HMDState.cpp",
        "src/ovr/LibOVR/Src/CAPI/CAPI_HSWDisplay.cpp",
        "src/ovr/LibOVR/Src/Displays/OVR_Display.cpp",
        "src/ovr/LibOVR/Src/Kernel/OVR_Atomic.cpp",
        "src/ovr/LibOVR/Src/Kernel/OVR_CRC32.cpp",
        "src/ovr/LibOVR/Src/Kernel/OVR_File.cpp",
        "src/ovr/LibOVR/Src/Kernel/OVR_FileFILE.cpp",
        "src/ovr/LibOVR/Src/Kernel/OVR_Lockless.cpp",
        "src/ovr/LibOVR/Src/Kernel/OVR_Math.cpp",
        "src/ovr/LibOVR/Src/Service/Service_NetSessionCommon.cpp",
        
        "src/ovr/LibOVR/Src/Kernel/OVR_SharedMemory.cpp",
        "src/ovr/LibOVR/Src/Kernel/OVR_Std.cpp",
        "src/ovr/LibOVR/Src/Kernel/OVR_String.cpp",
        "src/ovr/LibOVR/Src/Kernel/OVR_String_FormatUtil.cpp",
        "src/ovr/LibOVR/Src/Kernel/OVR_String_PathUtil.cpp",
        "src/ovr/LibOVR/Src/Kernel/OVR_SysFile.cpp",
        "src/ovr/LibOVR/Src/Kernel/OVR_ThreadCommandQueue.cpp",
        "src/ovr/LibOVR/Src/Kernel/OVR_UTF8Util.cpp",
        "src/ovr/LibOVR/Src/Tracking/Tracking_SensorStateReader.cpp",
        "src/ovr/LibOVR/Src/Util/Util_ImageWindow.cpp",
        "src/ovr/LibOVR/Src/Util/Util_Interface.cpp",
        "src/ovr/LibOVR/Src/Util/Util_LatencyTest2Reader.cpp",
        "src/ovr/LibOVR/Src/Util/Util_Render_Stereo.cpp",

        "src/ovr/LibOVR/Src/OVR_JSON.cpp",
        "src/ovr/LibOVR/Src/OVR_Profile.cpp",
        "src/ovr/LibOVR/Src/OVR_SerialFormat.cpp",
        "src/ovr/LibOVR/Src/OVR_Stereo.cpp",

        "src/ovr/LibOVR/Src/Net/OVR_BitStream.cpp",
        "src/ovr/LibOVR/Src/Net/OVR_NetworkPlugin.cpp",
        "src/ovr/LibOVR/Src/Net/OVR_PacketizedTCPSocket.cpp",
        "src/ovr/LibOVR/Src/Net/OVR_RPC1.cpp",
        "src/ovr/LibOVR/Src/Net/OVR_Session.cpp",
        "src/ovr/LibOVR/Src/Net/OVR_Socket.cpp",
        "src/ovr/LibOVR/Src/Net/OVR_Unix_Socket.cpp",




        "nodeOculus.cc",
        "Device.cc"
      ],

      "conditions" : [
        ['OS=="linux"', {
            "sources": [
            ]
        }],
        ['OS=="mac"', {
            "sources": [
              "src/ovr/LibOVR/Src/Displays/OVR_OSX_Display.cpp",
              "src/ovr/LibOVR/Src/Displays/OVR_OSX_Display.h",
              "src/ovr/LibOVR/Src/Displays/OVR_OSX_FocusObserver.h",
              "src/ovr/LibOVR/Src/Displays/OVR_OSX_FocusReader.h"
            ],
            "link_settings": {
              "libraries": [
                "ApplicationServices.framework",
                "CoreGraphics.framework",
                "IOKit.framework"
              ],
            }
        }],
        ['OS=="win"', {
          "sources": [
          ],
          "link_settings": {
            "libraries": [
            ]
          }
        }],
      ]
    }
  ]
}
