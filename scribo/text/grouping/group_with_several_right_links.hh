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

#ifndef SCRIBO_TEXT_GROUPING_GROUP_WITH_SEVERAL_RIGHT_LINKS_HH
# define SCRIBO_TEXT_GROUPING_GROUP_WITH_SEVERAL_RIGHT_LINKS_HH

/// \file scribo/text/grouping/group_with_several_right_links.hh
///
/// Link text bounding boxes with their right neighbor.
///
/// Merge code with text::grouping::group_with_single_right_link.hh

# include <mln/core/concept/image.hh>
# include <mln/core/concept/neighborhood.hh>

# include <mln/util/array.hh>

# include <scribo/core/object_image.hh>
# include <scribo/core/macros.hh>
# include <scribo/text/grouping/internal/init_link_array.hh>
# include <scribo/text/grouping/internal/find_right_link.hh>
# include <scribo/util/text.hh>


namespace scribo
{

  namespace text
  {

    namespace grouping
    {

      using namespace mln;

      /// Map each character bounding box to its right bounding box neighbor
      /// if possible.
      /// Iterate to the right but link boxes to the right.
      ///
      /// \return an mln::util::array. Map a bounding box to its right neighbor.
      template <typename L>
      inline
      mln::util::array<unsigned>
      group_with_several_right_links(const object_image(L)& objects,
				     unsigned neighb_max_distance);

# ifndef MLN_INCLUDE_ONLY

      template <typename L>
      inline
      mln::util::array<unsigned>
      group_with_several_right_links(const object_image(L)& objects,
				     unsigned neighb_max_distance)
      {
	trace::entering("scribo::text::grouping::group_with_several_right_links");

	mln_precondition(objects.is_valid());

	mln::util::array<unsigned>
	  link_1(objects.nlabels().next()), link_2(objects.nlabels().next()),
	  link_3(objects.nlabels().next()), final_link(objects.nlabels().next());
	internal::init_link_array(link_1);
	internal::init_link_array(link_2);
	internal::init_link_array(link_3);

	mln::util::array<mln_result(accu::center<mln_psite(L)>)>
	    mass_centers = labeling::compute(accu::meta::center(),
					     objects, objects.nlabels());


	for_all_ncomponents(i, objects.nlabels())
	{
	  //  -------
	  //  |	 X------->
	  //  |	    |
	  //  |	    |
	  //  |	 X------->
	  //  |	    |
	  //  |	    |
	  //  |	 X------->
	  //  -------
	  unsigned midcol = (objects.bbox(i).pmax().col()
				- objects.bbox(i).pmin().col()) / 2;
	  int dmax = midcol + neighb_max_distance;

	  mln_site(L) c = objects.bbox(i).center();

	  /// Right link from the top anchor.
	  mln_site(L) a1 = c;
	  a1.row() = objects.bbox(i).pmin().row() + (c.row() - objects.bbox(i).pmin().row()) / 4;
	  internal::find_right_link(objects, link_1, i, dmax, a1);

	  /// Right link from the central site
	  internal::find_right_link(objects, link_2, i, dmax, mass_centers[i]);

	  /// Right link from the bottom anchor.
	  mln_site(L) a2 = c;
	  a2.row() = objects.bbox(i).pmax().row() - (c.row() - objects.bbox(i).pmin().row()) / 4;
	  internal::find_right_link(objects, link_3, i, dmax, a2);
	}

	for_all_ncomponents(i, objects.nlabels())
	{
	  if (link_2[i] != i)
	    final_link[i] = link_2[i];
	  else if (link_1[i] == link_3[i])
	    final_link[i] = link_1[i];
	  else if (link_1[i] != i && link_3[i] == i)
	    final_link[i] = link_1[i];
	  else if (link_3[i] != i && link_1[i] == i)
	    final_link[i] = link_3[i];
	  else
	    final_link[i] = i;
	}

	trace::exiting("scribo::text::grouping::group_with_several_right_links");
	return final_link;
      }

# endif // ! MLN_INCLUDE_ONLY

    } // end of namespace scribo::text::grouping

  } // end of namespace scribo::text

} // end of namespace scribo

#endif // ! SCRIBO_TEXT_GROUPING_GROUP_WITH_SEVERAL_RIGHT_LINKS_HH
