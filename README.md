# std::bind vs. lambda in cpp

For function pointers like for callback functions there are multiple ways to
exchange function pointers. In this repository, I wanted to explore how
std::bind and a lambda wrapper of a member function impact run time and binary
size.

## Hypothesis

std::bind and lambda wrapper should result in similar run time and binary size.

## Experiment

Compile `main.cpp` with and without setting \_\_using\_bind\_\_, measure the run time,
and report the binary sizes.

### Compile

```cpp
g++ -O3 -D__using_bind__ main.cpp -o bind.o
g++ -O3 main.cpp -o lambda.o
```

### Run

```bash
\time -f "%U" ./bind.o 100000000 1> /dev/null
\time -f "%U" ./lambda.o 100000000 1> /dev/null
```

## Results

Compiled with gcc 12.1.0

### Run time

bind.o: 23.54sec

lambda.o: 19.96sec

### Binary size

bind.o: 24kB

lambda.o: 19kB

## Evaluation

The lambda version is slightly faster than the std::bind version. Also, the
lambda version is significantly smaller than the std::bind version.

## Related work

https://stackoverflow.com/questions/1930903/bind-vs-lambda#4581747

## Conclusion

The lambda version is better in terms of run time and binary size. I would
recommend using lambda wrappers in similar cases.
