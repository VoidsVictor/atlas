// AOT compiler for Colossus.
// This is a simple compiler that compiles the WASM file to a native code.

#include <filesystem>
#include <iostream>
#include <sstream>
#include <wasmedge/wasmedge.h>

using namespace std;

// Function to check for file
// TODO move this to utilities
bool fileExists(const string& filename)
{
	return filesystem::exists(filename);
}

bool compile(string filename)
{
	// Ensure the output directory exists
	filesystem::create_directories("bin/contracts");

	// Checking for existence of AOT compiled file
	ostringstream oss;
	oss << "bin/contracts/" << filename << "_aot.wasm";
	string outputFile = oss.str();

	// TODO ensure that the file that exists is valid as well
	if (fileExists(outputFile))
	{
		return true;
	}

	/* Create the configure context. */
	WasmEdge_ConfigureContext* ConfCxt = WasmEdge_ConfigureCreate();

	/* Result. */
	WasmEdge_Result Res;

	/* Create the compiler context. The configure context can be NULL. */
	WasmEdge_CompilerContext* CompilerCxt = WasmEdge_CompilerCreate(ConfCxt);

	// Creating filepath of the input file
	oss.str("");
	oss.clear();
	oss << "contracts/" << filename << ".wasm";

	string inputFile = oss.str();

	/* Compile the WASM file with input and output paths. */
	Res = WasmEdge_CompilerCompile(CompilerCxt, inputFile.c_str(), outputFile.c_str());

	if (!WasmEdge_ResultOK(Res))
	{
		// cout << "Compilation failed: " << WasmEdge_ResultGetMessage(Res) << endl;
		return false;
	}

	WasmEdge_CompilerDelete(CompilerCxt);
	WasmEdge_ConfigureDelete(ConfCxt);
	return true;
}

int main(int argc, char* argv[])
{
	string filename;

	// Check if filename is provided as a CLI argument
	if (argc > 1)
	{
		filename = argv[1];
	}
	else
	{
		cout << "Enter the filename (without extension): ";
		cin >> filename;
	}

	cout << "Compiling " << filename << "..." << endl;

	if (compile(filename))
	{
		cout << "Compilation successful!" << endl;
	}
	else
	{
		cout << "Compilation failed." << endl;
	}

	return 0;
}
