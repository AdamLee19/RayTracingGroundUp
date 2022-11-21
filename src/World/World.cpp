#include <cmath>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// this file contains the definition of the World class
#include "World.h"
#include "Constants.h"

// geometric objects

#include "Plane.h"
#include "Sphere.h"

// tracers

#include "SingleSphere.h"
#include "MultipleObjects.h"

// utilities

#include "Vector3D.h"
#include "Point3D.h"
#include "Point2D.h"
#include "Normal.h"
#include "ShadeRec.h"
#include "Maths.h"
#include "MultiJittered.h"
#include "Pinhole.h"
#include "ThinLens.h"

// build functions

#include "BuildSingleSphere.cpp"
// #include "BuildMultipleObjects.cpp"
//#include "BuildBBCoverPic.cpp"


// -------------------------------------------------------------------- default constructor

World::World(void)
	:  	background_color(black),
		tracer_ptr(NULL),
		camera_ptr(NULL),
		image_ptr(NULL)
{}



//------------------------------------------------------------------ destructor

World::~World(void) {	
	
	if(tracer_ptr) {
		delete tracer_ptr;
		tracer_ptr = NULL;
	}

	if(camera_ptr) {
		delete camera_ptr;
		camera_ptr = NULL;
	}


	if(image_ptr) {
		delete image_ptr;
		image_ptr = NULL;
	}		
		
	
	delete_objects();	
}


//------------------------------------------------------------------ render_scene

// This uses orthographic viewing along the zw axis

void 												
World::render_scene(void) const {

	RGBColor	pixel_color;	 	
	Ray			ray;					
	int 		hres 	= vp.hres;
	int 		vres 	= vp.vres;
	float		s		= vp.s;
	float		zw		= 100.0;			// hardwired in
	Point2D     sp;
	Point2D     pp;
	
	//set_rand_seed(100);

	// open_window(hres, vres);

	ray.d = Vector3D(0, 0, -1);
	
	for (int r = 0; r < vres; r++)			// up
		for (int c = 0; c < hres; c++) {	// across
			pixel_color = black;

			for (int j = 0; j < vp.num_samples; j++) {
				sp = vp.sampler_ptr->sample_unit_square();
				pp.x = 	s * (c - hres * 0.5 + sp.x);	
				pp.y = 	s * (r - vres * 0.5 + sp.y);	
				ray.o = Point3D(pp.x, pp.y, zw);
				pixel_color += tracer_ptr->trace_ray(ray);
			}
			pixel_color /= vp.num_samples;
			display_pixel(r, c, pixel_color);
		}

}  

void 												
World::render_perspective(void) const {

	RGBColor	pixel_color;	 	
	Ray			ray;					
	int 		hres 	= vp.hres;
	int 		vres 	= vp.vres;
	float		s		= vp.s;
	float		d		= 50.0;			// hardwired in
	float		eye		= 150.0;			// hardwired in
	Point2D     sp;
	Point2D     pp;
	

	// open_window(hres, vres);

	ray.o = Point3D(0, 0, eye);
	
	for (int r = 0; r < vres; r++)			// up
		for (int c = 0; c < hres; c++) {	// across
			pixel_color = black;

			for (int j = 0; j < vp.num_samples; j++) {
				sp = vp.sampler_ptr->sample_unit_square();
				pp.x = 	s * (c - hres * 0.5 + sp.x);	
				pp.y = 	s * (r - vres * 0.5 + sp.y);	
				ray.d = Point3D(pp.x, pp.y, -d);
				ray.d.normalize();
				pixel_color += tracer_ptr->trace_ray(ray);
			}
			pixel_color /= vp.num_samples;
			display_pixel(r, c, pixel_color);
		}

}  

// ------------------------------------------------------------------ clamp

RGBColor
World::max_to_one(const RGBColor& c) const  {
	float max_value = max(c.r, max(c.g, c.b));
	
	if (max_value > 1.0)
		return (c / max_value);
	else
		return (c);
}


// ------------------------------------------------------------------ clamp_to_color
// Set color to red if any component is greater than one

RGBColor
World::clamp_to_color(const RGBColor& raw_color) const {
	RGBColor c(raw_color);
	
	if (raw_color.r > 1.0 || raw_color.g > 1.0 || raw_color.b > 1.0) {
		c.r = 1.0; c.g = 0.0; c.b = 0.0;
	}
		
	return (c);
}


// ---------------------------------------------------------------------------display_pixel

// raw_color is the pixel color computed by the ray tracer
// its RGB floating point components can be arbitrarily large
// mapped_color has all components in the range [0, 1], but still floating point
// display color has integer components for computer display
// the Mac's components are in the range [0, 65535]
// a PC's components will probably be in the range [0, 255]
// the system-dependent code is in the function convert_to_display_color
// the function SetCPixel is a Mac OS function


void
World::display_pixel(const int row, const int column, const RGBColor& raw_color) const {
	RGBColor mapped_color;

	if (vp.show_out_of_gamut)
		mapped_color = clamp_to_color(raw_color);
	else
		mapped_color = max_to_one(raw_color);
	
	if (vp.gamma != 1.0)
		mapped_color = mapped_color.powc(vp.inv_gamma);
	
   //have to start from max y coordinate to convert to screen coordinates
   int x = column;
   int y = vp.vres - row - 1;

	image_ptr[(y * vp.hres + x) * 3    ] = (uint8_t)(mapped_color.r * 255);
	image_ptr[(y * vp.hres + x) * 3 + 1] = (uint8_t)(mapped_color.g * 255);
	image_ptr[(y * vp.hres + x) * 3 + 2] = (uint8_t)(mapped_color.b * 255);
}



// ----------------------------------------------------------------------------- hit_bare_bones_objects

ShadeRec									
World::hit_bare_bones_objects(const Ray& ray) {
	ShadeRec	sr(*this); 
	double		t; 			
	float		tmin 			= kHugeValue;
	int 		num_objects 	= objects.size();
	
	for (int j = 0; j < num_objects; j++)
		if (objects[j]->hit(ray, t, sr) && (t < tmin)) {
			sr.hit_an_object	= true;
			tmin 				= t; 
			sr.color			= objects[j]->get_color(); 
		}
		
	return (sr);   
}


//------------------------------------------------------------------ delete_objects

// Deletes the objects in the objects array, and erases the array.
// The objects array still exists, because it's an automatic variable, but it's empty 

void
World::delete_objects(void) {
	int num_objects = objects.size();
	
	for (int j = 0; j < num_objects; j++) {
		delete objects[j];
		objects[j] = NULL;
	}	
	
	objects.erase (objects.begin(), objects.end());
}

//------------------------------------------------------------------ write_image
void
World::write_image(string img_name) const {
	stbi_write_jpg(img_name.c_str(), vp.hres, vp.vres, 3, image_ptr, 100);
}	