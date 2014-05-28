/*!
 * \file
 * \brief Définition de la classe HostI2cBus, gestion du bus i2c pour APF9328.
 */

#ifndef HOSTI2CBUS_HPP
#define HOSTI2CBUS_HPP

#include <stddef.h>
//#include <cstdio>
#include <iostream>
#include <string>

#include "Exception.hpp"
#include "Macro.hpp"
#include "Mutex.hpp"

/*
 extern "C"
 {

 extern void * __libc_stack_end;

 struct backtrace_frame_t
 {
 void * fp;
 void * sp;
 void * lr;
 void * pc;
 };


 int backtracetest(void ** array, int size)
 {
 void * top_frame_p;
 void * current_frame_p;
 struct backtrace_frame_t * frame_p;
 int frame_count;

 top_frame_p = __builtin_frame_address(0);
 current_frame_p = top_frame_p;
 frame_p = (struct backtrace_frame_t*)((void**)(current_frame_p)-3);
 frame_count = 0;

 if (__builtin_return_address(0) != frame_p->lr)
 {
 fprintf(stderr, "backtrace error: __builtin_return_address(0) != frame_p->lr\n");
 return frame_count;
 }

 if (current_frame_p != NULL
 && current_frame_p > (void*)&frame_count
 && current_frame_p < __libc_stack_end)
 {
 while (frame_count < size
 && current_frame_p != NULL
 && current_frame_p > (void*)&frame_count
 && current_frame_p < __libc_stack_end)
 {
 frame_p = (struct backtrace_frame_t*)((void**)(current_frame_p)-3);
 array[frame_count] = frame_p->lr;
 frame_count++;
 current_frame_p = frame_p->fp;
 }
 }

 return frame_count;
 }


 static inline void printStackTrace()
 {
 printf( "stack trace:\n");

 // storage array for stack trace address data
 void* addrlist[63+1];

 // retrieve current stack addresses
 int addrlen = backtracetest( addrlist, sizeof( addrlist ) / sizeof( void* ));

 if ( addrlen == 0 )
 {
 printf( "  \n" );
 return;
 }

 }

 }*/

struct as_i2c_device;
//to remove error: cannot convert 'utils::as_i2c_device*' to 'as_i2c_device*' for argument '1' to 'int32_t as_i2c_close(as_i2c_device*)'

namespace utils
{

/*!
 * \brief Exception lancée s'il y a une erreur avec l'I2C.
 */
class I2cException: public Exception
{
public:
	I2cException(const std::string & message)
			: Exception(message)
	{
		std::cout << "I2cException=====" << message << std::endl;
	}

	virtual ~ I2cException() throw ()
	{
	}
};

class I2cWarning: public Exception
{
public:
	I2cWarning(const std::string & message)
			: Exception(message)
	{
	}

	virtual ~ I2cWarning() throw ()
	{
	}
};

class HostI2cBus: public utils::Mutex
{

private:
	/*!
	 * \brief Stored i2c parameters.
	 */
	struct as_i2c_device *device_;

	/*!
	 * \brief true if the i2c is opened.
	 */
	int opened_;

public:
	/*!
	 * \brief Constructeur de la classe.
	 */
	HostI2cBus();

	/*!
	 * \brief Destructeur de la classe.
	 */
	virtual ~HostI2cBus()
	{
		try
		{
			close_i2c();
		} catch (utils::Exception * e)
		{

			std::cout << "HostI2cBus()::Exception - close_i2c :" << e->what()
					<< std::endl;
		}
	}

	int isOpened(void);

	/*!
	 * \brief Read a byte from the given register.
	 *
	 * \param   reg   the given register.
	 * \param   data   the read value.
	 *
	 * \return return 0 on success, -1 on write error (\e reg byte), -2 on read error.
	 */
	int readRegValue(uchar slave_addr, uchar reg, uchar* data);

	/*!
	 * \brief Write a byte to the I2C given register.
	 *
	 * \param   reg   register to write.
	 * \param   value   value to apply.
	 *
	 * \return 0 on success, -1 on error.
	 */
	int writeRegValue(uchar slave_addr, uchar reg, uchar value);

	int readI2cSize(uchar slave_addr, char *buf, size_t size);

	int writeI2cSize(uchar slave_addr, const char *buf, size_t size);

	/*!
	 * \brief Read 4 bytes from the given register.
	 *
	 * \param   reg   the given register.
	 * \param   data   the read value.
	 *
	 * \return return 0 on success, -1 on write error (\e reg byte), -2 on read error.
	 */
//int readReg_nValue(uchar reg, uchar* data, size_t size);
	/*!
	 * \brief Open i2c.
	 */
	void open(uchar slave_addr);

	/*!
	 * \brief Close i2c.
	 */
	void close_i2c();

private:
	/*!
	 * \brief Set the slave by his address.
	 * \param   slaveAddr	slave address.
	 */
	void setSlave(uchar slaveAddr);

};
}

#endif
