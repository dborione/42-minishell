[Signaux]
* OK - double prompte pour heredoc ctl-c 
* OK - signaux apres cmd bloquante comme cat sans arguments print le prompt deux fois
* OK - quand on est dans un subshell les signaux sont pris en compte deux fois

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
- exit avec arguments

[Exit]
* OK Changer le atoi: pour l'instant ne prends en charge que les ints
* OK Prendre en charge 'exit ""': dans bash, 'numeric argument required'
- Prendre en charge exit + commande

[CD]
- bash prend en charge `cd ~ pwd` alors que nous non
- cd ~
- cd -
