









Auto Anonymous
==============

Sounds like a meeting you can join to recover from overusing auto?

Everybody has seen or writter this or similar:

    __COUNTER__
    This macro expands to sequential integral values starting from 0. In conjunction with the ## operator,
    this provides a convenient means to generate unique identifiers.




Proposal, an anonymous variable:
================================

    auto = make_guard();

Pros
====
- you cannot take a reference and the compiler can know this
- you cannot move from it
- you cannot copy it
- it is still guararenteed to be destroyed at the end of its scope as usual
