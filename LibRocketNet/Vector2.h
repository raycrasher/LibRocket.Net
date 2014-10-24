#pragma once;

#include "Rocket/Core/Vertex.h"

typedef Rocket::Core::Vertex RVertex;
typedef Rocket::Core::Vector2f RVector2f;
typedef Rocket::Core::Vector2i RVector2i;

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
	T(RVector2f a) { X=(baseT)a.x; Y=(baseT)a.y; } \
	T(RVector2i a) { X=(baseT)a.x; Y=(baseT)a.y; } \
};

DEFINE_VECTOR(Vector2f, float);
DEFINE_VECTOR(Vector2i, int);
DEFINE_VECTOR(Vector2u, unsigned int);

}