#pragma once

#include <chrono>
#include <memory>

using Duration = std::chrono::duration<double, std::milli>;

struct StatData {
	Duration lastGeneretionDuration = Duration::zero();
	unsigned int maxIterations = 0;
};

class StatService {
public:
	StatService();
	StatData data;
};
