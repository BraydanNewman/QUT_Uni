import numpy as np
import csv


def fertiliser(csv_filename: str, n: float, p: float, k: float):
    with open(csv_filename, newline="") as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=",", quotechar="|")
        next(csv_reader)
        csv_data = [i for i in csv_reader]
    fertilizer_data = np.rot90(np.array([i[1:] for i in csv_data], float), axes=(1, 0))
    names = [i[0] for i in csv_data]
    names.reverse()
    try:
        results = np.linalg.solve(fertilizer_data, np.array([n, p, k], float))
    except np.linalg.LinAlgError:
        return None
    return {names[i]: round(v * 100, 2) for i, v in enumerate(results)} if all(results >= 0) else None
