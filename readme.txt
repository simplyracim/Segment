This is a basic project that creates vectors starting from points, and checks the relationship
between created segments (intersection, colinearity ect...)

This project was made as a learning exercise for C++, especially on the functionnality of classes.

Things to do :

Graphics ============================================-

Interface for adding, editing, removing segments

Representation for operations (Scalar, dot, cross, negate)

Make an integrated terminal in the SFML window

Adaptive Label scale (like geogebra) (2^n, 2^n, 10^n)

Resizing
--> Janky, creates artifacts when scaling but otherwise works 

Controls :
(X) Zoom/Pan
(X) Mouse controls

Logic ===============================================

Introduce a Segment manager for creating and deleting as many segments as I want, using a std::vector instead of a pointer array

(X) Errors squiggles but code compiles and runs fine
--> Wrong C++ standard defined in settings.json (98 instead of 20)

(X) Makefile doesn't work
--> Fixed Makefile, now functional but still some issues

(X) Understand the code
--> Renamed sub() and add() to vector_from_points() and translate() for clarity

(X) Replace C style function to C++ methods (eg: vector_getX(&vector) to getX())
--> Done for Vectors and Points, and Segments

(X) Rename Point2 to Point (I'd like to discover to do this clean, because I struggles with Vector2 to Vector)
--> right-click / rename symbol. it's as easy as that.