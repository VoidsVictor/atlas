// Engine to execute smart contracts securely
// BTW The name is a homage to Colossus - World's first electronic digital computer

// #include "Colossus.hpp"
#include <iostream>
#include <sstream>
#include <wasmedge/wasmedge.h>

#include "Colossus/compiler.hpp"

using namespace std;

int main(int argc, const char* argv[])
{
	// Compile the file first
	ostringstream oss;
	oss << "contracts/" << argv[1] << ".wasm";

	if (compile(argv[1]))
	{
		// Clearing stream
		oss.clear();
		oss.str("");

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
		WasmEdge_String FuncName = WasmEdge_StringCreateByCString("contract");
		/* Run the WASM function from file. */
		oss << "bin/contracts/" << argv[1] << "_aot.wasm";
		WasmEdge_Result Res = WasmEdge_VMRunWasmFromFile(VMCxt, oss.str().c_str(), FuncName, Params, 1, Returns, 1);

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
	else
	{
		cout << "Failed to compile to AOT. Exiting..." << endl;
		return 1;
	}
}