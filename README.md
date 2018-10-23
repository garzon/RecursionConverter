# RecursionConverter
C++ macros that can be used to convert recursive function into a state-based loop with context

```
g++ test.cpp -o test -O3
```

### example

```cpp
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

int main() {
	cout << fib(1) << " " << fib(2) << " " << fib(3) << " " << fib(4) << " " << fib(5) << endl; // 1 2 3 5 8
	return 0;
}
```
