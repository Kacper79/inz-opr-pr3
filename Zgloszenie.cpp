#include "Zgloszenie.h"

Zgloszenie::Zgloszenie() : Serializowalne(){}
Zgloszenie::Zgloszenie(int ZID,int KID, FORMA_SERWISU fs) : ZID(ZID), KID(KID), formaSerwisu(fs), przeszedlPrzeglad(false), kosztUslugi(0), dataSpotkania("1970-1-1"), usterki(std::vector<std::string>(0)), Serializowalne() {}
Zgloszenie::Zgloszenie(Zgloszenie&& inny): ZID(inny.ZID), KID(inny.KID), formaSerwisu(inny.formaSerwisu), usterki(inny.usterki), przeszedlPrzeglad(inny.przeszedlPrzeglad), kosztUslugi(inny.kosztUslugi), dataSpotkania(inny.dataSpotkania) {}

void Zgloszenie::DodajDaneSerwisowe(std::vector<std::string> listaNaprawionychUsterek, bool zdolnyDoJazdy)
{
	this->usterki = listaNaprawionychUsterek;
	this->przeszedlPrzeglad = zdolnyDoJazdy;
}

void Zgloszenie::DopiszUstalonyKosztNaprawy(int kosztObslugi)
{
	this->kosztUslugi = kosztObslugi;
}

void Zgloszenie::UstalTerminSpotkania(std::string dataSpotkania)
{
	this->dataSpotkania = dataSpotkania;
}

int Zgloszenie::ZwrocIDZgloszenia()
{
	return ZID;
}

FORMA_SERWISU Zgloszenie::ZwrocFormeZgloszenia()
{
	return formaSerwisu;
}

std::vector<std::string> Zgloszenie::ZwrocListeUsterek()
{
	return usterki;
}
