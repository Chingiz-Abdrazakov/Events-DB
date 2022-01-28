#pragma once
#include <iostream>
#include <tuple>
#include <memory>

using namespace std;

class Date {
public:
	Date(const int& year,
		const int& month, const int& day);
	
	tuple<int, int, int> ReturnDate() const;
private:
	const int day_, month_, year_;
};

ostream& operator <<
(ostream& os, const Date& d);

Date ParseDate(istream& is);

bool operator < (const Date& lhs, const Date& rhs);
bool operator == (const Date& lhs, const Date& rhs);
// bool operator > (const Date& lhs, const Date& rhs);
// bool operator != (const Date& lhs, const Date& rhs);