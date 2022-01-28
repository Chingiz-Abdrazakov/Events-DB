#pragma once
#include "date.h"
#include "print.h"
#include <map>
#include <string>
#include <set>
#include <utility>
#include <vector>
#include <functional>

using namespace std;

class Database {
public:
	Database();

	void Add(const Date& date,
		const string& event);

	void Print(ostream& stream) const;

	int RemoveIf(std::function<bool(Date, string)>
		predicate);

	vector<pair<Date, string>> FindIf(
		std::function<bool(Date, string)>
		predicate) const;

	pair<Date, string> Last(const Date& date) const;
private:
	//map<Date, pair<set<string>, vector<set<string>::iterator>>> db;

	map<Date, set<string>> database_;
	map<Date, vector<string>> not_sorted_db;
	map<Date, bool> is_valid_date;

	// set<pair<Date, string>> date_to_event;
	map<pair<Date, string>, bool> data_in_db;
};


ostream& operator << (ostream& os,
	const pair<const Date, set<string>>& p);

ostream& operator << (ostream& os,
	const pair<const Date, vector<string>>& p);

ostream& operator << (ostream& os, const pair<Date, string>& p);