#include "database.h"
#include "print.h"
#include "date.h"
#include <iostream>
#include <algorithm>
using namespace std;

Database::Database() {}

void Database::Add(const Date& date,
	const string& event) {
	if (!database_[date].count(event)) {
		not_sorted_db[date].push_back(event);
	}
	database_[date].insert(event);
	data_in_db[{ date, event }] = true;
	is_valid_date[date] = true;
//	date_to_event.insert({ date, event });
}

void Database::Print(ostream& stream) const {
	for (auto& kv : not_sorted_db) {
		for (auto& event : kv.second) {
			if (data_in_db.at({ kv.first, event })) {
				stream << kv.first << " " << event << endl;
			}
		}
	}
	//for (const auto& item : not_sorted_db) {
	//	stream << item;
	//}
}

vector<pair<Date, string>> Database::FindIf(
	std::function<bool(Date, string)>
	predicate) const {
	vector<pair<Date, string>> to_return;
	for (const auto& item : not_sorted_db) {
		for (const string& event : item.second) {
			if (predicate(item.first, event) && data_in_db.at({item.first, event})) {
				to_return.push_back({item.first, event});
			}
		}
	}

	return to_return;
}

int Database::RemoveIf(std::function<bool(Date, string)>
		predicate) {
	int counter = 0;
	set<pair<Date, string>> to_erase;

	for (auto& kv: database_) {
		int count_valid_events = 0;
		for (auto& event : kv.second) {
			if (predicate(kv.first, event) && data_in_db[{kv.first, event}]) {
				data_in_db[{kv.first, event}] = false;
				counter++;
			} 
			count_valid_events += data_in_db[{kv.first, event}];
		}
		if (!count_valid_events) {
			is_valid_date[kv.first] = 0;
		}
		
		//if (kv.second.empty()) {
		//	is_valid_date[kv.first] = false;
		//}

//		if (predicate(kv.first, kv.second)) {
			
			
			/*to_erase.insert(item);
			auto it_set = database_.find(item.first);
			auto it_element = it_set->second.find(item.second);
			it_set->second.erase(it_element);
			
			auto it_vec = not_sorted_db.find(item.first);
			auto it_erase = stable_partition(begin(it_vec->second),
				end(it_vec->second), [item](const string& var) {
					return (var == item.second);
				});

			it_vec->second.erase(begin(it_vec->second), it_erase);
			++counter;*/
//		}		
	}

	//for (auto& element : to_erase) {
	//	date_to_event.erase(element);
	//}

	return counter;




	/*
	for (auto& item : database_) {
		auto it = not_sorted_db.find(
			item.first);
		set<string> to_iterate = item.second;
		for (string event : to_iterate) {
			if (predicate(item.first, event)) {
				// Delete from set
				item.second.erase(event);
				// Delete from vector
				stable_partition(begin(it->second),
					end(it->second), [event](const string& s)
					{return (s != event); });

				auto erase_it = find(begin(it->second),
					end(it->second), event);
				it->second.erase(erase_it end(it->second));

				counter++;
			}
		}
	}*/

	return counter;
}

pair<Date, string> Database::Last(const Date& date) const {
	auto date_iter = is_valid_date.upper_bound(date);

	if (date_iter == is_valid_date.begin()) {
		throw(invalid_argument("No entries"));
	} else {
		date_iter = prev(date_iter);
	}

	while (true) {
		if (!date_iter->second) {
			if (date_iter == begin(is_valid_date)) {
				throw(invalid_argument("No entries"));
			}
			date_iter = prev(date_iter);
		} else {
			break;
		}
	}
	auto iter = not_sorted_db.find(date_iter->first);
	vector<string>::const_iterator vector_it = end(iter->second) - 1;

	while (true) {
		if (data_in_db.at({ iter->first, *vector_it })) {
			break;
		} else {
			vector_it = prev(vector_it);
		}
	}
	return { iter->first, *vector_it };
}

ostream& operator << (ostream& os,
	const pair<const Date, set<string>>& p) {
	for (const string& s : p.second) {
		os << p.first << " " << s << endl;
	}

	return os;
}

ostream& operator << (ostream& os, const pair<Date, string>& p) {
	os << p.first << " " << p.second;

	return os;
}

ostream& operator << (ostream& os,
	const pair<const Date, vector<string>>& p) {
	for (const string& s : p.second) {
		os << p.first << " " << s << endl;
	}

	return os;
}