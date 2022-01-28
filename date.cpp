#include "date.h"
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

Date::Date(const int& year,
		const int& month,
		const int& day) :
		day_(day), month_(month),
		year_(year) {}

tuple<int, int, int> Date::ReturnDate() const {
		return make_tuple(
			day_, month_, year_);
}

ostream& operator << (ostream& os,
	const Date& d) {
	tuple<int, int, int> t =
		d.ReturnDate();

	os << setw(4) << setfill('0') << 
		get<2>(t) << "-" <<
		setw(2) << setfill('0') << 
		get<1>(t) << "-" <<
		setw(2) << setfill('0') <<
		get<0>(t);

	return os;
}

Date ParseDate(istream& is) {
	string s;
	is >> s;

	string full_date = s.substr(
		s.find(' ') + 1);

	int year = stoi(full_date.substr(0, 
		full_date.find('-')));

	string month_day = full_date.substr(
		full_date.find('-') + 1);

	int month = stoi(month_day.substr(0,
		month_day.find('-')));

	string day_event = month_day.substr(
		month_day.find('-') + 1);

	int day = stoi(day_event.substr(0,
		day_event.find('-')));

	return Date(year, month, day);
}

bool operator < (const Date& lhs, const Date& rhs) {
	int l_year = get<2>(lhs.ReturnDate());
	int l_month= get<1>(lhs.ReturnDate());
	int l_day = get<0>(lhs.ReturnDate());

	int r_year = get<2>(rhs.ReturnDate());
	int r_month = get<1>(rhs.ReturnDate());
	int r_day = get<0>(rhs.ReturnDate());

	if (l_year < r_year) {
		return true;
	}
	else if (l_year > r_year) {
		return false;
	}

	if (l_month < r_month) {
		return true;
	}
	else if (l_month > r_month) {
		return false;
	}

	if (l_day < r_day) {
		return true;
	}
	else if (l_day > r_day) {
		return false;
	}

	return false;
}

bool operator == (const Date& lhs, const Date& rhs) {
	return (lhs.ReturnDate() == rhs.ReturnDate());
}