#ifndef __WORLD__
#define __WORLD__


// This file contains the declaration of the class World
// The World class does not have a copy constructor or an assignment operator, for the followign reasons:

// 1 	There's no need to copy construct or assign the World
// 2 	We wouldn't want to do this anyway, because the world can contain an arbitray amount of data
// 3 	These operations wouldn't work because the world is self-referencing:
//	 	the Tracer base class contains a pointer to the world. If we wrote a correct copy constructor for the 
// 	  	Tracer class, the World copy construtor would call itself recursively until we ran out of memory. 


#include <vector>
#include <string>




#include "ViewPlane.h"
#include "RGBColor.h"
#include "Tracer.h"
#include "GeometricObject.h"
#include "Sphere.h"
#include "Ray.h"
#include "Camera.h"


using namespace std;




class World {	
	public:
	
		ViewPlane					vp;
		int                         width;
		int                         height;
		RGBColor					background_color;
		Tracer*						tracer_ptr;
		Sphere 						sphere;		// for Chapter 3 only
		vector<GeometricObject*>	objects;		
		Camera* 					camera_ptr;

		mutable uint8_t*            image_ptr;		

	public:
	
		World(void);												
		
		~World();
								
		void 
		add_object(GeometricObject* object_ptr);
		
		void 					
		build(void);

		void 												
		render_scene(void) const;

		void
		set_camera(Camera* c_ptr);
		
		void
		open_window(const int w, const int h);

		void
		write_image(string img_name) const;

		void 												
		render_perspective(void) const;
						
		RGBColor
		max_to_one(const RGBColor& c) const;
		
		RGBColor
		clamp_to_color(const RGBColor& c) const;
		
		void
		display_pixel(const int row, const int column, const RGBColor& pixel_color) const;

		ShadeRec									
		hit_bare_bones_objects(const Ray& ray);

	private:

		
		void 
		delete_objects(void);

};


// ------------------------------------------------------------------ add_object

inline void 
World::add_object(GeometricObject* object_ptr) {  
	objects.push_back(object_ptr);	
}

// ------------------------------------------------------------------ set_camera
inline void
World::set_camera(Camera* c_ptr) {
	camera_ptr = c_ptr;
}

// ------------------------------------------------------------------ open_window
inline void
World::open_window(const int w, const int h) {
	width = w;
	height = h;
	image_ptr = new uint8_t [w * h * 3];
}
	
#endif
