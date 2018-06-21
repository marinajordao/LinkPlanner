#include "bit_decision.h"

void BitDecision::initialize(void) {
	outputSignals[0]->setSymbolPeriod(0.001);
	outputSignals[0]->setSamplingPeriod(0.001);
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[1]->getFirstValueToBeSaved());
	outputSignals[0]->setSamplesPerSymbol(1);

	outputSignals[1]->setSymbolPeriod(0.001);
	outputSignals[1]->setSamplingPeriod(0.001);
	outputSignals[1]->setFirstValueToBeSaved(inputSignals[1]->getFirstValueToBeSaved());
	outputSignals[1]->setSamplesPerSymbol(1);
}

bool BitDecision::runBlock() {
	bool alive{ false };

	int ready0 = inputSignals[0]->ready();
	int ready1 = inputSignals[1]->ready();

	int ready = min(ready0, ready1);

	int space0 = outputSignals[0]->space();
	int space1 = outputSignals[1]->space();

	int space = min(space0, space1);

	int process = min(ready,space);

	if (process > 0) {
		for (auto n = 0; n < process; n++) {
			t_real bitIn;
			t_real logicValue;
			inputSignals[0]->bufferGet(&bitIn);
			inputSignals[1]->bufferGet(&logicValue);

			if (logicValue == 1.0) {
				if(bitIn == 1.0)
					outputSignals[0]->bufferPut((t_binary)1);
				else if(bitIn == 0.0)
					outputSignals[0]->bufferPut((t_binary)0);
				else if(bitIn == -2.0)
					outputSignals[0]->bufferPut((t_binary)2);
				else if(bitIn == -1.0)
					outputSignals[0]->bufferPut((t_binary)3);
			//	cout << "1: " << bitIn << "\n";
			}
			else {
				if (bitIn == 1.0)
					outputSignals[1]->bufferPut((t_binary)1);
				else if (bitIn == 0.0)
					outputSignals[1]->bufferPut((t_binary)0);
				else if (bitIn == -2.0)
					outputSignals[1]->bufferPut((t_binary)2);
				else if (bitIn == -1.0)
					outputSignals[1]->bufferPut((t_binary)3);
			//	cout << "0: " << bitIn << "\n";
			}
				
		}
		alive = true;
	}

	return alive;
}