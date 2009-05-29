// Copyright (C) 2008, 2009 EPITA Research and Development Laboratory
// (LRDE)
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

#ifndef MLN_SET_COMPUTE_WITH_WEIGHTS_HH
# define MLN_SET_COMPUTE_WITH_WEIGHTS_HH

/// \file mln/set/compute_with_weights.hh
///
/// Compute an accumulator on a site set described by an image.
///
/// \todo Add a meta version for the labeling variation.

# include <mln/core/concept/meta_accumulator.hh>
# include <mln/core/concept/image.hh>
# include <mln/core/concept/site_set.hh>
# include <mln/util/array.hh>
# include <mln/convert/from_to.hh>


namespace mln
{

  namespace set
  {

    /// Compute an accumulator on a site set described by an image.
    ///
    /// \param[in] a An accumulator.
    /// \param[in] w An image of weights (a site -> a weight).
    /// \return The accumulator result.
    //
    template <typename A, typename I>
    mln_result(A)
    compute_with_weights(const Accumulator<A>& a, const Image<I>& w);


    template <typename A, typename I, typename L>
    util::array<mln_result(A)>
    compute_with_weights(const Accumulator<A>& a,
			 const Image<I>& w,
			 const Image<L>& label,
			 const mln_value(L)& nlabels);


    /// Compute an accumulator on a site set described by an image.
    ///
    /// \param[in] a A meta-accumulator.
    /// \param[in] s A site set.
    // \return The accumulator result.
    ///
    template <typename A, typename I>
    mln_accu_with(A, mln_site(I))::result
    compute_with_weights(const Meta_Accumulator<A>& a, const Image<I>& w);



# ifndef MLN_INCLUDE_ONLY


    // Tests.


    namespace internal
    {

      template <typename A, typename I, typename L>
      void
      compute_with_weights_tests(const Accumulator<A>& a_,
				 const Image<I>& w_,
				 const Image<L>& label_)
      {
	const A& a = exact(a_);
	const I& w = exact(w_);
	const L& label = exact(label_);
	
	mln_precondition(w.is_valid());
	mln_precondition(label.is_valid());
	mln_precondition(w.domain() <= label.domain());
	
	(void) a;
	(void) w;
	(void) label;
      }

    } // end of namespace mln::internal



    // Implementations.


    namespace impl
    {

      namespace generic
      {

	template <typename A, typename I>
	inline
	mln_result(A)
	compute_with_weights(const Accumulator<A>& a_, const Image<I>& w_)
	{
	  trace::entering("set::impl::generic::compute_with_weights");

	  mlc_converts_to(mln_site(I), mln_argument(A))::check();
	  mlc_converts_to(mln_value(I), unsigned)::check();

	  A a = exact(a_);
	  const I& w = exact(w_);

	  a.init();
	  mln_piter(I) p(w.domain());
	  for_all(p)
	    a.take_n_times(w(p), p);

	  trace::exiting("set::impl::generic::compute_with_weights");
	  return a.to_result();
	}

	template <typename A, typename I, typename L>
	util::array<mln_result(A)>
	compute_with_weights(const Accumulator<A>& a_,
			     const Image<I>& w_,
			     const Image<L>& label_,
			     const mln_value(L)& nlabels)
	{
	  trace::entering("set::impl::generic::compute_with_weights");

	  mlc_equal(mln_site(I), mln_site(L))::check();
	  mlc_converts_to(mln_site(I), mln_argument(A))::check();
	  mlc_converts_to(mln_value(I), unsigned)::check();

	  A a = exact(a_);
	  const I& w = exact(w_);
	  const L& label = exact(label_);

	  internal::compute_with_weights_tests(a, w, label);

	  util::array<A> accus(static_cast<unsigned>(nlabels) + 1, a);

	  mln_piter(I) p(w.domain());
	  for_all(p)
	    accus[label(p)].take_n_times(w(p), p);

	  util::array<mln_result(A)> r;
	  convert::from_to(accus, r);

	  trace::exiting("set::impl::generic::compute_with_weights");
	  return r;
	}

      } // end of namespace mln::set::impl::generic

    } // end of namespace mln::set::impl



    // Facades.


    template <typename A, typename I>
    inline
    mln_result(A)
    compute_with_weights(const Accumulator<A>& a, const Image<I>& w)
    {
      trace::entering("set::compute_with_weights");

      mlc_converts_to(mln_site(I), mln_argument(A))::check();
      mlc_converts_to(mln_value(I), unsigned)::check();
      mln_precondition(exact(w).is_valid());

      mln_result(A) r = impl::generic::compute_with_weights(a, w);

      trace::exiting("set::compute_with_weights");
      return r;
    }


    template <typename A, typename I, typename L>
    util::array<mln_result(A)>
    compute_with_weights(const Accumulator<A>& a,
			 const Image<I>& w,
			 const Image<L>& label,
			 const mln_value(L)& nlabels)
    {
      trace::entering("set::compute_with_weights");

      mlc_equal(mln_site(I), mln_site(L))::check();
      mlc_converts_to(mln_site(I), mln_argument(A))::check();
      mlc_converts_to(mln_value(I), unsigned)::check();

      internal::compute_with_weights_tests(a, w, label);

      util::array<mln_result(A)> r;
      r = impl::generic::compute_with_weights(a, w, label, nlabels);

      trace::exiting("set::compute_with_weights");
      return r;
    }


    template <typename A, typename I>
    inline
    mln_accu_with(A, mln_site(I))::result
    compute_with_weights(const Meta_Accumulator<A>& a, const Image<I>& w)
    {
      trace::entering("set::compute_with_weights");

      mlc_converts_to(mln_value(I), unsigned)::check();

      mln_precondition(exact(w).is_valid());

      typedef mln_site(I) P;
      typedef mln_accu_with(A, P) A_;
      A_ a_ = accu::unmeta(exact(a), P());

      mln_result(A_) r = impl::generic::compute_with_weights(a_, w);
      
      trace::exiting("set::compute_with_weights");
      return r;
    }

# endif // ! MLN_INCLUDE_ONLY

  } // end of namespace mln::set

} // end of namespace mln


#endif // ! MLN_SET_COMPUTE_WITH_WEIGHTS_HH
