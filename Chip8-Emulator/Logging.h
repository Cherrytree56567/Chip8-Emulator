#pragma once
#include <string>
#include <iostream>

class Logging {
public:
	Logging(bool enable) : pEnable(enable) {}

	void Error(std::string str) {
		std::cout << "[Chip8::Core] Error: " << str << std::endl;
		exit(-1);
	}

	void Warning(std::string str) {
		std::cout << "[Chip8::Core] Warning: " << str << std::endl;
	}

	void Info(std::string str) {
		if (pEnable) {
			std::cout << "[Chip8::Core] Info: " << str << std::endl;
		}
	}

private:
	bool pEnable;
};

