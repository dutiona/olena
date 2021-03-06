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

#include <mln/core/image/image2d.hh>
#include <mln/accu/math/count.hh>
#include <mln/accu/image/set_value.hh>

#include <mln/data/compare.hh>
#include <mln/pw/cst.hh>
#include <mln/pw/image.hh>


int main()
{
  using namespace mln;

  typedef accu::math::count<int> A;
  image2d<A> ima(2, 2);

  accu::image::set_value(ima, 3);
  mln_assertion(ima == (pw::cst(3u) | ima.domain()));


  image2d<unsigned> res(1, 1);
  res.at_(0, 0) = 51;
  accu::image::set_value(ima, res);
  mln_assertion(ima.at_(0, 0) == 51);
}
