#pragma once

using namespace System;
using namespace System::Collections::Generic;

namespace LibRocketNet {

ref class SystemInterface;
ref class RenderInterface;
ref class FileInterface;
ref class Context;
ref class Plugin;

public ref class Core abstract 
{
	static SystemInterface^ _systemInterface;
	static RenderInterface^ _renderInterface;
	static FileInterface^ _fileInterface;

	static System::Collections::Generic::Dictionary<IntPtr,Context^>^ _contexts;

public:
	static bool Initialize();
	static void Shutdown();
	static property String^ Version { String^ get(); }

	static property SystemInterface^ SystemInterface { LibRocketNet::SystemInterface^ get(); void set(LibRocketNet::SystemInterface^ s); }
	static property RenderInterface^ RenderInterface { LibRocketNet::RenderInterface^ get(); void set(LibRocketNet::RenderInterface^ s); }
	static property FileInterface^ FileInterface { LibRocketNet::FileInterface^ get(); void set(LibRocketNet::FileInterface^ s); }

	static Context^ CreateContext(String^ name, Vector2i dimensions, LibRocketNet::RenderInterface^ renderInterface);
	static Context^ CreateContext(String^ name, Vector2i dimensions) { return CreateContext(name, dimensions, nullptr); }

	static Context^ GetContext(String^ name);
	static Context^ GetContext(int index);

	static property int NumContexts { int get(); }
	
	static void ReleaseCompiledGeometries();
	static void ReleaseTextures();
};

}
