// Copyright (C) 2007 EPITA Research and Development Laboratory
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

#ifndef MLN_LINEAR_LAP_Y_HH
# define MLN_LINEAR_LAP_Y_HH

/*! \file mln/linear/lap.hh
 *
 * \brief Laplacian.
 */

# include <mln/linear/convolve.hh>
# include <mln/make/w_window2d.hh>



namespace mln
{

  namespace linear
  {

    template <typename I, typename O>
    void lap_y(const Image<I>& input, Image<O>& output);

# ifndef MLN_INCLUDE_ONLY

    // Laplacian operators (Cf. Sonka et al., p. 81)

    template <typename I, typename O>
    void lap_y(const Image<I>& input, Image<O>& output)
    {
      mln_precondition(exact(output).domain() == exact(input).domain());
      int ws[] = { +0, +1, +1,  +2,  +2,  +2, +1, +1,  0,
		   +1, +2, +4,  +5,  +5,  +5, +4, +2, +1,
		   +1, +4, +5,  +3,   0,  +3, +5, +4, +1,
		   +2, +5, +3, -12, -24, -12, +3, +5, +2,
		   +2, +5,  0, -24, -40, -24,  0, +5, +2,
		   +2, +5, +3, -12, -24, -12, +3, +5, +2,
		   +1, +4, +5,  +3,   0,  +3, +5, +4, +1,
		   +1, +2, +4,  +5,  +5,  +5, +4, +2, +1,
		   +0, +1, +1,  +2,  +2,  +2, +1, +1,  0 };
      convolve(input, make::w_window2d(ws), output);
    }

# endif // ! MLN_INCLUDE_ONLY

  } // end of namespace mln::linear

} // end of namespace mln


#endif // ! MLN_LINEAR_LAP_HH
