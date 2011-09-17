#include <glutwindow.hpp>
#include <ppmwriter.hpp>
#include <pixel.hpp>
//#include <unittest++/UnitTest++.h>

#include <iostream>
#include <cmath>

#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

#include <vector.hpp>
#include <matrix.hpp>
#include <point.hpp>
#include "material.hpp"
#include "triangle.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "scene.hpp"
#include "tube.hpp"
#include "cone.hpp"
#include "color.hpp"
#include "renderer.hpp"
#include "circle.hpp"

#ifdef __APPLE__
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

/*for (std::size_t y = 0; y < window.height(); ++y)
{
	for (std::size_t x = 0; x < window.width(); ++x)
	{
        // create pixel at x,y
        pixel p(x, y);

        example_math3d();

        // compute color for pixel
        if ( ((x/checkersize)%2) != ((y/checkersize)%2)) {
	        p.rgb = color(0.0, 1.0, float(x)/window.height());
        } else {
			p.rgb = color(1.0, 0.0, float(y)/window.width());
        }

        // write pixel to output window
        window.write(p);

        // write pixel to image writer
        image.write(p);
	}
}


// save final image
    image.save();
  }*/


/*SUITE(ambient)
{
    TEST(get_reflectivity)
    {
        material mat;
        CHECK_EQUAL(1, mat.get_reflectivity());
    }
}*/







// this is a dummy raytrace application
class application
{
public :

  // raytracing is initiated from here
  void start()
  {
    // the following code might also be executed in any method
    // just start your raytracing algorithm from here


    scene_.load_sdf("material.sdf");
    renderer_.set_scene(scene_);
    //std::cout << "read sdf file" << std::endl;

    // get glutwindow instance
    glutwindow& window = glutwindow::instance();

    // create a ppmwriter
    ppmwriter image (window.width(), window.height(), "./checkerboard.ppm");

    // for all pixels of window
    for (std::size_t y = 0; y < window.height(); ++y)
    {
      for (std::size_t x = 0; x < window.width(); ++x)
      {
        // create pixel at x,y
        pixel p(x, y);

        ray r = scene_.main_camera().calc_eye_ray(x,y);


        color c = renderer_.raytrace(r);
        // size of a tile in checkerboard
        p.rgb = c;

        // write pixel to output window
        window.write(p);

        // write pixel to image writer
        image.write(p);
      }
    }

    // save final image
    image.save();
  }

  // this method shows how to use the supplied classes for matrix, point and vector
  /*void example_math3d()
  {
    // create some geometric objects
    math3d::point origin;
    math3d::point p0 ( 1.0, 5.0, -3.0 );
    math3d::vector v0 ( 2.0, 2.0, 1.0 );

    // some methods
    v0.normalize();

    // operator's
    math3d::vector v1 = origin - p0;  // difference between points is a vector
    double z_component = v0[2];       // random access into components of point/vector

    // you can create transformation matrices
    math3d::matrix rotate = math3d::make_rotation_x ( M_PI / 4.0 );    // rotation matrix: 45 deg about x axis
    math3d::matrix scale  = math3d::make_scale      ( 1.0, 2.0, 1.0 ); // scale y axis
    math3d::matrix invrot = math3d::inverse(rotate);

    // concatenate transformations and transform points or vectors
    math3d::vector tv0 = rotate * scale * v0;
    math3d::point  tp0 = rotate * scale * p0;
  }*/

private : // attributes

  // you may add your scene description here
  scene scene_;
  renderer renderer_;
};





int main(int argc, char* argv[])
{   /*
    point3d a(0,0,-20);
    point3d b(0,6,-20);
    point3d c(6,0,-20);
    material m;
    point3d origin (0,0,0);
    point3d direction (-0.2,-0.1,-1);
    circle circ ("name",m,a,b,c);
    ray r (origin, direction);
    double t=circ.intersect(r);
    std::cout<<"Abstand sollte 20,4939 sein."<<t<<std::endl;


    point3d p1 (4,4,-20);
    point3d p2 (0,0,-24);
    material mat;
    box bo("box",mat,p1,p2);
    point3d origin2 (3,2,0);
    point3d dir2 (3,2,-1);
    ray l(origin2, dir2);
    double d=bo.intersect(l);
    std::cout<<"Abstand sollte 20 sein."<<d<<std::endl;



    material mat;
    std::cout<<mat<<std::endl;

    shape* dbox = new box ("die box", mat, point3d(1,1,1), point3d(2,2,2));
    std::cout<<*dbox<<std::endl;

    triangle tr;
    std::cout<<tr<<std::endl;

    box box;
    std::cout<<box<<std::endl;

    sphere kugel;
    std::cout<<kugel<<std::endl;

    point3d punkt (3,3,3);
    color grau (0.8,0.8,0.5);
    material betong ("Betong",(grau),(grau),(grau),0.1);
    sphere ball ("Ball", betong, 2.0, (punkt));
    std::cout<<ball<<std::endl;

    tube conan;
    std::cout<<conan<<std::endl;

    cone tuba;
    std::cout<<tuba<<std::endl;

    ray r;
    kugel.intersect(r);*/







  // set resolution and checkersize
  const std::size_t width = 500;
  const std::size_t height = 500;

  // create output window
  glutwindow::init(width, height, 1350, 510, "CheckerBoard", argc, argv);

  // create a ray tracing application
  application app;

  // start computation in thread
  boost::thread thr(boost::bind(&application::start, &app));

  // start output on glutwindow
  glutwindow::instance().run();

  // wait on thread
  thr.join();

  return 0;//UnitTest::RunAllTests();
}



