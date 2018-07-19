#include <iostream>
#include <stack>
#include <map>

using namespace std;

// magic goes here ------------------------------------------

#define TOKEN_CONCAT(x, y) x ## y
#define MAKE_STATE(state_id, ...) save_context(&&TOKEN_CONCAT(st, state_id)); __VA_ARGS__; calling(); goto _recursive_context_reentry; TOKEN_CONCAT(st, state_id):
#define CALL_SELF(...) MAKE_STATE(__COUNTER__, __VA_ARGS__)
#define RET_VAL _returnValue
#define RETURN(x) { _ret_val = x; goto _recursive_context_reentry; }
#define DECLARE_RECURSIVE_FUNCTION_START(returnType, functionName) \
struct functionName { \
	using ReturnType = returnType; \
	static std::stack<functionName> _ctxStack; \
	void *_currState = nullptr; \
	\
	inline void calling() { \
		_currState = nullptr; \
		_ctxStack.push(*this); \
	} \
	\
	inline void save_context(void *nextState) { \
		std::swap(_currState, nextState); \
		_ctxStack.push(*this); \
		std::swap(_currState, nextState); \
	}
	
	
#define CURRENT_DEPTH (_ctxStack.size())
#define DECLARE_RECURSIVE_FUNCTION_END \
ReturnType call() { \
		ReturnType _ret_val; \
		save_context(0); \
		\
_recursive_context_reentry: \
		if (!_ctxStack.empty()) { \
			ReturnType RET_VAL = _ret_val; \
			*this = _ctxStack.top(); \
			_ctxStack.pop(); \
			if (_currState) goto *_currState;

#define RECURSIVE_FUNCTION_END(functionName) \
			goto _recursive_context_reentry; \
		} \
		if (_ctxStack.empty()) return _ret_val; \
		\
	} \
}; \
std::stack<functionName> functionName::_ctxStack;

// magic ends -----------------------------------------------------


DECLARE_RECURSIVE_FUNCTION_START(int, Fib)
	// args
	int n;
	// local vars
	int ret1;
DECLARE_RECURSIVE_FUNCTION_END {
	cout << std::string(CURRENT_DEPTH*2, ' ') << "n == " << n << endl;
	if (n <= 1) { RETURN(1); }
	else {
		CALL_SELF(n=n-1);
		ret1 = RET_VAL;
		CALL_SELF(n=n-2);
		RETURN(ret1 + RET_VAL);
	}
} RECURSIVE_FUNCTION_END(Fib);

int fib(int n) {
	Fib tmp;
	tmp.n = n;
	return tmp.call();
};

DECLARE_RECURSIVE_FUNCTION_START(int, Combination)
	int m, n;
	int tmp;
DECLARE_RECURSIVE_FUNCTION_END {
	if (n == m || m == 0) {
		RETURN(1);
	} else {
		CALL_SELF(m=m-1, n=n-1);
		tmp = RET_VAL;
		CALL_SELF(m=m, n=n-1);
		RETURN(tmp + RET_VAL);
	}
} RECURSIVE_FUNCTION_END(Combination);

int combination(int m, int n) {
	Combination tmp;
	tmp.n = n; tmp.m = m;
	return tmp.call();
};

int main() {
	cout << fib(1) << " " << fib(2) << " " << fib(3) << " " << fib(4) << " " << fib(5) << endl;
	cout << combination(0, 5) << " "<< combination(1, 5) << " " << combination(2, 5) << " " << combination(3, 5) << " " << combination(4, 5) << " " << combination(5, 5) << endl;
	return 0;
}

