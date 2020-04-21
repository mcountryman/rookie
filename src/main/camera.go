package main

import (
  "gocv.io/x/gocv"
  "sync"
)

type Camera struct {
  done     bool
  frame    gocv.Mat
  frameMtx sync.RWMutex
  camera   *gocv.VideoCapture
}

func NewCamera(id int) (Camera, error) {
  camera, err := gocv.VideoCaptureDevice(id)

  return Camera{
    frame:    gocv.NewMat(),
    frameMtx: sync.RWMutex{},
    camera:   camera,
  }, err
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

func (c *Camera) Close() {
  c.done = true
  c.camera.Close()
}

func (c *Camera) handleLoop() {
  for !c.done {
    c.readFrame()
  }
}

func (c *Camera) readFrame() bool {
  c.frameMtx.Lock()
  ok := c.camera.Read(&c.frame)
  c.frameMtx.Unlock()
  return ok
}
