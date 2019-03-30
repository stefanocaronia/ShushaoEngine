#include "curve.h"

namespace se {

using namespace std;
using namespace glm;

Curve::Curve(std::vector<Curve::Point> points_) {
    _points = points_;
}

Curve::Point Curve::operator[](int index) {
    return points[index];
}

int Curve::AddKey(float time_, float value_) {
    Point key(time_, value_, 0.0f, 0.0f);

    // TODO: calcolo tangenti e weight automatico. è una parola

    _points.push_back(key);
    _length = points.size();
    return _length - 1;
}

int Curve::AddKey(float time_, float value_, float inTangent_, float outTangent_) {
    Point key(time_, value_, inTangent_, outTangent_);
    _points.push_back(key);
    _length = points.size();
    return _length - 1;
}

int Curve::MoveKey(int index, Point key) {
    if (index >= (int)_points.size()) return -1;
    _points[index] = key;
    return index;
}

void Curve::RemoveKey(int index) {
    if (index >= (int)_points.size()) return;
    _points.erase(points.begin() + index);
    _length = points.size();
}

// NB: funziona solo con curve di 2 punti, ma mi basta per ora
float Curve::Evaluate(float time) {
    if (points.empty()) return 0.0f;

    Point A = points[0];
    Point B = points.back();

    float result = hermite(time, A, B);
    return result;
}

float Curve::hermite(const float& time, const Point& start, const Point& end) {
    float h1 = 2 * glm::pow(time, 3) - 3 * glm::pow(time, 2) + 1;
    float h2 = -2 * glm::pow(time, 3) + 3 * glm::pow(time, 2);
    float h3 = glm::pow(time, 3) - 2 * glm::pow(time, 2) + time;
    float h4 = glm::pow(time, 3) - glm::pow(time, 2);
    float p = (start.value * h1) + (end.value * h2) + (start.outTangent * h3) + (end.inTangent * h4);
    return p;
}

Curve Curve::Constant(float timeStart, float timeEnd, float value) {
    return Linear(timeStart, value, timeEnd, value);
}

Curve Curve::EaseInOut(float timeStart, float valueStart, float timeEnd, float valueEnd) {
    if (timeStart == timeEnd) {
        Point key(timeStart, valueStart);
        return Curve({key});
    }

    return Curve({Point(timeStart, valueStart, 0.0f, 0.0f),
                  Point(timeEnd, valueEnd, 0.0f, 0.0f)});
}

Curve Curve::Linear(float timeStart, float valueStart, float timeEnd, float valueEnd) {
    if (timeStart == timeEnd) {
        Point key(timeStart, valueStart);
        return Curve({key});
    }

    float tangent = (valueEnd - valueStart) / (timeEnd - timeStart);
    return Curve({Point(timeStart, valueStart, 0.0f, tangent),
                  Point(timeEnd, valueEnd, tangent, 0.0f)});
}

}  // namespace se
