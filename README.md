# skibidi language

Hello world
```
// void by default
fn main(string[] argv) {
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

fn main(string[] argv) {
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
