use std::io::Result;
use actix_web::{App, HttpServer, web, HttpRequest, Responder, HttpResponse};

async fn index(_: HttpRequest) -> impl Responder {
  HttpResponse::Ok()
    .content_type("application/json")
    .header("Server", "rookie")
    .body("{ \"hey\": \"world\" }")
}

#[actix_rt::main]
async fn main() -> Result<()> {
  HttpServer::new(|| {
    App::new()
      .route("/", web::get().to(index))
      .service(fs::Files::new("/", "."))
  })
    .bind("0.0.0.0:8080")?
    .run()
    .await
}
