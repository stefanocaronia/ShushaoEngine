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
        _rect.YUP = true;
        _rect.name = transform->entity->name;
    }

    glm::mat4 RectTransform::GetLocalToParentMatrix() {
        glm::mat4 matrix;
        if (hasSingleAnchorPoint()) {
            vec2 parentAnchorCoord = parentRectTransform->rectCoordToLocal(anchorMin * parentRectTransform->rect.size);
            matrix = glm::translate(glm::mat4(), vec3(parentAnchorCoord, 0.0f))
                    * glm::translate(glm::mat4(), transform->localPosition)
                    * glm::toMat4(transform->localRotation) * glm::scale(glm::mat4(), transform->localScale);
        } else {
            if (rectInvalid) SetSizeWithCurrentAnchors();
            matrix = glm::translate(glm::mat4(), vec3(anchoredPosition, 0.0f))
                     /* glm::translate(glm::mat4(), transform->localPosition) */
                    * glm::toMat4(transform->localRotation) * glm::scale(glm::mat4(), transform->localScale);
        }

        return matrix;
    }

    void RectTransform::update() {
        if (isRectTransformChild && !hasSingleAnchorPoint()) {
            // if (rectInvalid) SetSizeWithCurrentAnchors();
        } else {
            _rect.SetPosition(vec2(0, rect.height) -localPivot());
        }
    }

	vec2 RectTransform::rectCoordToLocal(vec2 pcoord) {
        return pcoord - localPivot();
	}

    vec2 RectTransform::localPivot(bool flipY) {
        if (flipY) {
            return rect.size * pivot * vec2(1, -1);
        }
        return rect.size * pivot;
    }

    Rect RectTransform::GetAnchorsParentRect() {
        Rect ar;
        ar.YUP = true;
        ar.Set(
            anchorMin.x * parentRectTransform->rect.width,
            anchorMax.y * parentRectTransform->rect.height,
            anchorMax.x * parentRectTransform->rect.width - anchorMin.x * parentRectTransform->rect.width,
            anchorMax.y * parentRectTransform->rect.height - anchorMin.y * parentRectTransform->rect.height
        );

        return ar;
    }

    void RectTransform::SetSizeWithCurrentAnchors() {
        if (!isRectTransformChild) return;
        Rect apr = GetAnchorsParentRect();
        vec2 piv = pivot * vec2(deltas.width, deltas.height);

        Rect tempRect;
        tempRect.YUP = true;

        switch (registerMode) {
            case RegisterMode::LRYH: // OK
                deltas.width = parentRectTransform->rect.width - deltas.left - deltas.right;

                tempRect.Set(
                    apr.xMin + deltas.left,
                    apr.yMax + deltas.Y + pivot.y,
                    deltas.width,
                    deltas.height
                );

                break;

            case RegisterMode::TBXW: // OK
                deltas.left = deltas.X - piv.x;
                deltas.right = parentRectTransform->rect.width - deltas.width - deltas.left;
                deltas.height = parentRectTransform->rect.height - deltas.top - deltas.bottom;

                tempRect.Set(
                    apr.xMin + deltas.left,
                    apr.yMax - deltas.top,
                    deltas.width,
                    deltas.height
                );

                break;

            case RegisterMode::LRTH: // OK
                deltas.width = parentRectTransform->rect.width - deltas.left - deltas.right;

                tempRect.Set(
                    apr.xMin + deltas.left,
                    apr.yMax - deltas.top,
                    deltas.width,
                    deltas.height
                );

                break;

            case RegisterMode::LRTB: // OK
                deltas.width = parentRectTransform->rect.width - deltas.left - deltas.right;
                deltas.height = parentRectTransform->rect.height - deltas.top - deltas.bottom;

                tempRect.Set(
                    apr.xMin + deltas.left,
                    apr.yMax - deltas.top,
                    deltas.width,
                    deltas.height
                );

                break;
        }

        vec2 localPosition = tempRect.position - parentRectTransform->localPivot();

        _rect.SetSize(tempRect.size);
        _rect.SetPosition(vec2(0,0) - localPivot(true));
        _anchoredPosition = localPosition + localPivot(true);

        /* Debug::Log << "AnchorsParentRect" << endl;
        Debug::Log << apr.ToString() << endl;
        Debug::Log << "Rect" << endl;
        Debug::Log << tempRect.ToString() << endl;
        Debug::Log << "Anchored Position: " <<_anchoredPosition.x << ", " << _anchoredPosition.y << endl;
        Debug::Log(WARNING) << deltas.toString() << endl; */

        rectInvalid = false;
    }

    void RectTransform::RegisterPositionLRYH(float left_, float right_, float Y_, float height_) { // OK
        deltas.left = left_;
        deltas.right = right_;
        deltas.Y = Y_;
        deltas.height = height_;

        registerMode = RegisterMode::LRYH;
        SetSizeWithCurrentAnchors();
    }

    void RectTransform::RegisterPositionTBXW(float top_, float bottom_, float X_, float width_) {
        deltas.top = top_;
        deltas.bottom = bottom_;
        deltas.X = X_;
        deltas.width = width_;

        registerMode = RegisterMode::TBXW;
        SetSizeWithCurrentAnchors();
    }

    void RectTransform::RegisterPositionLRTH(float left_, float right_, float top_, float height_) {
        deltas.left = left_;
        deltas.right = right_;
        deltas.top = top_;
        deltas.height = height_;

        registerMode = RegisterMode::LRTH;
        SetSizeWithCurrentAnchors();
    }

    void RectTransform::RegisterPositionLRTB(float left_, float right_, float top_, float bottom_) {
        deltas.left = left_;
        deltas.right = right_;
        deltas.top = top_;
        deltas.bottom = bottom_;

        registerMode = RegisterMode::LRTB;
        SetSizeWithCurrentAnchors();
    }

    void RectTransform::SetPivot(glm::vec2 value) {
        if (value != _pivot) {
            _pivot = value;
            // transform->Invalidate();
            update();
        }
    }

    void RectTransform::SetAnchor(glm::vec2 value) {
        _anchorMax = value;
        _anchorMin = value;
        update();
    }

    void RectTransform::SetAnchorMax(glm::vec2 value) {
        _anchorMax = value;
        update();
    }

    void RectTransform::SetAnchorMin(glm::vec2 value) {
        _anchorMin = value;
        update();
    }

    void RectTransform::SetRect(Rect value) {
        if (value != _rect) {
            InvalidateChildren();
            _rect = value;
            transform->Invalidate();
            update();
        }
    }

	void RectTransform::SetRectSize(glm::vec2 size_) {
        if (size_ != _rect.size) {
            InvalidateChildren();
             _rect.SetSize(size_);
            transform->Invalidate();
            update();
        }

    }

    void RectTransform::init() {
        if (transform->parent != nullptr) {
            parentRectTransform = transform->parent->rectTransform;
            isRectTransformChild = transform->parent->isRectTransform;
        }
        renderMode = transform->entity->canvas != nullptr ? transform->entity->canvas->renderMode : RenderMode::WORLD;
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
            vec3 position = Transform::VEC3_ZERO;
            if (renderMode == RenderMode::WORLD) {
                color = {0.1f, 0.1f, 0.5f, 0.6f};
            } else if (renderMode == RenderMode::SCREEN) {
                color = {0.5f, 0.0f, 0.1f, 0.2f};
                position = transform->position;
            }
            Design::DrawRect(Transform::VEC3_ZERO, rect, color, DrawMode::HOLLOW, renderMode, transform->MVP);

            Design::DrawVector(position, transform->up / 3.0f, Color::green, false, renderMode, transform->MVP);
			Design::DrawVector(position, transform->right / 3.0f, Color::red, false, renderMode, transform->MVP);
			Design::DrawVector(position, transform->forward / 3.0f, Color::blue, false, renderMode, transform->MVP);
        }

    }
}