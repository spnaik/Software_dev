#include "Shapes.h"
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include<iterator>
#include<numeric>
#include<algorithm>
#include<cmath>
#include<set>
#include<map>

// Add other #include(s) and using statements...
using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::vector;
using std::for_each;
using std::transform;
using std::sort;
using std::back_inserter;
using std::set;
using std::map;
using std::min_element;
using std::max_element;
using std::make_pair;

// numeric algorithms:
using std::accumulate;
using std::inner_product;

//enum type


void shapeShifter();


int main()
{
	shapeShifter();

	return 0;
}

// Assignment 4:
void shapeShifter()
{
	
	// Follow instructions for the assignment here
	vector<unique_ptr<Shape> > shapes;
	shapes.push_back(make_unique<Rectangle>(20.5, 5.6));
	shapes.push_back(make_unique<Rectangle>(12.0, 52.0));
	shapes.push_back(make_unique<Circle>(10.0));
	shapes.push_back(make_unique<Circle>(8.7));
	shapes.push_back(make_unique<Triangle>(20.5, 5.6));
	shapes.push_back(make_unique<Triangle>(12.0, 52.0));
	shapes.push_back(make_unique<Trapezoid>(10.6, 8.74, 5.863));
	shapes.push_back(make_unique<Trapezoid>(12.0, 4.0, 15.0));

	vector<double> area;
	auto iter = shapes.begin();
	for (iter = shapes.begin(); iter != shapes.end(); ++iter)
	{
		print((*(*iter)).whatAmI());
		print((*(*iter))());
		print('\n');
		area.push_back((*(*iter))());
	}
	print("\n"); // one vertical space

	vector<double> squares;
	auto mySquare = [](double x) {return x * x; }; // creating a lambda
	transform(area.begin(), area.end(), back_inserter(squares), mySquare);
	sort(squares.begin(), squares.end());
	print("Sorted Squares of Areas:");
	print("\n");
	for_each(squares.begin(), squares.end(), print<double>);
	print("\n\n");


	enum RtnType
	{
		MEAN,
		NORM,
		MAX,
		MIN

	};
	map<RtnType, double> results;
	double mean = accumulate(squares.begin(), squares.end(), 0.0) / squares.size();
	double norm = std::sqrt(inner_product(squares.begin(), squares.end(), squares.begin(), 0.0));
	results.insert(make_pair(MEAN, mean));
	results.insert(make_pair(NORM, norm));
	results.insert(make_pair(MAX, *std::max_element(squares.begin(), squares.end())));
	results.insert(make_pair(MIN, *std::min_element(squares.begin(), squares.end())));
	print("Mean, Norm, Max, and Min values of the vector of square areas are : \n");

	for (auto mIter = results.begin(); mIter != results.end(); ++mIter)
	{
		print(mIter->second);
	}
	print("\n\n"); // two new lines 

}





