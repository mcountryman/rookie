import cv2
import math
import numpy as np
from os.path import join, dirname, realpath
from util.csv_dataset_builder import CsvDatasetBuilder
from itertools import chain

folder = realpath(join(dirname(realpath(__file__)), "../data/img"))
builder = CsvDatasetBuilder(folder)


def get_sliced_mat(annotation, img=None):
    if img is None:
        path = join(folder, annotation["path"])
        img = cv2.imread(path)

    x = annotation["x1"]
    y = annotation["y1"]
    w = annotation["x2"]
    h = annotation["y2"]

    return img[y: y + h, x: x + w]


def ensure_size(full, sliced, x, y):
    width = max(full.shape[1], x + sliced.shape[1])
    height = max(full.shape[0], y + sliced.shape[0])

    if width > full.shape[1] or height > full.shape[0]:
        new = np.zeros((height, width, full.shape[2]), np.uint8)
        new[:full.shape[0], :full.shape[1], :full.shape[2]] = full
        full = new

    return full


def append_sliced_mat(full, sliced, x=0, y=0):
    full = ensure_size(full, sliced, x, y)
    full[y: y + sliced.shape[0], x: x + sliced.shape[1]] = sliced
    return full, x + sliced.shape[0], y


def main():
    annotations = {}

    for annotation in builder.annotations:
        class_name = annotation["class_name"]

        if class_name not in annotations:
            annotations[class_name] = []

        annotations[class_name].append(annotation)

    for class_name in annotations:
        currents = annotations[class_name]
        others_src = [
            annotations[other_name] for other_name in annotations
            if other_name != class_name
        ]

        for current in currents:
            full = np.zeros((0, 0, 3), np.uint8)
            sliced = get_sliced_mat(current)
            full, x, y = append_sliced_mat(full, sliced)

            others = list(chain.from_iterable(others_src))
            others_len = len(others)
            others_dimensions = math.ceil(math.sqrt(others_len))

            for i in range(0, others_dimensions):
                for j in range(0, others_dimensions):
                    if len(others) <= 0:
                        break

                    sliced = get_sliced_mat(others.pop(0))
                    full, x, y = append_sliced_mat(full, sliced, x, y)

                y = full.shape[0]
                x = 0

            builder.save_image(class_name, full, (0, 0, sliced.shape[0], sliced.shape[1]))

    return 0


if __name__ == "__main__":
    exit(main())
