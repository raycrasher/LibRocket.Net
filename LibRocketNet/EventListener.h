#pragma once

#include "Core.h"
#include "Util.h"
#include <Rocket/Core/EventListenerInstancer.h>
#include <Rocket/Core/EventListener.h>

namespace LibRocketNet {
	class LibRocketNetEventInstancer : public Rocket::Core::EventListenerInstancer {
	public:

		class LibRocketNetEventListener: public Rocket::Core::EventListener {
			const Rocket::Core::String *_value;
		public:
			LibRocketNetEventListener(const Rocket::Core::String &value) {
				_value = &value;
			}

			virtual void ProcessEvent(Rocket::Core::Event& evt) {
				Core::FireScriptEvent(Util::ToNetString(*_value), evt);
			}

			virtual void OnDetach(Rocket::Core::Element* element)
			{
				delete this;
			}

		};

		virtual Rocket::Core::EventListener* InstanceEventListener(const Rocket::Core::String& value, Rocket::Core::Element* element){
			return new LibRocketNetEventListener(value);
		}

		virtual void Release(){
			delete this;
		}
	};
}