#include <stdio.h>
#define NULL 0

enum Result {OK, ERROR};

enum Result eHexStringToUInt(char pcStr[],unsigned int *puiValue){

    int ucCharCounter;
    unsigned int uiValue = 0;

    //na poczatku sprawdze czy zaczyna sie od 0X czy 0x
    if(pcStr[0] != '0' || (pcStr[1] != 'x' && pcStr[1] != 'X')){
        return ERROR;
    }
    //iterujemy po znakach lancucha zostawiamy jeden bajt na znak konca lancucha
    for(ucCharCounter = 2; pcStr[ucCharCounter] != NULL; ucCharCounter++){

        unsigned char ucHexChar = pcStr[ucCharCounter];
        uiValue = uiValue << 4; //przesuwamy wartosc o 4 bity w lewo, aby zrobic miejsce na kolejny znak heksadecymalny

        if (ucCharCounter > 5) {
            return ERROR;
        }
        else {
            if (ucHexChar >= '0' && ucHexChar <= '9') {
                uiValue = uiValue + (ucHexChar -'0'); //dodajemy wartosc znaku heksadecymalnego do wartosci calkowitej, ustwianie odpowiednich bitów w nazwie zmiennej
            } else if (ucHexChar >= 'A' && ucHexChar <= 'F') {
                uiValue |= ucHexChar - 'A' + 10;
            } else {
                return ERROR;
            }
        }
    }
    *puiValue = uiValue; //zapisujemy wartosc wskaznika do zmiennej przechowujacej wartosc calkowita
    return OK;
}

void UIntToHexStr(unsigned int uiValue, char pcStr[]) {

    unsigned char ucCharCounter;
    unsigned char uiTetrade; //zmienna pomocnicza

    pcStr[0] = '0';
    pcStr[1] = 'x'; //ustawienie drugiego elementu w tablicy na wartosc x
    pcStr[6] = NULL;

    for (ucCharCounter = NULL; ucCharCounter < 4; ucCharCounter++) {
        uiTetrade = (uiValue >> (ucCharCounter * 4) & 0xF);  //Przypisanie zmiennej uiTetrade wartosci zapisanej w uiValue,
        // przesuniecie bitowe w prawo bo przesuniecie
        //zeby zlapac te ostenie 4 miejsca i wsadzic selected nible


        if (uiTetrade < 10) {
            pcStr[5 - ucCharCounter] = '0' + uiTetrade;
            //przypisuje znak reprezentujacy tetradowa cyfre liczby value do odpowiedniego elementu tablicy w notacji 16sykowej 
            //Jesli wartosc zmiennej uiTetrade jest mniejsza niz 10, to przypisz do odpowiedniego elementu tablicy pcStr
            // odpowiadajacego danej tetradzie cyfre '0' powiekszona o wartosc zmiennej uiTetrade.
        } else {
            pcStr[5 - ucCharCounter] = 'A' + (uiTetrade - 10);
            // w ascci 16-stkowo to jest odstep 10 miedzy 1 a 'A' zeby
            //W przeciwnym wypadku przypisz do odpowiedniego elementu tablicy pcStr odpowiadajacego danej tetradzie litere 'A' powiekszona o róznice
            // wartosci zmiennej uiTetrade i 10.
        }
    }
}




void AppendUIntToString (unsigned int uiValue,char pcDestinationStr[]) {
   
 unsigned char ucCharCounter ;

    for(ucCharCounter = NULL ; pcDestinationStr[ucCharCounter] != NULL ; ucCharCounter++){}
    UIntToHexStr(uiValue, pcDestinationStr + ucCharCounter);
}


int main() {

	unsigned int uiValue;
	char pcStr[7];
	char pcDestinationStr[9] = "str";
   // enum Result result;
    //result = eHexStringToUInt("0x3F5A", &uiValue);
	
		//UIntToHexStr(uiValue = 0xFDE8, pcStr);
	
	  AppendUIntToString(0xF, pcDestinationStr);
    
}