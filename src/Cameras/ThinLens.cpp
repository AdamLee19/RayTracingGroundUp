// This file contains the definition of the Pinhole class

#include "Constants.h" 
#include "Point3D.h"
#include "Vector3D.h"
#include "ThinLens.h"
#include <math.h>

// ----------------------------------------------------------------------------- default constructor

ThinLens::ThinLens(void)		
	:	Camera(),
		lens_radius(1.0),
		d(40.0),
		f(74.0),
		zoom(1.0)
{}


// ----------------------------------------------------------------------------- copy constructor

ThinLens::ThinLens(const ThinLens& c)   		
	: 	Camera(c),
		lens_radius(c.lens_radius),
		d(c.d),
		f(c.f),
		zoom(c.zoom)
{}


// ----------------------------------------------------------------------------- clone

Camera* 
ThinLens::clone(void) const {
	return (new ThinLens(*this));
}



// ----------------------------------------------------------------------------- assignment operator

ThinLens& 
ThinLens::operator= (const ThinLens& rhs) { 	
	if (this == &rhs)
		return (*this);
		
	Camera::operator= (rhs);

	lens_radius = rhs.lens_radius;
	d 		    = rhs.d;
	f       	= rhs.f;
	zoom		= rhs.zoom;
	
	sampler_ptr = rhs.sampler_ptr->clone();

	return (*this);
}


// ----------------------------------------------------------------------------- destructor

ThinLens::~ThinLens(void) {}	

void 
ThinLens::set_sampler(Sampler* sp){
    if(sampler_ptr){
        delete sampler_ptr;
        sampler_ptr = NULL;
    }
    sampler_ptr = sp;
    sampler_ptr->map_samples_to_unit_disk();
}

// ----------------------------------------------------------------------------- ray_direction

Vector3D 
ThinLens::ray_direction(const Point2D& pixel_point, const Point2D& lens_point) const{
    Point2D p;
    p.x = pixel_point.x * f / d;
    p.y = pixel_point.y * f / d;
    Vector3D dir = (p.x - lens_point.x)*u + (p.y - lens_point.y)*v - f*w;
    dir.normalize();

    return dir;
}



// ----------------------------------------------------------------------------- render_scene

void 												
ThinLens::render_scene(const World& w) {
	RGBColor L;
    Ray ray;
    ViewPlane vp(w.vp);
    int depth = 0;

    Point2D sp; // Sample point in unity square
    Point2D pp; // Sample point on pixel
    Point2D dp; // Sample point on unit disk
    Point2D lp; // Sample point on lens
	
	vp.s /= zoom;

	float s = vp.s;
	float hres = vp.hres;
	float vres = vp.vres;

	for (int r = 0; r < vp.vres; r++)			// up
		for (int c = 0; c < vp.hres; c++) {		// across 					
			L = black; 
			
			for (int n = 0; n < vp.num_samples; n++) {
				sp = vp.sampler_ptr->sample_unit_square();
				pp.x = 	s * (c - hres * 0.5 + sp.x);	
				pp.y = 	s * (r - vres * 0.5 + sp.y);

				dp = sampler_ptr->sample_unit_disk();
				lp = dp * lens_radius;

				ray.o = eye + lp.x * u + lp.y * v;
				ray.d = ray_direction(pp, lp);

				L += w.tracer_ptr->trace_ray(ray);
			}	
											
			L /= vp.num_samples;
			L *= exposure_time;
			w.display_pixel(r, c, L);
		} 
}


