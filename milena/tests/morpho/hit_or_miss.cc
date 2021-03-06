// Copyright (C) 2007, 2008, 2009, 2010 EPITA Research and Development
// Laboratory (LRDE)
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

#include <mln/core/image/image2d.hh>
#include <mln/value/int_u8.hh>

#include <mln/win/rectangle2d.hh>
#include <mln/core/alias/window2d.hh>

#include <mln/win/shift.hh>
#include <mln/win/diff.hh>

#include <mln/io/pbm/load.hh>
#include <mln/io/pbm/save.hh>
#include <mln/data/fill.hh>

#include <mln/morpho/hit_or_miss.hh>

# include <mln/convert/to.hh>

#include "tests/data.hh"


int main()
{
  using namespace mln;
  using value::int_u8;

  window2d win_hit = win::shift(win::rectangle2d(3, 3),
				dpoint2d(+1, +1));
  window2d win_miss = win::rectangle2d(5, 5) - win_hit;

  {
    bool hit[] = { 0, 0, 0, 0, 0,
		   0, 0, 0, 0, 0,
		   0, 0, 1, 1, 1,
		   0, 0, 1, 1, 1,
		   0, 0, 1, 1, 1 };
    window2d win_hit_ = convert::to<window2d>(hit);
    mln_assertion(win_hit_ == win_hit);

    bool miss[] = { 1, 1, 1, 1, 1,
		    1, 1, 1, 1, 1,
		    1, 1, 0, 0, 0,
		    1, 1, 0, 0, 0,
		    1, 1, 0, 0, 0 };
    window2d win_miss_ = convert::to<window2d>(miss);
    mln_assertion(win_miss_ == win_miss);
  }

  border::thickness = 2;

  image2d<bool> pic;
  io::pbm::load(pic, MLN_IMG_DIR "/picasso.pbm");
  image2d<bool> out = morpho::hit_or_miss(pic, win_hit, win_miss);
  io::pbm::save(out, "hit_or_miss-out.pbm");

  mln_postcondition(morpho::hit_or_miss(morpho::complementation(pic),
					win_miss, win_hit) == out);

  // FIXME: Do not work if the input image is pgm!
}
