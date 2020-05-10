# PythonLike-Range
Some ideas to implement something similar to Python range function. Some of the implementations require c++20 features.
This project is not meant to be used directly as a library, but individual .hpp files could be used in your project.

## Syntax
`range(T min, T max, size_t step)`
Returns something that (kind of) satisfies the Range concept.
By iterating that thing, you get the numbers in [*min*, *max*), increasing by _step_ every tupe
The version that takes one parameter sets *min* to T{} (which is 0 when _T=int_), and step to 1.
## Guide
- std::vector: This is the less sophisticated option. It just fills a vector and returns it, the the range-based for loop iterate over the elements. If you are lucky, NRVO will happen and this will be quit fast. Anyway, this option have linear memory consumption, so keep that in mind.
- coroutine: Overkill. At least until we have std::generator. Until then, this solution is just too much. It was more like a fun thing to do while learning some of the coroutines intricacies than anything else.
- std::iota_view: The closest to standard way to do this. The "step" parameter makes things much, much complex, but probably not much slower as everything is lazy evaluated. I would be nice to have something like stride in boost.
- view: Probably my favourite. It have some problems with being standard compliant as a view, but it's a simple approach to views and ranges and might be implemented easily in c++11 (you just need to remove the sentinel, and a two iterators)
