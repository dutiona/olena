// Copyright (C) 2008, 2009 EPITA Research and Development Laboratory (LRDE)
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
#include <mln/accu/transform_line.hh>
#include <mln/accu/math/count.hh>
#include <mln/pw/all.hh>
#include <mln/data/compare.hh>


int main()
{
  using namespace mln;

  typedef unsigned T;
  image2d<T> ima(4, 5);

  typedef accu::math::count<T> A;
  const unsigned len = 31;
  for (unsigned dir = 0; dir < 2; ++dir)
  {
    image2d<unsigned> out = accu::impl::transform_line_fastest(A(), ima, len, dir);
    mln_assertion(out == (pw::cst(len) | ima.domain()));
    mln_assertion(accu::impl::generic::transform_line(A(), ima, len, dir) == out);
  }
}
