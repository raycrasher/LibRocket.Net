#pragma once;

using namespace System;
using namespace System::Runtime::InteropServices;

namespace LibRocketNet {

	[StructLayout(LayoutKind::Sequential)]
	public value class Color {
		float R, G, B, A;
	};

}