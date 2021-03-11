# SOI_2-process-rescheduling
**minix_usr/a.c**
- kod programu testującego będącego procesem z grupy A
- wymuszenie należenia do grupy A poprzez changegroup()
- długa pętla zawarta między time_t(&Begin) a time_t(&end)
- wywołania _syscall(0,GETGROUP,&msg) oraz _syscall(0,CHANGEGROUP,&msg)
- wykonywalny jako ./a


**minix_usr/b.c**
- kod programu testującego będącego procesem z grupy B
- wymuszenie należenia do grupy B poprzez changegroup()
- długa pętla zawarta między time_t(&Begin) a time_t(&end)
- wywołania _syscall(0,GETGROUP,&msg) oraz _syscall(0,CHANGEGROUP,&msg)
- wykonywalny jako ./b


**minix_usr/c.c**
- kod programu testującego będącego procesem z grupy B
- wymuszenie należenia do grupy B poprzez changegroup()
- nieskończona pętla
- wywołania _syscall(0,GETGROUP,&msg) oraz _syscall(0,CHANGEGROUP,&msg)
- wykonywalny jako ./c


**minix_usr/setscheduler.c**
- kod programu ustawiającego proporcje czasu procesora
- zwraca -1 gdy należy do gruby B
- wywołanie _syscall(0,SETSCHEDULER,&msg)
- przyjmuje jeden argument (int)


**minix_usr/include/minix/callnr.h**
- edytowane linie: 1, 68-70
- NCALLS ustawione na 81
- dodane wpisy syscalli SETSCHEDULER, CHANGEGROUP, GETGROUP


**minix_usr/src/fs/table.c**
- edytowane linie: 98-100
- dopisanie do tablicy wywołań modułu FS trzech wywołań pustych


**minix_usr/src/mm/table.c**
- edytowane linie: 96-98
- dopisanie do tablicy wywołań modułu MM wpisów odpowiadających stworzonym syscallom


**minix_usr/src/mm/main.c**
- edytowane linie: 22, 23, 72-99
- dodanie syscalli wywołujących odpowiednie taskcalle
- kontrola poprawności podanego argumentu w set_scheduler()


**minix_usr/src/mm/proto.h**
- edytowane linie: 41-43
- dodanie prototypów stworzonych syscalli


**minix_usr/include/minix/com.h**
- edytowane linie: 137-139
- dodane wpisy taskcalli SYS_SETSCHEDULER, SYS_CHANGEGROUP, SYS_GETGROUP


**minix_usr/src/kernel/system.c**
- edytowane linie: 149-151, 187-189, 244-248, 1239-1277
- dodane prototypy taskcalli i ich decydenta
- przydzielanie procesów do odpowiednich grup na podstawie parzystości ich PID w do_fork
- dodanie definicji stworzonych taskcalli


**minix_usr/src/kernel/clock.c**
- edytowane linie: 186-195
- sprawdzanie do której grupy należy następny w kolejce proces i odpowiednie ustawianie sched_ticks


**minix_usr/src/kernel/main.c**
- edytowane linie: 39
- inicjalizacja zmiennej percent przechowującej ustaloną proporcję czasu procesora


**minix_usr/src/kernel/proc.h**
- edytowane linie: 62, 66-69
- zadeklarowanie zmiennej group przechowywującej informacje o grupie do której należy proces
- dwa odpowiednie define’y dla grup A i B minix_usr/go.sh
- skrypt testujący działanie projektu w przypadku dwóch skończonych programów z różnych grup. Ma na celu pokazać że dwa wywołane programy z różnych grup rzeczywiście otrzymują różny przydział procesora. Nie pokazuje jednak czy proporcje są zgodne z podanym argumentem, gdyż po zakończeniu pierwszego programu – drugi już nie ma z kim „walczyć” o czas procesora.


**minix_usr/go2.sh**
- skrypt wywołujący program z grupy A na tle nieskończonego procesu z grupy B. Ma na celu pokazać czy rzeczywiście procesor jest rozdzielany zgodnie z podanym argumentem.

Czas wykonywania procesu dla argumentu dziewięciu podanych wartości argumentu przedstawia
wykres:  
![Obraz1](https://user-images.githubusercontent.com/48189079/110814566-d9bb6700-8289-11eb-908f-64cb51b63276.png)  
Oś pionowa to czas wykonywania się procesu A w sekundach a oś pozioma przydzielony grupie A procent czasu procesora. Z wykresu widać, że np. dla argumentu 60% proces wykonuje się około dwa razy dłużej niż dla 30% oraz fakt, że wywołując dwa skończone procesy z dwóch rożnych grup z argumentem 50% (./go.sh) potwierdza poprawność rozdystrybuowania czasu procesora pomiędzy grupy A i B (zauważmy że rozbieżność między przewidywanymi wynikami (linia szara) a rzeczywistością (pomarańczowa) jest niewielka i wynika najprawdopodobniej z rzadkich (ale mających miejsce) wyścigów między funkcjami do_clocktick oraz clock_handler w clock.c oraz czasem operacji samego shedulera)

Zrzut ekranu działania dla dwóch skończonych procesów z różnych grup z argumentem 50 i czasem wykonania zgodnym z wykresem (27 s):  
![Obraz2](https://user-images.githubusercontent.com/48189079/110814704-ff487080-8289-11eb-827d-54dd3289cf9e.png)  
