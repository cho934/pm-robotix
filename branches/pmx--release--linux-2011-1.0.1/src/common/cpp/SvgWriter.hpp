#ifndef UTILS_SVGWRITER_HPP
#define	UTILS_SVGWRITER_HPP

#include "LoggerFactory.hpp"

namespace utils
{
    /*!
     * \brief Wrapper pour la génération de fichier svg via le système de log.
     */
    class SvgWriter
    {
    private:

        /*!
         * \brief Retourne le \ref Logger nommé svg associé à la classe \ref SvgWriter.
         */
        static inline const utils::Logger & svg()
        {
            static const utils::Logger & svg_ = utils::LoggerFactory::logger("utils::SvgWriter::svg");
            return svg_;
        }

    private:

        /*!
         * \brief Constructeur de la classe.
         * 
         * Ce constructeur est privé pour empécher la création d'une instance
         * de la classe.
         */
        SvgWriter();

    public:

        /*!
         * \brief Destructeur de la classe.
         */
        virtual ~SvgWriter();

        /*!
         * \brief Affiche la position actuel du robot sur le svg.
         * \param x
         *        Position en abscisse du robot.
         * \param y
         *        Position en ordonnée du robot.
         */
        static void writePosition(double x, double y);

        static void writeText(double x, double y, std::string text);

        static void writePawn(double x, double y);
    };
}

#endif
