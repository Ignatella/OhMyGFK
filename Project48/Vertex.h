#pragma once


struct Vertex {
	static bool less_in_x(const Vertex& a, const Vertex& b) { return a.x < b.x; }
	static bool less_in_y(const Vertex& a, const Vertex& b) { return a.y < b.y; }
	static bool greater_in_x(const Vertex& a, const Vertex& b) { return a.x > b.x; }
	static bool greater_in_y(const Vertex& a, const Vertex& b) { return a.y > b.y; }

	Vertex(double _x, double _y) : x{ _x }, y{ _y } {}
	Vertex(int _x, int _y, double ratio) : x{ _x * ratio }, y{ _y * ratio } {}
	double x, y;
};