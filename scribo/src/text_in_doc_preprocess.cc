// Copyright (C) 2010 EPITA Research and Development Laboratory (LRDE)
//
// This file is part of Olena.
//
// Olena is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free
// Software Foundation, version 2 of the License.
//
// Olena is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Olena.  If not, see <http://www.gnu.org/licenses/>.
//
// As a special exception, you may use this file as part of a free
// software project without restriction.  Specifically, if other files
// instantiate templates or use macros or inline functions from this
// file, or you compile this file and link it with other files to produce
// an executable, this file does not by itself cause the resulting
// executable to be covered by the GNU General Public License.  This
// exception does not however invalidate any other reasons why the
// executable file might be covered by the GNU General Public License.


#include <libgen.h>
#include <iostream>

#include <mln/core/image/image2d.hh>

#include <mln/io/magick/load.hh>
#include <mln/io/pbm/save.hh>

#include <mln/value/rgb8.hh>

#include <mln/logical/not.hh>

#include <scribo/binarization/sauvola_ms.hh>

#include <scribo/debug/usage.hh>

#include <scribo/preprocessing/split_bg_fg.hh>
#include <scribo/preprocessing/deskew.hh>


#include <mln/io/pgm/all.hh>


const char *args_desc[][2] =
{
  { "input.*", "An image." },
  { "output.pbm", "A text file with all the recognized text" },
  { "enable fg/bg", "If set to 1 enables foreground extraction. (disabled by default)" },
  { "lambda", "Lambda used in remove fg/bg (Automaticaly deduced by default)." },
  {0, 0}
};


int main(int argc, char* argv[])
{
  using namespace scribo;
  using namespace mln;

  if (argc != 3 && argc != 4 && argc != 5)
    return scribo::debug::usage(argv,
				"Find text in a color document.",
				"input.* output.pbm <enable fg/bg> <lambda>",
				args_desc);

  image2d<value::rgb8> input_rgb;
  io::magick::load(input_rgb, argv[1]);

  unsigned lambda;
  if (argc == 5)
    lambda = atoi(argv[4]);
  else
    lambda = 1.2 * (input_rgb.nrows() + input_rgb.ncols());

  // Extract foreground
  if (argc >= 4 && atoi(argv[3]) == 1)
  {
    std::cout << "Extracting foreground..." << std::endl;
    input_rgb = preprocessing::split_bg_fg(input_rgb, lambda, 32).second();
  }

  // Convert to Gray level image.
  image2d<value::int_u8>
    input_gl = data::transform(input_rgb, mln::fun::v2v::rgb_to_int_u<8>());


  // Deskewing
  std::cout << "Deskew if needed..." << std::endl;
  input_gl = preprocessing::deskew(input_gl);

  // Binarize foreground to use it in the processing chain.
  std::cout << "Binarizing foreground..." << std::endl;
  image2d<bool> input_bin = scribo::binarization::sauvola_ms(input_gl, 101, 3);

  logical::not_inplace(input_bin);

  mln::io::pbm::save(input_bin, argv[2]);
}