#pragma once

#include "LibRocketNet.h"



namespace LibRocketNet {


namespace Util {
	String^ ToNetString(const Rocket::Core::String& const s);
	Rocket::Core::String ToRocketString(const String^ const s);
}

}