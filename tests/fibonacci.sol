fn int fib(int x) {
    if (x) {
        if (x - 1) {
            return fib(x - 1) + fib(x - 2);
        } else return 1;
    } else return 0;
}

fn void main() {
    std::println(fib(20));
}