Exercises/milestones

any enviro

1. sphere, plane, triangle

ray intersection with primitives. get info about ray.

2. camera (perspective and ortho), adaptive sampling (antialiasing), image
3. phong shading model
4. recursive raytracer (reflections and caustics)

5. extra task will be given individually (for 5)

## Lecture Notes


/*
Exercise 3 notes
point light: position (xyz), light intensity (rgb) (falloff not necessary)
ambient light: only light intensity, added to all light calculations (color of darkness) - for faking GI
GI (global ilumination): light scatters so you can see under the table
Area light: can be approximated by a copule of point lights uniformly scattered on a plane (line, etc) - gives soft shadows
more correct implementation of area light would be instead of tracing to a point light, trace to a surface (somewhat discretized)
isn't this the same thing? I mean the same calclations (we can go for the simpler one)
cosine function can help us calculate light intensity given angle of attack and surface normal. 
(it's 1 for angle 0 - when light is the most intense, and 0 when 90 - when light is the least intense)
lightintensity * cos(angle(attackVector, normalVector)) --- (mind radians-degrees), mind edge values (clamp to 1 when adding ambient)
cosine between 2 vectors is dot product
Lambert model = L_ambient + cos(N, toLight) * L_diffuse -> only matte surfaces, no specular
Phong model = lamber model + specular
specular = ...
for specular there's an optimization, where you calculate with respect to half vector (between toLight and toEye), 
because its faster then computing the refleted vector. This improvement is called phong-blin model.
the power n is called shininess

for every sum element we can multiply with coefficient K which tells which rgb is allowed (which are absorbed and which are reflected)

*/
