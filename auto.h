#pragma once

#ifdef __cplusplus

template <class Lambda> class AtScopeExit {
  Lambda& m_lambda;
public:
  AtScopeExit(Lambda& action) : m_lambda(action) {}
  ~AtScopeExit() { m_lambda(); }
};

#define Auto_INTERNAL2(lname, aname, ...) \
    auto lname = [&]() { __VA_ARGS__; }; \
    AtScopeExit<decltype(lname)> aname(lname);

#else

/* use GCC extensions in C */
#define Auto_INTERNAL2(lname, aname, ...) \
    void lname(int *aname) { (void)aname; __VA_ARGS__; } \
    __attribute__((cleanup(lname))) int aname;

#endif

#define Auto_TOKENPASTE(x, y) Auto_ ## x ## y

#define Auto_INTERNAL1(ctr, ...) \
    Auto_INTERNAL2(Auto_TOKENPASTE(func_, ctr), \
                   Auto_TOKENPASTE(instance_, ctr), __VA_ARGS__)

#define Auto(...) Auto_INTERNAL1(__COUNTER__, __VA_ARGS__)
