#pragma once

#include "LibRocketNet.h"



namespace LibRocketNet {


namespace Util {
	String^ ToNetString(const RocketString& const s);
	RocketString ToRocketString(const String^ const s);
}

}