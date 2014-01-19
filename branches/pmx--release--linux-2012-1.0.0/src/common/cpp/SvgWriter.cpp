/*!
 * \file
 * \brief Implémentation de la classe SvgWriter.
 */

#include "SvgWriter.hpp"
#include "Level.hpp"
#include <string>
#include <cmath>

utils::SvgWriter::SvgWriter()
{
}

utils::SvgWriter::~SvgWriter()
{
}

void
utils::SvgWriter::writePosition(double x, double y, double angle, SvgPositionColor svgcolor)
{
    if (svg().isActive(utils::Level::INFO))
    {
        double delta_y = 0.0;
        double delta_x = 0.0;
        switch(svgcolor)
        {
            case SVG_POS_END :
                svg().info()
                    << "<circle cx=\"" << x << "\" cy=\"" << -y << "\" r=\"4\" stroke=\"blue\" fill=\"none\"  />"
                    << utils::end;
                break;
            case SVG_POS_RED :
                svg().info()
                    << "<circle cx=\"" << x << "\" cy=\"" << -y << "\" r=\"3\" stroke=\"red\" fill=\"none\"  />"
                    << utils::end;
                break;
            case SVG_POS_YELLOW :
                svg().info()
                    << "<circle cx=\"" << x << "\" cy=\"" << -y-6 << "\" r=\"1\" stroke=\"yellow\" fill=\"none\"  />"
                    << utils::end;
                break;
            case SVG_POS_BLACK :
                // inversion du y pour affichage dans le bon sens dans le SVG
                svg().info()
                    << "<circle cx=\"" << x << "\" cy=\"" << -y << "\" r=\"2\" stroke=\"black\" fill=\"none\"  />"
                    << utils::end;
                //std::ostringstream log;
                //log << "x:"<< x << " y:" << y << " a:" << angle;
                svg().info()
                    << "<text x='" << x+5 << "' y='" << -y << "' font-size='5' fill='black'>" << "x:"<< x << " y:" << y << " a:" << (angle * 180) / M_PI << "°</text>"
                    << utils::end;
                break;
            case SVG_POS_BLUE :
                svg().info()
                    << "<circle cx=\"" << x << "\" cy=\"" << -y-3 << "\" r=\"1\" fill=\"blue\" />"
                    << utils::end;
                break;
             case SVG_POS_ANGLE :
                 delta_y = -100.0 * sin(angle);
                 delta_x = -100.0 * cos(angle);
                 svg().info()
                    << "<line x1=\"" << x << "\" y1=\"" << -y << "\" x2=\"" << x + delta_x << "\" y2=\"" << -y - delta_y << "\" stroke-width=\"0.1\" stroke=\"grey\"  />"
                    << utils::end;
                svg().info()
                    << "<circle cx=\"" << x + delta_x << "\" cy=\"" << -y - delta_y << "\" r=\"1\" fill=\"red\" />"
                    << utils::end;
                break;
            case SVG_POS_ROBOT :
                svg().info()
                    << "<use x=\"0\" y=\"0\" xlink:href=\"#robot-pmx\" transform=\"rotate("<< 0*angle*180/M_PI <<") translate("<< x-190 <<","<< -y-190 <<")\"/>"
                        //<< "<circle cx=\"" << x << "\" cy=\"" << -y << "\" r=\"19\" fill=\"none\" stroke=\"black\"/>"
                    << utils::end;
                break;
            case SVG_POS_GREEN :
            default:
                // inversion du y pour affichage dans le bon sens dans le SVG
                svg().info()
                    << "<circle cx=\"" << x << "\" cy=\"" << -y << "\" r=\"1\" fill=\"green\" />"
                    << utils::end;
                delta_y = 25.0 * sin(angle);
                delta_x = 25.0 * cos(angle);
                svg().info()
                    << "<line x1=\"" << x << "\" y1=\"" << -y << "\" x2=\"" << x + delta_x << "\" y2=\"" << -y - delta_y << "\" stroke-width=\"0.1\" stroke=\"grey\"  />"
                    << utils::end;
                break;
        } 
    }
}

void
utils::SvgWriter::writeText(double x, double y, std::string text)
{
    if (svg().isActive(utils::Level::INFO))
    {
        // inversion du y pour affichage dans le bon sens dans le SVG
        svg().info()
            << "<text x='" << x << "' y='" << -y << "' font-size='5' fill='black'>" << text << "</text>"
            << utils::end;
    }
}

void
utils::SvgWriter::writeTextCustom(double x, double y, std::string text, std::string color, std::string fontsize)
{
    if (svg().isActive(utils::Level::INFO))
    {
        // inversion du y pour affichage dans le bon sens dans le SVG
        svg().info()
            << "<text x='" << x << "' y='" << -y << "' font-size='" << fontsize << "' fill='" << color << "'>" << text << "</text>"
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

