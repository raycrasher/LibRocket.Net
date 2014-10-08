// LibRocketNet.h

#pragma once

#include "Rocket/Core.h"

using namespace System;

typedef Rocket::Core::String RocketString;
typedef Rocket::Core::Element RocketElement;
typedef Rocket::Core::Event RocketEvent;


namespace LibRocketNet {

	public ref class LibRocket abstract {
	public:
		static bool ThrowIfElementDestroyed;

		static void Initialize();
		
	};
}