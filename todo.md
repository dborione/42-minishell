[Signaux]
- ~~double prompte pour heredoc ctl-c~~
- ~~signaux apres cmd bloquante comme cat sans arguments print le prompt deux fois~~
- ~~quand on est dans un subshell les signaux sont pris en compte deux fois~~
- CTl D ne marche pas quand après avoir stoppé une boucle infinie avec Ctl C
- Ctl C ne marche pas pour stopper boucle infinie

[Heredoc]
- double heredoc (avec pipe; ex `cat <<EOF | cat<<EOF`) ne marche pas, ou `ls << EOF | wc -l <<eof` donne des resultats differents
- `ls >>eof` + ctl c; chez nous exit code 1, bash: 1

[Gestion Commandes]
- Ne pas oublier que :
	~$ test
	test2
n'est pas une commande (sauf si on utilise "") mais 2 commandes,
il faudra le prendre en charge dans le parsing

~~- Prendre en charge les "|" (guillemets + pipe ensemble)~~

- Créer des "commandes vides" exemple : < infile | cat -e

[Prompt]
- erreur de free

[Autres]
- ~~variables env~~
- ~~checker si on a les bons exit codes par rapport a bash ($?)~~
- '>>': redirections en append mode
- ~~exit code si cat sans input + ctl C~~
- ~~exit avec arguments~~
- erreur "is a directory" quand on entre un dossier en commande
- bien vérifier que les variables importantes du shell_data sont intactes à chaque attente du prompt
- le include_var ne marche pas quand un pipe colle la $VAR

[Exit]
- ~~Changer le atoi: pour l'instant ne prends en charge que les ints~~
- ~~Prendre en charge 'exit ""': dans bash, 'numeric argument required'~~
- ~~Prendre en charge exit + commande~~
- ~~Permission denied~~
- ~~Nombres 0000000000001 par ex~~

[CD]
- ~~bash prend en charge `cd ~ pwd` alors que nous non~~
- ~~cd -~~

[Export]
- erreur message supprime les ' ' par ex `export '    456asd=value '`
- ~~pour l'instant pas de prise en charge pour les variables a qui on attribue une nouvelle valeur~~

[Unset]
- ~~prise en charge non valid chars~~

[Echo]
- ~~Prise en charge `echo $? hello`~~
- ~~Prise en charge `echo ~`~~
- Prise en charge `echo ~` quand $HOME est unset
- `echo ~$USER/sdfsfsfdsfs` : chez nous donne `/Users/dborione`
- --> remplacer ~/ par le path dans cat, par ex chez nous pour `cat ~/echo` l'erreur bash `cat: /Users/dborione/echo: No such file or directory$` sort `cat: ~/echo: No such file or directory$`
- `echo "'$USER'"` devrait afficher la valeur de $USER, là il affiche `'`

[Cat]
- Dans bash, `cat | cat | ls` + deux fois entree: sort et remet le prompt, nous il ne sort pas

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
- test 21: cd 'fichier sans perm' -> nous on sort l'erreur not a directory alors que bash: Permissiomn denied

[Mpanic parser]

[Mpanic pipe]
- all tests OK

[Mpanic redirection]

[Mpanic status]
- ~~test 4, 5, 7, 9: `cat < nonexist --> echo $?`: manque 'nonexist' dans le msd d'erreur~~
- ~~test 6, 8: pareil + exit est 1 alors que bash 0~~
- ~~test 12, 13: exit code est 0 au lieu de 127 --> `sleep 1 | jgfk`~~
- ~~test 20, 21, 22, 23: pareil dans no such file~~
- ~~test 24, 25: cmd not found au lieu de no such file~~

[Mpanic shlvl]

[Mpanic panicm]
- test 1: cannot access parent directories: No such file or directory
- test 3: `echo all &> testfile < non_exist_file --> rm testfile`: nous no such file, bash pas d'erreur
- test 7: `ecoh ~` pas pris en charge
- test 8: unset PWD no working
- test 10: `echo hi <> file --> ls --> rm file`
- test 11: no passed