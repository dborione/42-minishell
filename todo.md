- signaux apres cmd bloquante comme cat sans arguments print le prompt deux fois
- double heredoc (avec pipe; ex `cat <<EOF | cat<<EOF`) ne marche pas
- variables env
- checker si on a les bons exit codes ($?)

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