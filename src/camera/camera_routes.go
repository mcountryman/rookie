package camera

import (
  "github.com/gin-gonic/gin"
  "github.com/gorilla/websocket"
  "github.com/spf13/viper"
  "gocv.io/x/gocv"
  "net/http"
  "strconv"
)

var upgrader = websocket.Upgrader{
  ReadBufferSize: 1024,
  WriteBufferSize: 1024,
}

func SetupRoutes(app *gin.Engine) {
  app.GET("camera/ws", handleWs)

  app.GET("camera", func(ctx *gin.Context) { ctx.JSON(http.StatusOK, GetProperties()) })
  app.PATCH("camera", func(ctx *gin.Context) {
    props := make(map[string] float64)

    if err := ctx.Bind(&props); err != nil {
      ctx.JSON(http.StatusBadRequest, err)
      return
    }

    SetProperties(props)

    if err := viper.WriteConfig(); err != nil {
      ctx.JSON(http.StatusInternalServerError, err)
      return
    }

    ctx.JSON(http.StatusOK, true)
  })

  app.GET("camera/id", func(ctx *gin.Context) { ctx.JSON(http.StatusOK, GetDeviceId()) })
  app.PATCH("camera/id/:value", func(ctx *gin.Context) {
    if id, err := strconv.Atoi(ctx.Param("value")); err != nil {
      ctx.JSON(http.StatusBadRequest, err)
    } else {
      if err := SetDeviceId(id); err != nil {
        ctx.JSON(http.StatusInternalServerError, err)
      } else {
        ctx.JSON(http.StatusOK, true)
      }
    }
  })
}

func handleWs(ctx *gin.Context) {
  conn, err := upgrader.Upgrade(ctx.Writer, ctx.Request, nil)

  if err != nil {
    ctx.JSON(http.StatusInternalServerError, err)
    return
  }

  for {
    frame, err := GetFrame()

    if err != nil {
      break
    }

    buf, err := gocv.IMEncode(".png", frame)

    if err != nil {
      break
    }

    if err := conn.WriteMessage(websocket.BinaryMessage, buf); err != nil {
      break
    }
  }
}