void 												
World::build(void) {
	int num_samples = 100;

    vp.set_hres(400);
	vp.set_vres(400);
	vp.set_pixel_size(1.0);
	vp.set_gamma(1.0);
	vp.set_sampler(new MultiJittered(num_samples));

	
	background_color = white;
	tracer_ptr = new MultipleObjects(this); 
	// use access functions to set centre and radius
	
	Sphere* sphere_ptr = new Sphere;
	sphere_ptr->set_center(0, -25, 0);
	sphere_ptr->set_radius(80);
	sphere_ptr->set_color(1, 0, 0);  // red
	add_object(sphere_ptr);

	// use constructor to set centre and radius 
	
	sphere_ptr = new Sphere(Point3D(0, 30, 0), 60);
	sphere_ptr->set_color(1, 1, 0);	// yellow
	add_object(sphere_ptr);
	
	Plane* plane_ptr = new Plane(Point3D(0), Normal(0, 1, 1));
	plane_ptr->set_color(0.0, 0.3, 0.0);	// dark green
	add_object(plane_ptr);

	Spherical* camera_ptr = new Spherical;
	camera_ptr->set_horizontal_fov(360);
	camera_ptr->set_vertical_fov(180);
	
	camera_ptr->set_eye(0, 0, 250);
	camera_ptr->set_lookat(0);    
	
	camera_ptr->compute_uvw();		  
	set_camera(camera_ptr);
}
