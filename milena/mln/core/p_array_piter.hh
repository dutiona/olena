// Copyright (C) 2007, 2008 EPITA Research and Development Laboratory (LRDE)
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

#ifndef MLN_CORE_P_ARRAY_PITER_HH
# define MLN_CORE_P_ARRAY_PITER_HH

/// \file mln/core/p_array_piter.hh
/// \brief Definition of point iterators on mln::p_array.

# include <mln/core/p_array.hh>
# include <mln/core/internal/site_iterator_base.hh>


namespace mln
{

  /// \brief Forward iterator on sites of a p_array<P>.
  template <typename P>
  class p_array_fwd_piter_
    :
    public internal::site_iterator_base_< p_array<P>,
					  p_array_fwd_piter_<P> >
  {
    typedef p_array_fwd_piter_<P> self;
    typedef internal::site_iterator_base_<p_array<P>, self> super;

  protected:
    using super::p_;

  public:

    /// Constructor with no argument.
    p_array_fwd_piter_();

    /// Constructor.
    p_array_fwd_piter_(const p_array<P>& arr);

    /// Test if the iterator is valid.
    bool is_valid_() const;

    /// Invalidate the iterator.
    void invalidate_();

    /// Start an iteration.
    void start_();

    /// Go to the next point.
    void next_();

    /// Return the current index.
    int index() const;
  };


  template <typename P, typename A>
  int index_of_in(const p_array_fwd_piter_<P>& p, const A& arr);



  /// \brief Backward iterator on sites of a p_array<P>.
  template <typename P>
  class p_array_bkd_piter_
    :
    public internal::site_iterator_base_< p_array<P>,
					  p_array_bkd_piter_<P> >
  {
    typedef p_array_bkd_piter_<P> self;
    typedef internal::site_iterator_base_<p_array<P>, self> super;

  protected:
    using super::p_;

  public:

    /// Constructor with no argument.
    p_array_bkd_piter_();

    /// Constructor.
    p_array_bkd_piter_(const p_array<P>& arr);

    /// Test if the iterator is valid.
    bool is_valid_() const;

    /// Invalidate the iterator.
    void invalidate_();

    /// Start an iteration.
    void start_();

    /// Go to the next point.
    void next_();

    /// Return the current index.
    int index() const;
  };


  template <typename P, typename A>
  int index_of_in(const p_array_bkd_piter_<P>& p, const A& arr);


# ifndef MLN_INCLUDE_ONLY

  /*------------------------.
  | p_array_fwd_piter_<P>.  |
  `------------------------*/

  template <typename P>
  inline
  p_array_fwd_piter_<P>::p_array_fwd_piter_()
  {
  }

  template <typename P>
  inline
  p_array_fwd_piter_<P>::p_array_fwd_piter_(const p_array<P>& arr)
  {
    this->change_target(arr);
  }

  template <typename P>
  inline
  bool
  p_array_fwd_piter_<P>::is_valid_() const
  {
    mln_invariant(p_.index() >= 0);
    return p_.index() < int(p_.target()->nsites());
  }

  template <typename P>
  inline
  void
  p_array_fwd_piter_<P>::invalidate_()
  {
    p_.index() = int(p_.target()->nsites());
  }

  template <typename P>
  inline
  void
  p_array_fwd_piter_<P>::start_()
  {
    p_.index() = 0;
  }

  template <typename P>
  inline
  void
  p_array_fwd_piter_<P>::next_()
  {
    ++p_.index();
  }

  template <typename P>
  inline
  int
  p_array_fwd_piter_<P>::index() const
  {
    return p_.index();
  }


  /*------------------------.
  | p_array_bkd_piter_<P>.  |
  `------------------------*/

  template <typename P>
  inline
  p_array_bkd_piter_<P>::p_array_bkd_piter_()
  {
  }

  template <typename P>
  inline
  p_array_bkd_piter_<P>::p_array_bkd_piter_(const p_array<P>& arr)
  {
    this->change_target(arr);
  }

  template <typename P>
  inline
  bool
  p_array_bkd_piter_<P>::is_valid_() const
  {
    mln_invariant(p_.index() < int(p_.target()->nsites()));
    return p_.index() >= 0;
  }

  template <typename P>
  inline
  void
  p_array_bkd_piter_<P>::invalidate_()
  {
    p_.index() = -1;
  }

  template <typename P>
  inline
  void
  p_array_bkd_piter_<P>::start_()
  {
    p_.index() = int(p_.target()->nsites()) - 1;
  }

  template <typename P>
  inline
  void
  p_array_bkd_piter_<P>::next_()
  {
    --p_.index();
  }

  template <typename P>
  inline
  int
  p_array_bkd_piter_<P>::index() const
  {
    return p_.index();
  }


  // Procedure.

  template <typename P, typename A>
  int
  index_of_in(const p_array_fwd_piter_<P>& p, const A& arr)
  {
    return index_of_in(p.unproxy(), arr);
  }

  template <typename P, typename A>
  int
  index_of_in(const p_array_bkd_piter_<P>& p, const A& arr)
  {
    return index_of_in(p.unproxy(), arr);
  }

# endif // ! MLN_INCLUDE_ONLY

} // end of namespace mln


#endif // ! MLN_CORE_P_ARRAY_PITER_HH
