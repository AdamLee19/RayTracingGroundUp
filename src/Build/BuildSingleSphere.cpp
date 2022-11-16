
void 												
World::build(void) {

	int num_samples = 25;

    vp.set_hres(400);
	vp.set_vres(400);
	vp.set_pixel_size(1.0);
	vp.set_gamma(1.0);
	vp.set_sampler(new Jittered(num_samples));

	
	background_color = white;
	tracer_ptr = new SingleSphere(this); 
	
	sphere.set_center(0.0);
	sphere.set_radius(85);

	Pinhole* camera_ptr = new Pinhole;
	camera_ptr->set_eye(0, 0, 150);
	camera_ptr->set_lookat(0);    
	camera_ptr->set_view_distance(50); 
	
	camera_ptr->compute_uvw();		  
	set_camera(camera_ptr);
}
