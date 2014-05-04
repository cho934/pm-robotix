

#ifndef UTILS_UTILS_HPP
#define UTILS_UTILS_HPP

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include "Macro.hpp"


using namespace std;

namespace utils
{

typedef unsigned char byte;

class Utils
{
public:

	static byte checkSumatory(byte data[], int length)
	{
		uint cs = 0;
		for (int i = 2; i < length; i++)
		{
			cs += data[i];
		}

		cs = ~cs;

		return (byte) (cs & 0x0FF);
	}

	static void sleepMS(int ms)
	{
		sleepMS((long) ms);
	}

	static void sleepMS(long ms)
	{
		usleep(ms * 1000);
	}

	static int convertToInt(string str)
	{
		int i = 0;
		std::istringstream ist(str);
		ist >> i;

		return i;
	}

	static double convertToDouble(string str)
	{
		double d = 0;
		std::istringstream ist(str);
		ist >> d;

		return d;
	}

	static string byteArrayTostring(unsigned char array[], int size)
	{
		ostringstream ost;
		string str;

		for (int i = 0; i < size; i++)
		{
//			sprintf (buffer, "%s", array[i])
			ost << (int) array[i] << ", ";
		}

		ost << endl;

		return ost.str();
	}
};

class Hex
{
public:
	/*
	static void toHexHLConversion_(int pos, byte &hexH, byte &hexL)
	{
		ushort uPos = (ushort) pos;
		hexH = (byte) (uPos >> 8);
		hexL = (byte) uPos;
	}*/

	static void toHexHLConversion(short pos, byte *hexH, byte *hexL)
	{
		*hexH = (byte)(pos >> 8);
		*hexL = (byte) pos;
	}

	static ushort fromHexHLConversion(byte hexH, byte hexL)
	{
		return (ushort) ((hexL << 8) + hexH);
	}

	static short fromHexHLConversionToShort(byte hexH, byte hexL)
	{
		return (short) ((hexL << 8) + hexH);
	}

	/*
	 static void toHexHLConversion(int pos, string &hexH, string &hexL) {

	 string hex;
	 int lon, start;
	 hex = String.Format("{0:X4}", pos);
	 lon = hex.Length;
	 if (lon < 2)
	 {
	 hexL = hex;
	 hexH = "0";
	 }
	 else
	 {
	 start = lon - 2;// lon = 4, start = 2; lon=3, start=1
	 hexL = hex.Substring(start);
	 hexH = hex.Substring(0, start);
	 }

	 }
	 */
};

} /* namespace MyCommunications */
#endif /* UTIL_H_ */

