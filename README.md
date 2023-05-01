Instruções

0 - Você precisa ter em sua máquina o conjunto de ferramentas GNU, o MinGW.
- Você pode obter a versão mais estável no link: https://winlibs.com/
- Recomendo baixar a versão UCRT Runtime estável sem o LLVM/Clang/LLD/LLDB porque você não irá utilizar essas ferramentas.

1 - Extraia a pasta do MinGW no diretório raiz do Windows, no meu caso é o C:\

2- Copie a pasta sqlite-libs no diretório raiz do Windows, no meu caso é o C:\

3- Configure as variáveis de ambiente para o MinGW e o SQLite.
Adicione na PATH os caminhos:
- C:\mingw64\bin
- C:\sqlite-libs

4- Instale o Visual Studio Code para compilar e executar o código dentro da IDE.
- Você pode obter a versão mais estável no link: https://code.visualstudio.com/download/

5- Ao abrir o código main.c pelo VS Code ele irá te sugerir uma extensão para programas feitos em C, é recomendável que você instale ela.

6-
- Na linha 2 do código main.c especifique o caminho da biblioteca do SQLite.
- Na linha 45 do código main.c especifique o caminho do banco de dados.

7 - Caso faça uma alteração no código, será necessário recompilar, você pode fazer isso pelo comando no terminal do VS Code (É necessário estar no diretório \code):
- gcc main.c sqlite3.o -Ic:\sqlite-libs -o main.exe

8- Para rodar o programa use o comando no terminal do VS Code (É necessário estar no diretório \code):
- .\main.exe
