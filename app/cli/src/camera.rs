use std::error::Error;
use std::result::Result;
use std::sync::RwLock;

use opencv::core::{Mat, ToOutputArray};
use opencv::videoio::{CAP_ANY, CAP_PROP_FPS, VideoCapture, VideoCaptureProperties, VideoCaptureTrait};
use serde::{Serialize, Serializer};
use serde::ser::SerializeStruct;

type DynErr = Box<dyn Error>;

struct Camera {
  capture: RwLock<Option<VideoCapture>>,
  capture_id: Option<i32>,
}

impl Camera {
  fn new() -> Self {
    Self {
      capture: RwLock::new(None),
      capture_id: None,
    }
  }

  fn read(&self, frame: &mut dyn ToOutputArray) -> Result<bool, DynErr> {
    let capture = self.capture.read()?;
    let capture = (*capture)?;

    capture.read(frame)
  }

  fn get_device_id(&self) -> Option<i32> {
    self.capture_id
  }

  fn set_device_id(&mut self, device_id: i32) -> Result<(), DynErr> {
    let capture = VideoCapture::new(device_id, CAP_ANY)?;
    self.capture_id = Some(device_id);
    let mut lock = self.capture.write()?;
    *lock = Some(capture);

    Ok(())
  }

  fn get_device_property(&self, prop: i32) -> Result<f64, DynErr> {
    let capture = self.capture.read()?;
    let capture = (*capture)?;

    capture.get(prop)
  }

  fn set_device_property(&mut self, prop: i32, value: f64) -> Result<bool, DynErr> {
    let capture = self.capture.write()?;
    let capture = (*capture)?;

    capture.set(prop, value)
  }
}

impl Serialize for Camera {
  fn serialize<S>(&self, serializer: S) -> Result<S::Ok, S::Error> where S: Serializer {
    let mut state = serializer.serialize_struct("Camera", 3)?;

    state.serialize_field("id", &self.get_device_id());
    state.serialize_field("captureFPS", &self.get_device_property(CAP_PROP_FPS));
    state.end()
  }
}
