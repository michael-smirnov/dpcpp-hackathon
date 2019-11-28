#include <iostream>

#include <vector>
#include <tuple>

#include <cmath>
#include <algorithm>
#include <limits>

struct Point {
    float x;
    float y;
    
    Point(float x, float y)
        : x(x), y(y)
    { }
    
    static float distance(const Point& p1, const Point& p2) {
        float result = 0.f;
        result += (p1.x - p2.x)*(p1.x - p2.x);
        result += (p1.y - p2.y)*(p1.y - p2.y);
        
        return std::sqrt(result);
    }
};

std::vector<float> find_distances(const std::vector<Point>& points);
void find_shortest_path(const std::vector<float>& distances);

int main() {
    std::vector<Point> points;
    {
        int number_of_points = 0;
        std::cin >> number_of_points;
    
        for (size_t i = 0; i < number_of_points; i++) {
            float x, y;
            std::cin >> x >> y;
            points.emplace_back(x, y);
        }
    }
    
    std::vector<float> distances = find_distances(points);
    find_shortest_path(distances);
    
    return 0;
}

std::vector<float> find_distances(const std::vector<Point>& points) {
    const size_t n = points.size();
    
    std::vector<float> distances(n*n, 0.f);
    for (size_t row = 0; row < n; row++) {
        for (size_t col = 0; col < n; col++) {
            distances[row*n + col] = Point::distance(points[row], points[col]);
        }
    }
    
    return distances;
}

void find_shortest_path(const std::vector<float>& distances) {
    const size_t n = std::sqrt(distances.size());
    const size_t start_point = 0;
    const size_t end_point = 1;
    
    std::vector<size_t> point_indices;
    for (size_t i = 2; i < n; i++) {
            point_indices.push_back(i);
    }
    
    auto min_path = std::numeric_limits<float>::max();
    do {
        std::vector<size_t> cur_path;
        
        float cur_path_weight = 0.f;
        size_t cur_point = start_point;
        
        for (size_t i = 0; i < point_indices.size(); i++) {
            cur_path_weight += distances[cur_point*n + point_indices[i]];
            cur_point = point_indices[i];
            cur_path.push_back(cur_point);
        }
        cur_path_weight += distances[cur_point*n + end_point];
        
        if (min_path > cur_path_weight) {
            min_path = cur_path_weight;
            for (size_t idx : cur_path) {
                std::cout << idx << ",";
            }
            std::cout << std::endl;
        }
    } while (std::next_permutation(point_indices.begin(), point_indices.end()));
}