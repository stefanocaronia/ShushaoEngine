#include "hermite.h"

using namespace se;

Hermite::Hermite() {
    GeometryRenderer* gr = AddComponent<GeometryRenderer>();
    gr->sortingLayerID = Config::SortingLayers.over();

    Curve curve = Curve::EaseInOut(0.0f, 0.0f, 1.0f, 1.0f);

    //curve.AddPoint(0.2813312f, 0.6913764f, -1.775311f);
    //curve.AddPoint(0.7149807f, 0.04005498f, -9.476109f, 0.2281767f); */
//
    //Curve curve;
//
    //curve.AddPoint(0, 1, -2, -2);
    //curve.AddPoint(1, 0, 0, 0);


    // Time: 0.7149807; Value: 0.04005498; inTangent: -9.476109; outTangent: 0.2281767

    std::vector<glm::vec3> points;
    for (double d = 0.0; d <= 1.0; d += 0.001) {
        vec3 point = vec3(d * 6.0, curve.Evaluate(d) * 2.0f, 0.0f);
        points.push_back(point);
    }

    for (auto point : curve.points) {
        Debug::Log << "point: " << point.time << ", " << point.value << endl;
    }

    gr->AddPolyline(points, Color::green);
}