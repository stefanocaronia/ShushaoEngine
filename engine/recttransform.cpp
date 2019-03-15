#include "transform.h"
#include "debug.h"
#include "design.h"
#include "entity.h"

namespace se {

    using namespace glm;

    RectTransform::RectTransform(Transform* transform_) {
        transform = transform_;
        init();
        update();
    }

    glm::mat4 RectTransform::GetLocalToParentMatrix() {
        vec2 parentAnchorCoord = anchorMin * parentRectTransform->rect.size;
        return glm::translate(glm::mat4(), vec3(anchoredPosition - parentAnchorCoord, 0.0f)) * glm::toMat4(transform->localRotation) * glm::scale(glm::mat4(), transform->localScale);
    }

    Rect RectTransform::GetAnchorsParentRect() {
        Rect ar;
        ar.SetPosition({
            anchorMin.x * parentRectTransform->rect.width,
            anchorMax.y * parentRectTransform->rect.height
        });
        ar.SetSize({
            (anchorMax.x - anchorMin.x) * parentRectTransform->rect.width,
            (anchorMax.y - anchorMin.y) * parentRectTransform->rect.height
        });
        return ar;
    }

    void RectTransform::SetSizeWithCurrentAnchors() {
        if (!isRectTransformChild) return;
        Rect ar = GetAnchorsParentRect();

        if (ar.height = 0 && ar.width > 0) {
            _rect.SetX(ar.xMin + _left);
            _rect.SetXMax(ar.xMax - _right);
        } else if (ar.width = 0 && ar. height > 0) {
            _rect.SetY(ar.yMax - _top);
            _rect.SetYMin(ar.yMin + _bottom);
        } else if (anchorMin != anchorMax) {
            _rect.SetPosition({ar.xMin + _left, ar.yMax - _top});
            _rect.SetSize({_right - ar.xMin, ar.yMin + _bottom});
        }

        rectInvalid = false;
    }

    void RectTransform::CalculateSizeDelta() {
        if (!isRectTransformChild) return;
        Rect apr = GetAnchorsParentRect();
        _top = apr.yMax - rect.yMax; // anchoredPosition.y + (rect.height * (1.0f - pivot.y));
        _right = apr.xMax - rect.xMax; // anchoredPosition.x + (rect.width * (1.0f - pivot.x));
        _left = rect.xMin - apr.xMin; // apr.xMin - anchorMin.x * parentRectTransform->rect.width - (rect.width * pivot.x);
        _bottom = rect.yMin - apr.yMin; //apr.yMin - anchorMin.y * parentRectTransform->rect.height - (rect.height * pivot.y);
    }

    void RectTransform::SetAnchorMax(glm::vec2 value) {
        if (value != _anchorMax) {
            _anchorMax = value;
            Invalidate();
            CalculateSizeDelta();
            update();
        }
    }

    void RectTransform::SetPivot(glm::vec2 value) {
        if (value != _pivot) {
            _pivot = value;
            // transform->Invalidate();
            update();
        }
    }

    void RectTransform::SetAnchorMin(glm::vec2 value) {
        if (value != _anchorMin) {
            _anchorMin = value;
            Invalidate();
            CalculateSizeDelta();
            update();
        }
    }

    void RectTransform::SetAnchoredPosition(glm::vec2 value) {
        if (value != _anchoredPosition) {
            InvalidateChildren();
            _anchoredPosition = value;
            transform->Invalidate();
            CalculateSizeDelta();
            update();
        }
    }

    void RectTransform::SetRect(Rect value) {
        if (value != _rect) {
            InvalidateChildren();
            _rect = value;
            transform->Invalidate();
            CalculateSizeDelta();
            update();
        }
    }

	void RectTransform::SetRectSize(glm::vec2 size_) {
        if (size_ != _rect.size) {
            InvalidateChildren();
             _rect.SetSize(size_);
            transform->Invalidate();
            CalculateSizeDelta();
            update();
        }

    }

    void RectTransform::init() {
        if (transform->parent != nullptr) {
            parentRectTransform = transform->parent->rectTransform;
            isRectTransformChild = transform->parent->isRectTransform;
        }
    }

    void RectTransform::update() {

        if (isRectTransformChild) {
            if (anchorMax == anchorMin) {
                vec2 parentAnchorCoord = anchorMin * parentRectTransform->rect.size;
                _rect.SetPosition(parentAnchorCoord - rect.size * pivot);
            } else {
               if (rectInvalid) SetSizeWithCurrentAnchors();
            }

        } else {

            _rect.SetPosition(-rect.size * pivot);
        }

    }

    void RectTransform::Invalidate() {
		if (!rectInvalid) {
			rectInvalid = true;
		}

		InvalidateChildren();
	}

    void RectTransform::InvalidateChildren() {
        for (Transform* child : transform->children) {
            if (child->isRectTransform)
			    child->rectTransform->Invalidate();
		}
    }

    void RectTransform::render() {

        if (Debug::enabled) {
            Color color;
            if (renderMode == RenderMode::WORLD)        color = {0.1f, 0.1f, 0.5f, 0.6f};
            else if (renderMode == RenderMode::SCREEN)  color = {0.5f, 0.0f, 0.1f, 0.2f};
            Design::DrawRect(Transform::VEC3_ZERO, rect, color, DrawMode::HOLLOW, renderMode, transform->MVP);

            vec3 boxTransformPoint = vec3(rect.position + rect.size * pivot, 0.0f);

            Design::DrawVector(boxTransformPoint, transform->up / 3.0f, Color::green, false, renderMode, transform->MVP);
			Design::DrawVector(boxTransformPoint, transform->right / 3.0f, Color::red, false, renderMode, transform->MVP);
			Design::DrawVector(boxTransformPoint, transform->forward / 3.0f, Color::blue, false, renderMode, transform->MVP);
        }

    }
}