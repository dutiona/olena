// Copyright (C) 2007, 2009 EPITA Research and Development Laboratory (LRDE)
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

#include <iostream>

#include <mln/util/lazy_set.hh>

int main ()
{
  using namespace mln;

  util::lazy_set_<int> s1;
  util::lazy_set_<int> s2;

  s1.insert(3);
  s1.insert(-2);
  s1.insert(9);
  s1.insert(0);
  s2.insert(3);
  s2.insert(-2);
  s2.insert(9);
  s2.insert(0);

  mln_assertion(s1.nelements() == 4);
  s2.set_const_mode(true);
  mln_assertion(s2.nelements() == 4);

  for (unsigned i = 0; i < s1.nelements(); ++i)
  {
    std::cout << s1[i] << " = " << s2[i] << std::endl;
    mln_assertion(s1[i] == s2[i]);
  }
}
