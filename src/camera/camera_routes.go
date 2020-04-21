package camera

import (
  "github.com/gin-gonic/gin"
  "net/http"
  "strconv"
)

func SetupRoutes(app *gin.Engine) {
  app.GET("/cameras/primary", handleGetPrimary)
  app.PATCH("/cameras/primary/:id", handleSetPrimary)

  app.GET("/cameras", handleGetCameras)
  app.GET("/cameras/:id", handleGetCamera)
  app.PUT("/cameras/:deviceId", handleAddCamera)
  app.DELETE("/cameras/:id", handleDeleteCamera)
}

func handleGetPrimary(ctx *gin.Context) {
  primary := GetService().GetPrimary()

  if primary == nil {
    ctx.JSON(http.StatusOK, primary)
    return
  }

  ctx.JSON(http.StatusOK, primary.GetSettings())
}

func handleSetPrimary(ctx *gin.Context) {
  ctx.JSON(http.StatusOK, GetService().SetPrimary(ctx.Param("id")))
}

func handleGetCamera(ctx *gin.Context) {}
func handleGetCameras(ctx *gin.Context) {}

func handleAddCamera(ctx *gin.Context) {
  deviceId, err := strconv.Atoi(ctx.Param("deviceId"))

  if err != nil {
    ctx.JSON(http.StatusBadRequest, err)
    return
  }

  camera, err := MakeCamera(deviceId)

  if err != nil {
    ctx.JSON(http.StatusInternalServerError, err)
    return
  }

  GetService().Add(camera)
}

func handleDeleteCamera(ctx *gin.Context) {
  GetService().Remove(ctx.Param("id"))
  ctx.JSON(http.StatusOK, true)
}
