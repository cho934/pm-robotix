//drivers...EV3

#include "ServoDriver.hpp"

#include <stddef.h>
#include <fstream>
#include <iostream>

#include <string>

#include <list>
#include <map>
#include <algorithm>
#include <system_error>
#include <mutex>
#include <string.h>
#include <math.h>

#include <dirent.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>

#include "../Log/Logger.hpp"

using namespace std;
using namespace ev3dev;

namespace
{

// This class implements a small LRU cache. It assumes the number of elements
// is small, and so uses a simple linear search.
template<typename K, typename V>
class lru_cache
{
private:
	// typedef st::pair<K, V> item;
	// std::pair seems to be missing necessary move constructors :(
	struct item
	{
		K first;
		V second;

		item(const K &k) :
				first(k)
		{
		}
		item(item &&m) :
				first(std::move(m.first)), second(std::move(m.second))
		{
		}
	};

public:
	lru_cache(size_t size = 3) :
			_size(size)
	{
	}

	V &operator[](const K &k)
	{
		iterator i = find(k);
		if (i != _items.end())
		{
			// Found the key, bring the item to the front.
			_items.splice(_items.begin(), _items, i);
		}
		else
		{
			// If the cache is full, remove oldest items to make room.
			while (_items.size() + 1 > _size)
			{
				_items.pop_back();
			}
			// Insert a new default constructed value for this new key.
			_items.emplace_front(k);
		}
		// The new item is the most recently used.
		return _items.front().second;
	}

	void clear()
	{
		_items.clear();
	}

private:
	typedef typename std::list<item>::iterator iterator;

	iterator find(const K &k)
	{
		return std::find_if(_items.begin(), _items.end(), [&](const item &i)
		{	return i.first == k;});
	}

	size_t _size;
	std::list<item> _items;
};

// A global cache of files.
lru_cache<std::string, std::ifstream> ifstream_cache(FSTREAM_CACHE_SIZE);
lru_cache<std::string, std::ofstream> ofstream_cache(FSTREAM_CACHE_SIZE);
std::mutex ofstream_cache_lock;
std::mutex ifstream_cache_lock;

//-----------------------------------------------------------------------------

std::ofstream &ofstream_open(const std::string &path)
{
	std::lock_guard<std::mutex> lock(ofstream_cache_lock);
	std::ofstream &file = ofstream_cache[path];
	if (!file.is_open())
	{
		// Don't buffer writes to avoid latency. Also saves a bit of memory.
		file.rdbuf()->pubsetbuf(NULL, 0);
		file.open(path);
	}
	else
	{
		// Clear the error bits in case something happened.
		file.clear();
	}
	return file;
}

std::ifstream &ifstream_open(const std::string &path)
{
	std::lock_guard<std::mutex> lock(ifstream_cache_lock);
	std::ifstream &file = ifstream_cache[path];
	if (!file.is_open())
	{
		file.open(path);
	}
	else
	{
		// Clear the flags bits in case something happened (like reaching EOF).
		file.clear();
		file.seekg(0, std::ios::beg);
	}
	return file;
}

} // namespace

AServoDriver * AServoDriver::create()
{
	static ServoDriver *instance = new ServoDriver();
	return instance;
}

ServoDriver::ServoDriver() :
		connected_(0)
{

	static const std::string _strClassDir
	{ "/sys/class/servo-motor/" };
	static const std::string _strPattern
	{ "motor" };

	logger().debug() << "ServoDriver()" << logs::end;
	/*
	 servo_motor mt_;
	 mt_ = servo_motor(SV0);

	 if (mt_.connected())
	 {
	 cout << "mt connected" << endl;
	 }else
	 {
	 cout <<"mt not connected"<< endl;
	 }
	 */
	/*
	 if (m_.connected())
	 {
	 cout << endl << "Found servo motor on port " << m_.port_name() << endl << endl;

	 cout << "  Current command is " << m_.command() << endl << "    position:     "
	 << m_.position() << endl << "    rate:         " << m_.rate() << endl
	 << "    min_pulse_ms: " << m_.min_pulse_ms() << endl << endl << "    mid_pulse_ms: "
	 << m_.mid_pulse_ms() << endl << endl << "    max_pulse_ms: " << m_.max_pulse_ms()
	 << endl << endl << "    polarity:     " << m_.polarity() << endl << endl;
	 }
	 else
	 cout << "No servo motor found" << endl;
	 */

	//positionOpFileName_ = getFilename(SERVO_DRIVER_SERVO_POSITION_FILE);
	//sprintf(positionOpFileName_, "%s%s%d", _strClassDir, _strPattern);
	ostringstream out;
	out << _strClassDir << _strPattern << "0/";
	_pathSV1 = out.str();
	//out.clear();
	ostringstream out2;
	out2 << _strClassDir << _strPattern << "7/";
	_pathSV8 = out2.str();


	//init
	_path = _pathSV8;
	set_attr_string("polarity", "inverted");

	//cout << "_path=" << _path << endl;
}

void ServoDriver::set_attr_int(const std::string &name, int value)
{
	using namespace std;

	if (_path.empty())
		throw system_error(make_error_code(errc::function_not_supported), "no device connected");

	//cout << _path + name << ":" << value << endl; //LOG

	ofstream &os = ofstream_open(_path + name);
	if (os.is_open())
	{
		os << value;
		return;
	}

	throw system_error(make_error_code(errc::no_such_device), _path + name);
}

void ServoDriver::set_attr_string(const std::string &name, const std::string &value)
{
	using namespace std;

	if (_path.empty())
		throw system_error(make_error_code(errc::function_not_supported), "no device connected");

	//cout << _path + name << ":" << value << endl; //LOG

	ofstream &os = ofstream_open(_path + name);
	if (os.is_open())
	{
		os << value;
		return;
	}

	throw system_error(make_error_code(errc::no_such_device), _path + name);
}

void ServoDriver::hold(int servoId) // 1 à 8
{
	if (servoId == 1)
	{
		_path = _pathSV1;
	}
	else
	{
		_path = _pathSV8;
	}
	set_attr_string("command", "run");
}

void ServoDriver::setPosition(int servoId, int pos)
{
	if (servoId == 1)
	{
		_path = _pathSV1;
	}
	else
	{
		_path = _pathSV8;
	}
	set_attr_int("position", pos);
}

void ServoDriver::release(int servoId)
{
	if (servoId == 1)
	{
		_path = _pathSV1;
	}
	else
	{
		_path = _pathSV8;
	}
	set_attr_string("command", "float");
}
