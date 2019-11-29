#include <iostream> 
#include <fstream> 
#include <vector> 
#include <algorithm> 
#include <tuple> 
#include <limits> 
#include<cmath> 
struct Point { 
float x; 
float y; 

Point(float x, float y) 
: x(x), y(y) 
{ } 

static float distance(const Point& p1, const Point& p2) { 
float result = 0.f; 
result += (p1.x - p2.x) * (p1.x - p2.x); 
result += (p1.y - p2.y) * (p1.y - p2.y); 

return std::sqrt(result); 
} 
}; 

//-------------------------------------------------------------------------------------------------------------— 
std::vector<Point> inputtxt(void) 
{ 
std::vector<Point> points; 
{ 
size_t qty; 
std::cin>>qty; 

for (int i=0; i<qty; i++)
{
	float x, y; 
	std::cin>>x>>y;
}
points.emplace_back(x, y); 

} 
return points; 
} 

//-----------------------------------------------------------------------------------------------— 
float findShortestPath(std::vector<Point> points, std::vector<size_t>& output) { 
std::vector<bool> exist(points.size(), true); 
float sum = 0; 
size_t num = 1; 
exist[1] = false; 
for (size_t i = 1; i < points.size()+10; i++) { 
float min = 10000; 
size_t k = -1; 
for (size_t j = 1; j < points.size(); j++) { 
if (!exist[j] || num == j) continue; 
float d = Point::distance(points[num], points[j]); 
if (d < min) { 
min = d; 
k = j; 
num = k; 
} 
} 
if (k != -1) { 
sum += min; 
exist[k] = false; 
output.push_back(num); 
} 
} 
sum += Point::distance(points[0], points[num]); 
return sum; 
} 

//-----------------------------------------------------------------------------------------------------------------------— 
int main(void) 
{ 
std::vector<Point> points = inputtxt(); 
std::vector<size_t> output; 
float shortestPath = findShortestPath(points, output); 

for (int i = 0; i <= output.size(); i++) { 
std::cout<<output[i]<<","; 
} 
std::cout<<"\r";
}