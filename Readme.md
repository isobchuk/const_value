# const_value

**Simple component to convert function's parameters from non-type template to constexpr (to use with static_assert, if constexpr, et cetera).**

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

// Now it is possible with passing iso::const_v<index>
template <typename Index>
constexpr auto operator[](const Index) -> TypeYouWant const {
    // Some static_assert or compile-time evaluations for Index::value
}
```

Another example, class constructor:

```cpp
// ERROR: Cannot call it in your program (as MyClass myObject<1>();):
template <const int param, ...>
constexpr MyClass::MyClass() {
    // Some static_assert or compile-time evaluations
}

//  Now it is possible with passing iso::const_v<param>
template <typename Param. ...>
constexpr MyClass::MyClass(const Param, ...) {
    // Some static_assert or compile-time evaluations for Param::value
}
```

Or just for clearness:

```cpp
// Instead this:
MyFunction<0x12345678UL>();

static constexpr auto myVarNT = 0x12345678UL;
static constexpr MyClass<myVarNT> myObject;

// Now You can:
MyFunction(iso::const_v<0x12345678UL>);

static constexpr auto myVarCV = iso::const_v<0x12345678UL>;
static constexpr MyClass myObject(myVarCP);
```

## How to use?

```cpp
// Example of function
template<typename Param>
static constexpr void MyFunction(const Param) {
    if constexpr (Param::value) {
        // Write your compile-time code here
    }

    static_assert(Param::value > 100, "The values was overflowed!");
}

// It is possible to create constexpr variable and call function with this:
static constexpr auto myVar = iso::const_v<0x12345678UL>;
MyFunction(myVar);

// Or directly with value cast
MyFunction(iso::const_v<0x12345678UL>); // Compare to the traditional: MyFunction<0x12345678UL>();
```

Basically, type and value cast are available:

```cpp
// Using variable
led1.Write(iso::const_v<true>);
// Using type
Printf<iso::const_t<100U>> log;
```

## Concepts and type traits

For C++20 and higher concept to check type for ConstexprParameter is available:

```cpp
// You can add check like this
template<typename Param>
requires iso::const_value<Param> // If type is not ConstVal - compiler and IntelliSense error
static constexpr void MyFunction(const Param) {
    // Write your code here
}
```

Or you can use trait in case of C++17:

```cpp
// You can add check like this
template<typename Param>
static constexpr std::enable_if_t<iso::is_constexpr_v<Param>, void> MyFunction(const Param) {
    // Write your code here
}
```
