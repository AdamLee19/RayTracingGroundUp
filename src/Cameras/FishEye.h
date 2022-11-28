#ifndef __FishEye__
#define __FishEye__

// This file contains the declaration of the class Pinhole

#include "Point2D.h"
#include "Sampler.h"    // we can #include "World.h" here
#include "Camera.h"
#include "World.h"  

//--------------------------------------------------------------------- class Pinhole

class FishEye: public Camera {
	public:
	
		FishEye();   							

		FishEye(const FishEye& fe);	
		
		virtual Camera*						
		clone(void) const;			

		FishEye& 							
		operator= (const FishEye& rhs);	
		
		virtual
		~FishEye();   						
			
		void
		set_fov(const float fov);
		

		
		Vector3D								
		ray_direction(const Point2D& pp, const int hres,
			const int vres, const float s, float& r_squared) const;
		
		virtual void 												
		render_scene(World& w);
		
	private:
		
		float   psi_max;
		
		
};

//-------------------------------------------------------------------------- set_lens_radius

inline void
FishEye::set_fov(const float fov) {
	psi_max = fov / 2.0f;
}	
	




#endif