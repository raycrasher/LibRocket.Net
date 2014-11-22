#pragma once

#include "LibRocketNet.h"


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

	class InternalSystemInterface;

	public ref class SystemInterface abstract
	{
	internal:
		InternalSystemInterface *_nativeInterface;
		bool _methodUnused;
		void SetCore();
	protected:
		SystemInterface(void);
	public:
		virtual ~SystemInterface();
	public protected:
		
		virtual float GetElapsedTime() abstract;
		virtual int TranslateString(String^% translated, String^ input) { _methodUnused = true; return 0; }
		virtual void JoinPath(String^% translatedPath, String^ documentPath, String^ path) { _methodUnused = true; }
		virtual bool LogMessage(LogType type, String^ message) { _methodUnused = true; return false; }
		virtual void ActivateKeyboard() { _methodUnused = true; }
		virtual void DeactivateKeyboard() { _methodUnused = true; }	

		
	};



}