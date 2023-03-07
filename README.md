Instruções

1 - Você precisa ter em sua máquina o conjunto de ferramentas GNU, o MinGW.
Você pode obter a versão mais estável no link: https://github.com/niXman/mingw-builds-binaries/releases
Recomendo baixar a versão: 12.2.0-rt_v10-rev2/x86_64-12.2.0-release-win32-seh-ucrt-rt_v10-rev2.7z

2 - Extraia a pasta do MinGW no diretório raiz do Windows, no meu caso é o C:\

3 - Copie a pasta sqlite-libs no diretório raiz do Windows, no meu caso é o C:\

4 - Configure as variáveis de ambiente para o MinGW e o SQLite.
Adicione na PATH os caminhos:
- C:\mingw64\bin
- C:\sqlite-libs

5 - Instale o Visual Stdio Code para compilar e executar o código dentro da IDE.
Você pode obter a versão mais estável no link: https://visualstudio.microsoft.com/pt-br/downloads/

6 - Ao abrir o código main.c pelo Visual Studio Code ele irá te sugerir uma extensão para programas feitos em C, você precisará instalar ela.

7 - Na linha 2 do código especifique o caminho da biblioteca do SQLite.
    Na linha 45 especifique o caminho do banco de dados.

8 - Caso faça uma alteração no código você pode recompilar pelo comando no terminal do VS Code:
gcc main.c sqlite3.o -Ic:\sqlite -o main.exe

9 - Para rodar o programa use o comando no terminal do VS Code:
.\main.exe
