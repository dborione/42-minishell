[Signaux]
- signaux ne marchent pas après avoir stoppé une boucle infinie avec Ctl C

[Heredoc]
- double heredoc (avec pipe; ex `cat <<EOF | cat<<EOF`) ne marche pas, ou `ls << EOF | wc -l <<eof` donne des resultats differents

[Gestion Commandes]
- Ne pas oublier que :
	~$ test
	test2
n'est pas une commande (sauf si on utilise "") mais 2 commandes,
il faudra le prendre en charge dans le parsing

- Créer des "commandes vides" exemple : < infile | cat -e

[Prompt]

[Autres]
- '>>': redirections en append mode
- bien vérifier que les variables importantes du shell_data sont intactes à chaque attente du prompt
- le include_var ne marche pas quand un pipe colle la $VAR

[Exit]

[CD]
- `cd mpanic test`: bash cd dans mpanic, nous too many args
- cd avec unset variables

[Export]
- erreur message supprime les ' ' par ex `export '    456asd=value '`
- export test+=value non pris en charge 

[Unset] 

[Echo]
- Prise en charge `echo ~` quand $HOME est unset
- `echo ~$USER/sdfsfsfdsfs` : chez nous donne `/Users/dborione`
- --> remplacer ~/ par le path dans cat, par ex chez nous pour `cat ~/echo` l'erreur bash `cat: /Users/dborione/echo: No such file or directory$` sort `cat: ~/echo: No such file or directory$`
- `echo "'$USER'"` devrait afficher la valeur de $USER, là il affiche `'`

[Cat]

[Pipes]
- cas du genre `ls |`




---- Mpanic tests checks ----

Quand les tests sont marqués KO dans mpanic mais ne sont pas notés ici c'est qu'ils sont bons et qu'il y a juste un erreur à cause du prompt ou d'un abort dans le tester

[Mpanic echo]
- test 16: remplacement du ~ par le path dans le msg d'erreur -> a cause de cat
- ~~test 18: unset PATH -> provoque un bug~~

[Mpanic export]
- test 10: export EMPTY EMPTY_TOO= NOT_EMPTY=contnent ne march epas chez nous
- test 12: `export TEST=value` puis `export TEST+=" added value"` --> non pris en charge chez nous

[Mpanic env]
- tous les tests sont bons, juste le probleme d'abort dans mpanic

[Mpanic directory]
- test 3: `pwd -> cd "" -> pwd`: nous 'no such file'
- test 5: cd "" "" pareil que 6
- test 6: `cd / non_existent` : bash no output exit 0, nous: bash: cd: too many arguments.$
- test 15 : `cd file/non_existent`: nous 'not such file or dir', bash 'not a dir'

[Mpanic parser]

[Mpanic pipe]

[Mpanic redirection]

[Mpanic status]

[Mpanic shlvl]

[Mpanic panicm]
- test 1: cannot access parent directories: No such file or directory
- test 3: `echo all &> testfile < non_exist_file --> rm testfile`: nous no such file, bash pas d'erreur
- ~~test 7: `ecoh ~` pas pris en charge~~
- test 8: unset PWD no working
- test 10: `echo hi <> file --> ls --> rm file`
- test 11: no passed