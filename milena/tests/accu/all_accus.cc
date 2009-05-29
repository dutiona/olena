// Copyright (C) 2007, 2008, 2009 EPITA Research and Development
// Laboratory
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

/// \file tests/accu/all_accus.cc
///
/// \brief Tests on all_accus files in mln/accu/.

#include <mln/accu/all.hh>
#include <mln/core/alias/point2d.hh>
#include <mln/value/set.hh>


int main()
{
  using namespace mln;
  using namespace mln::accu;

  bbox<point2d> b;
  count<int> c;
  mln::accu::histo<bool> h;
  max<int> ma;
  mean<int> me;
  // median< value::set<bool> > med; // FIXME: bool has no min so workaround!
  min<int> mi;
  // min_h< value::set<bool> > mh;   // OK: do not work since bool has
                                     // no min/max :)
  min_max<int> mm;
  nil<int> n;
  pair< min<int>, max<int> > p;
  sum<int> s;
}
