# Refine - v3.0 - PT-BR
*Ler linhas específicas de documentos de texto.*
<br/>

O comando refine foi criado para ler linhas específicas de arquivos de texto. Este comando, geralmente faz o serviço que o *head* e o *tail* fazem. Porém, ele possui alguns parâmetros extras que não estão presentes em outros comandos de forma natural.

O interesse desse projeto é criar um comando que facilite a busca por linhas específicas em arquivos, sem precisar recorrer a *pipes* ou códigos enormes para obter a saída desejada.
<br/><br/>

Por exemplo, eu quero a saída limpa da linha 10:
```sh
$ cat -n file.txt | grep -w "10" | cut -d$'\t' -f2-
```
<br/>

Se houver um modo mais eficiente, ele não será diferente disso. Outro Exemplo, é exibir as linhas de 10 a 20:
```sh
$ head -20 file.txt | tail -11
```
<br/>

Até que é curto, mas se o arquivo tem 15 linhas ao invés de 20, essa combinação não fará esse controle e exibirá 11 linhas e não 6, que seria de 10 a 15.
<br/><br/>

### Parametros:
<br/>

O *refine* possui a seguinte Sintaxe:
```
$ refn [options] file.txt
```
<br/>

O refine possui uma série de parâmetros. Veja a seguir:
```sh
    -f: Para ler as primeiras linhas de arquivos de texto.
    -l: Para ler as últimas linhas de arquivos de texto.
  	-d: Para ler um número específico de linhas de arquivos de texto.
    -i: Para ler um número específico de linhas de arquivos de texto de forma invertida.
    -c: Habilitar cor para os parâmetros f, l, d e i.
    -s: Visualização simples para os parâmetros f, l, d e i.
    -h: Para visualizar as informações de ajuda.
```
<br/>

### Comparação e Uso:
<br>

O uso do *refine* é bem simples. Vamos começar com os comandos básicos. Como foi dito, esse comando possui as funções do *head* e do *tail*, só que com algumas melhorias, como pode ser visto a seguir:
```sh
$ head -5 LICENSE 
                    GNU GENERAL PUBLIC LICENSE
                       Version 3, 29 June 2007

 Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
 Everyone is permitted to copy and distribute verbatim copies
```
```sh
$ refn -f 5 LICENSE 

/home/mauricio/GIT/refine/LICENSE:
         1:                     GNU GENERAL PUBLIC LICENSE
         2:                        Version 3, 29 June 2007
         3: 
         4:  Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
         5:  Everyone is permitted to copy and distribute verbatim copies
```
```sh
$ refn -f 5 -s LICENSE 
                    GNU GENERAL PUBLIC LICENSE
                       Version 3, 29 June 2007

 Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
 Everyone is permitted to copy and distribute verbatim copies
```
<br/>

Agora, comparando com o *tail*. Como vocês podem ver, a última linha não entra na equação se for vazia, assim como no *tail*:
```sh
$ tail -5 LICENSE 
into proprietary programs.  If your program is a subroutine library, you
may consider it more useful to permit linking proprietary applications with
the library.  If this is what you want to do, use the GNU Lesser General
Public License instead of this License.  But first, please read
<https://www.gnu.org/licenses/why-not-lgpl.html>.
```
```sh
$ refn -l 5 LICENSE 

/home/mauricio/GIT/refine/LICENSE:
       670: into proprietary programs.  If your program is a subroutine library, you
       671: may consider it more useful to permit linking proprietary applications with
       672: the library.  If this is what you want to do, use the GNU Lesser General
       673: Public License instead of this License.  But first, please read
       674: <https://www.gnu.org/licenses/why-not-lgpl.html>.
```
```sh
$ refn -l 5 -s LICENSE 
into proprietary programs.  If your program is a subroutine library, you
may consider it more useful to permit linking proprietary applications with
the library.  If this is what you want to do, use the GNU Lesser General
Public License instead of this License.  But first, please read
<https://www.gnu.org/licenses/why-not-lgpl.html>.
```
<br/>

Agora chegou a parte que faz sentido a existência do comando. Vamos comparar a saída de números específicos de linhas que, no exemplo, será listada as linhas de 26 a 30, como pode ser visto a seguir:
```sh
$ head -30 LICENSE | tail -5
want it, that you can change the software or use pieces of it in new
free programs, and that you know you can do these things.

  To protect your rights, we need to prevent others from denying you
these rights or asking you to surrender the rights.  Therefore, you have
```
```sh
$ refn -d 26-30 LICENSE 

/home/mauricio/GIT/refine/LICENSE:
        26: want it, that you can change the software or use pieces of it in new
        27: free programs, and that you know you can do these things.
        28: 
        29:   To protect your rights, we need to prevent others from denying you
        30: these rights or asking you to surrender the rights.  Therefore, you have
```
```sh
$ refn -d 26-30 -s LICENSE 
want it, that you can change the software or use pieces of it in new
free programs, and that you know you can do these things.

  To protect your rights, we need to prevent others from denying you
these rights or asking you to surrender the rights.  Therefore, you have
```
<br/>

Agora, para fechar com chave de ouro, vamos analizar aquele código usado para fazer a leitura de apenas uma linha específica, como no exemplo a seguir:
```sh
$ cat -n LICENSE | grep -w "  10"
    10    The GNU General Public License is a free, copyleft license for
   446    10. Automatic Licensing of Downstream Recipients.
```
```sh
$ cat -n LICENSE | grep -w "  10" | cut -d$'\t' -f2-
  The GNU General Public License is a free, copyleft license for
  10. Automatic Licensing of Downstream Recipients.
```
```sh
$ refn -d 10 LICENSE 

/home/mauricio/GIT/refine/LICENSE:
        10:   The GNU General Public License is a free, copyleft license for
```
```sh
$ refn -d 10 -s LICENSE 
  The GNU General Public License is a free, copyleft license for
```
<br/>

Você quer a décima última linha? Aqui está:
```sh
$ refn -i 10 /etc/slackpkg/mirrors 

/etc/slackpkg/mirrors:
       353: # https://mirror.slackbuilds.org/slackware/slackware64-current/
```
```sh
$ refn -i 10 -s /etc/slackpkg/mirrors 
# https://mirror.slackbuilds.org/slackware/slackware64-current/
```
<br/>

O resultado dispensa comentários. Então para concluir, aqui está uma alternativa de comando para facilitar na busca por linhas específicas em arquivos.

        --> Nota: Os comandos '-f', '-l', '-d' and '-i' foram pensados para serem usados separadamente.
