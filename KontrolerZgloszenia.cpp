#include "KontrolerZgloszenia.h"

constexpr NAZWA_TABEL typTabeli = NAZWA_TABEL::ZGLOSZENIA;

KontrolerZgloszenia::KontrolerZgloszenia(ObslugaIO& oio) : oio(oio)
{
	licznikZID = oio.znajdzNajwyzszeID(typTabeli)+1;
	stworzoneZgloszenia = std::vector<Zgloszenie*>(0);
}

KontrolerZgloszenia::~KontrolerZgloszenia()
{
	for (unsigned i = 0; i < stworzoneZgloszenia.size(); i++) {
		delete stworzoneZgloszenia[i];
	}
}

Zgloszenie* KontrolerZgloszenia::StworzNoweZgloszenie(int KID, FORMA_SERWISU fs)
{
	Zgloszenie* noweZgloszenie = new Zgloszenie(licznikZID, KID, fs);
	stworzoneZgloszenia.push_back(noweZgloszenie);
	std::string nowyRekord = noweZgloszenie->zapisz(noweZgloszenie);
	oio.dodajNowyRekord(typTabeli, nowyRekord, licznikZID);
	licznikZID++;
	return noweZgloszenie;
}

Zgloszenie* KontrolerZgloszenia::SzukajZgloszeniaPoZID(int ZID)
{
	std::string znalezionyRekord = oio.szukajRekordu(typTabeli, ZID);
	if (znalezionyRekord == "") return nullptr;
	Zgloszenie* noweZgloszenie = new Zgloszenie();
	noweZgloszenie->odczytaj<Zgloszenie>(znalezionyRekord);
	stworzoneZgloszenia.push_back(noweZgloszenie);
	return noweZgloszenie;
}

Zgloszenie* KontrolerZgloszenia::SzukajZgloszeniaPoKID(int KID)
{
	std::string znalezionyRekord = oio.szukajRekorduPoPolu(typTabeli, 1, std::to_string(KID));
	if (znalezionyRekord == "") return nullptr;
	Zgloszenie* noweZgloszenie = new Zgloszenie();
	noweZgloszenie->odczytaj<Zgloszenie>(znalezionyRekord);
	stworzoneZgloszenia.push_back(noweZgloszenie);
	return noweZgloszenie;
}

void KontrolerZgloszenia::DodajDaneSerwisowe(Zgloszenie*& zgloszenie,std::vector<std::string> listaNaprawionychUsterek, bool zdolnyDoJazdy)
{
	zgloszenie->DodajDaneSerwisowe(listaNaprawionychUsterek, zdolnyDoJazdy);
	std::string zedytRekord = zgloszenie->zapisz(zgloszenie);
	oio.edytujRekord(typTabeli, zedytRekord, zgloszenie->ZwrocIDZgloszenia()); //zwracaj zgl* przez ref
}

void KontrolerZgloszenia::DopiszUstalonyKosztNaprawy(Zgloszenie*& zgloszenie, int kosztObslugi)
{
	zgloszenie->DopiszUstalonyKosztNaprawy(kosztObslugi);
	std::string zedytRekord = zgloszenie->zapisz(zgloszenie);
	oio.edytujRekord(typTabeli, zedytRekord, zgloszenie->ZwrocIDZgloszenia());
}

void KontrolerZgloszenia::UstalTerminSpotkania(Zgloszenie*& zgloszenie, std::string dataSpotkania)
{
	zgloszenie->UstalTerminSpotkania(dataSpotkania);
	std::string zedytRekord = zgloszenie->zapisz(zgloszenie);
	oio.edytujRekord(typTabeli, zedytRekord, zgloszenie->ZwrocIDZgloszenia());
}

void KontrolerZgloszenia::UsunZgloszenie(Zgloszenie*& zgloszenie)
{
	oio.usunRekord(typTabeli, zgloszenie->ZwrocIDZgloszenia());
	zgloszenie = nullptr;
}
