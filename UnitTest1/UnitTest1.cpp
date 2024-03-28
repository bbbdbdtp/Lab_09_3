#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_09_3/Main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:

		TEST_METHOD(TestSearch)
		{
			Note S[3];
			int B[3][3];

			S[0].surname = "Doe";
			S[0].name = "John";
			S[0].number = "0679584251";
			B[0][0] = 1;
			B[0][1] = 2;
			B[0][2] = 2000;

			S[1].surname = "Smith";
			S[1].name = "Jane";
			S[1].number = "0579486324";
			B[1][0] = 3;
			B[1][1] = 4;
			B[1][2] = 1999;

			S[2].surname = "Johnson";
			S[2].name = "Robert";
			S[2].number = "0975824657";
			B[2][0] = 5;
			B[2][1] = 6;
			B[2][2] = 2001;

			string searchName = "Smith";
			search(S, B, 3, searchName);
		}
	};
}