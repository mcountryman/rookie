package camera

import (
  "encoding/base64"
  "encoding/binary"
  "fmt"
  "github.com/spf13/viper"
  "gocv.io/x/gocv"
  "math"
)

type Settings struct {
  Id string `json:"id"`
  Fps float64 `json:"fps"`
}

func MakeSettings(device *gocv.VideoCapture) Settings {
  id := getDeviceId(device)

  viper.SetDefault(getKey(id, "fps"), 30.0)

  fps := viper.GetFloat64(getKey(id, "fps"))

  return Settings{
    id,
    fps,
  }
}

func (s *Settings) Apply(device *gocv.VideoCapture) {
  device.Set(gocv.VideoCaptureFPS, s.Fps)
}

func (s *Settings) Save() error {
  viper.Set(getKey(s.Id, "fps"), s.Fps)

  return viper.SafeWriteConfig()
}

func getKey(id string, key string) string {
  return fmt.Sprintf("cameras.%s.%s", id, key)
}

func getDeviceId(device *gocv.VideoCapture) string {
  idBuf := make([]byte, 8)
  idF64 := device.Get(gocv.VideoCaptureGUID)
  idU64 := math.Float64bits(idF64)
  binary.BigEndian.PutUint64(idBuf[:], idU64)

  return base64.StdEncoding.EncodeToString(idBuf)
}