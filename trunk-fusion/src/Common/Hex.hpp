#include <iostream>

template<typename T>
inline T highbit(T& t)
{
	return t = (((T) (-1)) >> 1) + 1;
}

/*!
 *  Display binary value
 * @param value
 * @param o (= std::cout)
 * @return
 */
/* example:
	 cout << "hexPosition=" << hex << hexPosition << " dec=" << dec << hexPosition << " bin=";
	 bin(hexPosition, cout);
	 cout << endl;
*/
template<typename T>
std::ostream& bin(T& value, std::ostream &o)
{
	for (T bit = highbit(bit); bit; bit >>= 1)
	{
		o << ((value & bit) ? '1' : '0');
	}
	return o;
}
