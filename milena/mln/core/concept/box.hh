#ifndef MLN_CORE_CONCEPT_BOX_HH
# define MLN_CORE_CONCEPT_BOX_HH

/*! \file mln/core/concept/box.hh
 * \brief This file defines the concept of mln::Box.
 */

# include <mln/core/concept/point_set.hh>


namespace mln
{

  /*! \brief Base class for implementation classes of boxes.
   *
   * Boxes are particular point sets useful to bound any set of
   * points.
   *
   * \see mln::doc::Box for a complete documentation of this class
   * contents.
   */
  template <typename E>
  struct Box : public Point_Set<E>
  {
    /*
      const point& pmin() const;
      const point& pmax() const;
    */

    const E& bbox() const; //! final; \see mln::doc::Box::bbox
    std::size_t npoints() const;  //! final; \see mln::doc::Box::npoints

  protected:
    Box();
  };


# ifndef MLN_INCLUDE_ONLY

  template <typename E>
  const E& Box<E>::bbox() const
  {
    return exact(*this);
  }

  template <typename E>
  Box<E>::Box()
  {
    typedef mln_point(E) point;
    point (E::*m1)() const = & E::pmin;
    m1 = 0;
    point (E::*m2)() const = & E::pmax;
    m2 = 0;
  }

  template <typename E>
  std::size_t
  Box<E>::npoints() const
  {
    std::size_t count = 1;
    for (unsigned i = 0; i < E::point::dim; ++i)
      count *=
	exact(this)->pmax()[i]
	+ 1
	- exact(this)->pmin()[i];
    return count;
  }

# endif // ! MLN_INCLUDE_ONLY

} // end of namespace mln


#endif // ! MLN_CORE_CONCEPT_BOX_HH
