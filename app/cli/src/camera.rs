use std::error::Error;
use std::result::Result;
use std::sync::RwLock;

use opencv::core::{Mat, ToOutputArray};
use opencv::videoio::{CAP_ANY, CAP_PROP_FPS, VideoCapture, VideoCaptureProperties, VideoCaptureTrait};

type DynErr = Box<dyn Error>;

pub struct Camera {
  capture: RwLock<Option<VideoCapture>>,
  capture_id: Option<i32>,
}

impl Camera {
  pub fn new() -> Self {
    Self {
      capture: RwLock::new(None),
      capture_id: None,
    }
  }

  pub fn read(&self, frame: &mut dyn ToOutputArray) -> Result<bool, DynErr> {
    let capture = self.capture.read()?;
    let capture = (*capture)?;

    capture.read(frame)
  }

  pub fn get_device_id(&self) -> Option<i32> {
    self.capture_id
  }

  pub fn set_device_id(&mut self, device_id: i32) -> Result<(), DynErr> {
    let capture = VideoCapture::new(device_id, CAP_ANY)?;
    self.capture_id = Some(device_id);
    let mut lock = self.capture.write()?;
    *lock = Some(capture);

    Ok(())
  }

  pub fn get_device_property(&self, prop: VideoCaptureProperties) -> Result<f64, DynErr> {
    let capture = self.capture.read()?;
    let capture = (*capture)?;

    capture.get(prop as i32)
  }

  pub fn set_device_property(&mut self, prop: VideoCaptureProperties, value: f64) -> Result<bool, DynErr> {
    let capture = self.capture.write()?;
    let capture = (*capture)?;

    capture.set(prop as i32, value)
  }
}
