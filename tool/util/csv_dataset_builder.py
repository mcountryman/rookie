from os import listdir, mkdir
from os.path import join, isfile
from csv import reader, writer
from cv2 import imwrite

class CsvDatasetBuilder:
    directory: str
    classes: dict
    classes_path: str
    annotations: list
    annotations_path: str

    def __init__(self, directory):
        self.directory = directory
        self.classes = {}
        self.classes_path = join(directory, "_classes.csv")
        self.annotations = []
        self.annotations_path = join(directory, "_annotations.csv")

        self._try_load_classes()
        self._try_load_annotations()

    def save_image(self, name, image, rect):
        if name not in self.classes:
            self.classes[name] = len(self.classes)
            self._save_classes()
            print("Wrote to `_classes.csv`")

        image_number = len([
            f for f in listdir(self.directory)
            if isfile(join(self.directory, f)) and f.startswith(name)
        ])

        image_name = f"{name}_{image_number:03}.jpg"
        image_path = join(self.directory, image_name)
        imwrite(image_path, image)
        print(f"Wrote to `{image_name}`")

        self.annotations.append({
            "path": image_name,
            "x1": rect[0],
            "y1": rect[1],
            "x2": rect[2],
            "y2": rect[3],
            "class_name": name
        })

        self._save_annotations()
        print("Wrote to `_annotations.csv`")

    def _save_classes(self):
        with open(self.classes_path, "w", newline='') as f:
            write = writer(f)

            for name in self.classes:
                write.writerow([name, self.classes[name]])

    def _save_annotations(self):
        with open(self.annotations_path, "w", newline='') as f:
            write = writer(f)

            for annotation in self.annotations:
                write.writerow([
                    annotation["path"],
                    annotation["x1"],
                    annotation["y1"],
                    annotation["x2"],
                    annotation["y2"],
                    annotation["class_name"],
                ])

    def _try_load_classes(self):
        try:
            classes = {}

            with open(self.classes_path, newline='') as f:
                read = reader(f)

                for row in read:
                    classes[row[0]] = int(row[1])

            self.classes = classes
            return True
        except:
            return False

    def _try_load_annotations(self):
        try:
            annotations = []

            with open(self.annotations_path, newline='') as f:
                read = reader(f)

                for row in read:
                    annotations.append({
                        "path": row[0],
                        "x1": int(row[1]),
                        "y1": int(row[2]),
                        "x2": int(row[3]),
                        "y2": int(row[4]),
                        "class_name": row[5]
                    })

            self.annotations = annotations
            return True
        except Exception as ex:
            return False
