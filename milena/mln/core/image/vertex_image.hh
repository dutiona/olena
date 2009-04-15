// Copyright (C) 2009 EPITA Research and Development Laboratory
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

#ifndef MLN_CORE_IMAGE_VERTEX_IMAGE_HH
# define MLN_CORE_IMAGE_VERTEX_IMAGE_HH

/// \file mln/core/image/vertex_image.hh
///
/// Image based on graph vertices.

# include <mln/core/concept/graph.hh>
# include <mln/core/image/graph_elt_window.hh>
# include <mln/core/image/graph_elt_neighborhood.hh>
# include <mln/core/site_set/p_vertices.hh>
# include <mln/pw/internal/image_base.hh>
# include <mln/fun/i2v/array.hh>

namespace mln
{

  // Forward declaration.
  template <typename P, typename V, typename G> class vertex_image;
  namespace util { class graph; }


  // Properties

  namespace trait
  {

    template <typename P, typename V, typename G>
    struct image_< vertex_image<P,V,G> >
      : pw_image_<fun::i2v::array<V>,
		  p_vertices<util::graph, fun::i2v::array<P> >,
		  vertex_image<P,V,G> >
    {
    };

  } // end of namespace mln::traits.



  namespace internal
  {

    /// Data structure for mln::pw::internal::image
    template <typename P, typename V, typename G>
    struct data< mln::vertex_image<P,V,G> >
    {
      data(const fun::i2v::array<V>& vertex_values,
	   const p_vertices<G,fun::i2v::array<P> >& pv);

      fun::i2v::array<V> f_;
      p_vertices<G,fun::i2v::array<P> > pset_;
    };

  } // end of namespace mln::internal



  /// Construct a vertex image from a fun::i2v::array and a p_vertices.
  /// image = fun::i2v::array | p_vertices.
  template <typename V, typename G, typename P>
  vertex_image<P,V,G>
  operator | (const fun::i2v::array<V>& vertex_values,
	      const p_vertices<G,fun::i2v::array<P> >& pv);


  template <typename P, typename V, typename G = util::graph>
  class vertex_image
    : public pw::internal::image_base<fun::i2v::array<V>,
				      p_vertices<G, fun::i2v::array<P> >,
				      vertex_image<P,V,G> >
  {
    typedef pw::internal::image_base<fun::i2v::array<V>,
				     p_vertices<G, fun::i2v::array<P> >,
				     vertex_image<P,V,G> > super_;

  public:
    /// Skeleton type.
    typedef vertex_image< tag::psite_<P>,
			  tag::value_<V>,
			  tag::graph_<G> > skeleton;

    /// Function mapping graph elements to sites.
    typedef fun::i2v::array<P> site_function_t;

    /// Window type
    typedef graph_elt_window<G,p_vertices<G,site_function_t> > win_t;
    /// Neighborhood type.
    typedef graph_elt_neighborhood<G,p_vertices<G,site_function_t> > nbh_t;

    /// Constructors.
    /// @{
    vertex_image();
    vertex_image(const Graph<G>& g,
		 const Function_i2v< fun::i2v::array<P> >& vertex_sites,
		 const Function_i2v< fun::i2v::array<V> >& vertex_values);

    vertex_image(const p_vertices<G,fun::i2v::array<P> >& pv,
		 const Function_i2v< fun::i2v::array<V> >& vertex_values);

    template <typename FP, typename FV>
    vertex_image(const Graph<G>& g,
		 const Function_i2v<FP>& vertex_sites,
		 const Function_i2v<FV>& vertex_values);

    template <typename FV>
    vertex_image(const p_vertices<G,fun::i2v::array<P> >& pv,
		 const Function_i2v<FV>& vertex_values);
    /// @}

  };

  template <typename P, typename V, typename G, typename J>
  void init_(tag::image_t, vertex_image<P,V,G>& target, const Image<J>& model);


# ifndef MLN_INCLUDE_ONLY

  template <typename P, typename V, typename G, typename J>
  void init_(tag::image_t, vertex_image<P,V,G>& target, const Image<J>& model)
  {
    fun::i2v::array<V> f;
    init_(tag::function, f, exact(model));
    p_vertices<G,fun::i2v::array<P> > s;
    init_(tag::domain, s, exact(model));
    target.init_(f, s);
  }

  // Operator.

  template <typename V, typename G, typename P>
  inline
  vertex_image<P,V,G>
  operator | (const fun::i2v::array<V>& vertex_values,
	      const p_vertices<G,fun::i2v::array<P> >& pv)
  {
    vertex_image<P,V,G> tmp(vertex_values, pv);
    return tmp;
  }



  // data< pw::image >

  namespace internal
  {

    template <typename P, typename V, typename G>
    inline
    data< mln::vertex_image<P,V,G> >::data(const fun::i2v::array<V>& f,
					   const p_vertices<G,fun::i2v::array<P> >& ps)
      : f_(f),
	pset_(ps)
    {
    }

  } // end of namespace mln::internal



  // vertex_image<P,V,G>

  template <typename P, typename V, typename G>
  inline
  vertex_image<P,V,G>::vertex_image()
  {
  }


  template <typename P, typename V, typename G>
  inline
  vertex_image<P,V,G>::vertex_image(const Graph<G>& g,
				    const Function_i2v< fun::i2v::array<P> >& vertex_sites,
				    const Function_i2v< fun::i2v::array<V> >& vertex_values)
    : super_(exact(vertex_values),
	     p_vertices<G,fun::i2v::array<P> >(g, exact(vertex_sites)))
  {
  }


  template <typename P, typename V, typename G>
  inline
  vertex_image<P,V,G>::vertex_image(const p_vertices<G,fun::i2v::array<P> >& pv,
				    const Function_i2v< fun::i2v::array<V> >& vertex_values)
    : super_(exact(vertex_values), pv)
  {
  }


  template <typename P, typename V, typename G>
  template <typename FP, typename FV>
  inline
  vertex_image<P,V,G>::vertex_image(const Graph<G>& g,
				    const Function_i2v<FP>& vertex_sites,
				    const Function_i2v<FV>& vertex_values)
    : super_(convert::to<fun::i2v::array<V> >(exact(vertex_values)),
	     p_vertices<G,fun::i2v::array<P> >(g, vertex_sites))
  {
    mlc_converts_to(FV,fun::i2v::array<V>)::check();
    mlc_equal(mln_result(FP),P)::check();
    mlc_equal(mln_result(FV),V)::check();
  }



  template <typename P, typename V, typename G>
  template <typename FV>
  inline
  vertex_image<P,V,G>::vertex_image(const p_vertices<G,fun::i2v::array<P> >& pv,
				    const Function_i2v<FV>& vertex_values)
    : super_(convert::to<fun::i2v::array<V> >(exact(vertex_values)), pv)
  {
    mlc_converts_to(FV,fun::i2v::array<V>)::check();
    mlc_equal(mln_result(FV),V)::check();
  }


# endif // ! MLN_INCLUDE_ONLY


} // end of namespace mln

#endif // ! MLN_CORE_IMAGE_VERTEX_IMAGE_HH