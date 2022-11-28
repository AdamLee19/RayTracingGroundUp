// This file contains the definition of the Pinhole class

#include "Constants.h" 
#include "Point3D.h"
#include "Vector3D.h"
#include "FishEye.h"
#include <math.h>

// ----------------------------------------------------------------------------- default constructor

FishEye::FishEye(void)		
	:	Camera(),
		psi_max(180)
{}


// ----------------------------------------------------------------------------- copy constructor

FishEye::FishEye(const FishEye& fe)
	: 	Camera(fe),
		psi_max(fe.psi_max)
{}


// ----------------------------------------------------------------------------- clone

Camera* 
FishEye::clone(void) const {
	return (new FishEye(*this));
}



// ----------------------------------------------------------------------------- assignment operator

FishEye& 
FishEye::operator= (const FishEye& rhs) { 	
	if (this == &rhs)
		return (*this);
		
	Camera::operator= (rhs);

	psi_max 		= rhs.psi_max;

	return (*this);
}


// ----------------------------------------------------------------------------- destructor

FishEye::~FishEye(void) {}	


// ----------------------------------------------------------------------------- ray_direction

Vector3D 
FishEye::ray_direction(const Point2D& pp, const int hres,
			const int vres, const float s, float& r_squared) const{

    Point2D pn(2.0f / (s * hres) * pp.x, 2.0f / (s * vres) * pp.y);
    r_squared = pn.x * pn.x + pn.y * pn.y;

    if (r_squared <= 1.0f) {
        float r = sqrtf(r_squared);
        float psi = r * psi_max * PI_ON_180;
        float sin_psi = sinf(psi);
        float cos_psi = cosf(psi);
        float sin_alpha = pn.y / r;
        float cos_alpha = pn.x / r;
        Vector3D dir = sin_psi * cos_alpha * u + sin_psi * sin_alpha * v - cos_psi * w;

        return dir;
    } else
        return Vector3D(0.0f);
}



// ----------------------------------------------------------------------------- render_scene

void 												
FishEye::render_scene(World& w) {
	RGBColor L;
    ViewPlane vp(w.vp);
	float s = vp.s;
	int hres = vp.hres;
	int vres = vp.vres;
	Ray ray;
    int depth = 0;

    Point2D sp; // Sample point in unity square
    Point2D pp; // Sample point on pixel
    float r_squared;


	w.open_window(hres, vres);
		
	ray.o = eye;
	for (int r = 0; r < vp.vres; r++)			// up
		for (int c = 0; c < vp.hres; c++) {		// across 					
			L = black; 
			
			for (int n = 0; n < vp.num_samples; n++) {
				sp = vp.sampler_ptr->sample_unit_square();
				pp.x = 	s * (c - hres * 0.5 + sp.x);	
				pp.y = 	s * (r - vres * 0.5 + sp.y);

				
				ray.d = ray_direction(pp, hres, vres, s, r_squared);

				if (r_squared <= 1.0){
					L += w.tracer_ptr->trace_ray(ray);
				}
				
					
			}	
											
			L /= vp.num_samples;
			L *= exposure_time;
			w.display_pixel(r, c, L);
		} 
}


