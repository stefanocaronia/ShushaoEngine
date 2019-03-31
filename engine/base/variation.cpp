#include "variation.h"
#include "../debug.h"

namespace se {
    using namespace std;

    Variation::Variation() {
        _constant = 0.0f;
        _mode = VariationMode::CONSTANT;
    }

    Variation::Variation(float constant_) {
        _constant = constant_;
        _mode = VariationMode::CONSTANT;
    }

    Variation::Variation(float min_, float max_) {
        _min = min_;
        _max = max_;
        _mode = VariationMode::RANGE;
    }

    Variation::Variation(float value_, Curve& curve_) {
        _curveMultiplier = value_;
        _curve = curve_;
        _mode = VariationMode::CURVE;
    }

    void Variation::operator=(float constant_) {
        _constant = constant_;
        _mode = VariationMode::CONSTANT;
    }

    void Variation::operator=(Range range_) {
        _min = range_.min;
        _max = range_.max;
        _mode = VariationMode::RANGE;
    }

    void Variation::operator=(Path curvescaled_) {
        _curveMultiplier = curvescaled_.scale;
        _curve = curvescaled_.curve;
        _mode = VariationMode::CURVE;
    }

    float Variation::Evaluate(float x) {
        float result;
        switch (mode) {
            case VariationMode::CONSTANT:
                return constant;
                break;
            case VariationMode::RANGE:
                result = x * (max - min);
                break;
            case VariationMode::CURVE:
                result = _curve.Evaluate(x) * curveMultiplier;
                break;
        }
        return result;
    }
}