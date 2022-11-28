#ifndef __StereoCamera__
#define __StereoCamera__


#include "Point2D.h"
#include "Sampler.h"    // we can #include "World.h" here
#include "Camera.h"
#include "World.h"  

//--------------------------------------------------------------------- class Pinhole

typedef enum {
	parallel, 
	transverse
} ViewingType;

#include "Camera.h"

class StereoCamera: public Camera {						
	public:
	
		StereoCamera();

		StereoCamera(const StereoCamera& c);

		virtual Camera*						
		clone(void) const;

		StereoCamera& 							
		operator= (const StereoCamera& rhs);

		virtual
		~StereoCamera();	
		
		void 
		setup_cameras(void);

		void
		use_parallel_viewing();

		void
		use_transverse_viewing();

		void
		set_pixel_gap(const int pg);

		void
		set_stereo_angle(const float angle);

		void
		set_left_camera(Camera* c);

		void
		set_right_camera(Camera* c);

		virtual void 												
		render_scene(World& w);
		
	private:
		
		ViewingType	viewing_type;		// parallel or transverse viewing
		int			pixel_gap;			// gap in pixels between the left and right images
		float		beta;				// stereo separation angle	
		Camera*		left_camera_ptr;	// left eye camera
		Camera*		right_camera_ptr;	// right eye camera
};



//-------------------------------------------------------------------------- use_parallel_viewing

inline void
StereoCamera::use_parallel_viewing()
{
	viewing_type = ViewingType::parallel;
}

//-------------------------------------------------------------------------- use_transverse_viewing

inline void
StereoCamera::use_transverse_viewing()
{
	viewing_type = ViewingType::transverse;
}

//-------------------------------------------------------------------------- set_pixel_gap
inline void
StereoCamera::set_pixel_gap(const int pg)
{
	pixel_gap = pg;
}

//-------------------------------------------------------------------------- set_stereo_angle
inline void
StereoCamera::set_stereo_angle(const float angle)
{
	beta = angle;
}


#endif