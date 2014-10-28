#pragma once

#include "Vector2.h"
#include "Color.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace LibRocketNet {

	[StructLayout(LayoutKind::Sequential)]
	public value class Vertex {
	public:
		Vector2f Position;
		Color Color;
		Vector2f TexCoords;
	};

}