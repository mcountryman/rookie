package main

import (
  "github.com/gin-contrib/static"
  "github.com/gin-gonic/gin"
  "github.com/gorilla/websocket"
  "github.com/spf13/viper"
)

var camera Camera
var upgrader websocket.Upgrader

func main() {
  defer camera.Close()

  doConfig()
  doCamera()
  doServer()
}

func doConfig() {
  viper.SetConfigName("rookie")
  viper.AddConfigPath(".")
  viper.SetConfigType("json")
}

func doCamera() {
  var err error
  camera, err = NewCamera(0)

  if err != nil {
    panic(err)
    return
  }

  camera.Run()
}

func doServer() {
  upgrader = websocket.Upgrader{
    ReadBufferSize:  1024,
    WriteBufferSize: 1024,
  }

  app := gin.Default()
  app.Use(
    static.Serve(
      "/",
      static.LocalFile("web/dist", false),
    ),
  )

  app.GET("/ws/camera", handleCamera)

  if err := app.Run(); err != nil {
    panic(err)
  }
}

func handleIndex(ctx *gin.Context) {
  // ctx.File("web/dist/index.html")
}
