package camera

import "sync"

var singleton = Service{}

type Service struct {
  camera  *Camera
  cameras map[string]Camera
  sync.RWMutex
}

func GetService() *Service {
  return &singleton
}

func (s *Service) Get(id string) (Camera, bool) {
  s.RLock()
  camera, ok := s.cameras[id]
  s.RUnlock()
  return camera, ok
}

func (s *Service) GetAll() map[string]Camera {
  result := make(map[string]Camera)

  for id, camera := range s.cameras {
    result[id] = camera
  }

  return result
}

func (s *Service) Add(camera Camera) {
  s.Lock()
  s.cameras[camera.GetId()] = camera
  s.Unlock()

  if len(s.cameras) == 1 {
    s.SetPrimary(camera.GetId())
  }
}

func (s *Service) Remove(id string) {
  s.Lock()
  delete(s.cameras, id)
  s.Unlock()
}

func (s *Service) GetPrimary() *Camera {
  s.RLock()
  camera := s.camera
  s.RUnlock()
  return camera
}

func (s *Service) SetPrimary(id string) bool {
  camera, ok := s.Get(id)

  if ok {
    s.Lock()
    s.camera = &camera
    s.Unlock()
  }

  return ok
}
