#include <mln/core/image/image2d.hh>
#include <mln/value/int_u8.hh>
int main()
{
  using namespace mln;

  // \{
  // Build an empty image;
  image2d<value::int_u8> img1a;

  // Build an image with 2 rows
  // and 3 columns sites
  image2d<value::int_u8> img1b(box2d(2, 3));
  image2d<value::int_u8> img1c(2, 3);
  // \}
}
