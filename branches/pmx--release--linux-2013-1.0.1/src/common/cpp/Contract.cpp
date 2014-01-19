/*!
 * \file
 * \brief Implémentation de la classe Contract.
 */

#include "Contract.hpp"

void
utils::Contract::isNotNull(void* value, const std::string& message)
{
    if (value == NULL)
    {
        // La valeur est null, une exception est levée.
        throw new utils::ContractException(message);
    }
}
