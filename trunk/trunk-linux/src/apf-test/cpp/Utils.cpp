/*------------------------------------------------------------------------------*\
 * This source file is subject to the GPLv3 license that is bundled with this   *
 * package in the file COPYING.                                                 *
 * It is also available through the world-wide-web at this URL:                 *
 * http://www.gnu.org/licenses/gpl-3.0.txt                                      *
 * If you did not receive a copy of the license and are unable to obtain it     *
 * through the world-wide-web, please send an email to                          *
 * siempre.aprendiendo@gmail.com so we can send you a copy immediately.         *
 *                                                                              *
 * @category  Robotics                                                          *
 * @copyright Copyright (c) 2011 Jose Cortes (https://plus.google.com/105007891378677151287/about) *
 * @license   http://www.gnu.org/licenses/gpl-3.0.txt GNU v3 Licence            *
 *                                                                              *
\*------------------------------------------------------------------------------*/


/*
 * Util.cpp
 *
 *  Created on: Jul 18, 2012
 *      Author: jose
 */

#include "Utils.hpp"

namespace MyUtil {
    void Debug::show(string message, int value) {
        //printf("%s: %i", message.c_str(), value);
        cout << message << "(si)=> [" << value << "] " << endl;
    }

    void Debug::show(string message, string value) {
        //printf("%s: %s", message.c_str(), value.c_str());
        cout << message << "(ss)=> [" << value << "] " << endl;
    }
}
/* namespace MyCommunications */
