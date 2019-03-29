#pragma once

#include <vector>

namespace se {

struct Keyframe {
    enum class WeightedMode {
        NONE,  // Exclude both inWeight or outWeight when calculating curve segments.
        IN,    // Include inWeight when calculating the previous curve segment.
        OUT,   // Include outWeight when calculating the next curve segment.
        BOTH   // Include inWeight and outWeight when calculating curve segments.
    };

    float inTangent;            // Sets the incoming tangent for this key. The incoming tangent affects the slope of the curve from the previous key to this key.
    float inWeight;             // Sets the incoming weight for this key. The incoming weight affects the slope of the curve from the previous key to this key.
    float outTangent;           // Sets the outgoing tangent for this key. The outgoing tangent affects the slope of the curve from this key to the next key.
    float outWeight;            // Sets the outgoing weight for this key. The outgoing weight affects the slope of the curve from this key to the next key.
    float time;                 // The time of the keyframe.
    float value;                // The value of the curve at keyframe.
    WeightedMode weightedMode;  // Weighted mode for the keyframe.
};

class AnimationCurve {
public:

    AnimationCurve();

    std::vector<Keyframe>& keys = _keys;  // All keys defined in the animation curve.
    unsigned int& length = _lengh; // The number of keys in the curve.(Read Only)

    static void Constant();
    static void EaseInOut();
    static void Linear();

    int AddKey(float time, float value); //Add a new key to the curve.
    float Evaluate(float time); //Evaluate the curve at time.
    //int MoveKey(int index, Keyframe key); //Removes the keyframe at index and inserts key.
    //void RemoveKey(int index); //Removes a key.
    //void SmoothTangents(int index, float weight); //Smooth the in and out tangents of the keyframe at index.

private:

    std::vector<Keyframe> _keys; // All keys defined in the animation curve.
    unsigned int _length; // The number of keys in the curve.(Read Only)
};

}  // namespace se