/*!
 * \file
 * \brief Définition de l'énumeration ThreadState.
 * \todo deplacer dans macro.hpp
 */

#ifndef UTILS_THREADSTATE_HPP
#define	UTILS_THREADSTATE_HPP

namespace utils
{
    /*!
     * \brief Enumération des états des threads.
     */
    enum ThreadState
    { CREATED, STARTING, STARTED, STOPPED };
}

#endif
