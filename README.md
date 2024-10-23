# skibidi language

Hello world
```
// void by default
fn main(const string[] argv) {
  std::println("Hello, world!");
}
```

Variables
```
// mutable reference, mutable value
int x;

// constant reference, mutable value
constref int x;

// constant reference, constant value
const int x;
```

Functions
```
fn const int add(int a, int b) {
  return a + b;
}

fn main(const string[] argv) {
  std::println(add(1, 2));
}
```

Union Types
```
(int | string) x;

// const/constref variables cannot have union types
constref (int | string) x; // Error
const (int | string) x; // Error
```

Arrays
```
// normal array
constref int[] x;

// tuple
constref [string, int] x;

// tuple of 3 ints and 2 strings
constref [int:3, string:2] x;

// array members are mutable by default, unless the array is const
const int[] x;
constref (const int)[] x;
```

Objects
```
interface MyInterface {
  int property;
  const string otherProperty;
}

fn main(const string[] argv) {
  MyInterface obj = MyInterface {
    property: 69,
    otherProperty: "hi"
  };

  obj.property = 420;
  obj.otherProperty = "bye"; // error
}
```

Generics
```
interface Addable {
  constref This operator +(const This other);
}

fn constref T genericAdd<T(Addable)>(const T a, const T b) {
  return a + b;
}
```

Enums
```
enum MyEnum {
  Thing,
  OtherThing,
  AnotherThing
}

enum PredefinedEnum {
  One = 1,
  Ten = 10,
  Hundred = 100,
  Name = "hi"
}

enum ParameterEnum<T> {
  Some(T value),
  None
}
```
