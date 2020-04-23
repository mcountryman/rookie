use std::error::Error;
use std::iter::Map;
use std::sync::Mutex;

use actix_web::{App, HttpRequest, HttpResponse, HttpServer, Responder, web};
use actix_web::web::{resource, ServiceConfig};
use actix_web_actors::ws;
use opencv::videoio::VideoCaptureProperties;
use opencv::videoio::VideoCaptureProperties::CAP_PROP_FPS;

use crate::camera::Camera;

struct CameraState {
  camera: Mutex<Camera>,
}

#[derive(Serialize, Deserialize)]
enum CameraOption {
  Id(i32),
  Property(VideoCaptureProperties, float64),
}

pub fn setup(cfg: &mut ServiceConfig) {
  let state = web::Data::new(
    CameraState {
      camera: Mutex::new(Camera::new()),
    },
  );

  cfg.service(
    web::scope("/camera")
      .app_data(state.clone())
      .route("/", web::get().to(get_camera_settings))
      .route("/", web::patch().to(set_camera_settings))
      .route("/image", web::get().to(get_camera_image))
  );
}

async fn get_camera_settings(
  state: web::Data<CameraState>,
) -> Result<Vec<CameraOption>, Box<dyn Error>> {
  let camera = state.camera.lock()?;
  let camera = *camera;

  Ok(
    vec![
      CameraOption::Id(camera.get_device_id()?),
      CameraOption::Property(CAP_PROP_FPS, camera.get_device_property(CAP_PROP_FPS)),
    ]
  )
}

async fn set_camera_settings(
  state: web::Data<CameraState>,
  settings: web::Json<Vec<CameraOption>>,
) -> Result<(), Box<dyn Error>> {
  let mut camera = state.camera.lock()?;
  let mut camera = *camera;

  for setting in settings {
    match setting {
      CameraOption::Id(id) =>
        camera.set_device_id(id)?,
      CameraOption::Property(prop, value) =>
        camera.set_device_property(prop, value)?,
    }
  }

  Ok(())
}

async fn get_camera_image(
  req: HttpRequest
) -> HttpResponse {
  let body = futures::stream::empty();

  HttpResponse::Ok()
    .content_type("image/png")
    .streaming(body)
}
