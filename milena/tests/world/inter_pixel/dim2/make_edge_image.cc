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
#include <mln/world/inter_pixel/dim2/make_edge_image.hh>
#include <mln/value/int_u8.hh>
#include <mln/make/image.hh>
#include <mln/math/abs.hh>
#include <mln/data/compare.hh>


namespace mln
{

  struct myfun : Function_vv2v<myfun>
  {
    typedef mln::value::int_u8 result;

    result operator()(const value::int_u8& v1, const value::int_u8& v2) const
    {
      return math::abs(v1-v2);
    }
  };

}



int main()
{
  using namespace mln;

  value::int_u8 vals[][5] = { { 3, 0, 4, 0, 5 },
			      { 0, 0, 0, 0, 0 },
			      { 1, 0, 3, 0, 6 },
			      { 0, 0, 0, 0, 0 },
			      { 8, 0, 7, 0, 3 } };

  value::int_u8 refs[][5] = { { 0, 1, 0, 1, 0 },
			      { 2, 0, 1, 0, 1 },
			      { 0, 2, 0, 3, 0 },
			      { 7, 0, 4, 0, 3 },
			      { 0, 1, 0, 4, 0 } };

  typedef image2d<value::int_u8> ima_t;
  ima_t ima = make::image(vals);
  ima_t ref = make::image(refs);

  ima_t res = world::inter_pixel::dim2::make_edge_image(ima, myfun());

  mln_assertion(res == ref);
}
