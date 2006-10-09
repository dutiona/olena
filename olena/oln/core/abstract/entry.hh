// Copyright (C) 2005, 2006 EPITA Research and Development Laboratory
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

#ifndef OLN_CORE_ABSTRACT_ENTRY_HH
# define OLN_CORE_ABSTRACT_ENTRY_HH

# include <oln/core/typedefs.hh>
# include <oln/core/case.hh>

namespace oln
{

  template < template <class> class abstraction,
	     unsigned num >
  struct hierarchy
  {
  };


  namespace internal
  {

    // fwd decl
    template < template <class> class abstraction, typename E, unsigned num >
    struct entry_node;

    template < template <class> class abstraction,
	       typename E,
	       unsigned num,
	       typename another_hierarchy = mlc::false_ >
    struct next_entry_node
    {
      // here: no other hierarchy
    };


    template < template <class> class abstraction,
	       typename E >
    struct next_entry_node < abstraction, E, 1, mlc::false_ > 
      : public abstraction<E>
    {
    };


    template < template <class> class abstraction,
	       typename E,
	       unsigned num >
    struct next_entry_node < abstraction,
			     E,
			     num,
			     mlc::true_>

      : // plug to client sub-abstractions
        public virtual oln::switch_< hierarchy<abstraction, num>, E >::ret,

        // here: another hierarchy (number is 'num + 1')
        public entry_node<abstraction, E, num + 1>
    {
    };


    template < template <class> class abstraction,
	       typename E,
	       unsigned num >
    struct entry_node
      : public next_entry_node< abstraction,
				E,
				num,
				typename mlc::is_defined_< oln::case_< oln::hierarchy<abstraction, num>,
								       E, 1 > >::eval >
    {
      ~entry_node();
    };


# ifndef OLN_INCLUDE_ONLY

    template < template <class> class abstraction,
	       typename E,
	       unsigned num >
    entry_node<abstraction, E, num>::~entry_node()
    {
    }

# endif

  } // end of namespace oln::internal



  template < template <class> class abstraction,
	     unsigned num,
	     typename E >
  struct default_case_ < oln::hierarchy<abstraction, num>,
			 E >
  {
    typedef abstraction<E> ret;
  };
  


  template < template <class> class abstraction,
	     typename E >
  struct entry : public internal::entry_node<abstraction, E, 1>
  {
    ~entry();
  protected:
    entry();
  };


# ifndef OLN_INCLUDE_ONLY

  template < template <class> class abstraction,
	     typename E >
  entry<abstraction, E>::entry()
  {
  }

  template < template <class> class abstraction,
	     typename E >
  entry<abstraction, E>::~entry()
  {
  }

# endif


  // Super type declaration.
  template < template <class> class abstraction,
	     typename E >
  struct set_super_type< entry<abstraction, E> >
  {
    typedef abstraction<E> ret;
  };


} // end of namespace oln


#endif // ! OLN_CORE_ABSTRACT_ENTRY_HH
