// Copyright (C) 2009 EPITA Research and Development Laboratory (LRDE)
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

#include <mln/core/alias/point2d.hh>
#include <mln/world/inter_pixel/separator_to_pixels.hh>


int main()
{
  using namespace mln;
  using namespace world::inter_pixel;

  point2d
    p00(0, 0), p01(0, 1), p02(0, 2),
    p10(1, 0), 
    p20(2, 0);

  {
    point2d p00_, p02_;
    separator_to_pixels(p01, p00_, p02_);
    mln_assertion(p00_ == p00 && p02_ == p02);
  }
  {
    point2d p00_, p20_;
    separator_to_pixels(p10, p00_, p20_);
    mln_assertion(p00_ == p00 && p20_ == p20);
  }
}
