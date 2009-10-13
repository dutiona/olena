// DEMO ON KMEAN2D

#include <mln/clustering/kmean2d.hh>

#include <iostream>
#include <sstream>

#include <mln/img_path.hh>
#include <mln/pw/value.hh>

#include <mln/value/int_u8.hh>
#include <mln/value/label_8.hh>
#include <mln/value/rgb8.hh>
#include <mln/value/value_array.hh>

#include <mln/core/macros.hh>
#include <mln/core/image/image2d.hh>
#include <mln/core/image/dmorph/image_if.hh>

#include <mln/data/transform.hh>
#include <mln/fun/v2v/rgb8_to_rgbn.hh>
#include <mln/fun/v2v/component.hh>

#include <mln/io/ppm/load.hh>
#include <mln/io/pgm/load.hh>
#include <mln/io/pgm/save.hh>
#include <mln/io/ppm/save.hh>
#include <mln/io/plot/save_image_sh.hh>

#include <mln/value/rg.hh>
#include <mln/fun/v2v/rgb_to_rg.hh>
#include <mln/fun/v2v/rg_to_rgb.hh>

#include <mln/accu/stat/histo2d.hh>
#include <mln/data/compute.hh>



void do_demo(const std::string& image,
	     const unsigned     k_center,
	     const unsigned     n_times,
	     const unsigned     watch_dog)
{
  typedef mln::clustering::kmean2d<double,8>          t_kmean;
  typedef mln::value::rg<8>                           t_rg8;
  typedef mln::value::rgb8                            t_rgb8;
  typedef mln::value::int_u8                          t_int_u8;
  typedef mln::algebra::vec<2,t_int_u8>               t_vec_rg8;
  typedef mln::image2d<t_rgb8>                        t_image2d_rgb8;
  typedef mln::image2d<t_int_u8>                      t_image2d_int_u8;
  typedef mln::fun::v2v::component<t_rgb8, 0>         t_comp_red;
  typedef mln::fun::v2v::component<t_rgb8, 1>         t_comp_green;
  typedef mln::fun::v2v::component<t_rgb8, 2>         t_comp_blue;
  typedef mln::fun::v2v::rgb_to_rg<8>                 t_rgb_to_rg;
  typedef mln::fun::v2v::rg_to_rgb<8>                 t_rg_to_rgb;
  typedef mln::image2d<t_vec_rg8>                     t_image2d_vec_rg8;
  typedef mln::image2d<t_rg8>                         t_image2d_rg8;
  typedef mln::image2d<unsigned>                      t_histo2d;

  t_image2d_rgb8                                      house_rgb8;
  t_image2d_int_u8                                    house_red;
  t_image2d_int_u8                                    house_blue;
  t_image2d_int_u8                                    house_green;
  //t_image2d_vec_rg8                                   house_rg8;
  t_image2d_rgb8                                      house_cast;
  t_image2d_rg8                                       house_rg8;
  t_histo2d                                           house_histo;


  mln::io::ppm::load(house_rgb8, image.c_str());
  house_red   = mln::data::transform(house_rgb8, t_comp_red());
  house_green = mln::data::transform(house_rgb8, t_comp_green());
  house_blue  = mln::data::transform(house_rgb8, t_comp_blue());

  house_rg8   = mln::data::transform(house_rgb8, t_rgb_to_rg());
  house_histo = mln::data::compute(mln::accu::meta::stat::histo2d(), house_rg8);

  house_cast  = mln::data::transform(house_rg8,  t_rg_to_rgb());

  t_kmean kmean(house_rg8, k_center, watch_dog, n_times);

  mln::io::pgm::save(house_red,   "red.pgm");
  mln::io::pgm::save(house_green, "green.pgm");
  mln::io::pgm::save(house_blue,  "blue.pgm");
  mln::io::ppm::save(house_cast,  "red_green.ppm");
  mln::io::pgm::save(house_histo, "histo.pgm");
  mln::io::plot::save_image_sh(house_histo, "histo.sh");

/*
  mln::io::plot::save_image_sh(mean_img,     "mean.sh");
  mln::io::plot::save_image_sh(mean_cnv,     "mean_cnv.sh");
  mln::io::plot::save_image_sh(variance_cnv, "variance_cnv.sh");
*/
}
/*
void do_demo(const std::string& image,
	     const unsigned     k_center,
	     const unsigned     n_times,
	     const unsigned     watch_dog)
{
  typedef mln::clustering::kmean3d<double,5>          t_kmean;
  typedef mln::value::label_8                         t_label_8;
  typedef mln::value::rgb8                            t_rgb8;
  typedef mln::value::rgb<5>                          t_rgb5;
  typedef mln::image2d<t_rgb8>                        t_image2d_rgb8;
  typedef mln::image2d<t_rgb5>                        t_image2d_rgb5;

  t_image2d_rgb8                                      house_rgb8;
  t_image2d_rgb5                                      house_rgb5;

  mln::io::ppm::load(house_rgb8, image.c_str());
  house_rgb5=mln::data::transform(house_rgb8,mln::fun::v2v::rgb8_to_rgbn<5>());

  t_kmean kmean(house_rgb5, k_center, watch_dog, n_times);

  mln::trace::quiet = false;

  //kmean.launch_one_time();
  kmean.launch_n_times();

  // Not safe because we don't test kmean.is_valid()

  t_kmean::t_color_dbg    color_img    = kmean.get_color_dbg();
  t_kmean::t_mean_dbg     mean_img     = kmean.get_mean_dbg();
  t_kmean::t_label_dbg    label_img    = kmean.get_label_dbg();
  t_kmean::t_variance_cnv variance_cnv = kmean.get_variance_cnv();
  t_kmean::t_mean_cnv     mean_cnv     = kmean.get_mean_cnv();

  mln::io::ppm::save(mean_img,  "mean.ppm");
  mln::io::ppm::save(color_img, "color.ppm");
  mln::io::pgm::save(label_img, "label.pgm");

  mln::io::plot::save_image_sh(mean_img,     "mean.sh");
  mln::io::plot::save_image_sh(mean_cnv,     "mean_cnv.sh");
  mln::io::plot::save_image_sh(variance_cnv, "variance_cnv.sh");
}
*/
void demo(const std::string& image     = OLENA_IMG_PATH"/house.ppm",
	  const unsigned     k_center  = 3,
	  const unsigned     n_times   = 10,
	  const unsigned     watch_dog = 10)
{
  std::cout << "----------------------------------------" << std::endl;
  std::cout << "Launching the demo with these parameters" << std::endl;
  std::cout << "image     : " << image                    << std::endl;
  std::cout << "k_center  : " << k_center                 << std::endl;
  std::cout << "n_times   : " << n_times                  << std::endl;
  std::cout << "watch_dog : " << watch_dog                << std::endl;
  std::cout << "----------------------------------------" << std::endl;

  do_demo(image, k_center, n_times, watch_dog);
}

