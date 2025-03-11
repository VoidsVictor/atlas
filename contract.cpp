#include <emscripten.h>

extern "C"
{
	EMSCRIPTEN_KEEPALIVE
	int contract(int x)
	{
		return x * 2;
	}
}
