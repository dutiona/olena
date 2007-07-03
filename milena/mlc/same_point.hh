#ifndef MLC_SAME_POINT_HH
# define MLC_SAME_POINT_HH

# include <mlc/equal.hh>
# include <mln/core/macros.hh>


namespace mln
{

  namespace mlc
  {

    template <typename T1, typename T2>
    struct same_point : mlc::equal<mln_point(T1), mln_point(T2)>
    {
    };

  } // end of namespace mln::mlc

} // end of namespace mln


#endif // ! MLC_SAME_POINT_HH
