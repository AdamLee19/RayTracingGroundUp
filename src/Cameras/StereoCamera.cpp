// This file contains the definition of the Pinhole class

#include "Constants.h" 
#include "Point3D.h"
#include "Vector3D.h"
#include "StereoCamera.h"
#include "Pinhole.h"
#include <math.h>

// ----------------------------------------------------------------------------- default constructor

StereoCamera::StereoCamera(void)		
	:	Camera(),
		viewing_type(parallel),
		pixel_gap(5),
		beta(0.75),
		left_camera_ptr(nullptr),
		right_camera_ptr(nullptr)
{}


// ----------------------------------------------------------------------------- copy constructor

StereoCamera::StereoCamera(const StereoCamera& c)   		
	: 	Camera(c),
		viewing_type(c.viewing_type),
		pixel_gap(c.pixel_gap),
		beta(c.beta),
		left_camera_ptr(c.left_camera_ptr -> clone()),
		right_camera_ptr(c.right_camera_ptr -> clone())
{}


// ----------------------------------------------------------------------------- clone

Camera* 
StereoCamera::clone(void) const {
	return (new StereoCamera(*this));
}


// ----------------------------------------------------------------------------- set_left_camera
void 
StereoCamera::set_left_camera(Camera* c){
    if(left_camera_ptr){
        delete left_camera_ptr;
        left_camera_ptr = nullptr;
    }
    left_camera_ptr = c -> clone();
}

// ----------------------------------------------------------------------------- set_right_camera
void 
StereoCamera::set_right_camera(Camera* c){
    if(right_camera_ptr){
        delete right_camera_ptr;
        right_camera_ptr = nullptr;
    }
    right_camera_ptr = c -> clone();
}


// ----------------------------------------------------------------------------- assignment operator

StereoCamera& 
StereoCamera::operator= (const StereoCamera& rhs) { 	
	if (this == &rhs)
		return (*this);
		
	Camera::operator= (rhs);

	viewing_type    = rhs.viewing_type;
	pixel_gap       = rhs.pixel_gap;
	beta            = rhs.beta;
	left_camera_ptr	= rhs.left_camera_ptr -> clone();
	right_camera_ptr	= rhs.right_camera_ptr -> clone();
	
	return (*this);
}


// ----------------------------------------------------------------------------- destructor

StereoCamera::~StereoCamera(void) 
{
	if (left_camera_ptr) delete left_camera_ptr;
	if (right_camera_ptr) delete right_camera_ptr;
}

// ----------------------------------------------------------------------------- setup_cameras
void 
StereoCamera::setup_cameras(void) {
	double r = eye.distance(lookat);
	double x = r * tan(0.5 * beta * PI_ON_180);  //  half the camera separation distance
		
	left_camera_ptr->set_eye(eye - x * u);
	left_camera_ptr->set_lookat(lookat - x * u);
	left_camera_ptr->compute_uvw();
	
	right_camera_ptr->set_eye(eye + x * u);
	right_camera_ptr->set_lookat(lookat + x * u);
	right_camera_ptr->compute_uvw();
}


// ----------------------------------------------------------------------------- render_scene

void 												
StereoCamera::render_scene(World& w) {
	
	ViewPlane	vp 		= w.vp;					
	int 		hres	= vp.hres;
	int 		vres 	= vp.vres;
	
	
	w.open_window(2 * hres + pixel_gap, vres);  
						
	double r = eye.distance(lookat);
	double x = r * tan(0.5 * beta * PI_ON_180);  
		
	if (viewing_type == parallel) {
		left_camera_ptr->render_stereo(w, x, 0);						// left view on left
		right_camera_ptr->render_stereo(w, -x, hres + pixel_gap);   	// right view on right
	}
	
	if (viewing_type == transverse) {
		right_camera_ptr->render_stereo(w, -x, 0);   					// right view on left
		left_camera_ptr->render_stereo(w, x, hres + pixel_gap);    		// left view on right
	}
}


