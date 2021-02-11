# Refine - v1.0
*Reads specific lines of text documents.*
<br/>

The *refine* command was created to read specific lines of text files. This command, usually does the service that *head* and *tail* do. However, it has some extra parameters that are not present in other commands in a natural way.

The interest of this project is to create a command that facilitates the search for specific lines in files, without having to resort to *pipes* or huge codes to obtain the desired output.
<br/><br/>

For example, I want the clean output of line 10:
```sh
$ cat -n file.txt | grep -w "10" | cut -d$'\t' -f2-
```
<br/>

If there is a more efficient way, it will not be different from that. Another example is to display lines 10 to 20:
```sh
$ head -20 file.txt | tail -11
```
<br/>

It is short, but if the file has 15 lines instead of 20, this combination will not do this control and will display 11 lines and not 6, which would be 10 to 15.
<br/><br/>

### Parameters:
<br/>

The *refine* it has the following syntax:
```
$ refine [options] file.txt
```
<br/>

The *refine* it has a series of parameters. See the follow:
```sh
  -f:  To read the first lines of the files.
  -f0: The same effect, but cleanly.
  -l:  To read the last lines of the files.
  -l0: The same effect, but cleanly.
  -a:  To read a line from a text file.
  -a0: The same effect, but cleanly.
  -d:  To read the specific lines of the files. This one delimits the start of the reading.
  -d0: The same effect, but cleanly.
  -s:  Select the limit of specific lines. Must be used after -d or -d0.
  -h:  To view help information.
```
<br/>

### Comparation and Use:
<br>

The use of *refine* is very simple. Let's start with the basic commands. How was said, this command has the functions of *head* and *tail*, but with some improvements, as can be seen folow:
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

Now, compared to the *tail*. As you can see the empty line also comes into the equation. The line is empty, but it exists, so it must be counted. However, it will be visible only in -l and as an extra line:
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

Now comes the part that makes sense of the command existance. Let's compare the output of specific numbers of lines, which, in the example, will be listed lines in 26 to 30, as can be seen folow:
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

Now, to close with golden key, let's analyze the code used to read only a specific line, as in the following example:
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

The result dispenses with comments. So, to conclude, here is a command alternative to facilitate the search for specific lines in files.

        --> NOTE: The commands were thought to be used separately, so nothing of "-fl".
<br/>

### GNU General Public License:

This repository has scripts that were created to be free software.<br/>
Therefore, they can be distributed and / or modified within the terms of the *GNU General Public License*.

>[General Public License](https://pt.wikipedia.org/wiki/GNU_General_Public_License)
>
>Free Software Foundation (FSF) Inc. 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
<br/><br/>

### Comments:

In case of bugs, execution problems or packages construction, constructive criticism, among others, please submit a message to one of the contacts below.
<br/><br/>

### Contact:

Autor: Mauricio Ferrari

E-Mail: *m10ferrari1200@gmail.com*

Telegram: *@maurixnovatrento*
