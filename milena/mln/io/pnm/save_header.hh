// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009,
// 2011 EPITA Research and Development Laboratory (LRDE)
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

#ifndef MLN_IO_PNM_SAVE_HEADER_HH
# define MLN_IO_PNM_SAVE_HEADER_HH

/// \file
///
/// Define a function which saves header for PNM image.

# include <iostream>
# include <fstream>

# include <mln/version.hh>

# include <mln/io/pnm/max_component.hh>

# include <mln/value/rgb.hh>
# include <mln/geom/nrows.hh>
# include <mln/geom/ncols.hh>


namespace mln
{

  namespace io
  {

# ifndef MLN_INCLUDE_ONLY

    namespace pnm
    {

      template <typename V>
      inline
      void save_max_val(V&, std::ofstream& file)
      {
	file << max_component(V()) << std::endl;
      }

      inline
      void save_max_val(bool&, std::ofstream&)
      {
      }

      template <typename I>
      inline
      void save_header(char type,
		       const I& ima, const std::string& filename,
		       std::ofstream& file)
      {
	if (! file)
	{
	  std::cerr << "error: cannot open file '" << filename
		    << "'!";
	  abort();
	}
	file << "P" << type << std::endl;
	// We have a two-line comment because xv is buggy for some
	// tiny binary images and their workaround is to have such a
	// two-line comment...
	file << "# Generated by " OLN_PACKAGE_STRING " (" OLN_PACKAGE_URL ")"
	     << std::endl
	     << "# " OLN_PACKAGE_AUTHORS << std::endl;
	file << geom::ncols(ima) << ' ' << geom::nrows(ima) << std::endl;

	mln_value(I) i;
	save_max_val(i, file);
      }

    } // end of namespace mln::io::pnm


# endif // ! MLN_INCLUDE_ONLY

  } // end of namespace mln::io

} // end of namespace mln


#endif // ! MLN_IO_PNM_SAVE_HEADER_HH
