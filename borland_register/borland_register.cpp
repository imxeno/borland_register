// borland_register.cpp : Defines the entry point for the application.
//

#include "borland_register.h"
#include "asmjit/asmjit.h"

using namespace asmjit;
using namespace x86;

borland_register::translator::translator() : runtime_(new JitRuntime())
{
}

void* borland_register::translator::cdecl_to_register(void* func, const int argc) const
{
	CodeHolder code;
	code.init(runtime_->environment());
	Assembler a(&code);
	
	auto offset = 0;
	for(auto i = 3; i < argc; i++)
	{
		a.push(ptr(esp, 16 + offset * 2, 4));
		
		offset += 4;
	}

	if(argc > 2)
	{
		a.mov(ecx, ptr(esp, 12 + offset, 4));
	}

	if (argc > 1)
	{
		a.mov(edx, ptr(esp, 8 + offset, 4));
	}

	if (argc > 0)
	{
		a.mov(eax, ptr(esp, 4 + offset, 4));
	}

	a.call(func);
	a.ret();

	void* proxy_address;
	const auto err = runtime_->add(&proxy_address, &code);
	
	if(err)
	{
		return nullptr;
	}

	return proxy_address;
}

void* borland_register::translator::register_to_cdecl(void* func, const int argc) const
{
	CodeHolder code;
	code.init(runtime_->environment());
	Assembler a(&code);

	for (auto i = 3; i < argc; i++)
	{
		const auto offset = ((i - 3) * 8) + 4;
		a.push(ptr(esp, offset, 4));
	}

	if (argc > 2)
	{
		a.push(ecx);
	}

	if (argc > 1)
	{
		a.push(edx);
	}

	if (argc > 0)
	{
		a.push(eax);
	}

	
	a.call(func);
	a.add(esp, argc * 4);

	// Remove parameters from stack but preserve return address and EAX
	a.push(eax);
	a.mov(eax, ptr(esp, 4));
	a.mov(ptr(esp, (argc - 2) * 4), eax);
	a.pop(eax);
	a.add(esp, (argc - 3) * 4);

	a.ret();

	void* proxy_address;
	const auto err = runtime_->add(&proxy_address, &code);
	
	if (err)
	{
		return nullptr;
	}
	
	return proxy_address;
}

bool borland_register::translator::release(void* func) const
{
	return runtime_->release(func) == 0;
}
