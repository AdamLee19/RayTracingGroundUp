#ifndef __ThinLens__
#define __ThinLens__

// This file contains the declaration of the class Pinhole

#include "Point2D.h"
#include "Sampler.h"    // we can #include "World.h" here
#include "Camera.h"
#include "World.h"  

//--------------------------------------------------------------------- class Pinhole

class ThinLens: public Camera {
	public:
	
		ThinLens();   							

		ThinLens(const ThinLens& ph);	
		
		virtual Camera*						
		clone(void) const;			

		ThinLens& 							
		operator= (const ThinLens& rhs);	
		
		virtual
		~ThinLens();   						
			
		void
		set_lens_radius(const float lr);
		void
		set_view_distance(const float vpd);
		void
		set_flocal_distance(const float f);
		void
		set_zoom(const float zoom_factor);
		void
		set_sampler(Sampler* sp);

		
		Vector3D								
		ray_direction(const Point2D& pixel_point, const Point2D& lens_point) const;
		
		virtual void 												
		render_scene(const World& w);
		
	private:
		
		float   lens_radius;
		float	d;		// view plane distance
		float   f;
		float	zoom;	// zoom factor
		Sampler *sampler_ptr;
		
};

//-------------------------------------------------------------------------- set_lens_radius

inline void
ThinLens::set_lens_radius(const float lr) {
	lens_radius = lr;
}	
	


//-------------------------------------------------------------------------- set_vpd

inline void
ThinLens::set_view_distance(float _d) {
	d = _d;
}	
	

//-------------------------------------------------------------------------- set_flocal_distance

inline void
ThinLens::set_flocal_distance(const float _f) {
	f = _f;
}	
	

//-------------------------------------------------------------------------- set_zoom

inline void
ThinLens::set_zoom(float zoom_factor) {
	zoom = zoom_factor;
}	

#endif