#include "json.hpp"
#include <iostream>

// For convenience
using json = nlohmann::json;

int main()
{
	// Create a JSON object
	json j = "Hello, world!";

	// Store a list (array) in the JSON object under the key "names"
	// j["names"] = {"Alice", "Bob", "Charlie"};

	// Alternatively, you can build the array incrementally:
	json jList = json::array();
	jList.push_back("David");
	jList.push_back("Eve");
	jList.push_back("Frank");

	// Store the incremental list under a different key
	// j["more_names"] = jList;

	// Serialize the JSON object to a string
	std::string serialized = j.dump(4); // '4' gives pretty-printed output with indent of 4 spaces

	// Print the serialized JSON
	std::cout << serialized << std::endl;

	return 0;
}
