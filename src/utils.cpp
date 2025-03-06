#include "utils.h"
#include <chrono>

time_t epochTimeStamp()
{
	auto now = std::chrono::system_clock::now();
	return std::chrono::system_clock::to_time_t(now);
}
