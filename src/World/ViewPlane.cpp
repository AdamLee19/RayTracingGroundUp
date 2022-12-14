// This file contains the definition the ViewPlane class

#include "ViewPlane.h"
#include "Regular.h"
#include "MultiJittered.h"
	
// ---------------------------------------------------------------- default constructor	
						
ViewPlane::ViewPlane(void)							
	: 	hres(400), 
		vres(400),
		s(1.0),
		num_samples(25),
		sampler_ptr(nullptr),
		gamma(1.0),
		inv_gamma(1.0),
		show_out_of_gamut(false)
{}


// ---------------------------------------------------------------- copy constructor

ViewPlane::ViewPlane(const ViewPlane& vp)   
	:  	hres(vp.hres),  
		vres(vp.vres), 
		s(vp.s),
		num_samples(vp.num_samples),
		gamma(vp.gamma),
		inv_gamma(vp.inv_gamma),
		show_out_of_gamut(vp.show_out_of_gamut)
{
	if(vp.sampler_ptr != nullptr) {
		sampler_ptr = vp.sampler_ptr->clone();
	}
}


// ---------------------------------------------------------------- assignment operator

ViewPlane& 
ViewPlane::operator= (const ViewPlane& rhs) {
	if (this == &rhs)
		return (*this);
		
	hres 				= rhs.hres;
	vres 				= rhs.vres;
	s					= rhs.s;
	num_samples 		= rhs.num_samples;
	gamma				= rhs.gamma;
	inv_gamma			= rhs.inv_gamma;
	show_out_of_gamut	= rhs.show_out_of_gamut;

	if(rhs.sampler_ptr != nullptr) {
		if (sampler_ptr) {
			delete sampler_ptr;
			sampler_ptr = nullptr;
		}
		sampler_ptr = rhs.sampler_ptr->clone();
	}
	return (*this);
}


// -------------------------------------------------------------- destructor

ViewPlane::~ViewPlane(void) 
{
	delete sampler_ptr;
}



// -------------------------------------------------------------- set_sampler

void
ViewPlane::set_sampler(Sampler* sp)
{
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = nullptr;
	}

	num_samples = sp->get_num_samples();
	sampler_ptr = sp;
}


// -------------------------------------------------------------- set_samplers
void ViewPlane::set_samples(const int n) {
	num_samples = n;

	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = nullptr;
	}

	if (num_samples > 1)
		sampler_ptr = new MultiJittered(num_samples);
	else
		sampler_ptr = new Regular(1);
}




	





