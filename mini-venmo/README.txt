This is implemented using python3.4, although it very well could be compatible with python2.7.

To run the commandline version of the application execute:
    python3.4 mini-venmo.py

To run with commands from a input file execute:
    python3.4 mini_venmo.py <input_file>
An example input.txt is included

a makefile is included and support:
make clean
make test

I chose to make a very lightweight application using basic library modules. I chose to split the functionality into separate modules, sort of like some web service frameworks, and use a sqlite in memory database. I thought given the structure of the application, this makes the most sense.

I chose python because it was probably the simplest way for me to get this done. I don't think performance of the source code will be the bottleneck in such an application, the various database operations will be. As a result I believe python to be sufficient in performance.

I chose not to use an ORM, the original thought was in keeping with making the application as simple and lightweight as possible and in an attempt to get it done as quickly as possible. However thinking back using an ORM would have been a good choice.

I mainly functional tested this application as I worked on it. I provide very small sample unittests. They were put together quickly and are far from a refined product. They provide a setup where more unit tests can be written following the existing examples. I've also come to realize that I'm still lacking some expertise in python's unittesting framework.

Some error cases which were not explicity mentioned in the spec or example output will not have well formed error messages. However they should not stall the continued execution of the application.

Also I had a little trouble getting transactions working using sqlite, so none of the db logic are in transactions. With a single user using it, its not a problem. I recognize that we would need those transactions otherwise.
