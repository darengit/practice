wordcount
=========

I copied this example from someone else. I learned a lot while writing my own rendition:

* its bad practice to initialize char * to string literal, use const char[] or const char *const
* there are some cases where c++ provide nice abstractions, in particular in areas where equivalent actions in c require allocating and de-allocating metadata, like threads and file-io
* there are cases when c style is much simpler, like timing a section of code with clock() (time.h)
* c++ threads passing of parameters by reference is tricky, best to not do it
* template of templates is possible, possible to have a std::map as a template parameter, std::map and std::unordered_map are quite different
* template function and types have their unique overall types, an instance of a templated function is not the same type as an equivalent non templated version. For instance vector<int> is not same type as myVectorInt
* accessing a small vector sequentially is faster than accessing unordered map which is faster map (balanced rb tree)

