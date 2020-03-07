#include "pch.h"
#include "CppUnitTest.h"
#include "../Individual_Homework/geos.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IndividualTest
{
	TEST_CLASS(IndividualTest)
	{
	public:
		// 题目样例
		TEST_METHOD(Example1)
		{
			Individual* ind = new Individual;
			ind->save(0, 0, 1, 1);
			Assert::AreEqual(0, ind->calc());
		}

		TEST_METHOD(Example2)
		{
			Individual* ind = new Individual;
			ind->save(0, 0, 1, 1);
			ind->save(1, 0, 0, 1);
			ind->save(1, 2, 2, 0);
			Assert::AreEqual(3, ind->calc());
		}

		TEST_METHOD(Example3)
		{
			Individual* ind = new Individual;
			ind->save(0, 0, 1, 1);
			ind->save(0, 0, 0, 1);
			ind->save(0, 0, -1, 0);
			Assert::AreEqual(1, ind->calc());
		}

		// 边界条件
		TEST_METHOD(Boundary1)
		{
			Individual* ind = new Individual;
			ind->save(-99999, 99999, 99999, 99998);
			ind->save(-99999, 99998, 99998, 99997);
			Assert::AreEqual(1, ind->calc());
		}

		TEST_METHOD(Boundary2)
		{
			Individual* ind = new Individual;
			ind->save(-99999, 99999, 99999, 99998);
			ind->save(-99999, 99998, 99999, 99997);
			Assert::AreEqual(0, ind->calc());
		}

		TEST_METHOD(Boundary3)
		{
			Individual* ind = new Individual;
			ind->save(2, 3, 3, 5);
			ind->save(5, 3, 6, 5);
			ind->save(19, 3, 20, 5);
			Assert::AreEqual(0, ind->calc());
		}

		TEST_METHOD(Boundary4)
		{
			Individual* ind = new Individual;
			ind->save(2, 5, 3, 5);
			ind->save(2, 2, 3, 2);
			ind->save(-2, 1, -2, -10000);
			Assert::AreEqual(2, ind->calc());
		}

		TEST_METHOD(Boundary5)
		{
			Individual* ind = new Individual;
			ind->save(2, 5, 2, -1);
			ind->save(3, 2, 3, 4);
			ind->save(-2, 1, -2, -10000);
			Assert::AreEqual(0, ind->calc());
		}

		//复杂情况测试
		TEST_METHOD(Complex1)
		{
			Individual* ind = new Individual;
			ind->save(-9999, -9999, 9999, 9999);
			ind->save(0, 3, -3, -3);
			ind->save(1, 9, 0, 5);
			ind->save(0, 0, -6, 36);
			ind->save(0, 3, 3, 0);
			Assert::AreEqual(10, ind->calc());
		}

		TEST_METHOD(Complex2)
		{
			Individual* ind = new Individual;
			ind->save(-9999, -9999, 9999, 9999);
			ind->save(3, 4, -3, -4);
			ind->save(98, -99, -98, 99);
			ind->save(-114, 514, 114, -514);
			ind->save(1926, 817, -1926, -817);
			Assert::AreEqual(1, ind->calc());
		}

		TEST_METHOD(Complex3)
		{
			Individual* ind = new Individual;
			ind->save(1, 1, -2, -2);
			ind->save(1, 3, -2, 0);
			ind->save(1, 5, -2, 2);
			ind->save(1, 7, -2, 4);
			ind->save(-1, 1, -2, -2);
			ind->save(-1, 3, -2, 0);
			ind->save(-1, 5, -2, 2);
			ind->save(-1, 7, -2, 4);
			Assert::AreEqual(16, ind->calc());
		}
	};

	TEST_CLASS(ExtraTest) {
	public:
		TEST_METHOD(Example1) {
			Individual* ind = new Individual;
			ind->save(1, 0, 2);
			ind->save(2, 2, 1);
			ind->save(3, -2, 6);
			ind->save(-1, 4, 4, -1);
			Assert::AreEqual(6, ind->calc());
		}
	};
}
