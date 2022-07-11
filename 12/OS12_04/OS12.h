#pragma once
#include <objbase.h>
#include <iostream>
#define OS12HANDEL void*

namespace OS12 {
	OS12HANDEL Init();
	namespace ADDER {
		double Add(OS12HANDEL h, double x, double y);
		double Sub(OS12HANDEL h, double x, double y);
	}
	namespace MULTIPLIER {
		double Mul(OS12HANDEL h, double x, double y);
		double Div(OS12HANDEL h, double x, double y);

	}
	void Dispose(OS12HANDEL h); // завершение работы с OS12
}