void usage(const int argc, const char *args[])
{
  std::cout << "----------------------------------------" << std::endl;
  std::cout << "argc    : " << argc                       << std::endl;

  for (int i = 0; i < argc; ++i)
    std::cout << "args[" << i << "] : " << args[i] << std::endl;

  std::cout << "----------------------------------------" << std::endl;
  std::cout << "usage: kmean1d [image [k_center [n_times [watch_dog]]]]"
	    << std::endl;
  std::cout << "pbm image          (points to work with)" << std::endl;
  std::cout << "unsigned k_center  (number of centers)"   << std::endl;
  std::cout << "unsigned n_times   (number of launching)" << std::endl;
  std::cout << "unsigned watch_dog (convergence loop)"    << std::endl;
  std::cout << "----------------------------------------" << std::endl;
}

bool char_to_unsigned(const bool status, const char *arg, unsigned& val)
{
  bool result = false;

  if (status)
  {
    std::istringstream arg_stream(arg);

    arg_stream >> val;

    result = !arg_stream.fail();
  }

  return result;
}

bool char_to_string(const bool status, const char *arg, std::string& val)
{
  bool result = false;

  if (status)
  {
    std::istringstream arg_stream(arg);

    arg_stream >> val;

    return !arg_stream.fail();
  }

  return result;
}

int main(const int argc, const char *args[])
{
  std::string image("top");
  unsigned    k_center;
  unsigned    watch_dog;
  unsigned    n_times;
  bool        status = true;

  switch (argc)
  {
  case 5:  status = char_to_unsigned(status, args[4], watch_dog);
  case 4:  status = char_to_unsigned(status, args[3], n_times);
  case 3:  status = char_to_unsigned(status, args[2], k_center);
  case 2:  status = char_to_string(status, args[1], image); break;
  case 1:  status = true; break;
  default: status = false;
  }

  if (status)
  {
    switch (argc)
    {
    case 1: demo(); break;
    case 2: demo(image); break;
    case 3: demo(image, k_center); break;
    case 4: demo(image, k_center, n_times); break;
    case 5: demo(image, k_center, n_times, watch_dog); break;
    }
  }
  else
    usage(argc, args);

  return 0;
}