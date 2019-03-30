#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace se {

class Curve {
public:
    enum class WrapMode {
        DEFAULT,
        ONCE,
        LOOP,
        PINGPONG,
        CLAMPFOREVER,
        CLAMP
    };

    struct Point {
        float time, value, inTangent, outTangent;

        Point(float time_ = 0.0f, float value_ = 0.0f, float inTangent_ = 0.0f, float outTangent_ = 0.0f) : time(time_), value(value_), inTangent(inTangent_), outTangent(outTangent_) {}

        glm::vec2 xy() {
            return glm::vec2(time, value);
        }

        glm::vec4 xyxw() {
            return glm::vec4(time, value, inTangent, outTangent);  // x = time, y = value, z = inTangent, w = outTangent
        }
    };

    Curve();
    Curve(std::vector<Curve::Point> points_);

    std::vector<Curve::Point>& points = _points;  // All points defined in the animation curve.
    unsigned int& length = _length;               // The number of points in the curve.(Read Only)
    WrapMode wrapMode = WrapMode::DEFAULT;

    Point operator[](int index);

    int AddKey(float time, float value);  // Add a new key to the curve.
    int AddKey(float time, float value, float inTangent, float outTangent);
    int MoveKey(int index, Point key);  // Removes the keyframe at index and inserts key.
    void RemoveKey(int index);
    float Evaluate(float time);  // Evaluate the curve at time.

    // static methods
    static float hermite(const float& time, const Point& start, const Point& end);
    static Curve Constant(float timeStart, float timeEnd, float value);
    static Curve EaseInOut(float timeStart, float valueStart, float timeEnd, float valueEnd);
    static Curve Linear(float timeStart, float valueStart, float timeEnd, float valueEnd);

private:
    std::vector<Point> _points;  // All points defined in the animation curve.
    unsigned int _length = 0;    // The number of points in the curve.(Read Only)
};

}  // namespace se