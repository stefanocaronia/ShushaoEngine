#include "animationcurve.h"

namespace se {

    using namespace std;

    int AnimationCurve::AddKey(float time, float value) {

        Keyframe key;

        key.time = time;
        key.value = value;
    }

}


/*
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class check : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {

        ParticleSystem ps = GetComponent<ParticleSystem>();

        AnimationCurve ac = ps.sizeOverLifetime.size.curve;

        Keyframe[] keys = ac.keys;

        foreach(Keyframe key in keys)
        {
            Debug.Log("Time: " + key.time + "; Value: " + key.value + "; inTangent: " + key.inTangent + "; outTangent: " + key.outTangent + "; inWeight: " + key.inWeight + "; outWeight: " + key.outWeight);
        }
    }

    // Update is called once per frame
    void Update()
    {

    }
}




*/