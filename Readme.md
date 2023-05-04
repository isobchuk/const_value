# constexpr_parameter

**Simple template to convert function's parameters from non-type template to constexpr.**

**Supported from C++17 and higher.**

## For what?

Sometimes, using non-type template parameters is prohibited or not looks clear.

For example, for type operations overloading:

```cpp
// ERROR: No way to write something like this:
template <const int index>
constexpr auto operator[]() const -> TypeYouWant {
    // Some static_assert or compile-time evaluations for index
}

// Now it is possible
template <typename Index>
constexpr auto operator[](const Index) -> TypeYouWant const {
    // Some static_assert or compile-time evaluations for Index::value
}
```

Another example, class constructor:

```cpp
// ERROR: Cannot call it in your program:
template <const int param, ...>
constexpr MyClass::MyClass() {
    // Some static_assert or compile-time evaluations
}

// Now it is possible
template <typename Param. ...>
constexpr MyClass::MyClass(const Param, ...) {
    // Some static_assert or compile-time evaluations for Param::value
}
```

Or just for clearness:

```cpp
// Instead this:
static constexpr auto myVarNT = 0x12345678UL;
MyFunction<myVarNT>();
static constexpr MyClass<myVarNT> myObject;

// Now You can:
static constexpr auto myVarCP = to_constexpr(0x12345678UL);
MyFunction(myVarCP);
static constexpr MyClass myObject(myVarCP);
```

## How to use?

```cpp
// Example of function
template<typename Param>
static constexpr void MyFunction(const Param) {
    // Write your code here
}

// It is possible to create constexpr variable and call function with this:
static constexpr auto myVar = to_constexpr(0x12345678UL);
MyFunction(myVar);

// Or directly with type cast
MyFunction(to_constexpr(0x12345678UL));
```

## Concepts and type traits

For C++20 and higher concept to check type for ConstexprParameter is available:

```cpp
// You can add check like this
template<typename Param>
requires meta::constexpr_parameter<Param>
static constexpr void MyFunction(const Param) {
    // Write your code here
}
```

Or you can use trait in case of C++17:

```cpp
// You can add check like this
template<typename Param>
static constexpr std::enable_if_t<meta::is_constexpr_v<Param>, void> MyFunction(const Param) {
    // Write your code here
}
```
