// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from camera.djinni

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, GBCameraExposureMode)
{
    GBCameraExposureModeNone,
    /** ios Indicates that the exposure should be locked at its current value. */
    GBCameraExposureModeLocked,
    /** ios Indicates that the device should automatically adjust exposure once and then change the exposure mode to Locked. */
    GBCameraExposureModeAutoExpose,
    /** ios Indicates that the device should automatically adjust exposure when needed. */
    GBCameraExposureModeContinuousAutoExposure,
    /**ios Indicates that the device should only adjust exposure according to user provided ISO, exposureDuration values. */
    GBCameraExposureModeModeCustom,
};
