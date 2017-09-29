









Auto Anonymous
==============

Sounds like a meeting you can join to recover from overusing auto?

Everybody has seen or writter this or similar:

```cpp
    __COUNTER__
    This macro expands to sequential integral values starting from 0. In conjunction with the ## operator,
    this provides a convenient means to generate unique identifiers.
```

```cpp
struct LogFunction
{
	LogFunction(const char* func) : func_(func)
	{
		std::cout << func_.c_str() << " enter\n";
	}

	~LogFunction()
	{
		std::cout << func_.c_str() << " leave\n";
	}
private:
	std::string func_;
};


#define STR_CONCAT_(a, b) a##b
#define STR_CONCAT(a, b) STR_CONCAT_(a, b)
#define LOG_FUNCTION LogFunction STR_CONCAT(log_function_, __COUNTER__) (__FUNCTION__)

int main()
{
    LOG_FUNCTION;
    return 0;
}
```


Proposal, an anonymous variable:
================================

    auto = make_guard();
    
Example usage
=============

```
template <typename T, typename = void>
void foo() { }

void log_function(const char* ) {}
auto make_guard() { return 0; }

void main()
{
	auto = log_function(__FUNCTION__);
	auto = make_guard(mutex); 
	
	~~~ do stuff ~~~

	// guard leaves scope 
	// log_function leaves scope
}
```

Pros
====
- its pure raii (and raii == beauty)
- optimization opportunities ? since:
  - you cannot take a reference and the compiler can know this
  - you cannot move from it
  - you cannot copy it
- it is still guararenteed to be destroyed at the end of its scope as usual
- look mam, no macros!
- syntax consistent with typename = void

Cons
====
- not exciting?
- no rainbows nor unicorns?


- there must be cons, but what are they?
- channel Andrei Alexandrescu: 'destroy me!'
