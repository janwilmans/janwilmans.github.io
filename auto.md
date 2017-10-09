Auto Anonymous (unnamed variables)
==================================

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

Example usage:
=======================

```cpp
template <typename T, typename = void>   // example of the typename = void syntax
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
- it is RAII / guararenteed to be destroyed at the end of its scope as usual
- syntax consistent with typename = void
- less dependency on macros
- less dependency on macros (so nice, I had to list it twice)

Observations
=============
- its idiomatically consistent with c++ priciples / pure raii
- ~~optimization opportunities ? since:~~
  - you cannot take a reference and the compiler can know this
  - you cannot move from it
  - you cannot copy it
  
  Turns out most of this is not true, as pointed out by Ansel Sermersheim, you _can_ take its reference and so also move and copy it, if
  you pass its reference from its own constructor to another object.

  Appearently, this could be useful in TMP to add anonymous member functions to a class, why you would want to do that is another thing
  and not clear it me yet.

Cons
====
- would it break anything?
- no rainbows nor unicorns? if there are cons, what are they?

Questions
=========
- are the presentered usecases worth a language extention?


Existing discussion references:
- https://groups.google.com/a/isocpp.org/forum/#!msg/std-proposals/8lsCinlSO1w/JWkYRnndCQAJ (closed)
- https://groups.google.com/a/isocpp.org/forum/#!searchin/std-proposals/anonymous$20variable/std-proposals/BfAtczj81Kg/pga0JJ2JijwJ
- https://groups.google.com/a/isocpp.org/forum/#!searchin/std-proposals/anonymous$20variable/std-proposals/OKUpODP9-7w/oQq-asoYCgAJ
