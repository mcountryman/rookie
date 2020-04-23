use std::env;
use std::io::Result;

use actix_files::{Files, NamedFile};
use actix_web::{App, HttpRequest, HttpResponse, HttpServer, Responder, web};
use actix_web::dev::Service;

mod camera;
mod camera_route;

#[actix_rt::main]
async fn main() -> Result<()> {
  HttpServer::new(|| {
    App::new()
      .configure(camera_route::setup)
      .service(
        Files::new("/", "web/dist")
          .index_file("index.html")
      )
      .wrap_fn(|req, srv| {
        srv
          .call(req)
          .map(|res| {
            res
          })
      })
  })
    .bind("0.0.0.0:8080")?
    .run()
    .await
}
