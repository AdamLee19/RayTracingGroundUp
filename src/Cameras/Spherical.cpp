// This file contains the definition of the Pinhole class

#include "Constants.h" 
#include "Point3D.h"
#include "Vector3D.h"
#include "Spherical.h"
#include <math.h>

// ----------------------------------------------------------------------------- default constructor

Spherical::Spherical(void)		
	:	Camera(),
		psi_max(120),
		lambda_max(120)
{}


// ----------------------------------------------------------------------------- copy constructor

Spherical::Spherical(const Spherical& s)
	: 	Camera(s),
		psi_max(s.psi_max),
		lambda_max(s.lambda_max)
{}


// ----------------------------------------------------------------------------- clone

Camera* 
Spherical::clone(void) const {
	return (new Spherical(*this));
}



// ----------------------------------------------------------------------------- assignment operator

Spherical& 
Spherical::operator= (const Spherical& rhs) { 	
	if (this == &rhs)
		return (*this);
		
	Camera::operator= (rhs);

	psi_max 		= rhs.psi_max;
	lambda_max      = rhs.lambda_max;

	return (*this);
}


// ----------------------------------------------------------------------------- destructor

Spherical::~Spherical(void) {}	


// ----------------------------------------------------------------------------- ray_direction

Vector3D 
Spherical::ray_direction(const Point2D& pp, const int hres,
			const int vres, const float s) const{

    // compute the normalized device coordinates

    Point2D pn(2.0f / (s * static_cast<float>(hres)) * pp.x, 2.0f / (s * static_cast<float>(vres)) * pp.y);

    // compute the angles lambda and psi in radians

    float lambda = pn.x * lambda_max * PI_ON_180;
    float psi = pn.y * psi_max * PI_ON_180;

    // compute the sherical azimuth and polar angles

    float phi = PI - lambda;
    float theta = 0.5f * PI - psi;

    float sin_phi = sinf(phi);
    float cos_phi = cosf(phi);
    float sin_theta = sinf(theta);
    float cos_theta = cosf(theta);

    Vector3D dir = sin_theta * sin_phi * u + cos_theta * v + sin_theta * cos_phi * w;

    return dir;
}



// ----------------------------------------------------------------------------- render_scene

void 												
Spherical::render_scene(World& w) {
	RGBColor L;
    ViewPlane vp(w.vp);
	float s = vp.s;
	int hres = vp.hres;
	int vres = vp.vres;
	Ray ray;
    int depth = 0;

    Point2D sp; // Sample point in unity square
    Point2D pp; // Sample point on pixel

	w.open_window(hres, vres);
	
	ray.o = eye;
	for (int r = 0; r < vp.vres; r++)			// up
		for (int c = 0; c < vp.hres; c++) {		// across 					
			L = black; 
			
			for (int n = 0; n < vp.num_samples; n++) {
				sp = vp.sampler_ptr->sample_unit_square();
				pp.x = 	s * (c - hres * 0.5 + sp.x);	
				pp.y = 	s * (r - vres * 0.5 + sp.y);

				
				ray.d = ray_direction(pp, hres, vres, s);

				
				L += w.tracer_ptr->trace_ray(ray);
					
			}	
											
			L /= vp.num_samples;
			L *= exposure_time;
			w.display_pixel(r, c, L);
		} 
}


