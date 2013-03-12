/* Computer Graphics and Game Technology, Assignment Ray-tracing
 *
 * Student name .... David van Erkelens & Jelte Fennema
 * Student email ... info@davidvanerkelens.nl, me@jeltef.nl
 * Collegekaart .... 10264019, 10183159
 * Date ............ 6-7-8 maart 2013
 * Comments ........ Enjoy!
 *
 *
 * (always fill in these fields before submitting!!)
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "shaders.h"
#include "perlin.h"
#include "v3math.h"
#include "intersection.h"
#include "scene.h"
#include "quat.h"
#include "constants.h"

float max(float a, float b);

// shade_constant()
//
// Always return the same color. This shader does no real computations
// based on normal, light position, etc. As such, it merely creates
// a "silhouette" of an object.

vec3
shade_constant(intersection_point ip)
{
    return v3_create(1, 0, 0);
}

vec3
shade_matte(intersection_point ip)
{
    float intensity = scene_ambient_light;
    vec3 li;
    int i;
	// calculate intensity from all lights
	for(i = 0; i < scene_num_lights; i++)
	{
	    if(shadow_check(v3_add(ip.p, v3_multiply(ip.n, 0.0001)), scene_lights[i].position) == 0)   
	    {
	        li = v3_normalize(v3_subtract(scene_lights[i].position, ip.p));
	        intensity += (scene_lights[i].intensity * max(0, v3_dotprod(ip.n, li)));
	    }
	}
	// The intensity cannot be higher than 1
	if (intensity > 1)
		intensity = 1;
	return v3_create(intensity, intensity, intensity);
}

vec3
shade_blinn_phong(intersection_point ip)
{
    float a, b;
    vec3 li, halfway;
    int i;
    float matte = 0, phong = 0;
	// calculate intensity from all lights
	for(i = 0; i < scene_num_lights; i++)
	{
        // calculate the light vector
        li = v3_normalize(v3_subtract(scene_lights[i].position, ip.p));
        if(shadow_check(v3_add(ip.p, v3_multiply(ip.n, 0.0005)), scene_lights[i].position) == 0)   
        {
            // if there is no shadow calculate the color
            matte += (scene_lights[i].intensity * max(0, v3_dotprod(ip.n, li)));
        }
        halfway = v3_normalize(v3_add(ip.i, li));
        // add the highlight
        phong += (scene_lights[i].intensity * max(0, pow(v3_dotprod(halfway, ip.n), 50)));

	}
    matte *= 0.8;
    matte += scene_ambient_light;
    phong *= 0.5;
    a = matte + phong;
    b = phong;
    if(a > 1) a = 1;
    if(b > 1) b = 1;
	return v3_create(a, b, b);
}

vec3
shade_reflection(intersection_point ip)
{
    vec3 r = v3_normalize(v3_subtract(v3_multiply(ip.n, v3_dotprod(ip.i, ip.n) * 2), ip.i));
    vec3 result = v3_create(0, 0, 0);
    vec3 matte = shade_matte(ip);
    float a, b, c;
    result = v3_add(ray_color(ip.ray_level + 1, v3_add(ip.p, v3_multiply(ip.n, 0.0005)), r), result);
    a = 0.75 * matte.x + 0.25 * result.x;
    b = 0.75 * matte.y + 0.25 * result.y;
    c = 0.75 * matte.z + 0.25 * result.z;
    if(a > 1) a = 1;
    if(b > 1) b = 1;
    if(c > 1) c = 1;
    return v3_create(a, b, c);
}

// Returns the shaded color for the given point to shade.
// Calls the relevant shading function based on the material index.
vec3
shade(intersection_point ip)
{
  switch (ip.material)
  {
    case 0:
      return shade_constant(ip);
    case 1:
      return shade_matte(ip);
    case 2:
      return shade_blinn_phong(ip);
    case 3:
      return shade_reflection(ip);
    default:
      return shade_constant(ip);

  }
}

// Determine the surface color for the first object intersected by
// the given ray, or return the scene background color when no
// intersection is found
vec3
ray_color(int level, vec3 ray_origin, vec3 ray_direction)
{
    intersection_point  ip;

    // If this ray has been reflected too many times, simply
    // return the background color.
    if (level >= 3)
        return scene_background_color;

    // Check if the ray intersects anything in the scene
    if (find_first_intersection(&ip, ray_origin, ray_direction))
    {
        // Shade the found intersection point
        ip.ray_level = level;
        return shade(ip);
    }

    // Nothing was hit, return background color
    return scene_background_color;
}

float max(float a, float b)
{
    return (a > b)?(a):(b);
}
