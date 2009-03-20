/*!
 * \file   compute_histo_rgb.cc
 * \author etiennefolio <ornthalas@gmail.com>
 */

#include <mln/core/image/image2d.hh>
#include <mln/core/image/image3d.hh>
#include <mln/value/int_u8.hh>
#include <mln/value/rgb8.hh>
#include <iostream>

namespace mln
{
  namespace histo
  {

    template <typename C, typename T>
    image3d<C> compute_histo_rgb(image2d<T> ima)
    {
      // out
      typedef typename trait::value_<T>::comp enc;
      image3d<C> out(mln_max(enc) + abs(mln_min(enc) + 1),
		     mln_max(enc) + abs(mln_min(enc) + 1),
		     mln_max(enc) + abs(mln_min(enc) + 1));
      data::fill(out, 0);

      // count
      mln_fwd_piter(image2d<T>) p(ima.domain());
      for_all(p)
	++out(point3d(ima(p).red(), ima(p).green(), ima(p).blue()));

      // return
      return out;
    }

  }
}