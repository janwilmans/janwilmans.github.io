









Auto Anonymous
==============

Sounds like a meeting you can join to recover from over using auto?

Everybody has seen or written this or similar:

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
```cpp
    auto = make_guard();
```    
Example usage
=============

```cpp
template <typename T, typename = void>
void foo() { }

template <typename F>
scope_guard<F> make_guard(F f)
{
	return scope_guard<F>(f);
}

void main()
{
	auto = log_function(__FUNCTION__);
	auto = make_guard([] { end_of_scope_action(); }); 
	
	~~~ do stuff ~~~

	// guard leaves scope 
	// log_function leaves scope
}
```

Pros
====
- its pure raii (and raii == beauty)
- it is still guararenteed to be destroyed at the end of its scope as usual
- look mam, no macros!
- syntax consistent with typename = void

Observations
=============
- optimization opportunities ? since:
  - you cannot take a reference and the compiler can know this
  - you cannot move from it
  - you cannot copy it
  
Turns out this is not true, as pointed out by Ansel Sermersheim, you _can_ take its reference and so also move and copy it, if
you pass its reference from its own constructor to another object.

Appearently, this could be useful in TMP to add anonymous member functions to a class, why you would want to do that is another thing and not clear it me yet.


Cons
====
- not exciting?
- no rainbows nor unicorns?


- there must be cons, but what are they?
- channel Andrei Alexandrescu: 'destroy me!'
