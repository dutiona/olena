// Copyright (C) 2006 EPITA Research and Development Laboratory
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

#ifndef OLN_CORE_INTERNAL_TOPOLOGY_MORPHER_HH
# define OLN_CORE_INTERNAL_TOPOLOGY_MORPHER_HH

# include <oln/core/topology_entry.hh>



namespace oln
{

  namespace internal
  {
    template <typename Topo, typename E>
    struct topology_morpher;

  } // end of namespace oln::internal

  template <typename Topo, typename E>
  struct set_pseudosuper_type< internal::topology_morpher<Topo, E> >
  {
    typedef Topo ret;
  };

  template <typename Topo, typename E>
  struct single_vtype< internal::topology_morpher<Topo, E>, typedef_::morpher_type >
  {
    typedef morpher::tag::identity ret;
  };

  template <typename Topo, typename E>
  struct single_vtype< internal::topology_morpher<Topo, E>, typedef_::delegated_type >
  {
    typedef Topo ret;
  };


  namespace internal
  {
   
    /// Base internal class for morphers on topology.
    
    template <typename Topo, typename E>
    struct topology_morpher : public topology_entry<E>
    {
    protected:
      topology_morpher();
    };

# ifndef OLN_INCLUDE_ONLY

    template <typename Topo, typename E>
    topology_morpher<Topo, E>::topology_morpher()
    {
    }

# endif

  } // end of namespace oln::internal



} // end of namespace oln


#endif // ! OLN_CORE_INTERNAL_TOPOLOGY_MORPHER_HH
