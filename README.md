# Solaris

im bored lol

## Component progress
* [x] Lexer
* [ ] Parser
* [ ] Compiler
* [ ] Runtime
* [ ] VSCode Extension
* [ ] Package Manager

## Files
* `solaris.json` - Solaris config
* `solaris-pkg-cache.json` - Solaris package cache
* `*.sol` - Solaris source code
* `*.solex` - Solaris bytecode

## Syntax (WIP)
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
fn const int add(const int a, const int b) {
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

// parameterized enums
enum Result<T, E> {
  Success(T),
  Error(E)
}

fn main(const string[] argv) {
  Result<const int, const string> result = Result.Success(69);

  decompose result {
    Success(const int? success),
    Error(const string? error)
  }
}
```

Classes
```
class MyClass {
  public int property;
  protected int otherProperty;
  private int anotherProperty;

  public constructor(property, otherProperty, anotherProperty) {
    this.property = property;
    this.otherProperty = otherProperty;
    this.anotherProperty = anotherProperty;
  }

  public destructor() {
    std::println("MyClass destroyed");
  }

  public fn myMethod() {
    std::println(this.property);
  }

  public get int another() {
    std::println("Getting another");
    return this.anotherProperty;
  }

  public set int another(const int value) {
    std::println("Setting another");
    this.anotherProperty = value;
  }
}

fn main(const string[] argv) {
  constref MyClass instance = new MyClass(1, 2, 3);

  std::println(instance.property); // 1
  std::println(instance.otherProperty); // error
  std::println(instance.anotherProperty); // error
  
  std::println(instance.another); // "Getting another", 3
  instance.another = 5; // "Setting another"
  std::println(instance.another); // "Getting another", 5
}
```
