// Copyright (C) 2009, 2010 EPITA Research and Development Laboratory
// (LRDE)
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

#ifndef IMAGE_REGION_HXX_
# define IMAGE_REGION_HXX_

# include "image_region.hh"

inline
void
ImageRegion::setOutline(bool outline)
{
  outline_ = outline;
  scene()->invalidate();
  update();
}

inline
void
ImageRegion::setPrecise(bool precise)
{
  precise_ = precise;
  scene()->invalidate();
  update();
}

inline
void
ImageRegion::setFill(bool fill)
{
  fill_ = fill;
  update();
}

inline
void
ImageRegion::setDraw(bool draw)
{
  draw_ = draw;
  update();
}

inline
void
ImageRegion::setDrawIfSameId(int id, bool draw)
{
  if (id == id_)
    {
      draw_ = draw;
      setVisible(draw);
      if (scene())
	{
	  scene()->invalidate();
	  update();
	}
    }
}

inline
void
ImageRegion::setFillAlpha(int alpha)
{
  alpha_ = alpha;
  update();
}

inline
QRectF
ImageRegion::boundingRect() const
{
//   if (selected_)
//     return mapFromScene(scene()->sceneRect()).boundingRect();
  return rect_;
}

inline
QPainterPath
ImageRegion::shape() const
{
  return shape_;
}

#endif /* !IMAGE_REGION_HXX_ */
