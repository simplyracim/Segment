This is a basic project that creates two vectors starting from points, and checks the relationship
between the two segments (intersection, colinearity ect...)

This project was made as a learning exercise for C++, especially on the functionnality of classes.

Things to do :

(X) Errors squiggles but code compiles and runs fine
--> Wrong C++ standard defined in settings.json (98 instead of 20)

(X) Makefile doesn't work
--> Fixed Makefile, now functional but still some issues

Understand Makefiles

Need to delete the whole obj folder to compile

Rename Point2 to Point (I'd like to discover to do this clean, because I struggles with Vector2 to Vector)

Fix the graphics :
	- Gradations of the axioms
	- Representation for operations (Scalar, dot, cross)

Understand the code

Later fuse the terminal to the graphics (one shared window)

Replace C style function to C++ methods (eg: vector_getX(&vector) to getX())
--> Done for Vectors, still need to do Points and Segments