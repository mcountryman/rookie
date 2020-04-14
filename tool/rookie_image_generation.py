import cv2
import numpy as np
from os.path import join, dirname, realpath
from skimage.metrics import structural_similarity
from util.csv_dataset_builder import CsvDatasetBuilder

camera = cv2.VideoCapture(0)
builder = CsvDatasetBuilder(join(dirname(realpath(__file__)), "../data/img"))


def prompt_base_img(capture):
    _, img_base = capture.read()

    while True:
        _, img_base = capture.read()

        cv2.imshow("base", img_base)

        key = cv2.waitKey(1) & 0xFF

        if key == ord('s'):
            cv2.destroyWindow("base")
            return True, img_base, ""
        if key == ord('q'):
            cv2.destroyWindow("base")
            return False, None, "Quitting..."


def prompt_image_delta(label, base, base_gray, capture):
    count = 0

    while True:
        if count == 10:
            cv2.destroyWindow("image")
            return True, "Done.."

        flag, contours, img_changed, img_render = get_image_delta(
            base,
            base_gray,
            capture
        )

        # Eh, we have nothing to show..
        if img_render is None:
            img_render = img_changed

        cv2.imshow("image", img_render)

        key = cv2.waitKey(1) & 0xFF

        # Save image
        if key == ord('s'):
            if flag:
                count += 1
                builder.save_image(label, img_changed, contours)
            else:
                print("\a")

        # Next category
        if key == ord('n'):
            cv2.destroyWindow("image")
            return True, None

        # Quit
        if key == ord('q'):
            cv2.destroyWindow("image")
            return False, "Quitting..."


def get_image_delta(base, base_gray, capture):
    flag, img_changed = capture.read()

    if not flag:
        return False, None, None

    img_render = img_changed.copy()
    gray_changed = cv2.cvtColor(img_changed, cv2.COLOR_BGR2GRAY)

    (score, diff) = structural_similarity(base_gray, gray_changed, full=True)
    diff = (diff * 255).astype("uint8")

    mask = np.zeros(base.shape, dtype='uint8')
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

        if w < 10 or h < 10:
            return False, (x, y, w, h), img_changed, img_render
        if w > 70 or h > 70:
            return False, (x, y, w, h), img_changed, img_render

        cv2.rectangle(img_render, (x, y), (x + w, y + h), (0, 0, 255), 1)
        cv2.drawContours(img_render, [c], 0, (0, 255, 0), -1)

        return True, (x, y, w, h), img_changed, img_render

    return False, None, None, None


def main():
    try:

        flag, base, message = prompt_base_img(camera)

        if not flag:
            print(message)
            return -1

        base_gray = cv2.cvtColor(base, cv2.COLOR_BGR2GRAY)

        while True:
            label = input("Image label: ")

            flag, message = prompt_image_delta(label, base, base_gray, camera)

            if flag:
                print(f"Capturing '{label}' complete..")
            else:
                print(message)
                return -1

    finally:
        camera.release()
        cv2.destroyAllWindows()


if __name__ == "__main__":
    exit(main())
