# Refine - v1.0 - PT-BR
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
$ refine [options] file.txt
```
<br/>

O refine possui uma série de parâmetros. Veja a seguir:
```sh
  -f: Para ler as primeiras linhas de arquivos de texto.
  -f0: O mesmo efeito, só que de forma limpa.
  -l: Para ler as últimas linhas de arquivos de texto.
  -l0: O mesmo efeito, só que de forma limpa.
  -a: Para ler uma linha de um arquivo de texto.
  -a0: O mesmo efeito, só que de forma limpa.
  -d: Para ler um número específico de linhas de arquivos de texto. Esse delimita o início da listagem.
  -d0: O mesmo efeito, só que de forma limpa.
  -s: Seleciona o limite de linhas específicas. Deve ser usado após -d ou -d0.
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
$ refine -f 5 LICENSE 

LICENSE:
        1:                     GNU GENERAL PUBLIC LICENSE
        2:                        Version 3, 29 June 2007
        3: 
        4:  Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
        5:  Everyone is permitted to copy and distribute verbatim copies
```
```sh
$ refine -f0 5 LICENSE 

                    GNU GENERAL PUBLIC LICENSE
                       Version 3, 29 June 2007

 Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
 Everyone is permitted to copy and distribute verbatim copies
```
<br/>

Agora, comparando com o *tail*. Como vocês podem ver a linha vazia também entra na equação. a linha está vazia, mas ela existe, portanto deve ser contada. Porém, ela será visível apenas em -l e como uma linha extra:
```sh
$ tail -5 LICENSE 
into proprietary programs.  If your program is a subroutine library, you
may consider it more useful to permit linking proprietary applications with
the library.  If this is what you want to do, use the GNU Lesser General
Public License instead of this License.  But first, please read
<https://www.gnu.org/licenses/why-not-lgpl.html>.
```
```sh
$ refine -l 5 LICENSE 

LICENSE:
        670: into proprietary programs.  If your program is a subroutine library, you
        671: may consider it more useful to permit linking proprietary applications with
        672: the library.  If this is what you want to do, use the GNU Lesser General
        673: Public License instead of this License.  But first, please read
        674: <https://www.gnu.org/licenses/why-not-lgpl.html>.
        675: 
```
```sh
$ refine -l0 5 LICENSE 

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
$ refine -d 26 -s 30 LICENSE 

LICENSE:
        26: want it, that you can change the software or use pieces of it in new
        27: free programs, and that you know you can do these things.
        28: 
        29:   To protect your rights, we need to prevent others from denying you
        30: these rights or asking you to surrender the rights.  Therefore, you have
```
```sh
$ refine -d0 26 -s 30 LICENSE 

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
$ refine -a 10 LICENSE 

LICENSE:
          The GNU General Public License is a free, copyleft license for
```
```sh
$ refine -a0 10 LICENSE 
  The GNU General Public License is a free, copyleft license for
```
<br/>

O resultado dispensa comentários. Então para concluir, aqui está uma alternativa de comando para facilitar na busca por linhas específicas em arquivos.

        --> Nota: Os comandos foram pensados para serem usados separadamente, então nada de "-fl".
