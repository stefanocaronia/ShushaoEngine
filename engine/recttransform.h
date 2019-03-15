#pragma once

#include "glm/glm.hpp"
#include "rect.h"
#include "types.h"
#include "transform.h"

namespace se {

	class Transform;

    class RectTransform {

		public:

            RectTransform(Transform* transform_);

            Transform* transform = nullptr;
            RectTransform* parentRectTransform = nullptr;
            bool isRectTransformChild = false;
			RenderMode renderMode = RenderMode::WORLD;

			const glm::vec2& anchoredPosition = _anchoredPosition; //The position of the pivot of this RectTransform relative to the anchor reference point.
			const glm::vec2& anchorMax = _anchorMax; // The normalized position in the parent RectTransform that the upper right corner is anchored to.
			const glm::vec2& anchorMin = _anchorMin; // The normalized position in the parent RectTransform that the lower left corner is anchored to.
			const glm::vec2& offsetMax = _offsetMax; // The offset of the upper right corner of the rectangle relative to the upper right anchor.
			const glm::vec2& offsetMin = _offsetMin; //	The offset of the lower left corner of the rectangle relative to the lower left anchor.
			const Rect& rect = _rect; // The calculated rectangle in the local space of the Transform.
			const glm::vec2& sizeDelta = _sizeDelta; //	The size of this RectTransform relative to the distances between the anchors.
			const glm::vec2& pivot = _pivot;
			const float& left = _left;
			const float& top = _top;
			const float& right = _right;
			const float& bottom = _bottom;

			glm::mat4 GetLocalToParentMatrix();

			void ForceUpdateRectTransforms(); // Force the recalculation of RectTransforms internal data.
			void GetLocalCorners(); // Get the corners of the calculated rectangle in the local space of its Transform.
			void GetWorldCorners(); // Get the corners of the calculated rectangle in world space.
			void SetInsetAndSizeFromParentEdge(); // Set the distance of this rectangle relative to a specified edge of the parent rectangle, while also setting its size.
			void SetSizeWithCurrentAnchors(); // Makes the RectTransform calculated rect be a given size on the specified axis.

			void SetRect(Rect rect_);
			void SetRectSize(glm::vec2 size_);

            void SetPivot(glm::vec2);
            void SetAnchorMax(glm::vec2);
            void SetAnchorMin(glm::vec2);
            void SetAnchoredPosition(glm::vec2);

			Rect GetAnchorsParentRect();
			void CalculateSizeDelta();

            void init();
            void update();
            void render();

			void Invalidate();
			void InvalidateChildren();
			bool rectInvalid = false;

		private:

			Rect _rect;
			glm::vec2 _anchoredPosition;
			glm::vec2 _anchorMax = {0.5f, 0.5f};
			glm::vec2 _anchorMin = {0.5f, 0.5f};
			glm::vec2 _offsetMax = {0.0f, 0.0f};
			glm::vec2 _offsetMin = {0.0f, 0.0f};
			glm::vec2 _sizeDelta;

			glm::vec2 _pivot = {0.5f, 0.5f};

			float _left;
			float _top;
			float _right;
			float _bottom;

	};

}