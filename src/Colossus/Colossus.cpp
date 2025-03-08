// Engine to execute smart contracts securely
// BTW The name is a homage to Colossus - World's first electronic digital computer

// #include "Colossus.hpp"

#include <iostream>
#include <wasmedge/wasmedge.h>

int main(int argc, const char* argv[])
{
	/* Create the configure context and add the WASI support. */
	/* This step is not necessary unless you need WASI support. */
	WasmEdge_ConfigureContext* ConfCxt = WasmEdge_ConfigureCreate();
	WasmEdge_ConfigureAddHostRegistration(ConfCxt, WasmEdge_HostRegistration_Wasi);
	/* The configure and store context to the VM creation can be NULL. */
	WasmEdge_VMContext* VMCxt = WasmEdge_VMCreate(ConfCxt, NULL);

	/* The parameters and returns arrays. */
	WasmEdge_Value Params[1] = {WasmEdge_ValueGenI32(32)};
	WasmEdge_Value Returns[1];

	/* Function name. */
	WasmEdge_String FuncName = WasmEdge_StringCreateByCString("fib");
	/* Run the WASM function from file. */
	WasmEdge_Result Res = WasmEdge_VMRunWasmFromFile(VMCxt, argv[1], FuncName, Params, 1, Returns, 1);

	if (WasmEdge_ResultOK(Res))
	{
		printf("Get result: %d\n", WasmEdge_ValueGetI32(Returns[0]));
	}
	else
	{
		printf("Error message: %s\n", WasmEdge_ResultGetMessage(Res));
	}

	/* Resources deallocations. */
	WasmEdge_VMDelete(VMCxt);
	WasmEdge_ConfigureDelete(ConfCxt);
	WasmEdge_StringDelete(FuncName);
	return 0;
}