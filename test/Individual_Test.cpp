#include "pch.h"
#include "CppUnitTest.h"
#include "../Individual_Homework/geos.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IndividualTest
{
	TEST_CLASS(IndividualTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Individual* ind = new Individual;
			ind->save(0, 0, 1, 1);
			Assert::AreEqual(0, ind->calc());
		}

		TEST_METHOD(TestMethod2)
		{
			Individual* ind = new Individual;
			ind->save(0, 0, 1, 1);
			ind->save(1, 0, 0, 1);
			ind->save(1, 2, 2, 0);
			Assert::AreEqual(3, ind->calc());
		}

		TEST_METHOD(TestMethod3)
		{
			Individual* ind = new Individual;
			ind->save(0, 0, 1, 1);
			ind->save(0, 0, 0, 1);
			ind->save(0, 0, -1, 0);
			Assert::AreEqual(1, ind->calc());
		}
	};
}
