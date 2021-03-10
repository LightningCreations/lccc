# lccc scope [lccc.scope]

1. Each implementation of lccc shall, in every translation unit, define implicitly, a scope named `__lccc`, which can be named from the global scope. This scope shall have public access.
2. Each implementation of lccc shall, in every translation unit, define implicitly, a scope named `__lccc__`, which can be named from the global scope with public access. All members defined within the `__lccc` scope shall also be defined identically within the `__lccc__` scope.
3. If the translation unit does not define an item named `lccc`, in the global scope, then the implementation shall define implicitly a scope by that name in every translation unit. All members defined within the `__lccc` scope shall also be defined identically within the `lccc` scope.
4. If a program declares a member of the global scope named `__lccc` or `__lccc__`, the behaviour is undefined. If a program declares a member of the global scope named `lccc`, then the implementation shall not implicitly declare that scope or any member thereof.
5. If a member is declared within the `__lccc` scope such that it has a name which is not prefixed with two consecutive underscores, a member with the same name but prefixed with two additional underscores is declared to be the same member, and a member with the same name but prefixed and suffixed by two additional underscores is declared to be the same member
6. _Note 1 - For example, if the name `__lccc::foo` is declared by the impementation, then `__lccc::__foo` and `__lccc::__foo__` shall also be declared 