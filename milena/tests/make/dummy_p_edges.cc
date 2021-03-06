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

#include <mln/core/image/image2d.hh>
#include <mln/core/site_set/p_array.hh>

#include <mln/util/graph.hh>

#include <mln/value/label_8.hh>

#include <mln/make/dummy_p_edges.hh>

int main()
{
  using namespace mln;

  typedef util::graph G;
  G g;
  g.add_vertices(5);
  g.add_edge(1,2);
  g.add_edge(1,3);
  g.add_edge(4,3);
  g.add_edge(4,2);

  {
    typedef p_edges<G> pe_t;
    pe_t pe = make::dummy_p_edges(g);
    unsigned i = 0;

    mln_assertion(pe.nsites() == 4);
    mln_piter_(pe_t) p(pe);
    for_all(p)
      mln_assertion(p.id() == i++);
  }

  {
    typedef p_edges<G, pw::cst_<point2d> > pe_t;
    pe_t pe = make::dummy_p_edges(g, point2d::plus_infty());

    mln_assertion(pe.nsites() == 4);
    mln_piter_(pe_t) p(pe);
    for_all(p)
      mln_assertion(p == point2d::plus_infty());
  }

}
