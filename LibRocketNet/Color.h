#pragma once;

#include "Rocket/Core/Colour.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace LibRocketNet {

	[StructLayout(LayoutKind::Sequential)]
	public value class Color {
	public:
		Byte R, G, B, A;
	internal:
		Color(Rocket::Core::Colourb c) {
			R = c.red;
			G = c.green;
			B = c.blue;
			A = c.alpha;
		}
	};

}