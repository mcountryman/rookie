package board

import (
	"fmt"
	"gocv.io/x/gocv"
	"image"
)

func ResolveEdges(frame gocv.Mat) (gocv.Mat, error) {
	blur := gocv.Mat{}
	gray := gocv.Mat{}

	gocv.Blur(frame, &blur, image.Pt(3, 3))
	gocv.CvtColor(blur, &gray, gocv.ColorBGRToGray)

	return gocv.Mat{}, fmt.Errorf("not implemented")
}
