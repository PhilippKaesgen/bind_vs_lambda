#include <functional>
#include <iostream>

class A {
public:
    explicit A(int x): x(x) { }
    void registerCallback(std::function<void(int,int)> f) {
#ifdef __using_bind__
        callback = std::bind(f, x, std::placeholders::_1);
#else
        callback = [this, f](int arg) {
            f(x,arg);
        };
#endif
    }
    void process(int y) {
        y *= 3;
        callback(y);
    }
private:
    const int x;
    std::function<void(int)> callback;
};

class B {
public:
    explicit B(A* a): a(a) {
#ifdef __using_bind__
        a->registerCallback(std::bind(&B::process, this, std::placeholders::_1, std::placeholders::_2));
#else
        a->registerCallback([this](int arg1, int arg2) {
            process(arg1, arg2);
        });
#endif
    }
    int getResult() {
        return res;
    }
    void run() {
        a->process(4);
    }
private:
    A* a;
    int res;
    void process(int x, int y) {
        res = x * y;
    }
};

int main(int argc, char** argv) {
    unsigned iterations = std::stoul(argv[1]);
    while (--iterations > 0) {
        A* a = new A(iterations);
        B* b = new B(a);

        b->run();
        delete b;
        delete a;
        std::cout << b->getResult() << std::endl;
    }
    return 0;
}
