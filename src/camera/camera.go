package camera

import (
  "gocv.io/x/gocv"
)

type Camera struct {
  device *gocv.VideoCapture
}

func MakeCamera(deviceId int) (Camera, error) {
  device, err := gocv.VideoCaptureDevice(deviceId)

  if err != nil {
    return Camera{}, err
  }

  settings := MakeSettings(device)
  settings.Apply(device)

  return Camera{
    device,
  }, nil
}

func (c *Camera) GetId() string {
  return getDeviceId(c.device)
}

func (c *Camera) GetSettings() Settings {
  return MakeSettings(c.device)
}

func (c *Camera) ApplySettings(settings Settings) {
  settings.Apply(c.device)
}
