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

#ifndef MLN_IO_RAW_SAVE_HH
# define MLN_IO_RAW_SAVE_HH

/// \file mln/io/raw/save.hh
///
/// Save a Milena image by dumping its data to a file.
/// \todo handle endianness.

# include <iostream>
# include <fstream>

# include <mln/core/concept/image.hh>
# include <mln/core/box_runstart_piter.hh>
# include <mln/core/pixel.hh>
# include <mln/data/memcpy_.hh>

namespace mln
{

  namespace io
  {

    namespace raw
    {

      /// Save a Milena image by dumping its data to a file.
      ///
      /// \param[in] ima_ The image to save.
      /// \param[in] filename the destination.
      template <typename I>
      void save(const Image<I>& ima_, const std::string& filename);


# ifndef MLN_INCLUDE_ONLY

      namespace internal
      {

        template <typename I>
        inline
        void save_header(const I& ima,
			 std::ofstream& file)
	{
	  typedef mln_site(I) P;
	  file << P::dim;

	  mln_site(I) p = ima.domain().pmin();
	  file.write((char*) (&p), sizeof (P));

	  p = ima.domain().pmax();
	  file.write((char*) (&p), sizeof (P));
	}


	template <typename I>
        inline
        void save_data(I& ima, std::ofstream& file)
	{
	  // Handle padding.
	  unsigned data_size = sizeof (mln_value(I)) + sizeof (mln_value(I)) % 2;

	  mln_box_runstart_piter(I) p(ima.domain());
	  for_all(p)
	  {
	    pixel<I> src(ima, p);
	    file.write((char*) (&src.val()), p.run_length() * data_size);
	  }
	}

      } // end of namespace mln::io::raw::internal


      template <typename I>
      void save(const Image<I>& ima_, const std::string& filename)
      {
	trace::entering("mln::io::raw::save");

	const I& ima = exact(ima_);

	std::ofstream file(filename.c_str());
	if (! file)
	{
	  std::cerr << "error: cannot open file '" << filename << "'!";
	  abort();
	}

	internal::save_header(ima, file);
	internal::save_data(ima, file);

	trace::exiting("mln::io::raw::save");
      }


# endif // ! MLN_INCLUDE_ONLY

    } // end of namespace mln::io::raw

  } // end of namespace mln::io

} // end of namespace mln

#endif // ! MLN_IO_RAW_SAVE_HH