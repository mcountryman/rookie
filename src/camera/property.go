package camera

import (
  "fmt"
  "github.com/spf13/viper"
  "gocv.io/x/gocv"
)

var nameToProperty = map[string]gocv.VideoCaptureProperties {
  "posMsec": gocv.VideoCapturePosMsec,
  "posFrames": gocv.VideoCapturePosFrames,
  "posAVIRatio": gocv.VideoCapturePosAVIRatio,
  "frameWidth": gocv.VideoCaptureFrameWidth,
  "frameHeight": gocv.VideoCaptureFrameHeight,
  "FPS": gocv.VideoCaptureFPS,
  "FOURCC": gocv.VideoCaptureFOURCC,
  "frameCount": gocv.VideoCaptureFrameCount,
  "format": gocv.VideoCaptureFormat,
  "mode": gocv.VideoCaptureMode,
  "brightness": gocv.VideoCaptureBrightness,
  "contrast": gocv.VideoCaptureContrast,
  "saturation": gocv.VideoCaptureSaturation,
  "hue": gocv.VideoCaptureHue,
  "gain": gocv.VideoCaptureGain,
  "exposure": gocv.VideoCaptureExposure,
  "convertRGB": gocv.VideoCaptureConvertRGB,
  "whiteBalanceBlueU": gocv.VideoCaptureWhiteBalanceBlueU,
  "rectification": gocv.VideoCaptureRectification,
  "monochrome": gocv.VideoCaptureMonochrome,
  "sharpness": gocv.VideoCaptureSharpness,
  "autoExposure": gocv.VideoCaptureAutoExposure,
  "gamma": gocv.VideoCaptureGamma,
  "temperature": gocv.VideoCaptureTemperature,
  "trigger": gocv.VideoCaptureTrigger,
  "triggerDelay": gocv.VideoCaptureTriggerDelay,
  "whiteBalanceRedV": gocv.VideoCaptureWhiteBalanceRedV,
  "zoom": gocv.VideoCaptureZoom,
  "focus": gocv.VideoCaptureFocus,
  "GUID": gocv.VideoCaptureGUID,
  "ISOSpeed": gocv.VideoCaptureISOSpeed,
  "backlight": gocv.VideoCaptureBacklight,
  "pan": gocv.VideoCapturePan,
  "tilt": gocv.VideoCaptureTilt,
  "roll": gocv.VideoCaptureRoll,
  "iris": gocv.VideoCaptureIris,
  "settings": gocv.VideoCaptureSettings,
  "bufferSize": gocv.VideoCaptureBufferSize,
  "autoFocus": gocv.VideoCaptureAutoFocus,
}
var propertyToName = getPropertyToName()

func getPropertyToName() map[gocv.VideoCaptureProperties] string {
  result := map[gocv.VideoCaptureProperties] string {}

  for k, v := range nameToProperty {
    result[v] = k
  }

  return result
}

func GetProperty(prop gocv.VideoCaptureProperties) float64 {
  var value = 0.0

  captureMtx.RLock()

  if capture != nil {
    value = capture.Get(prop)
  }

  captureMtx.RUnlock()

  return value
}

func SetProperty(prop gocv.VideoCaptureProperties, value float64) {
  captureMtx.Lock()

  if capture != nil {
    capture.Set(prop, value)
  }

  captureMtx.Unlock()

  viper.Set(fmt.Sprintf("camera.%s", propertyToName[prop]), value)
}

func GetProperties() map[string]float64 {
  result := make(map[string]float64)

  for key, prop := range nameToProperty {
    result[key] = GetProperty(prop)
  }

  return result
}

func SetProperties(props map[string]float64) {
  for key, value := range props {
    prop, ok := nameToProperty[key]

    if ok {
      SetProperty(prop, value)
    }
  }
}

func applyProperties(capture *gocv.VideoCapture) {
  for _, key := range viper.AllKeys() {
    name := fmt.Sprintf("camera.%s", key)
    prop, ok := nameToProperty[name]

    if ok {
      capture.Set(prop, viper.GetFloat64(key))
    }
  }
}