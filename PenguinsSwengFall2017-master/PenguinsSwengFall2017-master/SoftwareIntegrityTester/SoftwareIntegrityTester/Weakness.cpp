#include "Weakness.h"
#include <iostream>

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Collections::Generic;		

		Weakness::Weakness() {
			name = "default name";
			priority = Priority::Low;
			risk = Risk::Low;
			solution = "default solution";
		}
		Weakness::Weakness(String^ n, Priority p, Risk r, String^ s) {			
			name = n;
			priority = p;
			risk = r;
			solution = s;
		}

		String^ Weakness::toString() {
				return name + "\nPriority: " + priority.ToString() + "\nRisk: " + risk.ToString() + "\nSolution:\n" + solution + "\n";
			}
