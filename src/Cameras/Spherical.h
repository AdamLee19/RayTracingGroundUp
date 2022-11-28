#ifndef __Spherical__
#define __Spherical__

// This file contains the declaration of the class Pinhole

#include "Point2D.h"
#include "Sampler.h"    // we can #include "World.h" here
#include "Camera.h"
#include "World.h"  

//--------------------------------------------------------------------- class Pinhole

class Spherical: public Camera {
	public:
	
		Spherical();   							

		Spherical(const Spherical& s);	
		
		virtual Camera*						
		clone(void) const;			

		Spherical& 							
		operator= (const Spherical& rhs);	
		
		virtual
		~Spherical();   						
			
		void
		set_horizontal_fov(const float fov);
		void
		set_vertical_fov(const float fov);
		

		
		Vector3D								
		ray_direction(const Point2D& pp, const int hres,
			const int vres, const float s) const;
		
		virtual void 												
		render_scene(World& w);
		
	private:
		
		float   psi_max;
		float   lambda_max;
		
		
};

//-------------------------------------------------------------------------- set_vertical_fov

inline void
Spherical::set_horizontal_fov(const float fov) {
	lambda_max = fov / 2.0f;
}	
//-------------------------------------------------------------------------- set_vertical_fov	
inline void
Spherical::set_vertical_fov(const float fov) {
	psi_max = fov / 2.0f;
}	



#endif