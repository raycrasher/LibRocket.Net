#include "stdafx.h"
#include <gcroot.h>
#include "Rocket/Core/SystemInterface.h"

#include "SystemInterface.h"
#include "Util.h"

namespace LibRocketNet {

	class InternalSystemInterface: public Rocket::Core::SystemInterface {
	public:

		gcroot<LibRocketNet::SystemInterface^> Interface;

		
		virtual float GetElapsedTime() {
			return Interface->GetElapsedTime();
		}

		virtual int TranslateString(String& translated, const String& input) override {
			Interface->_methodUnused = false;
			String^ str;
			int retval = Interface->TranslateString(str, Util::ToNetString(input));
			if (Interface->_methodUnused) return Rocket::Core::SystemInterface::TranslateString(translated, input);
			translated = Util::ToRocketString(str);
			return retval;
		}

	};

	SystemInterface::SystemInterface(void)
	{
		SystemInterfacePtr = new InternalSystemInterface();
		SystemInterfacePtr->Interface = this;
		_methodUnused = false;
	}
}