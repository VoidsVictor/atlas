#include <emscripten.h>

extern "C"
{
	EMSCRIPTEN_KEEPALIVE
	int contract_function(int x)
	{
		return x * 2;
	}
}
