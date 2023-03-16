# KreatorWzorow
Ta aplikacja służy do tworzenia abstrakcyjnych wzorów. 
Wzory te można później wykorzystać do tworzenia sztuki opartej na pixel-art, na przykład
  - haft krzyżykowy
  - prace szydełkowe C2C
  - zaprasowywane koraliki
 i inne dziedziny.
 
 Koncept:
 
![SmartSelect_20230316_132328_Samsung Notes](https://user-images.githubusercontent.com/35116333/225616211-5ab667f5-1802-405b-9237-197d3b9afe12.jpg)

#### Wątki użyte w programie:
**wątek koloru** - reprezentuje kolor rozlewający się po płótnie
                 - tworzony jako odpowiedź na kliknięcie myszki
                 - może być ich tyle, ile zechce użytkownik
              
#### Sekcje krytyczne:
**płótno**  - przydzielane wątkowi na czas zamalowania jednego piksela
            - dostęp do sekcji za pomocą semafora binarnego czyli muteksu
