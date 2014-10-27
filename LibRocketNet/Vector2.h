#pragma once;

#include "Rocket/Core/Vertex.h"

typedef Rocket::Core::Vertex RVertex;

using namespace System;
using namespace System::Runtime::InteropServices;

namespace LibRocketNet {

#define DEFINE_VECTOR(T, baseT) \
[StructLayout(LayoutKind::Sequential)] \
public value class T { \
public: \
	baseT X, Y; \
	T(baseT x, baseT y) { X=x; Y=y; } \
	bool operator==(baseT a) { return X==a && Y==a; } \
	T operator+(T a) { return T(X+a.X, Y+a.Y); } \
	T operator-(T a) { return T(X-a.X, Y-a.Y); } \
	T operator*(T a) { return T(X*a.X, Y*a.Y); } \
	T operator/(T a) { return T(X/a.X, Y/a.Y); } \
	T operator+(baseT a) { return T(X+a, Y+a); } \
	T operator-(baseT a) { return T(X-a, Y-a); } \
	T operator*(baseT a) { return T(X*a, Y*a); } \
	T operator/(baseT a) { return T(X/a, Y/a); } \
internal: \
	T(Rocket::Core::Vector2f a) { X=(baseT)a.x; Y=(baseT)a.y; } \
	T(Rocket::Core::Vector2i a) { X=(baseT)a.x; Y=(baseT)a.y; } \
	operator Rocket::Core::Vector2f(){ return Rocket::Core::Vector2f((float)X,(float)Y); }\
	operator Rocket::Core::Vector2i(){ return Rocket::Core::Vector2i((int)X,(int)Y); }\
};

DEFINE_VECTOR(Vector2f, float);
DEFINE_VECTOR(Vector2i, int);
DEFINE_VECTOR(Vector2u, unsigned int);

}