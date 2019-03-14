#include "recttransform.h"
#include "transform.h"
#include "debug.h"
#include "design.h"
#include "entity.h"

namespace se {

    using namespace glm;

    RectTransform::RectTransform(void* transform_) {
        transform = (Transform*)transform_;
        if (((Transform*)transform)->parent != nullptr) {
            parentRectTransform = ((Transform*)transform)->parent->rectTransform;
            isRectTransformChild = ((Transform*)transform)->parent->isRectTransform;
        }
    }

    void RectTransform::SetAnchorMax(glm::vec2 value) {
        _anchorMax = value;
        update();
    }

    void RectTransform::SetPivot(glm::vec2 value) {
        _pivot = value;
        update();
    }

    void RectTransform::SetAnchorMin(glm::vec2 value) {
        _anchorMin = value;
        update();
    }

    void RectTransform::SetPosition(glm::vec2 value) {
        _anchoredPosition = value;
        update();
    }

    void RectTransform::SetRect(Rect value) {
        _rect = value;
        update();
    }

	void RectTransform::SetRectSize(glm::vec2 size_) {
        _rect.SetSize(size_);
        update();
    }

    void RectTransform::init() {
    }

    void RectTransform::update() {
        _rect.SetX(-(rect.width * pivot.x));
        _rect.SetY(-(rect.height * pivot.y));

        if (isRectTransformChild) {
            _top = anchorMax.y * parentRectTransform->rect.height - anchoredPosition.y + (rect.height * (1.0f - pivot.y));
            _right = anchorMax.x * parentRectTransform->rect.width - anchoredPosition.x + (rect.width * (1.0f - pivot.x));
            _left = anchoredPosition.x - anchorMin.x * parentRectTransform->rect.width - (rect.width * pivot.x);
            _bottom = anchoredPosition.y - anchorMin.y * parentRectTransform->rect.height - (rect.height * pivot.y);
        }
    }

    void RectTransform::render() {
        if (Debug::enabled) {
            Color color;
            if (renderMode == RenderMode::WORLD)        color = {0.1f, 0.1f, 0.5f, 0.6f};
            else if (renderMode == RenderMode::SCREEN)  color = {0.5f, 0.0f, 0.1f, 0.2f};
            Design::DrawRect(vec3(anchoredPosition, 0.0f), rect, color, DrawMode::HOLLOW, renderMode);
        }
    }
}