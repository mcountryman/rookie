package main

import (
  "github.com/gin-contrib/static"
  "github.com/gin-gonic/gin"
  "github.com/spf13/viper"
  "rookie/camera"
)

func main() {
  viper.SetConfigName("rookie")
  viper.AddConfigPath(".")
  viper.SetConfigType("json")

  app := gin.Default()

  app.Use(
    static.Serve(
      "/",
      static.LocalFile("web/dist", false),
    ),
  )

  camera.SetupRoutes(app)

  app.Use(handleIndex)

  if err := app.Run(); err != nil {
    panic(err)
  }

  camera.Close()
}

func handleIndex(ctx *gin.Context) {
  ctx.File("web/dist/index.html")
}