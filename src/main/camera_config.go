package main

import "gocv.io/x/gocv"

var CameraPropMap = map[string] gocv.VideoCaptureProperties {
  "capture.posMsec": gocv.VideoCapturePosMsec,
  "capture.posFrames": gocv.VideoCapturePosFrames,
  "capture.aviRatio": gocv.VideoCapturePosAVIRatio,
  "capture.frameWidth": gocv.VideoCaptureFrameWidth,
  "capture.frameHeight": gocv.VideoCaptureFrameHeight,
  "capture.fps": gocv.VideoCaptureFPS,
  "capture.fourcc": gocv.VideoCaptureFOURCC,
  "capture.frameCount": gocv.VideoCaptureFrameCount,
  "capture.format": gocv.VideoCaptureFormat,
  "capture.mode": gocv.VideoCaptureMode,
  "capture.brightness": gocv.VideoCaptureBrightness,
  "capture.contrast": gocv.VideoCaptureContrast,
  "capture.saturation": gocv.VideoCaptureSaturation,
  "capture.hue": gocv.VideoCaptureHue,
  "capture.gain": gocv.VideoCaptureGain,
  "capture.exposure": gocv.VideoCaptureExposure,
  "capture.convertRGB": gocv.VideoCaptureConvertRGB,
  "capture.whiteBalanceBlueU": gocv.VideoCaptureWhiteBalanceBlueU,
  "capture.rectification": gocv.VideoCaptureRectification,
  "capture.monochrome": gocv.VideoCaptureMonochrome,
  "capture.sharpness": gocv.VideoCaptureSharpness,
  "capture.autoExposure": gocv.VideoCaptureAutoExposure,
  "capture.gamma": gocv.VideoCaptureGamma,
  "capture.temperature": gocv.VideoCaptureTemperature,
  "capture.trigger": gocv.VideoCaptureTrigger,
  "capture.triggerDelay": gocv.VideoCaptureTriggerDelay,
  "capture.whiteBalanceRedV": gocv.VideoCaptureWhiteBalanceRedV,
  "capture.zoom": gocv.VideoCaptureZoom,
  "capture.focus": gocv.VideoCaptureFocus,
  "capture.captureGuid": gocv.VideoCaptureGUID,
  "capture.isoSpeed": gocv.VideoCaptureISOSpeed,
  "capture.backlight": gocv.VideoCaptureBacklight,
  "capture.pan": gocv.VideoCapturePan,
  "capture.tilt": gocv.VideoCaptureTilt,
  "capture.roll": gocv.VideoCaptureRoll,
  "capture.iris": gocv.VideoCaptureIris,
  "capture.bufferSize": gocv.VideoCaptureBufferSize,
  "capture.autoFocus": gocv.VideoCaptureAutoFocus,
}

var CameraConfigMap = _reverseMap(CameraPropMap)

func _reverseMap(in map[string] gocv.VideoCaptureProperties) map[gocv.VideoCaptureProperties] string {
  result := make(map[gocv.VideoCaptureProperties] string)

  for k, v := range in {
    result[v] = k
  }

  return result
}
