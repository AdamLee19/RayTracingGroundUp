
void 												
World::build(void) {

	int num_samples = 100;

    vp.set_hres(400);
	vp.set_vres(400);
	vp.set_pixel_size(1.0);
	vp.set_gamma(1.0);
	vp.set_sampler(new MultiJittered(num_samples));

	
	background_color = white;
	tracer_ptr = new SingleSphere(this); 
	
	sphere.set_center(0, 0, 150.0);
	sphere.set_radius(10);

	FishEye* camera_ptr = new FishEye;
	camera_ptr->set_fov(360);
	
	camera_ptr->set_eye(0, 0, 90);
	camera_ptr->set_lookat(0);    
	
	camera_ptr->compute_uvw();		  
	set_camera(camera_ptr);
}
