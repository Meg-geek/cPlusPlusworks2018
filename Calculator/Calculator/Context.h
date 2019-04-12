#pragma once
#include <stack>
#include <map>

class StackFrame
{
public:
	StackFrame(double numb) :number(numb), content('n') {}
	StackFrame(const std::string &parameter) : _parameter(parameter), content('p') {}
	std::string _parameter;
	double number;
	char content; // 'n' or 'p'
};

class Context {
	std::stack <StackFrame> Stack;
	std::map<const std::string, double> parameters;
public:
	void push(double number) { Stack.push(StackFrame(number)); }
	void push(const std::string &parameter) { Stack.push(StackFrame(parameter)); }

	void define(const std::string &parameter, double value) { parameters[parameter] = value; }

	double get_parameter_value(const std::string &parameter) { return parameters[parameter]; }
	bool empty() { return Stack.empty(); }
	void pop() { Stack.pop(); }

	double top() { StackFrame frame = Stack.top(); if (frame.content == 'n') return frame.number; return get_parameter_value(frame._parameter); }
	size_t size() { return Stack.size(); }
};
