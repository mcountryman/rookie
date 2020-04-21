package main

import (
  "github.com/gin-gonic/gin"
  "github.com/gorilla/websocket"
  "gocv.io/x/gocv"
)

func handleCamera(ctx *gin.Context) {
  conn, err := upgrader.Upgrade(ctx.Writer, ctx.Request, nil)

  if err != nil {
    _ = ctx.Error(err)
    return
  }

  for {
    frame := camera.GetFrame()
    buf, err := gocv.IMEncode(".png", frame)

    if err != nil {
      continue
    }

    if err := conn.WriteMessage(websocket.BinaryMessage, buf); err != nil {
      break
    }
  }
}
