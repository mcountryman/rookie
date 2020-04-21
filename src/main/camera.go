package main

import (
  "gocv.io/x/gocv"
  "sync"
)

type Camera struct {
  done      bool
  frame     gocv.Mat
  frameMtx  sync.RWMutex
  camera    *gocv.VideoCapture
  cameraMtx sync.RWMutex
}

func NewCamera() Camera {
  return Camera{
    frame:     gocv.NewMat(),
    frameMtx:  sync.RWMutex{},
    camera:    nil,
    cameraMtx: sync.RWMutex{},
  }
}

func (c *Camera) Run() {
  go func() { c.handleLoop() }()
}

func (c *Camera) GetFrame() gocv.Mat {
  c.frameMtx.RLock()
  frame := c.frame.Clone()
  c.frameMtx.RUnlock()
  return frame
}

func (c *Camera) Open(id int) error {
  camera, err := gocv.VideoCaptureDevice(id)

  if err != nil {
    return err
  }

  c.cameraMtx.Lock()

  if c.camera != nil {
    c.camera.Close()
  }

  c.camera = camera
  c.cameraMtx.Unlock()

  return nil
}

func (c *Camera) GetDeviceProperty(prop gocv.VideoCaptureProperties) float64 {
  value := -1.0

  c.cameraMtx.RLock()

  if c.camera != nil {
    value = c.camera.Get(prop)
  }

  c.cameraMtx.RUnlock()

  return value
}

func (c *Camera) SetDeviceProperty(prop gocv.VideoCaptureProperties, value float64) {
  c.cameraMtx.Lock()

  if c.camera != nil {
    c.camera.Set(prop, value)
  }

  c.cameraMtx.Unlock()
}

func (c *Camera) Close() {
  c.done = true
  c.cameraMtx.Lock()
  c.camera.Close()
  c.camera = nil
  c.cameraMtx.Unlock()
}

func (c *Camera) handleLoop() {
  for !c.done {
    c.readFrame()
  }
}

func (c *Camera) readFrame() bool {
  ok := false

  c.frameMtx.Lock()
  c.cameraMtx.RLock()

  if c.camera != nil {
    ok = c.camera.Read(&c.frame)
  }

  c.cameraMtx.RUnlock()
  c.frameMtx.Unlock()

  return ok
}
