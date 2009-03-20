// Copyright (C) 2009 EPITA Research and Development Laboratory (LRDE)
//
// This file is part of the Olena Library.  This library is free
// software; you can redistribute it and/or modify it under the terms
// of the GNU General Public License version 2 as published by the
// Free Software Foundation.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this library; see the file COPYING.  If not, write to
// the Free Software Foundation, 51 Franklin Street, Fifth Floor,
// Boston, MA 02111-1307, USA.
//
// As a special exception, you may use this file as part of a free
// software library without restriction.  Specifically, if other files
// instantiate templates or use macros or inline functions from this
// file, or you compile this file and link it with other files to
// produce an executable, this file does not by itself cause the
// resulting executable to be covered by the GNU General Public
// License.  This exception does not however invalidate any other
// reasons why the executable file might be covered by the GNU General
// Public License.

#ifndef MLN_ACCU_IMAGE_TAKE_HH
# define MLN_ACCU_IMAGE_TAKE_HH

/// \file mln/accu/image/take.hh
///
/// Update an image of accumulators by taking the contents of another
/// image.

# include <mln/core/concept/accumulator.hh>
# include <mln/core/concept/image.hh>


namespace mln
{

  namespace accu
  {

    namespace image
    {

      template <typename I, typename J>
      void
      take(Image<I>& input, const Image<J>& arg);



# ifndef MLN_INCLUDE_ONLY

      namespace impl
      {

	// Generic version.

	namespace generic
	{

	  template <typename I, typename J>
	  void
	  take(Image<I>& input_, const Image<J>& arg_)
	  {
	    trace::entering("accu::impl::image::generic::take");

	    I& input = exact(input_);
	    const J& arg = exact(arg_);

	    mln_precondition(input.is_valid());
	    mln_precondition(arg.is_valid());
	    mln_precondition(arg.domain() <= input.domain());

	    mln_piter(J) p(arg.domain());
	    for_all(p)
	      input(p).take(arg(p));

	    trace::exiting("accu::impl::image::generic::take");
	  }

	} // end of namespace mln::accu::image::impl::generic


	// Fastest version.

	template <typename I, typename J>
	void
	take_fastest(Image<I>& input_, const Image<J>& arg_)
	{
	  trace::entering("accu::impl::image::take_fastest");
	  
	  I& input = exact(input_);
	  const J& arg = exact(arg_);

	  mln_precondition(input.is_valid());
	  mln_precondition(arg.is_valid());
	  mln_precondition(arg.domain() == input.domain());
	  
	  mln_pixter(I)       p_in(input);
	  mln_pixter(const J) p_arg(arg);
	  for_all_2(p_in, p_arg)
	    p_in.val().take( p_arg.val() );

	  trace::exiting("accu::impl::image::take_fastest");
	}

      } // end of namespace mln::accu::image::impl



      // Dispatch.

      namespace internal
      {

	template <typename I, typename J>
	void
	take_dispatch(trait::image::speed::any,
		      trait::image::speed::any,
		      Image<I>& input, const Image<J>& arg)
	{
	  impl::generic::take(input, arg);
	}

	template <typename I, typename J>
	void
	take_dispatch(trait::image::speed::fastest,
		      trait::image::speed::fastest,
		      Image<I>& input, const Image<J>& arg)
	{
	  if (exact(arg).domain() == exact(input).domain())
	    impl::take_fastest(input, arg);
	  else
	    impl::generic::take(input, arg);
	}

	template <typename I, typename J>
	void
	take_dispatch(Image<I>& input, const Image<J>& arg)
	{
	  take_dispatch(mln_trait_image_speed(I)(),
			mln_trait_image_speed(J)(),
			input, arg);
	}

      } // end of namespace mln::accu::image::internal


      // Facade.

      template <typename I, typename J>
      void
      take(Image<I>& input_, const Image<J>& arg_)
      {
	trace::entering("accu::image::take");

	mlc_is_a(mln_value(I), Accumulator)::check();
	mlc_converts_to(mln_value(J),
			mln_deduce(I, value, argument))::check();

	I& input = exact(input_);
	const J& arg = exact(arg_);

	mln_precondition(input.is_valid());
	mln_precondition(arg.is_valid());
	mln_precondition(arg.domain() <= input.domain());

	internal::take_dispatch(input, arg);

	trace::exiting("accu::image::take");
      }

# endif // ! MLN_INCLUDE_ONLY

    } // end of namespace mln::accu::image

  } // end of namespace mln::accu

} // end of namespace mln


#endif // ! MLN_ACCU_IMAGE_TAKE_HH