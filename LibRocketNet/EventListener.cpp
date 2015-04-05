#include "Stdafx.h"
#include <Rocket/Core/EventListenerInstancer.h>
#include <Rocket/Core/EventListener.h>
#include "EventListener.h"


namespace LibRocketNet {

	LibRocketNetEventInstancer::LibRocketNetEventListener::LibRocketNetEventListener(const Rocket::Core::String &value) {
		_value = Util::ToNetString(value);
	}

	void LibRocketNetEventInstancer::LibRocketNetEventListener::ProcessEvent(Rocket::Core::Event& evt) {
		Core::FireScriptEvent(_value, evt);
	}

	void LibRocketNetEventInstancer::LibRocketNetEventListener::OnDetach(Rocket::Core::Element* element)
	{
		delete this;
	}

	Rocket::Core::EventListener* LibRocketNetEventInstancer::InstanceEventListener(const Rocket::Core::String& value, Rocket::Core::Element* element){
		return new LibRocketNetEventListener(value);
	}

	void LibRocketNetEventInstancer::Release(){
		delete this;
	}

	LibRocketNetEventInstancer::LibRocketNetEventInstancer() {}
}