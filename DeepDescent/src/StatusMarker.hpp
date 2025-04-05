#pragma once
#include "raylib.h"
#include "Timer.hpp"
#include <string>

class StatusMarker {
public:
	Vector2 pos = { 0,0 };
	Vector2 dir = { 0,-1 };
	Vector2 vel = { 0,0 };
	const float acc = 40.0f;
	const float fr = 0.05f;
	
	const int alphaChange = 3;
	std::string textValue = "none";
	int textSize = 20;
	Color textColor;
public:
	inline StatusMarker(const std::string& value, const Color& color) {
		textValue = value;
		textColor = color;
	}

	inline void Draw() const {	
		DrawText(textValue.c_str(), pos.x, pos.y, textSize, textColor);
	}
	inline void Update(const float& dt, const Vector2& targetPos) {
		
		vel.x += dir.x * acc * dt;
		vel.y += dir.y * acc * dt;

		vel.x -= vel.x * fr * dt;
		vel.y -= vel.y * fr * dt;

		// TODO: clamp the velocities

		// TODO: change position based on the player
		pos.x += vel.x + (targetPos.x - pos.x);
		pos.y += vel.y + (targetPos.y - pos.y);

		// IDEA: alpha should change according to 
		// the time. We can get that by calculating how
		// long it takes to stop, dividing it by 255 and 60 and
		// adding that amout to the alpha each frame
		if (textColor.a > 0) {
			textColor.a -= alphaChange;
		}
	}
	inline bool IsInvisible() const {
		return (textColor.a <= 0);
	}
};