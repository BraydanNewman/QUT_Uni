import math


def distance(p1, p2):
    return math.dist(p1, p2)


def find_closest(start_point, remaining_points):
    closest_point = ()
    shortest_distance = 100
    for point in remaining_points:
        length = distance(start_point, point)
        if length < shortest_distance:
            shortest_distance = length
            closest_point = point
    return closest_point


def path_distance(path):
    total_distance = 0
    current_point = path[0]
    path.pop(0)
    for point in path:
        total_distance += distance(current_point, point)
        current_point = point
    return total_distance


def best_path(points):
    current_point = points[0]
    points_path = [points[0]]
    points.pop(0)
    while len(points) > 0:
        current_point = find_closest(current_point, points)
        points_path.append(current_point)
        points.remove(current_point)
    return points_path


if __name__ == "__main__":
    import matplotlib.pyplot

    original_points = [
        (0.3, 8.3),
        (4.4, 8.8),
        (6.8, 7.4),
        (4.1, 0.3),
        (4.5, 0.0),
        (7.6, 1.1),
        (5.0, 8.2),
        (7.7, 1.8),
        (3.4, 6.9),
        (4.8, 3.2),
        (0.7, 7.9),
    ]
    original_start_point = (2.8, 9.8)
    original_points.insert(0, original_start_point)
    shortest_path = best_path(original_points)
    print(shortest_path)
    print(path_distance(shortest_path))

    shortest_path.insert(0, original_start_point)
    x = [x[0] for x in shortest_path]
    y = [x[1] for x in shortest_path]
    matplotlib.pyplot.scatter(x, y, color="black")
    matplotlib.pyplot.plot(*zip(*shortest_path), color="black")
    matplotlib.pyplot.scatter(shortest_path[-1][0], shortest_path[-1][1], color="red")
    matplotlib.pyplot.scatter(
        original_start_point[0], original_start_point[1], color="green"
    )
    matplotlib.pyplot.show()
