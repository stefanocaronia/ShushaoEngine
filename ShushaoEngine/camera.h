#pragma once

#include <glm.hpp>

#include "component.h"
#include "color.h"
#include "rect.h"
#include "macros.h"

using namespace std;
using namespace glm;

namespace ShushaoEngine {

	class Camera : public Component {

		public:

			Camera();

			float aspect;
			Color backgroundColor;
			mat4 cameraToWorldMatrix;
			float depth;
			float fieldOfView;
			bool orthographic;
			float orthographicSize;
			float farClipPlane;
			float nearClipPlane;
			//int pixelHeight;	// How tall is the camera in pixels (Read Only).
			//Rect pixelRect;	// Where on the screen is the camera rendered in pixel coordinates.
			//int pixelWidth;	// How wide is the camera in pixels (Read Only).
			//mat4x4 previousViewProjectionMatrix;	// Get the view projection matrix used on the last frame.
			//mat4 projectionMatrix;	// Set a custom projection matrix.
			Rect rect;	// Where on the screen is the camera rendered in normalized coordinates.
			vec3 velocity;	// Get the world-space speed of the camera (Read Only).
			mat4 worldToCameraMatrix; //	Matrix that transforms from world to camera space.

			mat4 getViewMatrix();
			mat4 getProjectionMatrix();

			// methods

			// AddCommandBuffer	Add a command buffer to be executed at a specified place.
			// CalculateFrustumCorners	Given viewport coordinates, calculates the view space vectors pointing to the four frustum corners at the specified camera depth.
			// CalculateObliqueMatrix	Calculates and returns oblique near-plane projection matrix.
			// CopyFrom	Makes this camera's settings match other camera.
			// GetCommandBuffers	Get command buffers to be executed at a specified place.
			// GetStereoProjectionMatrix	Gets the projection matrix of a specific left or right stereoscopic eye.
			// GetStereoViewMatrix	Gets the left or right view matrix of a specific stereoscopic eye.
			// RemoveAllCommandBuffers	Remove all command buffers set on this camera.
			// RemoveCommandBuffer	Remove command buffer from execution at a specified place.
			// RemoveCommandBuffers	Remove command buffers from execution at a specified place.
			// Render	Render the camera manually.
			// RenderToCubemap	Render into a static cubemap from this camera.
			// RenderWithShader	Render the camera with shader replacement.
			// ResetAspect	Revert the aspect ratio to the screen's aspect ratio.
			// ResetCullingMatrix	Make culling queries reflect the camera's built in parameters.
			// ResetProjectionMatrix	Make the projection reflect normal camera's parameters.
			// ResetReplacementShader	Remove shader replacement from camera.
			// ResetStereoProjectionMatrices	Reset the camera to using the Unity computed projection matrices for all stereoscopic eyes.
			// ResetStereoViewMatrices	Reset the camera to using the Unity computed view matrices for all stereoscopic eyes.
			// ResetTransparencySortSettings	Resets this Camera's transparency sort settings to the default. Default transparency settings are taken from GraphicsSettings instead of directly from this Camera.
			// ResetWorldToCameraMatrix	Make the rendering position reflect the camera's position in the scene.
			// ScreenPointToRay	Returns a ray going from camera through a screen point.
			// ScreenToViewportPoint	Transforms position from screen space into viewport space.
			// ScreenToWorldPoint	Transforms position from screen space into world space.
			// SetReplacementShader	Make the camera render with shader replacement.
			// SetStereoProjectionMatrix	Sets a custom projection matrix for a specific stereoscopic eye.
			// SetStereoViewMatrix	Sets a custom view matrix for a specific stereoscopic eye.
			// SetTargetBuffers	Sets the Camera to render to the chosen buffers of one or more RenderTextures.
			// ViewportPointToRay	Returns a ray going from camera through a viewport point.
			// ViewportToScreenPoint	Transforms position from viewport space into screen space.
			// ViewportToWorldPoint	Transforms position from viewport space into world space.
			// WorldToScreenPoint	Transforms position from world space into screen space.
			// WorldToViewportPoint	Transforms position from world space into viewport space.

			mat4 getMatrix();
	};

}
