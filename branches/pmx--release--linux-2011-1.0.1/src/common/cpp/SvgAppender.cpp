#include "SvgAppender.hpp"

#include <cstdlib> //lib for abs(int)

utils::SvgAppender::SvgAppender(const std::string & filename) : ofs_(filename.c_str())
{
    int ymin = -2200;
    int ymax = +2200;
    int xmin = -200;
    int xmax = 3100;

    this->ofs_ << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"" << (abs(xmin) + std::abs(xmax)) << "px\" height=\"" << (std::abs(ymin) + std::abs(ymax)) << "px\">" << std::endl;
    this->ofs_ << "<g transform=\"translate(" << std::abs(xmin) << "," << std::abs(ymin) << ")\">" << std::endl;

    //affichage des lignes d'abcisse vertes
    for (int i = ymax; i >= ymin; i -= 100)
    {
        this->ofs_ << "<line x1=\"" << xmin << "\" y1=\"" << i << "\" x2=\"" << xmax << "\" y2=\"" << i << "\" stroke=\"#eeeeee\" />" << std::endl;
        this->ofs_ << "<text x=\"0\" y=\"" << i << "\" dx=\"5\" dy=\"-5\" fill=\"#eeeeee\" font-size=\"12\">" << -i << "</text>" << std::endl;
    }
    //affichage des lignes d'ordonnée rouges
    for (int i = xmin; i <= xmax; i += 100)
    {
        this->ofs_ << "<line x1=\"" << i << "\" y1=\"" << ymin << "\" x2=\"" << i << "\" y2=\"" << ymax << "\" stroke=\"#eeeeee\" />" << std::endl;
        this->ofs_ << "<text x=\"" << i << "\" y=\"0\" dx=\"5\" dy=\"17\" fill=\"#eeeeee\" font-size=\"12\">" << i << "</text>" << std::endl;
    }
    this->ofs_ << "</g>" << std::endl << "<g transform=\"translate(" << std::abs(xmin) << "," << std::abs(ymin) << ")\">" << std::endl;


    //terrain de la coupe 2011
    this->ofs_ << "<circle cx='200' cy='-200' r='160' stroke='blue' fill='none' />" << std::endl
    << "<circle cx='200' cy='200' r='160' stroke='red' fill='none' />" << std::endl

    << "<rect x='0' y='-2100' width='3000' height='2100' stroke='blue' fill='none' />" << std::endl
    << "<rect x='0' y='0' width='3000' height='2100' stroke='red' fill='none' />" << std::endl

    << "<rect x='400' y='-2100' width='50' height='2100' stroke='blue' fill='none'/>" << std::endl
    << "<rect x='400' y='0' width='50' height='2100' stroke='red' fill='none'/>" << std::endl
    << "<rect x='2550' y='-2100' width='50' height='2100' stroke='blue' fill='none'/>" << std::endl
    << "<rect x='2550' y='0' width='50' height='2100' stroke='red' fill='none'/>" << std::endl

    << "<rect x='0' y='-422' width='400' height='22' stroke='black' fill='blue'/>" << std::endl
    << "<rect x='0' y='400' width='400' height='22' stroke='black' fill='red'/>" << std::endl
    << "<rect x='2600' y='-422' width='400' height='22' stroke='black' fill='blue'/>" << std::endl
    << "<rect x='2600' y='400' width='400' height='22' stroke='black' fill='red'/>" << std::endl

    << "<line x1='800' y1='0' x2='800' y2='-2100' stroke='black' />" << std::endl
    << "<line x1='1150' y1='0' x2='1150' y2='-2100' stroke='black' />" << std::endl
    << "<line x1='1500' y1='0' x2='1500' y2='-2100' stroke='black' />" << std::endl
    << "<line x1='1850' y1='0' x2='1850' y2='-2100' stroke='black' />" << std::endl
    << "<line x1='2200' y1='0' x2='2200' y2='-2100' stroke='black' />" << std::endl

    << "<line x1='800' y1='0' x2='800' y2='2100' stroke='black' />" << std::endl
    << "<line x1='1150' y1='0' x2='1150' y2='2100' stroke='black' />" << std::endl
    << "<line x1='1500' y1='0' x2='1500' y2='2100' stroke='black' />" << std::endl
    << "<line x1='1850' y1='0' x2='1850' y2='2100' stroke='black' />" << std::endl
    << "<line x1='2200' y1='0' x2='2200' y2='2100' stroke='black' />" << std::endl

    << "<line x1='450' y1='-350' x2='2550' y2='-350' stroke='black' />" << std::endl
    << "<line x1='450' y1='-700' x2='2550' y2='-700' stroke='black' />" << std::endl
    << "<line x1='450' y1='-1050' x2='2550' y2='-1050' stroke='black' />" << std::endl
    << "<line x1='450' y1='-1400' x2='2550' y2='-1400' stroke='black' />" << std::endl
    << "<line x1='450' y1='-1750' x2='2550' y2='-1750' stroke='black' />" << std::endl

    << "<line x1='450' y1='350' x2='2550' y2='350' stroke='black' />" << std::endl
    << "<line x1='450' y1='700' x2='2550' y2='700' stroke='black' />" << std::endl
    << "<line x1='450' y1='1050' x2='2550' y2='1050' stroke='black' />" << std::endl
    << "<line x1='450' y1='1400' x2='2550' y2='1400' stroke='black' />" << std::endl
    << "<line x1='450' y1='1750' x2='2550' y2='1750' stroke='black' />" << std::endl;

    this->ofs_ << "<rect x='455' y='-345' width='340' height='340' stroke='red' fill='none'/>" << std::endl
    << "<rect x='805' y='-345' width='340' height='340' stroke='blue' fill='none'/>" << std::endl
    << "<rect x='1155' y='-345' width='340' height='340' stroke='red' fill='none'/>" << std::endl
    << "<rect x='1505' y='-345' width='340' height='340' stroke='blue' fill='none'/>" << std::endl
    << "<rect x='1855' y='-345' width='340' height='340' stroke='red' fill='none'/>" << std::endl
    << "<rect x='2205' y='-345' width='340' height='340' stroke='blue' fill='none'/>" << std::endl

    << "<rect x='455' y='-1045' width='340' height='340' stroke='red' fill='none'/>" << std::endl
    << "<rect x='805' y='-1045' width='340' height='340' stroke='blue' fill='none'/>" << std::endl
    << "<rect x='1155' y='-1045' width='340' height='340' stroke='red' fill='none'/>" << std::endl
    << "<rect x='1505' y='-1045' width='340' height='340' stroke='blue' fill='none'/>" << std::endl
    << "<rect x='1855' y='-1045' width='340' height='340' stroke='red' fill='none'/>" << std::endl
    << "<rect x='2205' y='-1045' width='340' height='340' stroke='blue' fill='none'/>" << std::endl

    << "<rect x='455' y='-1745' width='340' height='340' stroke='red' fill='none'/>" << std::endl
    << "<rect x='805' y='-1745' width='340' height='340' stroke='blue' fill='none'/>" << std::endl
    << "<rect x='1155' y='-1745' width='340' height='340' stroke='red' fill='none'/>" << std::endl
    << "<rect x='1505' y='-1745' width='340' height='340' stroke='blue' fill='none'/>" << std::endl
    << "<rect x='1855' y='-1745' width='340' height='340' stroke='red' fill='none'/>" << std::endl
    << "<rect x='2205' y='-1745' width='340' height='340' stroke='blue' fill='none'/>" << std::endl

    << "<rect x='455' y='-695' width='340' height='340' stroke='blue' fill='none'/>" << std::endl
    << "<rect x='805' y='-695' width='340' height='340' stroke='red' fill='none'/>" << std::endl
    << "<rect x='1155' y='-695' width='340' height='340' stroke='blue' fill='none'/>" << std::endl
    << "<rect x='1505' y='-695' width='340' height='340' stroke='red' fill='none'/>" << std::endl
    << "<rect x='1855' y='-695' width='340' height='340' stroke='blue' fill='none'/>" << std::endl
    << "<rect x='2205' y='-695' width='340' height='340' stroke='red' fill='none'/>" << std::endl

    << "<rect x='455' y='-1395' width='340' height='340' stroke='blue' fill='none'/>" << std::endl
    << "<rect x='805' y='-1395' width='340' height='340' stroke='red' fill='none'/>" << std::endl
    << "<rect x='1155' y='-1395' width='340' height='340' stroke='blue' fill='none'/>" << std::endl
    << "<rect x='1505' y='-1395' width='340' height='340' stroke='red' fill='none'/>" << std::endl
    << "<rect x='1855' y='-1395' width='340' height='340' stroke='blue' fill='none'/>" << std::endl
    << "<rect x='2205' y='-1395' width='340' height='340' stroke='red' fill='none'/>" << std::endl

    << "<rect x='455' y='-2095' width='340' height='340' stroke='blue' fill='none'/>" << std::endl
    << "<rect x='805' y='-2095' width='340' height='340' stroke='red' fill='none'/>" << std::endl
    << "<rect x='1155' y='-2095' width='340' height='340' stroke='blue' fill='none'/>" << std::endl
    << "<rect x='1505' y='-2095' width='340' height='340' stroke='red' fill='none'/>" << std::endl
    << "<rect x='1855' y='-2095' width='340' height='340' stroke='blue' fill='none'/>" << std::endl
    << "<rect x='2205' y='-2095' width='340' height='340' stroke='red' fill='none'/>" << std::endl


    << "<rect x='455' y='5' width='340' height='340' stroke='blue' fill='none'/>" << std::endl
    << "<rect x='805' y='5' width='340' height='340' stroke='red' fill='none'/>" << std::endl
    << "<rect x='1155' y='5' width='340' height='340' stroke='blue' fill='none'/>" << std::endl
    << "<rect x='1505' y='5' width='340' height='340' stroke='red' fill='none'/>" << std::endl
    << "<rect x='1855' y='5' width='340' height='340' stroke='blue' fill='none'/>" << std::endl
    << "<rect x='2205' y='5' width='340' height='340' stroke='red' fill='none'/>" << std::endl

    << "<rect x='455' y='705' width='340' height='340' stroke='blue' fill='none'/>" << std::endl
    << "<rect x='805' y='705' width='340' height='340' stroke='red' fill='none'/>" << std::endl
    << "<rect x='1155' y='705' width='340' height='340' stroke='blue' fill='none'/>" << std::endl
    << "<rect x='1505' y='705' width='340' height='340' stroke='red' fill='none'/>" << std::endl
    << "<rect x='1855' y='705' width='340' height='340' stroke='blue' fill='none'/>" << std::endl
    << "<rect x='2205' y='705' width='340' height='340' stroke='red' fill='none'/>" << std::endl

    << "<rect x='455' y='1405' width='340' height='340' stroke='blue' fill='none'/>" << std::endl
    << "<rect x='805' y='1405' width='340' height='340' stroke='red' fill='none'/>" << std::endl
    << "<rect x='1155' y='1405' width='340' height='340' stroke='blue' fill='none'/>" << std::endl
    << "<rect x='1505' y='1405' width='340' height='340' stroke='red' fill='none'/>" << std::endl
    << "<rect x='1855' y='1405' width='340' height='340' stroke='blue' fill='none'/>" << std::endl
    << "<rect x='2205' y='1405' width='340' height='340' stroke='red' fill='none'/>" << std::endl

    << "<rect x='455' y='355' width='340' height='340' stroke='red' fill='none'/>" << std::endl
    << "<rect x='805' y='355' width='340' height='340' stroke='blue' fill='none'/>" << std::endl
    << "<rect x='1155' y='355' width='340' height='340' stroke='red' fill='none'/>" << std::endl
    << "<rect x='1505' y='355' width='340' height='340' stroke='blue' fill='none'/>" << std::endl
    << "<rect x='1855' y='355' width='340' height='340' stroke='red' fill='none'/>" << std::endl
    << "<rect x='2205' y='355' width='340' height='340' stroke='blue' fill='none'/>" << std::endl

    << "<rect x='455' y='1055' width='340' height='340' stroke='red' fill='none'/>" << std::endl
    << "<rect x='805' y='1055' width='340' height='340' stroke='blue' fill='none'/>" << std::endl
    << "<rect x='1155' y='1055' width='340' height='340' stroke='red' fill='none'/>" << std::endl
    << "<rect x='1505' y='1055' width='340' height='340' stroke='blue' fill='none'/>" << std::endl
    << "<rect x='1855' y='1055' width='340' height='340' stroke='red' fill='none'/>" << std::endl
    << "<rect x='2205' y='1055' width='340' height='340' stroke='blue' fill='none'/>" << std::endl

    << "<rect x='455' y='1755' width='340' height='340' stroke='red' fill='none'/>" << std::endl
    << "<rect x='805' y='1755' width='340' height='340' stroke='blue' fill='none'/>" << std::endl
    << "<rect x='1155' y='1755' width='340' height='340' stroke='red' fill='none'/>" << std::endl
    << "<rect x='1505' y='1755' width='340' height='340' stroke='blue' fill='none'/>" << std::endl
    << "<rect x='1855' y='1755' width='340' height='340' stroke='red' fill='none'/>" << std::endl
    << "<rect x='2205' y='1755' width='340' height='340' stroke='blue' fill='none'/>" << std::endl;

    this->ofs_ << "/*cases bonus*/" << std::endl
    << "<circle cx='975' cy='-525' r='50' fill='none' stroke='black'/>" << std::endl
    << "<circle cx='975' cy='-1225' r='50' fill='none' stroke='black'/>" << std::endl
    << "<circle cx='2025' cy='-525' r='50' fill='none' stroke='black'/>" << std::endl
    << "<circle cx='2025' cy='-1225' r='50' fill='none' stroke='black'/>" << std::endl
    << "<circle cx='1325' cy='-1925' r='50' fill='none' stroke='black'/>" << std::endl
    << "<circle cx='1675' cy='-1925' r='50' fill='none' stroke='black'/>" << std::endl

    << "<circle cx='975' cy='525' r='50' fill='none' stroke='black'/>" << std::endl
    << "<circle cx='975' cy='1225' r='50' fill='none' stroke='black'/>" << std::endl
    << "<circle cx='2025' cy='525' r='50' fill='none' stroke='black'/>" << std::endl
    << "<circle cx='2025' cy='1225' r='50' fill='none' stroke='black'/>" << std::endl
    << "<circle cx='1325' cy='1925' r='50' fill='none' stroke='black'/>" << std::endl
    << "<circle cx='1675' cy='1925' r='50' fill='none' stroke='black'/>" << std::endl

    << "/*fond de terrain noir*/" << std::endl
    << "<rect x='450' y='-2100' width='700' height='120' fill='black'/>" << std::endl
    << "<rect x='1850' y='-2100' width='700' height='120' fill='black'/>" << std::endl
    << "<rect x='450' y='-1980' width='22' height='130' fill='black'/>" << std::endl
    << "<rect x='1850' y='-1980' width='22' height='130' fill='black'/>" << std::endl
    << "<rect x='1128' y='-1980' width='22' height='130' fill='black'/>" << std::endl
    << "<rect x='2528' y='-1980' width='22' height='130' fill='black'/>" << std::endl

    << "<rect x='450' y='1980' width='700' height='120' fill='black'/>" << std::endl
    << "<rect x='1850' y='1980' width='700' height='120' fill='black'/>" << std::endl
    << "<rect x='450' y='1850' width='22' height='130' fill='black'/>" << std::endl
    << "<rect x='1850' y='1850' width='22' height='130' fill='black'/>" << std::endl
    << "<rect x='1128' y='1850' width='22' height='130' fill='black'/>" << std::endl
    << "<rect x='2528' y='1850' width='22' height='130' fill='black'/>" << std::endl

    << "/*pions jaunes*/" << std::endl
    << "<circle cx='200' cy='-1810' r='100' fill='yellow' stroke='black'/>" << std::endl
    << "<circle cx='200' cy='-1530' r='100' fill='yellow' stroke='black'/>" << std::endl
    << "<circle cx='200' cy='-1250' r='100' fill='yellow' stroke='black'/>" << std::endl
    << "<circle cx='200' cy='-970' r='100' fill='yellow' stroke='black'/>" << std::endl
    << "<circle cx='200' cy='-690' r='100' fill='yellow' stroke='black'/>" << std::endl
    << "<circle cx='2800' cy='-1810' r='100' fill='yellow' stroke='black'/>" << std::endl
    << "<circle cx='2800' cy='-1530' r='100' fill='yellow' stroke='black'/>" << std::endl
    << "<circle cx='2800' cy='-1250' r='100' fill='yellow' stroke='black'/>" << std::endl
    << "<circle cx='2800' cy='-970' r='100' fill='yellow' stroke='black'/>" << std::endl
    << "<circle cx='2800' cy='-690' r='100' fill='yellow' stroke='black'/>" << std::endl

    << "<circle cx='200' cy='1810' r='100' fill='yellow' stroke='black'/>" << std::endl
    << "<circle cx='200' cy='1530' r='100' fill='yellow' stroke='black'/>" << std::endl
    << "<circle cx='200' cy='1250' r='100' fill='yellow' stroke='black'/>" << std::endl
    << "<circle cx='200' cy='970' r='100' fill='yellow' stroke='black'/>" << std::endl
    << "<circle cx='200' cy='690' r='100' fill='yellow' stroke='black'/>" << std::endl
    << "<circle cx='2800' cy='1810' r='100' fill='yellow' stroke='black'/>" << std::endl
    << "<circle cx='2800' cy='1530' r='100' fill='yellow' stroke='black'/>" << std::endl
    << "<circle cx='2800' cy='1250' r='100' fill='yellow' stroke='black'/>" << std::endl
    << "<circle cx='2800' cy='970' r='100' fill='yellow' stroke='black'/>" << std::endl
    << "<circle cx='2800' cy='690' r='100' fill='yellow' stroke='black'/>" << std::endl;



    this->ofs_ << "</g>" << std::endl << "<g transform=\"translate(" << std::abs(xmin) << "," << std::abs(ymin) << ")\">" << std::endl;
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
