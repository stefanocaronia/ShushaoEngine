#pragma once

#include <glm/glm.hpp>
#include "curve.h"

namespace se {

class Variation {

    public:

        enum class VariationMode {
            CONSTANT,
            CURVE,
            RANGE,
            // CURVES,
            // CONSTANTS
        };

        typedef struct {
            float min;
            float max;
        } Range;

        typedef struct {
            float scale;
            Curve& curve;
        } Path;

        // readonly
        const VariationMode& mode = _mode;
        const float& constant = _constant;
        const float& min = _min;
        const float& max = _max;
        const float& curveMultiplier = _curveMultiplier;
        const Curve& curve = _curve;

        Variation();
        Variation(float constant_);
        Variation(float min_, float max_);
        Variation(float value_, Curve& curve_);

        void operator=(float constant_);
        void operator=(Range range_);
        void operator=(Path curvescaled_);

        float Evaluate(float x);

    private:

        float _constant;
        float _min;
        float _max;
        Curve _curve;

        //Curve _curveMin;
        //Curve _curveMax;
        float _curveMultiplier;
        VariationMode _mode = VariationMode::CONSTANT;
};

}