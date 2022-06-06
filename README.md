# Raytracer pixel-per-pixel in C 

This is the basis of a raytracer in C that I programmed as a coding exercice in August-September 2020. I used the book The Ray Tracer Challenge by Jamis Buck as a basis and developped the code following the pseudo-code indications he is giving in his book.

*example of the output below. Other images are in .ppm format and can be opened with Gimp.*

![My output from coding the Chapter 11 - Reflection and Refraction (nb of bounce = 3)](/images/image1_chapter11_bounce3.png)


The code is following the principe of a raytracing algorithm, where primary rays start at the camera, go through each pixel of the image plane, hit an object (or not) and generate a shadow ray (toward the light source), a refraction ray (if the object is not opaque) and the reflection ray (that is reflected at the contact point with respect to the normal). 

References :
- Han, J.H. (2011). 3D Graphics for Game Programming. CRC Press.
- Buck, J. (2019). The Ray Tracer Challenge: A Test-Driven Guide to Your First 3D Renderer. The Pragmatic Programmers.
- Ray tracing, Wikipedia. [https://en.wikipedia.org/wiki/Ray_tracing_(graphics)](https://en.wikipedia.org/wiki/Ray_tracing_(graphics))

