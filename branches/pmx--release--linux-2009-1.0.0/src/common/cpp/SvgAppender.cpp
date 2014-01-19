#include "SvgAppender.hpp"

utils::SvgAppender::SvgAppender(const std::string & filename) : ofs_(filename.c_str())
{
    //TODO mettre l'echelle en fichier de conf
    int ymin = -500;
    int ymax = +500;
    int xmin = -1000;
    int xmax = 3000;
        
    this->ofs_ << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"" << (abs(xmin) + abs(xmax)) << "px\" height=\"" << (abs(ymin) + abs(ymax)) << "px\">" << std::endl;
    this->ofs_ << "<g transform=\"translate(" << abs(xmin) << "," << abs(ymin) << ")\">" << std::endl;
    
    //affichage des lignes d'abcisse vertes
    for(int i=ymax ; i >= ymin ; i-=100)
    {
        this->ofs_ << "<line x1=\"" << xmin << "\" y1=\"" << i << "\" x2=\"" << xmax << "\" y2=\"" << i << "\" stroke=\"green\" />" << std::endl;
        this->ofs_ << "<text x=\"0\" y=\"" << i << "\" dx=\"5\" dy=\"-5\" fill=\"green\" font-size=\"12\">" << -i << "</text>" << std::endl;
    }
    //affichage des lignes d'ordonnée rouges
    for(int i=xmin; i <=xmax; i+= 100)
    {
        this->ofs_ << "<line x1=\"" << i << "\" y1=\"" << ymin << "\" x2=\"" << i << "\" y2=\"" << ymax << "\" stroke=\"red\" />" << std::endl;
        this->ofs_ << "<text x=\"" << i << "\" y=\"0\" dx=\"5\" dy=\"17\" fill=\"red\" font-size=\"12\">" << i << "</text>" << std::endl;
    }
}

utils::SvgAppender::~SvgAppender()
{
    this->flush();
}

void
utils::SvgAppender::flush()
{
    this->ofs_ << "</g>" << std::endl << "</svg>" << std::endl;
    this->ofs_.close();
}
