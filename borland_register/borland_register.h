// borland_register.h : Include file for standard system include files,
// or project specific include files.

#ifndef BORLAND_REGISTER_H
#define BORLAND_REGISTER_H
#include <memory>

namespace asmjit {
	// ReSharper disable once CppInconsistentNaming
	class JitRuntime;
}
	
namespace borland_register
{
	class translator {
	public:
		translator();
		void* cdecl_to_register(void* func, int argc) const;
		void* register_to_cdecl(void* func, int argc) const;
		bool release(void* func) const;
	private:
		std::unique_ptr<asmjit::JitRuntime> runtime_;
	};
}

#endif