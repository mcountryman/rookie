import cv2
import csv
import numpy as np
import imutils
import argparse
from os.path import join, dirname, realpath
from skimage.metrics import structural_similarity
from util.csv_dataset_builder import CsvDatasetBuilder

camera = cv2.VideoCapture(0)
builder = CsvDatasetBuilder(join(dirname(realpath(__file__)), "../data/img"))

p = argparse.ArgumentParser()
p.add_argument("label")
args = p.parse_args()

try:
    _, img_base = camera.read()
    gray_base = cv2.cvtColor(img_base, cv2.COLOR_BGR2GRAY)

    while True:
        _, img_base = camera.read()
        gray_base = cv2.cvtColor(img_base, cv2.COLOR_BGR2GRAY)

        cv2.imshow("base", img_base)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            cv2.destroyWindow("base")
            break

    while True:
        _, img_changed = camera.read()
        img_render = img_changed.copy()
        gray_changed = cv2.cvtColor(img_changed, cv2.COLOR_BGR2GRAY)

        (score, diff) = structural_similarity(gray_base, gray_changed, full=True)
        diff = (diff * 255).astype("uint8")

        mask = np.zeros(img_base.shape, dtype='uint8')
        thresh = cv2.threshold(diff, 200, 255, cv2.THRESH_BINARY_INV | cv2.THRESH_OTSU)[1]
        contours = cv2.findContours(
            thresh.copy(),
            cv2.RETR_EXTERNAL,
            cv2.CHAIN_APPROX_SIMPLE
        )

        contours = contours[0] if len(contours) == 2 else contours[1]
        contour_sizes = [(cv2.contourArea(contour), contour) for contour in contours]

        if len(contour_sizes) > 0:
            c = max(contour_sizes, key=lambda x: x[0])[1]
            (x, y, w, h) = cv2.boundingRect(c)
            cv2.rectangle(img_render, (x, y), (x + w, y + h), (0, 0, 255), 1)
            cv2.drawContours(img_render, [c], 0, (0, 255, 0), -1)

        cv2.imshow("image", img_render)

        key = cv2.waitKey(1) & 0xFF

        if key == ord('s'):
            c = max(contour_sizes, key=lambda x: x[0])[1]
            (x, y, w, h) = cv2.boundingRect(c)
            img_changed = img_changed[y:y + h, x:x + w]
            builder.save_image(args.label, img_changed, (0, 0, w, h))
        if key == ord('q'):
            break

finally:
    camera.release()
    cv2.destroyAllWindows()
