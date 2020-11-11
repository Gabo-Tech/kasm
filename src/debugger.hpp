#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "common.hpp"
#include "virtualMachine.hpp"

namespace kasm
{
	class Debugger : public VirtualMachine
	{
	public:
		Debugger() {};

		void loadProgram(const std::string& programPath, const std::string& symbolTablePath);
		void setBreakpoint(const std::string& label);
		void setBreakpoint(std::uint32_t address);
		void removeBreakpoint(const std::string& label);
		void removeBreakpoint(std::uint32_t address);
		void step();
		std::uint32_t peakRegister(Register reg);
		std::uint32_t peakMemory(std::uint32_t address);
	private:
		std::unordered_map<std::string, std::uint32_t> symbolTable;
	};
}
