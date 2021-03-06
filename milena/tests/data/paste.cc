// Copyright (C) 2007, 2008, 2009, 2013 EPITA Research and Development
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

#include <mln/core/image/image1d.hh>
#include <mln/core/image/image2d.hh>
#include <mln/core/image/image3d.hh>
#include <mln/pw/image.hh>
#include <mln/core/image/flat_image.hh>
#include <mln/core/image/vmorph/cast_image.hh>
#include <mln/core/image/dmorph/image_if.hh>
#include <mln/core/image/dmorph/sub_image.hh>
#include <mln/core/image/dmorph/extension_val.hh>

#include <mln/data/fill.hh>
#include <mln/data/paste.hh>
#include <mln/data/compare.hh>

#include <mln/fun/p2b/chess.hh>
#include <mln/fun/p2v/iota.hh>

#include <mln/debug/iota.hh>
#include <mln/debug/println.hh>


int main()
{
  using namespace mln;
  const unsigned size = 50;

  // tests in two dimension
  {
    box2d b(point2d(1,2), point2d(2,4));
    image2d<int> ima(b, 2);
    debug::iota(ima);

    box2d b2(point2d(-1,-2), point2d(3,6));
    image2d<int> ima2(b2, 0);
    debug::iota(ima2);

    image2d<int> ima3(b, 2);

    data::paste(ima, ima2); // Not so fast version...
    mln_assertion(ima == (ima2 | b));

    data::paste(ima, ima3); // Fast version...
    mln_assertion(ima == ima3);
  }

  // tests in three dimension
  {
    box3d b(point3d(1,2, 1), point3d(2,4, 3));
    image3d<int> ima(b, 2);
    debug::iota(ima);

    box3d b2(point3d(-1,-2, -1), point3d(3,6, 3));
    image3d<int> ima2(b2, 2);
    debug::iota(ima2);

    image3d<int> ima3(b, 2);

    data::paste(ima, ima2); // Not so fast version...
    mln_assertion(ima == (ima2 | b));

    data::paste(ima, ima3); // Fast version...
    mln_assertion(ima == ima3);
  }

    /// image 1d test
  {
    image1d<unsigned short> ima(size);
    image1d<unsigned short> out(size);

    debug::iota(ima);
    data::paste(ima, out);

    mln_assertion(ima == out);
  }


  /// pw image test
  {
    fun::p2v::iota f;
    const pw::image<fun::p2v::iota, box2d> ima(f, make::box2d(2,2, 5,5));
    image2d<short unsigned int> out(8, 8);

    data::fill(out, (short unsigned int)0);
    data::paste(ima, out);
  }

  // flat image test
  {
    flat_image<short, box2d> ima(5, make::box2d(size, size));
    image2d<unsigned short> out(size, size);

    data::fill_with_value(ima, 51);
    data::paste(ima, out);

    mln_assertion(ima == out);
  }

  // image if test
  {
    typedef image2d<unsigned short> I;
    typedef fun::p2b::chess F;
    F f;
    typedef image_if<I, F> II;

    I ima(size, size);
    I out(size, size);
    II ima_if = ima | f;

    data::fill_with_value(ima, 0);
    debug::iota(ima);
    data::paste(ima_if, out);

    mln_assertion(ima_if == (out | f));
  }

  // cast image test
  {
    typedef image2d<unsigned short> I;
    typedef cast_image_<int, I> II;
    typedef image2d<unsigned short> III;

    I in(size, size);
    II cast(in);
    III out(size, size);

    data::fill(in, (unsigned short)51);
    data::fill(out, (unsigned short)42);

    data::paste(cast, out);

    mln_assertion(cast == out);
  }

  // sub_image test
   {
     typedef image2d<int> I;
     typedef sub_image< image2d<int>, box2d > II;
     typedef image2d<unsigned short> III;

     I ima(size, size);
     II sub_ima(ima, make::box2d(4,4, 10,10));
     III out(size, size);

     data::fill(ima, 51);
     data::paste(sub_ima, out);

     II::piter p(sub_ima.domain());
     for_all(p)
       mln_assertion(sub_ima(p) == out(p));
   }

   // extended image test
  {
    typedef image2d<int> I;
    typedef extension_val< image2d<int> > II;
    typedef image2d<unsigned short> III;

    I ima(size, size);
    II extend_ima(ima, 5);
    III out(size, size);

    data::fill(ima, 51);
    data::paste(extend_ima, out);

    II::piter p(extend_ima.domain());
    for_all(p)
      mln_assertion(extend_ima(p) == out(p));
  }
}
