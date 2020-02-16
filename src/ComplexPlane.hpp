#include <complex>

#ifdef HIGH_PRECISION
#include <boost/multiprecision/mpfr.hpp>
using Number = boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0>>;
#else
using Number = double;
#endif

using Complex = std::complex<Number>;

template<typename T> class ComplexPlane {
public:
  T minX, minY, maxX, maxY;
public:
  ComplexPlane() :minX(0), minY(0), maxX(0), maxY(0) {}
  ComplexPlane(T minX, T minY, T maxX, T maxY) :minX(minX), minY(minY), maxX(maxX), maxY(maxY) {}
  T width() { return maxX - minX; }
  T height() { return maxY - minY; }

  inline void zoomTo(T x, T y, long long zoomAmmount)
  {
    T halfWidth = width() / (zoomAmmount * 2);
    T halfHeight = height() / (zoomAmmount * 2);
    minX = x - halfWidth;
    maxX = x + halfHeight;
    minY = y - halfWidth;
    maxY = y + halfHeight;
  }

  inline void updateForProportions(T proportions)
  {
    T newHalfHeight = width() * proportions / 2;
    T centerY = (minY + maxY) / 2;
    minY = centerY - newHalfHeight;
    maxY = centerY + newHalfHeight;
  }
};
