// Copyright (C) 2008, 2009 EPITA Research and Development Laboratory (LRDE)
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

#ifndef MLN_TOPO_COMPLEX_ITERATORS_HH
# define MLN_TOPO_COMPLEX_ITERATORS_HH

/// \file
/// \brief Iterators on complexes.
///
/// This file includes all iterators on faces.

/*-----------------------------.
| Iterators on sets of faces.  |
`-----------------------------*/

# include <mln/topo/face_iter.hh>
# include <mln/topo/n_face_iter.hh>
# include <mln/topo/static_n_face_iter.hh>
// FIXME: Disabled (moved to the attic).
# if 0
#  include <mln/topo/faces_iter.hh>
# endif

/*---------------------.
| Relative iterators.  |
`---------------------*/

# include <mln/topo/adj_lower_face_iter.hh>
# include <mln/topo/adj_higher_face_iter.hh>
# include <mln/topo/adj_lower_higher_face_iter.hh>

# include <mln/topo/adj_lower_dim_connected_n_face_iter.hh>
# include <mln/topo/adj_higher_dim_connected_n_face_iter.hh>

# include <mln/topo/adj_m_face_iter.hh>

/*--------------------.
| Special iterators.  |
`--------------------*/

# include <mln/topo/center_only_iter.hh>

#endif // ! MLN_TOPO_COMPLEX_ITERATORS_HH
