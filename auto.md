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
- less dependency on macros
- less dependency on macros (so nice, I had to list it twice)

Syntax
======

```
auto = foo();     // somewhat consistent with typename = void syntax
auto [] = foo();  // Yasskin '12 syntax
```

Observations
=============
- its idiomatically consistent with c++ priciples / pure raii
- optimization opportunities?
  - ~~you cannot take a reference and the compiler can know this~~
  - you cannot move from it
  - you cannot copy it
  
As pointed out by Ansel Sermersheim, you _can_ take its reference if you pass its reference from its own constructor to another object.
Appearently, this could be useful in TMP to add anonymous member functions to a class, why you would want to do that is not clear it me.

Cons
====
- SG14 discussion feedback: the auto = foo(); syntax is error-prone, it might be an accidentally ommitted name, and currently that would give you an compiler error.

Questions
=========
- are the presentered usecases worth a language extention?

Discussion
==========

```
35. [tiny] Some concise way to generate a unique, unused variable name
Section: 3.4 [basic.lookup] Status: Open Submitter: Jeffrey Yasskin Opened: 2012-10-24 Last modified: 2015-05-22
```

Sometimes we want to define a variable that's unused except for its constructor and destructor. lock_guard<mutex> and ScopeGuard are decent examples of this. In C++11, we have to manually name the variable something unique. Sometimes we use _some_name_##__LINE__ (suitably wrapped so the concatenation happens after expanding __LINE__) to try to generate unique names automatically, and gcc/clang have an extension _some_name_##__COUNTER__

http://gcc.gnu.org/onlinedocs/gcc-4.7.2/cpp/Common-Predefined-Macros.html

to allow multiple such variables on the same line. These are pretty verbose and not convenient for casual use. Haskell allows _ (underscore) to stand in for a variable that's not going to be used. Googlemock defines testing::_ to mean "don't care" as an argument, which is similar but not identical.

Bristol 2013: Stroustrup wondered how unique the name needs to be, and wondered whether parallel builds would have problems ensuring the uniqueness. Naumann pointed out that having an unnamed variable is useful also for cases where you don't want the variable's address to be taken etc. Stroustrup and Van Winkel said this is not tiny, and a proper paper is necessary for this issue.

Chicago 2013: Deemed not as C++14 material, Yasskin or someone else invited to write a paper, straw polls in favor of the feature. Things to consider in the paper: Consider double underscore "__". Can it be used only in local scope? For class members? For globals?

Discussed in Rapperswil 2014. Still encouraging a paper, Dennett to contact Yasskin about it.


- https://cplusplus.github.io/EWG/ewg-active.html#35 
- https://groups.google.com/a/isocpp.org/forum/#!topic/std-proposals/gg3_eUhCuqo
- https://groups.google.com/a/isocpp.org/forum/#!msg/std-proposals/8lsCinlSO1w/JWkYRnndCQAJ (closed)
- https://groups.google.com/a/isocpp.org/forum/#!searchin/std-proposals/anonymous$20variable/std-proposals/BfAtczj81Kg/pga0JJ2JijwJ
- https://groups.google.com/a/isocpp.org/forum/#!searchin/std-proposals/anonymous$20variable/std-proposals/OKUpODP9-7w/oQq-asoYCgAJ
