#include "node.h"

using namespace std;

EmptyNode::EmptyNode() {}

DateComparisonNode::DateComparisonNode(
	const Comparison& cmp, const Date& date) :
	cmp_(cmp), date_(date) {}

EventComparisonNode::EventComparisonNode(
	const Comparison& cmp, const string& event) :
	cmp_(cmp), event_(event) {}

LogicalOperationNode::LogicalOperationNode(
	const LogicalOperation& logical_operation,
	const shared_ptr<Node>& left, const
	shared_ptr<Node>& right) :
	log_op_(logical_operation), left_(left),
	right_(right) {}

bool EmptyNode::Evaluate(const Date& date,
	const string& event) const {
	return true;
}

bool DateComparisonNode::Evaluate(const Date& date,
	const string& event) const {
	bool res = false;
	switch (cmp_) {
	case Comparison::Less:
		res = (date < date_);
		break;
	case Comparison::LessOrEqual:
		res = (date < date_ || date == date_);
		break;
	case Comparison::Greater:
		res = (date_ < date);
		break;
	case Comparison::GreaterOrEqual:
		res = (date_ < date || date_ == date);
		break;
	case Comparison::Equal:
		res = (date == date_);
		break;
	case Comparison::NotEqual:
		res = !(date == date_);
		break;
	}

	return res;
}

bool EventComparisonNode::Evaluate(
	const Date& date,
	const string& event) const {
	bool res = false;

	switch (cmp_) {
	case Comparison::Equal:
		res = (event_ == event);
		break;
	case Comparison::NotEqual:
		res = !(event == event_);
		break;
	case Comparison::Greater:
		res = (event > event_);
		break;
	case Comparison::GreaterOrEqual:
		res = (event >= event_);
		break;
	case Comparison::Less:
		res = (event < event_);
		break;
	case Comparison::LessOrEqual:
		res = (event <= event_);
		break;
	default:
		throw(invalid_argument("Unexpected events comparison"));
		break;
	}

	return res;
}

bool LogicalOperationNode::Evaluate(
	const Date& date, const string& event) const {
	bool res = false;
	switch (log_op_) {
	case LogicalOperation::And:
		res = (left_->Evaluate(date, event) && 
			right_->Evaluate(date, event));
		break;
	case LogicalOperation::Or:
		res = (left_->Evaluate(date, event) ||
			right_->Evaluate(date, event));
		break;
	}
	return res;
}