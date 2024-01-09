#pragma once
#include "Klient.h"
#include "ObslugaIO.h"

class KontrolerKlienta {
public:
	KontrolerKlienta(ObslugaIO& oio);
	~KontrolerKlienta();
	Klient* StworzNowegoKlienta(std::string iin, std::string nrr);
	Klient* SzukajKlientaPoKID(int KID);
private:
	std::vector<Klient*> stworzeniKlienci;
	int licznikKID;
	ObslugaIO& oio;
};
