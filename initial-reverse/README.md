# A simple reverse program written in c

Link to the assingment: https://github.com/remzi-arpacidusseau/ostep-projects/tree/master/initial-reverse

Rest will be in finnish as well as the comment on the code.

## Dokumentaatio

Ohjelmisto on käännetty gcc:llä onnistuneesti seuraavilla lipuilla ilman virheviestejä, ubuntulla: -Wall -g -O

Ohjelma itsensä on jaettu kolmeen funktioon riippuen, kuinka monta argumenttia käyttäjä antaa. Ensimmäiset virhe tarkistukset ovat varmentaakseen, ettei käyttäjä ole syöttänyt liian monia argumentteja. Sen jälkeen varmistettaan, ettei input ja output tiedostot ole samoja.

Sitten riippuen monta argumenttia käyttäjä antaa siirrytään oikeaan funktioon. Ilman argumentteja kysytään käyttäjältä syötettä, joka sitten pilkotaan väleistä ja tallennetaan linkitettyyn listaan, jotta se voidaan tulostaa käänteisessä järjestyksessä käyttäjälle. Linkitettyä listaa myös hyödynnetään muissa funktiossa. Mahdollinen ongelma voi esiintyä, jos ohjelmalle tarjotaan todella isoa tiedostoa sillä se siirtää koko tiedoston ensin linkitettyyn listaan.

### Oletukset ja virheet

Ohjelmisto osaa tunnistaa, jos skannattava ja tulostettava tiedosto ovat sama ja reagoi tulostamalla fprintf käyttäen stderr:iin ” Input and output file must differ” ja poistumalla exit(1).
Käyttämällä getline() komentoa ohjelmiston ei tarvitse olettaa rivin pituutta, koska getline palauttaa sen pituuden. Samalla perjaatteella ohjelmistoon ei ole kovakoodattu limittejä liittyen tiedoston pituuteen vaan se dynaamisesti linkitettyjen listoen ja mallocin avulla kasvaa tilanteen mukaan.

Ohjelmisto kuitenkin tämän suunnittelun takia voi olla tuhlaavainen muistin kanssa kun käyttäjä ei syötä argumentteja, sillä se varaa jokaiselle sanalle koko rivin verran tilaa.
Ohjelma myös kertoo, jos malloc epäonnistuu reagoi tulostamalla fprintf käyttäen stderr:iin ” malloc failed” ja poistumalla exit(1). Samoin, jos tiedostoa ei saada avattua.
