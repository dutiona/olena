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

#ifndef SCRIBO_FILTER_SMALL_OBJECTS_HH
# define SCRIBO_FILTER_SMALL_OBJECTS_HH

/// \file scribo/filter/small_objects.hh
///
/// Remove small objects in a binary image.


# include <mln/core/concept/image.hh>
# include <mln/core/concept/neighborhood.hh>
# include <mln/core/concept/function.hh>

# include <mln/labeling/blobs.hh>
# include <mln/labeling/relabel.hh>

# include <mln/make/relabelfun.hh>

# include <mln/util/array.hh>

# include <mln/pw/all.hh>

# include <mln/accu/count.hh>

# include <mln/set/compute.hh>

# include <scribo/core/object_image.hh>
# include <scribo/extract/primitive/objects.hh>


//forward declaration.
namespace mln
{
  namespace accu
  {
    template <typename T> struct count;
  }
}

namespace scribo
{

  namespace filter
  {

    using namespace mln;


    /// Remove small objects in a binary image.
    /// Set to 'false' all the removed objects.
    ///
    /// \param[in] input_     A binary image.
    /// \param[in] nbh_	      A neighborhood used for labeling \p input_.
    /// \param[in] label_type The label type used for labeling.
    /// \param[in] min_size   The minimum cardinality of an object.
    ///
    /// \return A binary image without small objects.
    template <typename I, typename N, typename V>
    mln_concrete(I)
    small_objects(const Image<I>& input_,
		  const Neighborhood<N>& nbh_,
		  const V& label_type,
		  unsigned min_size);


    /// Remove too small objects.
    ///
    /// \param[in] objects    An object image.
    /// \param[in] min_size   The minimum cardinality of an object.
    ///
    /// \return An object image without small objects.
    template <typename L>
    object_image(L)
    small_objects(const object_image(L)& objects,
		  unsigned min_size);


# ifndef MLN_INCLUDE_ONLY


    namespace internal
    {


      /// Filter Functor.
      /// Return false for all objects which are too small.
      template <typename L>
      struct small_objects_filter
	: Function_v2b< small_objects_filter<L> >
      {
	typedef accu::count<mln_psite(L)> card_t;

	/// Constructor
	///
	/// \param[in] objects Component bounding boxes.
	/// \param[in] min_size Minimum component size.
	//
	small_objects_filter(const object_image(L)& objects,
			     unsigned min_size)
	{
	  card_ = labeling::compute(card_t(), objects, objects.nlabels());
	  min_size_ = min_size;
	}


	/// Check if the component is large enough.
	///
	/// \param l A label.
	///
	/// \return false if the component area is strictly inferion to
	/// \p min_size_.
	//
	bool operator()(const mln_value(L)& l) const
	{
	  if (l == literal::zero)
	    return true;
	  return card_[l] >= min_size_;
	}

	/// The component bounding boxes.
	mln::util::array<mln_result(card_t)> card_;

	/// The minimum area.
	unsigned min_size_;
      };


    } //  end of namespace scribo::filter::internal



   template <typename I, typename N, typename V>
   inline
   mln_concrete(I)
   small_objects(const Image<I>& input_,
		 const Neighborhood<N>& nbh_,
		 const V& label_type,
		 unsigned min_size)
   {
     trace::entering("scribo::filter::small_objects");

     const I& input = exact(input_);
     const N& nbh = exact(nbh_);

     mln_precondition(input.is_valid());
     mln_precondition(nbh.is_valid());

     V nlabels;
     typedef object_image(mln_ch_value(I,V)) lbl_t;
     lbl_t lbl = extract::primitive::objects(input, nbh, nlabels);

     typedef internal::small_objects_filter<lbl_t> func_t;
     func_t fv2b(lbl, min_size);
     labeling::relabel_inplace(lbl, nlabels, fv2b);

     mln_concrete(I) output = duplicate(input);
     data::fill((output | pw::value(lbl) == literal::zero).rw(), false);

     trace::exiting("scribo::filter::small_objects");
     return output;
   }


    template <typename L>
    inline
    object_image(L)
    small_objects(const object_image(L)& objects,
		  unsigned min_size)
    {
      trace::entering("scribo::filter::small_objects");

      mln_precondition(objects.is_valid());

      internal::small_objects_filter<L> f(objects, min_size);

      object_image(L) output;
      output.init_from_(objects);
      output.relabel(f);

      trace::exiting("scribo::filter::small_objects");
      return output;
    }


# endif // ! MLN_INCLUDE_ONLY

  } // end of namespace scribo::filter

} // end of namespace scribo

#endif // ! SCRIBO_FILTER_SMALL_OBJECTS_HH