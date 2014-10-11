// LibRocketNet.h

#pragma once

#define ROCKET_FORWARD_DECLARE(__T) \
namespace Rocket {\
namespace Core {\
	__T; \
}}

using namespace System;

ROCKET_FORWARD_DECLARE(class String);
ROCKET_FORWARD_DECLARE(class Element);
ROCKET_FORWARD_DECLARE(class Event);

typedef Rocket::Core::String RocketString;
typedef Rocket::Core::Element RocketElement;
typedef Rocket::Core::Event RocketEvent;


namespace LibRocketNet {

	public ref class LibRocket abstract {
	public:
		static bool ThrowIfElementDestroyed;	
	};
}