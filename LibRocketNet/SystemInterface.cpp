#include "stdafx.h"
#include <gcroot.h>
#include "Rocket/Core/SystemInterface.h"

#include "LibRocketNet.h"
#include "SystemInterface.h"
#include "Util.h"

namespace LibRocketNet {

	class InternalSystemInterface: public Rocket::Core::SystemInterface {
	public:

		gcroot<LibRocketNet::SystemInterface^> _netInterface;

		
		virtual float GetElapsedTime() {
			return _netInterface->GetElapsedTime();
		}

		virtual int TranslateString(Rocket::Core::String& translated, const Rocket::Core::String& input) override {
			_netInterface->_methodUnused = false;
			String^ str;
			int retval = _netInterface->TranslateString(str, Util::ToNetString(input));
			if (_netInterface->_methodUnused) return Rocket::Core::SystemInterface::TranslateString(translated, input);
			translated = Util::ToRocketString(str);
			return retval;
		}

		virtual void JoinPath(Rocket::Core::String& translated_path, const Rocket::Core::String& document_path, const Rocket::Core::String& path) {
			String^ tPath;
			_netInterface->_methodUnused = false;
			_netInterface->JoinPath(tPath, Util::ToNetString(document_path), Util::ToNetString(path));
			if (_netInterface->_methodUnused) Rocket::Core::SystemInterface::JoinPath(translated_path, document_path,path);
			else translated_path = Util::ToRocketString(tPath);
		}

		virtual bool LogMessage(Rocket::Core::Log::Type type, const Rocket::Core::String& message) {
			_netInterface->_methodUnused = false;
			auto retval = _netInterface->LogMessage((LogType)type, Util::ToNetString(message));
			if (_netInterface->_methodUnused) return Rocket::Core::SystemInterface::LogMessage(type,message);
			return retval;
		}

		virtual void ActivateKeyboard() {
			_netInterface->_methodUnused = false;
			_netInterface->ActivateKeyboard();
			if (_netInterface->_methodUnused) Rocket::Core::SystemInterface::ActivateKeyboard();
		}

		virtual void DeactivateKeyboard() {
			_netInterface->_methodUnused = false;
			_netInterface->DeactivateKeyboard();
			if (_netInterface->_methodUnused) Rocket::Core::SystemInterface::DeactivateKeyboard();
		}

	};

	SystemInterface::SystemInterface(void)
	{
		_nativeInterface = new InternalSystemInterface();
		_nativeInterface->_netInterface = this;
		_methodUnused = false;
	}

	SystemInterface::~SystemInterface() {
		delete _nativeInterface;
	}
}