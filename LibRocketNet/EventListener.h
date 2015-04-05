#pragma once

#include "Core.h"
#include "Util.h"
#include <Rocket/Core/EventListenerInstancer.h>
#include <Rocket/Core/EventListener.h>

namespace LibRocketNet {
	class LibRocketNetEventInstancer : public Rocket::Core::EventListenerInstancer {
	public:

		class LibRocketNetEventListener: public Rocket::Core::EventListener {
			gcroot<String^> _value;
		public:
			LibRocketNetEventListener(const Rocket::Core::String &value);

			virtual void ProcessEvent(Rocket::Core::Event& evt);

			virtual void OnDetach(Rocket::Core::Element* element);

		};

		LibRocketNetEventInstancer();

		virtual Rocket::Core::EventListener* InstanceEventListener(const Rocket::Core::String& value, Rocket::Core::Element* element);

		virtual void Release();
	};
}