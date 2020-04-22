package camera

import (
  "fmt"
  "gocv.io/x/gocv"
  "sync"
)

var id = -1
var frame = gocv.NewMat()
var frameMtx = sync.RWMutex{}
var capture *gocv.VideoCapture
var captureMtx = sync.RWMutex{}

func GetDeviceId() int {
  return id
}

func SetDeviceId(deviceId int) error {
  tmp, err := gocv.VideoCaptureDevice(id)

  if err != nil {
    return err
  }

  applyProperties(tmp)
  captureMtx.Lock()
  capture = tmp
  captureMtx.Unlock()
  id = deviceId

  return nil
}

func GetFrame() (gocv.Mat, error) {
  if capture != nil {
    frameMtx.Lock()
    ok := capture.Read(&frame)
    frameMtx.Unlock()

    if !ok {
      return frame, fmt.Errorf("failed to read frame")
    }

    return frame, nil
  }

  return frame, fmt.Errorf("capture device not open")
}

func Close() {
  if capture != nil {
    capture.Close()
  }
}
