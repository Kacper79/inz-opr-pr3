#include "KontrolerKlienta.h"

constexpr NAZWA_TABEL typTabeli = NAZWA_TABEL::KLIENCI;

KontrolerKlienta::KontrolerKlienta(ObslugaIO& oio) : oio(oio)
{
	licznikKID = oio.znajdzNajwyzszeID(typTabeli)+1;
	stworzeniKlienci = std::vector<Klient*>(0);
}

KontrolerKlienta::~KontrolerKlienta()
{
	for (unsigned i = 0; i < stworzeniKlienci.size(); i++) {
		delete stworzeniKlienci[i];
	}
}

Klient* KontrolerKlienta::StworzNowegoKlienta(std::string iin, std::string nrr)
{
	//sprawdz czy istnieje obecnie
	std::string rekordIstniej = oio.szukajRekorduPoPolu(typTabeli, 2, nrr);
	if (rekordIstniej != "" && oio.zwrocNtePoleRekordu(rekordIstniej, 1) == iin) {
		Klient* nowyKlient = new Klient();
		nowyKlient->odczytaj<Klient>(rekordIstniej);
		stworzeniKlienci.push_back(nowyKlient);
		return nowyKlient;
	}
	else {
		Klient* nowyKlient = new Klient(licznikKID, iin, nrr);
		stworzeniKlienci.push_back(nowyKlient);
		std::string nowyRekord = nowyKlient->zapisz(nowyKlient);
		oio.dodajNowyRekord(typTabeli, nowyRekord, licznikKID);
		licznikKID++;
		return nowyKlient;
	}
}

Klient* KontrolerKlienta::SzukajKlientaPoKID(int KID)
{
	std::string znalezionyRekord = oio.szukajRekordu(typTabeli, KID);
	if (znalezionyRekord == "") return nullptr;
	Klient* nowyKlient = new Klient();
	nowyKlient->odczytaj<Klient>(znalezionyRekord);
	stworzeniKlienci.push_back(nowyKlient);
	return nowyKlient;
}