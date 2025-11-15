This is a basic project that creates vectors starting from points, and checks the relationship
between created segments (intersection, colinearity ect...)

This project was made as a learning exercise for C++, especially on the functionnality of classes.

Things to do :

Introduce a Segment manager for creating and deleting as many segments as I want, using a std::vector instead of a pointer array

(X) Errors squiggles but code compiles and runs fine
--> Wrong C++ standard defined in settings.json (98 instead of 20)

(X) Makefile doesn't work
--> Fixed Makefile, now functional but still some issues

Understand Makefiles

Need to delete the whole obj folder to compile

Fix the graphics :
	- Gradations of the axioms
	- Representation for operations (Scalar, dot, cross, negate)
	- Later fuse the terminal to the graphics (one shared window)

(X) Understand the code
--> Renamed sub() and add() to vector_from_points() and translate() for clarity

Replace C style function to C++ methods (eg: vector_getX(&vector) to getX())
--> Done for Vectors and points, still need to do Segments

(X) Rename Point2 to Point (I'd like to discover to do this clean, because I struggles with Vector2 to Vector)
--> right-click / rename symbol. it's as easy as that.