#pragma once

#include "LibRocketNet.h"
#include "Rocket/Core/Plugin.h"



namespace LibRocketNet {
class LibRocketPlugin : public Rocket::Core::Plugin
{
public:
	virtual void OnElementDestroy(Rocket::Core::Element *elem);
};

}