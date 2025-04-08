#pragma once
#include "raylib.h"

#include <vector>
#include <string>
#include <iostream>

class StatusMarker {
public:
	Vector2 pos = { 0,0 };
	Vector2 dir = { 0.0f,-1.0f };
	Vector2 vel = { 40.0f, 40.0f };
	const float fr = 0.06f;
	
	int size = 22;
	std::string value = "n/a";

	Color color = { 255, 255, 255, 0 };
	const int alphaChange = 4;
public:
	inline StatusMarker(const std::string& value, const Color& color, const Vector2& pos) {
		this->value = value;
		this->color= color;
		this->pos = pos;
	}
	// Needs copy constructor for when erasing it from the vector
	inline StatusMarker operator=(const StatusMarker& other) {
		this->value = other.value;
		this->color = other.color;
		this->pos = other.pos;

		return *this;
	}

	inline void Draw() const {	
		DrawText(value.c_str(), pos.x, pos.y, size, color);
	}
	inline void Update(const float& dt) {
		vel.x *= dir.x * fr * dt;
		vel.y *= dir.y * fr * dt;

		// TODO: change position based on the player/entity
		pos.x += vel.x;
		pos.y += vel.y;

		// IDEA: alpha should change according to 
		// the time. We can get that by calculating how
		// long it takes to stop, dividing it by 255 and 60 and
		// adding that amout to the alpha each frame
		if (color.a + alphaChange < 255) {
			color.a += alphaChange;
		}
	}
	inline bool IsInvisible() const {
		return (color.a + alphaChange >= 255);
	}
};

class MarkerManager{
public:
	Color statusColor = { 246, 214, 189, 0 };

	std::vector<StatusMarker> markers;
public:
	inline MarkerManager() {}
	inline MarkerManager(const Color& color) {
		statusColor = color;
		statusColor.a = 0;
	}

	inline void Draw() const {
		for (const auto& marker : markers) {
			marker.Draw();
		}
	}

	inline void Update(const float& dt) {
		int markerIndex = 0;
		for (auto& marker : markers) {
			marker.Update(dt);

			if (marker.IsInvisible()) 
				markers.erase(markers.begin() + markerIndex);

			std::cout << "size: " << markers.size() << std::endl;

			markerIndex++;
		}
	}

	inline void AddMarker(std::string& value, const Vector2& pos) {
		StatusMarker marker = StatusMarker(value, statusColor, pos);
		markers.push_back(marker);
	}

	inline void ClearMarkers(){
		markers.clear();
	}

	inline void SetColor(const Color& color) {
		statusColor = color;
		statusColor.a = 0;
	}
};