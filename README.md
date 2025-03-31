Внедрение DLL — это метод, при котором код запускается в пространстве другого процесса, заставляя его загрузить динамическую библиотеку

Почему DLL Injection так распространено?

Это распространено, потому что самый простой способ изменить программу
Кроме того, когда вы внедряете DLL, ее код выполняется внутри целевого процесса, что намного быстрее, чем выполнение той же задачи из внешней программы!
По тем же причинам внедрение DLL так популярно для взлома игр - вместо того, чтобы изменять программу извне, вы можете заставить свой код выполняться внутри легитимного процесса

Зачем нужен Инжектор?
Если вы делаете внутренний взлом, вам необходимо использовать DLL-инжектор для его внедрения, с помощью инжектора и подгружается dll(ка)

![fi1](https://github.com/user-attachments/assets/189464dc-15c0-4cde-933d-7f3c602904a7)



  Пример моего успешного внедрения dll в легитимный процесс:



![success_example](https://github.com/user-attachments/assets/3a5588b0-0600-47de-b536-3a8773506ec1)


Создадим собственный dll injector + .dll на LINUX 👇

Ступень 1:
Скачиваем dll-injector.cpp + dll.cpp и выполняем команды:

x86_64-w64-mingw32-gcc -o injector.exe dll-injector.cpp -static

x86_64-w64-mingw32-gcc -shared -o hack.dll dll.cpp -static

Ступень 2:

┌──(exmanq㉿DESKTOP-BPGC5S5)-[~/hack_dll]
└─$ ls -l
total 340
-rw-r--r-- 1 exmanq exmanq    248 Mar 31 19:19 dll.cpp
-rw-r--r-- 1 exmanq exmanq   1125 Mar 31 19:19 dll-injector.cpp
-rwxr-xr-x 1 exmanq exmanq  87117 Mar 31 20:03 hack.dll
-rwxr-xr-x 1 exmanq exmanq 247262 Mar 31 19:36 injector.exe

Теперь мы имеем 2 новых файла - hack.dll и injector.exe

Ступень 3:

Заходим на Windows, на которой будем делать inject, в моем случае это было VMware, используйте в любом случаем VMware либо другую виртуальную машину для проведения тестов и изучений!

Ступень 4:
Запускаем на ней Process Hacker(Отследить потом наш dll)

Создаем notepad на рабочем столе - открываем

Открываем cmd от имени Администратора

в cmd прописываем: tasklist | findstr "notepad.exe"
Находим PID нашего notepad.exe и запоминаем!

Ступень 5:
Заключительная ступень - иньекция нашей .dll
Переходим с помощью cd "Папка где хранится injector.exe"

прописываем - injector.exe PID(нашего процесса в который будем внедрять DLL) "Путь до dll которая будет внедряться, УКАЗЫВАЕМ ПОЛНЫЙ ПУТЬ"
Заходим в Process Hacker - находим наш PID - ПКМ - Свойства - Модули - И в модулях видим наш hack.dll !
