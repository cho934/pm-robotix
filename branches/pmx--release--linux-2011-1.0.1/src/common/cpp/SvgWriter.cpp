/*!
 * \file
 * \brief Implémentation de la classe SvgWriter.
 */

#include "SvgWriter.hpp"
#include "Level.hpp"

utils::SvgWriter::SvgWriter()
{
}

utils::SvgWriter::~SvgWriter()
{
}

void
utils::SvgWriter::writePosition(double x, double y)
{
    if (svg().isActive(utils::Level::INFO))
    {
        // inversion du y pour affichage dans le bon sens dans le SVG
        svg().info()
            << "<circle cx=\"" << x << "\" cy=\"" << -y << "\" r=\"1\" fill=\"green\" />"
            << utils::end;
    }
}

void
utils::SvgWriter::writeText(double x, double y, std::string text)
{
    if (svg().isActive(utils::Level::INFO))
    {
        // inversion du y pour affichage dans le bon sens dans le SVG
        svg().info()
            << "<text x='" << x << "' y='" << -y << "'>" << text << "</text>"
            << utils::end;
    }
}

void
utils::SvgWriter::writePawn(double x, double y)
{
    if (svg().isActive(utils::Level::INFO))
    {
        // inversion du y pour affichage dans le bon sens dans le SVG
        svg().info()
            << "<circle cx='" << x << "' cy='" << -y << "' r='100' fill='green' stroke='yellow' />"
            << utils::end;
    }
}

