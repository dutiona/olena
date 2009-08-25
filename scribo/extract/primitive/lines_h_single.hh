// Copyright (C) 2009 EPITA Research and Development Laboratory (LRDE)
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

#ifndef SCRIBO_EXTRACT_PRIMITIVE_LINES_H_SINGLE_HH
# define SCRIBO_EXTRACT_PRIMITIVE_LINES_H_SINGLE_HH

/// \file
///
/// Fast Extraction of single horizontal thick lines.

# include <mln/core/concept/image.hh>
# include <mln/core/concept/neighborhood.hh>
# include <mln/win/hline2d.hh>

# include <scribo/core/object_image.hh>


namespace scribo
{

  namespace extract
  {

    namespace primitive
    {


      using namespace mln;

      /// Fast Extraction of single horizontal thick lines.
      /*!
       * Only single non discontinued lines are correctly extracted
       * with this routine.
       *
       * \param[in]     input_	    A binary image.
       * \param[in]     nbh_	    The neighborhood used for labeling image
       *			    components.
       * \param[in,out] nlines	    Type used for labeling.
       * \param[in]     line_length The minimum line length.
       * \param[in]     w_h_ratio   The minimum ratio width/height object
       *                            bounding boxes to consider an
       *                            object as a single line.
       *
       * \return An image in which only horizontal single lines are
       * labeled.
       */
      template <typename I, typename N, typename V>
      object_image(mln_ch_value(I,V))
      lines_v_single(const Image<I>& input,
		     const Neighborhood<N>& nbh, V& nlines,
		     unsigned min_line_length,
		     float w_h_ratio);


      /// Fast Extraction of single horizontal thick lines.
      /*!
       * Only single non discontinued lines are correctly extracted
       * with this routine.
       *
       * \param[in]     objects     A labeled image.
       * \param[in]     line_length The minimum line length.
       * \param[in]     w_h_ratio   The minimum ratio width/height object
       *                            bounding boxes to consider an
       *                            object as a single line.
       *
       * \return An image in which only horizontal single lines are
       * labeled.
       */
      template <typename L>
      object_image(L)
      lines_h_single(const object_image(L)& objects,
		     unsigned min_line_length,
		     float w_h_ratio);


# ifndef MLN_INCLUDE_ONLY

      namespace internal
      {

	template <typename L>
	struct is_line_h_single
	  : Function_v2b<is_line_h_single<L> >
	{
	  typedef bool result;

	  is_line_h_single(const object_image(L)& objects,
			   float w_h_ratio, unsigned min_line_length)
	    : objects_(objects),
	      w_h_ratio_(w_h_ratio), min_line_length_(min_line_length)
	  {
	  }


	  bool operator()(const mln_value(L)& label) const
	  {
	    mln_domain(L) box = objects_.bbox(label);

	    unsigned
	      height = box.pmax().row() - box.pmin().row() + 1,
	      width = box.pmax().col() - box.pmin().col() + 1;

	    return ((width / (float)height) > w_h_ratio_
		    && width > min_line_length_);
	  }

	  float w_h_ratio_;
	  unsigned min_line_length_;

	  object_image(L) objects_;
	};


      } // end of namespace mln::internal




      template <typename I, typename N, typename V>
      object_image(mln_ch_value(I,V))
      lines_h_single(const Image<I>& input_,
		     const Neighborhood<N>& nbh_, V& nlines,
		     unsigned min_line_length,
		     float w_h_ratio)
      {
	trace::entering("scribo::primitive::lines_h_single");

	const I& input = exact(input_);
	const N& nbh = exact(nbh_);
	mln_precondition(input.is_valid());
	mln_precondition(nbh.is_valid());

	typedef mln_ch_value(I,V) L;
	object_image(L)
	  output = objects(input, nbh, nlines);

	internal::is_line_h_single<L>
	  is_line(output, w_h_ratio, min_line_length);

	output.relabel(is_line);
	nlines = output.nlabels();

	trace::exiting("scribo::primitive::lines_h_single");
	return output;
      }




      template <typename L>
      object_image(L)
      lines_h_single(const object_image(L)& objects,
		     unsigned min_line_length,
		     float w_h_ratio)
      {
	trace::entering("scribo::primitive::lines_h_single");

	mln_precondition(objects.is_valid());

	internal::is_line_h_single<L>
	  is_line(objects, w_h_ratio, min_line_length);

	object_image(L) output;
	output.init_from_(objects);
	output.relabel(is_line);

	trace::exiting("scribo::primitive::lines_h_single");
	return output;
      }


# endif // ! MLN_INCLUDE_ONLY


    } // end of namespace scribo::extract::primitive

  } // end of namespace scribo::extract

} // end of namespace scribo

#endif // ! SCRIBO_EXTRACT_PRIMITIVE_LINES_H_SINGLE_HH
