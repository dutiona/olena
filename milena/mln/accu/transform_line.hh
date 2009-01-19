// Copyright (C) 2008 EPITA Research and Development Laboratory (LRDE)
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

#ifndef MLN_ACCU_TRANSFORM_LINE_HH
# define MLN_ACCU_TRANSFORM_LINE_HH

/// \file mln/accu/transform_line.hh
///
/// Run an accumulator over a line (in a particular direction).
///
/// \todo Import code from sandox/geraud/browsing/fwd.cc to handle the
/// case of no-domain-extension.
///
/// \todo Specialize for fastest images.

# include <mln/core/concept/image.hh>
# include <mln/core/concept/meta_accumulator.hh>
# include <mln/extension/adjust.hh>



namespace mln
{

  namespace accu
  {


    template <typename A, typename I>
    mln_ch_value(I, mln_result(A))
      transform_line(const Accumulator<A>& a,
		     const Image<I>& input,
		     unsigned length, unsigned dir);

    template <typename A, typename I>
    mln_ch_value(I, mln_accu_with(A, mln_value(I))::result)
      transform_line(const Meta_Accumulator<A>& a,
		     const Image<I>& input,
		     unsigned length, unsigned dir);



# ifndef MLN_INCLUDE_ONLY

    // Tests.

    namespace internal
    {

      template <typename A, typename I>
      void transform_line_tests(const Accumulator<A>& a_, const Image<I>& input_)
      {
	A a = exact(a_);
	const I& input = exact(input_);

	mln_precondition(input.is_valid());
	mln_psite(I)* p;
	mln_precondition(sizeof(a.take(input(*p)), 0) == sizeof(int));

	(void) p;
	(void) a;
	(void) input;
      }

    } // end of namespace mln::accu::internal


    namespace impl
    {

      namespace generic
      {

	template <typename A, typename I>
	inline
	mln_ch_value(I, mln_result(A))
	  transform_line(const Accumulator<A>& a_,
			 const Image<I>& input_,
			 unsigned length, unsigned dir)
	{
	  trace::entering("accu::impl::transform_line");

	  const I& input = exact(input_);
	  A a = exact(a_);

	  internal::transform_line_tests(a, input);

	  mln_ch_value(I, mln_result(A)) output;
	  initialize(output, input);

	  typedef mln_psite(I) P;
	  const P
	    pmin = input.domain().pmin(),
	    pmax = input.domain().pmax();
	  const def::coord
	    pmax_dir = pmax[dir],
	    pmin_dir = pmin[dir];

	  P p = pmin, // Starting point.
	    qt, qu;
	  def::coord& p_dir  = p [dir];
	  def::coord& qt_dir = qt[dir];
	  def::coord& qu_dir = qu[dir];

	  do
	    {

	      // Start the line.
	      // ---------------

	      qt = p;
	      qt_dir = p_dir - length / 2;
	      qu = qt;
	      a.init();

	      for (unsigned i = 0; i < length; ++i)
		{
 		  if (input.has(qt))
		    a.take(input(qt));
		  qt_dir++;
		}
 	      if (input.has(p))
		output(p) = a.to_result();

	      // Browse the line.
	      // ----------------

	      while (p_dir < pmax_dir)
		{
		  ++p_dir;
 		  if (input.has(qt))
		    a.take(input(qt));
 		  if (input.has(qu))
		    a.untake(input(qu));
 		  if (input.has(p))
		    output(p) = a.to_result();
		  qt_dir++;
		  qu_dir++;
		}
	  
	      p_dir = pmin_dir;


	      // Go to the next line.
	      // --------------------

	      for (int c = P::dim - 1; c >= 0; --c)
		{
		  if (c == int(dir))
		    continue;
		  if (p[c] != pmax[c])
		    {
		      ++p[c];
		      break;
		    }
		  p[c] = pmin[c];
		}

	    } while (p != pmin);

	  trace::exiting("accu::impl::transform_line");
	  return output;
	}

      } // end of namespace mln::accu::impl::generic

    } // end of namespace mln::accu::impl



    template <typename A, typename I>
    inline
    mln_ch_value(I, mln_result(A))
      transform_line(const Accumulator<A>& a,
		     const Image<I>& input,
		     unsigned length, unsigned dir)
    {
      trace::entering("accu::transform_line");

      internal::transform_line_tests(a, input);

      extension::adjust(input, length / 2);
      mln_ch_value(I, mln_result(A)) output;
      output = impl::generic::transform_line(a, input, length, dir);

      trace::exiting("accu::transform_line");
      return output;
    }


    template <typename A, typename I>
    inline
    mln_ch_value(I, mln_accu_with(A, mln_value(I))::result)
      transform_line(const Meta_Accumulator<A>& a,
		     const Image<I>& input,
		     unsigned length, unsigned dir)
    {
      trace::entering("accu::transform_line");

      typedef mln_accu_with(A, mln_value(I)) A_;
      A_ a_ = accu::unmeta(exact(a), mln_value(I)());

      internal::transform_line_tests(a_, input);

      extension::adjust(input, length / 2);
      mln_ch_value(I, mln_result(A_)) output;
      output = impl::generic::transform_line(a_, input, length, dir);

      trace::exiting("accu::transform_line");
      return output;
    }


# endif // ! MLN_INCLUDE_ONLY

  } // end of namespace mln::accu

} // end of namespace mln


#endif // ! MLN_ACCU_TRANSFORM_LINE_HH