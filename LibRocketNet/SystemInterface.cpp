#include "stdafx.h"
#include <gcroot.h>
#include "Rocket/Core/SystemInterface.h"

#include "LibRocketNet.h"
#include "SystemInterface.h"
#include "Util.h"

namespace LibRocketNet {

	class InternalSystemInterface: public Rocket::Core::SystemInterface {
	public:

		gcroot<LibRocketNet::SystemInterface^> Interface;

		
		virtual float GetElapsedTime() {
			return Interface->GetElapsedTime();
		}

		virtual int TranslateString(RocketString& translated, const RocketString& input) override {
			Interface->_methodUnused = false;
			String^ str;
			int retval = Interface->TranslateString(str, Util::ToNetString(input));
			if (Interface->_methodUnused) return Rocket::Core::SystemInterface::TranslateString(translated, input);
			translated = Util::ToRocketString(str);
			return retval;
		}

		virtual void JoinPath(RocketString& translated_path, const RocketString& document_path, const RocketString& path) {
			String^ tPath;
			Interface->_methodUnused = false;
			Interface->JoinPath(tPath, Util::ToNetString(document_path), Util::ToNetString(path));
			if (Interface->_methodUnused) Rocket::Core::SystemInterface::JoinPath(translated_path, document_path,path);
			else translated_path = Util::ToRocketString(tPath);
		}

		virtual bool LogMessage(Rocket::Core::Log::Type type, const RocketString& message) {
			Interface->_methodUnused = false;
			auto retval = Interface->LogMessage((LogType)type, Util::ToNetString(message));
			if (Interface->_methodUnused) return Rocket::Core::SystemInterface::LogMessage(type,message);
			return retval;
		}

		virtual void ActivateKeyboard() {
			Interface->_methodUnused = false;
			Interface->ActivateKeyboard();
			if (Interface->_methodUnused) Rocket::Core::SystemInterface::ActivateKeyboard();
		}

		virtual void DeactivateKeyboard() {
			Interface->_methodUnused = false;
			Interface->DeactivateKeyboard();
			if (Interface->_methodUnused) Rocket::Core::SystemInterface::DeactivateKeyboard();
		}

	};

	SystemInterface::SystemInterface(void)
	{
		SystemInterfacePtr = new InternalSystemInterface();
		SystemInterfacePtr->Interface = this;
		_methodUnused = false;
	}

	SystemInterface::~SystemInterface() {
		delete SystemInterfacePtr;
	}
}