#pragma once

using namespace System;
ref class Weakness
{
	public:
		String^ toString();
		enum class Priority { Low, Normal, Critical };
		enum class Risk { Low, Med, High };

		Weakness();
		Weakness(String^ n, Priority p, Risk r, String^ s);
	private:
		String^ name; 
		Priority priority;
		Risk risk; 
		String^ solution;
};

