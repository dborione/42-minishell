[Signaux]
- ~~double prompte pour heredoc ctl-c~~
- ~~signaux apres cmd bloquante comme cat sans arguments print le prompt deux fois~~
- ~~quand on est dans un subshell les signaux sont pris en compte deux fois~~
- CTl D ne marche pas quand après avoir stoppé une boucle infinie avec Ctl C
- Ctl C ne marche pas pour stopper boucle infinie


[Heredoc]
- double heredoc (avec pipe; ex `cat <<EOF | cat<<EOF`) ne marche pas

[Gestion Commandes]
- Ne pas oublier que :
	~$ test
	test2
n'est pas une commande (sauf si on utilise "") mais 2 commandes,
il faudra le prendre en charge dans le parsing

- Prendre en charge les "|" (guillemets + pipe ensemble), exemples :
	~$ echo test "|" cat -e
	test | cat -e
et alors que :
	~$ echo test | cat -e
	test$

[Prompt]
- erreur de free

[Autres]
- variables env
- checker si on a les bons exit codes par rapport a bash ($?)
- '>>': redirections en append mode
- exit code si cat sans input + ctl C
- ~~exit avec arguments~~

[Exit]
- ~~Changer le atoi: pour l'instant ne prends en charge que les ints~~
- ~~Prendre en charge 'exit ""': dans bash, 'numeric argument required'~~
- Prendre en charge exit + commande
- ~~Permission denied~~
- ~~Nombres 0000000000001 par ex~~

[CD]
- ~~bash prend en charge `cd ~ pwd` alors que nous non~~
- ~~cd ~/~~
- ~~cd -~~

[Export]
- erreur message supprime les ' ' par ex `export '    456asd=value '`
- ~~pour l'instant pas de prise en charge pour les variables a qui on attribue une nouvelle valeur~~

[Unset]
- ~~prise en charge non valid chars~~
