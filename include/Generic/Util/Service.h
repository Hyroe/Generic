#ifndef SERVICE_H
#define SERVICE_H

#include <functional>
#include <any>
#include <tuple>
#include <unordered_map>

class Service
{
public:
	template <typename ReturnType, typename ...Params>
	void addMethod(int index, ReturnType(*method)(Params...)) {
		methods[index] = [method](std::any params)->std::any {return std::apply(method, std::any_cast<std::tuple<Params...>>(params)); };
	}

	template <typename ...Params>
	void addMethod(int index, void(*method)(Params...)) {
		methods[index] = [method](std::any params)->std::any {std::apply(method, std::any_cast<std::tuple<Params...>>(params)); return{}; };
	}

	void addMethod(int index, void(*method)()) {
		methods[index] = [method](std::any)->std::any {method(); return {}; };
	}

	template <typename T, typename ...Types>
	T run(int method, Types... args) {
		return std::any_cast<T>(methods[method](std::make_tuple(args...)));
	}

	template <typename ...Types>
	void run(int method, Types... args) {
		methods[method](std::make_tuple(args...));
	}

	void run(int method) {
		methods[method](std::make_tuple());
	}


	std::unordered_map<int, std::function<std::any(std::any)>> methods;
};

#endif 
