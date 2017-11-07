#pragma once

#include "component.h"

#include <glm.hpp>

using namespace glm;
using namespace std;

namespace ShushaoEngine {

	class Renderer : public Component {

		public:

			Renderer();

			bool enabled;  // Makes the rendered 3D object visible if enabled.

			bool allowOcclusionWhenDynamic; //Controls if dynamic occlusion culling should be performed for this renderer.
			//bounds; //The bounding volume of the renderer (Read Only).
			//isPartOfStaticBatch; //Has this renderer been statically batched with any other renderers?
			bool isVisible; //Is this renderer visible in any camera? (Read Only)
			//lightmapIndex; //The index of the baked lightmap applied to this renderer.
			//lightmapScaleOffset; //The UV scale & offset used for a lightmap.
			//lightProbeProxyVolumeOverride; //If set, the Renderer will use the Light Probe Proxy Volume component attached to the source GameObject.
			//lightProbeUsage; //The light probe interpolation type.
			//localToWorldMatrix; // Matrix that transforms a point from local space into world space (Read Only).
			//Material* material; // Returns the first instantiated Material assigned to the renderer.
			//vector<Material*> materials; // Returns all the instantiated materials of this object.
			// motionVectorGenerationMode; //Specifies the mode for motion vector rendering.
			// probeAnchor; //If set, Renderer will use this Transform's position to find the light or reflection probe.
			// realtimeLightmapIndex; //The index of the realtime lightmap applied to this renderer.
			// realtimeLightmapScaleOffset; //The UV scale & offset used for a realtime lightmap.
			// receiveShadows; //Does this object receive shadows?
			// reflectionProbeUsage; //Should reflection probes be used for this Renderer?
			// shadowCastingMode; //Does this object cast shadows?
			//Material* sharedMaterial; //The shared material of this object.
			//vector<Material*> sharedMaterials; //All the shared materials of this object.
			int sortingLayerID; //Unique ID of the Renderer's sorting layer.
			string sortingLayerName; //Name of the Renderer's sorting layer.
			int sortingOrder; //Renderer's order within a sorting layer.
			mat4x4 worldToLocalMatrix; //Matrix that transforms a point from world space into local space (Read Only).

			// methods

			// GetClosestReflectionProbes(); // Returns an array of closest reflection probes with weights, weight shows how much influence the probe has on the renderer, this value is also used when blending between reflection probes occur.
			// GetPropertyBlock(); // Get per-renderer material property block.
			// SetPropertyBlock(); // Lets you add per-renderer material parameters without duplicating a material.

		protected:

			// messages

			void OnBecameInvisible(); // OnBecameInvisible is called when the object is no longer visible by any camera.
			void OnBecameVisible(); // OnBecameVisible is called when the object became visible by any camera.

		private:
	};

}
