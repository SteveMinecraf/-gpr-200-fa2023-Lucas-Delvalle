#pragma once
#include "../ew/ewMath/mat4.h"
#include "../ew/ewMath/vec3.h"

namespace myLib {
	//Identity matrix
	inline ew::Mat4 Identity() {
		return ew::Mat4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
	};
	//Scale on x,y,z axes
	inline ew::Mat4 Scale(ew::Vec3 s) {
		return ew::Mat4(
			s.x, 0, 0, 0,
			0, s.y, 0, 0,
			0, 0, s.z, 0,
			0, 0, 0, 1
		);
	};
	//Rotation around X axis (pitch) in radians
	inline ew::Mat4 RotateX(float rad) {
		float cosVar = cos(rad);
		float sinVar = sin(rad);
		return ew::Mat4(
			1, 0, 0, 0,
			0, cosVar, -sinVar, 0,
			0, sinVar, cosVar, 0,
			0, 0, 0, 1
		);
	};
	//Rotation around Y axis (yaw) in radians
	inline ew::Mat4 RotateY(float rad) {
		float cosVar = cos(rad);
		float sinVar = sin(rad);

		return ew::Mat4(
			cosVar, 0, sinVar, 0,
			0, 1, 0, 0,
			-sinVar, 0, cosVar, 0,
			0, 0, 0, 1
		);
	};
	//Rotation around Z axis (roll) in radians
	inline ew::Mat4 RotateZ(float rad) {
		float cosVar = cos(rad);
		float sinVar = sin(rad);

		return ew::Mat4(
			cosVar, -sinVar, 0, 0,
			sinVar, cosVar, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
	};
	//Translate x,y,z
	inline ew::Mat4 Translate(ew::Vec3 t) {
		return ew::Mat4(
			1, 0, 0, t.x,
			0, 1, 0, t.y,
			0, 0, 1, t.z,
			0, 0, 0, 1
		);
	};

	struct Transform {
		ew::Vec3 position = ew::Vec3(0.0f, 0.0f, 0.0f);
		ew::Vec3 rotation = ew::Vec3(0.0f, 0.0f, 0.0f); //Euler angles (degrees)
		ew::Vec3 scale = ew::Vec3(1.0f, 1.0f, 1.0f);
		ew::Mat4 getModelMatrix() const {
			ew::Mat4 modelMatrix = Identity();

			// Scale
			ew::Mat4 scaleMatrix = Scale(scale);
			modelMatrix = modelMatrix * scaleMatrix;

			// Rotate around Z
			ew::Mat4 rotateZMatrix = RotateZ(rotation.z);
			modelMatrix = modelMatrix * rotateZMatrix;

			// Rotate around X
			ew::Mat4 rotateXMatrix = RotateX(rotation.x);
			modelMatrix = modelMatrix * rotateXMatrix;

			// Rotate around Y
			ew::Mat4 rotateYMatrix = RotateY(rotation.y);
			modelMatrix = modelMatrix * rotateYMatrix;

			// Translate
			ew::Mat4 translateMatrix = Translate(position);
			modelMatrix = modelMatrix * translateMatrix;

			return modelMatrix;
		};
	};

}