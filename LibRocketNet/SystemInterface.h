#pragma once

#include "LibRocketNet.h"

ROCKET_FORWARD_DECLARE(class SystemInterface);



namespace LibRocketNet {
	public enum class LogType
	{
		Always = 0,
		Error,
		Assert,
		Warning,
		Info,
		Debug,
		Count
	};


	public ref class SystemInterface abstract
	{
	internal:
		InternalSystemInterface *SystemInterfacePtr;
		bool _methodUnused;
	protected:
		SystemInterface(void);
	public:
		virtual ~SystemInterface();
		virtual float GetElapsedTime() abstract;
		virtual int TranslateString(String^% translated, String^ input) { _methodUnused = true; }
		virtual void JoinPath(String^% translatedPath, String^ documentPath, String^ path) { _methodUnused = true; }
		virtual bool LogMessage(LogType type, String^ message) { _methodUnused = true; }
		virtual void ActivateKeyboard() { _methodUnused = true; }
		virtual void DeactivateKeyboard() { _methodUnused = true; }	
	};



}